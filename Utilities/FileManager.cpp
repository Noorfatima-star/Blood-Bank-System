// ============================================================
// FileManager.cpp  -  file I/O implementation (FINAL VERSION)
// Author : Esha Qaisar | Roll: 25L-2009
// ============================================================

#include "FileManager.h"
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <direct.h>       // for _mkdir
#include <windows.h>      // for GetModuleFileNameA
#include <string>         // for std::string

// ============================================================
// Static member definitions (non-const, will be set at runtime)
// ============================================================
const char* FileManager::USERS_FILE = nullptr;
const char* FileManager::LOGS_FILE = nullptr;
const char* FileManager::DONORS_FILE = nullptr;
const char* FileManager::INVENTORY_FILE = nullptr;
const char* FileManager::PATIENTS_FILE = nullptr;
const char* FileManager::REQUESTS_FILE = nullptr;

// ============================================================
// Helper: build absolute path inside "Database" folder
// ============================================================
static std::string GetDatabasePath(const char* relativeFileName)
{
    static char exeDir[MAX_PATH] = { 0 };
    static bool init = false;

    if (!init)
    {
        GetModuleFileNameA(NULL, exeDir, MAX_PATH);
        char* lastSlash = strrchr(exeDir, '\\');
        if (lastSlash) *lastSlash = '\0';
        init = true;
    }

    std::string fullPath = std::string(exeDir) + "\\Database\\" + relativeFileName;
    return fullPath;
}

// ============================================================
// Initialise static file paths (call once)
// ============================================================
static void InitFilePaths()
{
    static bool pathsInit = false;
    if (!pathsInit)
    {
        // Store strings in static buffers to keep them alive
        static std::string usersPath, logsPath, donorsPath, inventoryPath;
        static std::string patientsPath, requestsPath;

        usersPath = GetDatabasePath("users.txt");
        logsPath = GetDatabasePath("logs.txt");
        donorsPath = GetDatabasePath("donors.txt");
        inventoryPath = GetDatabasePath("inventory.txt");
        patientsPath = GetDatabasePath("patients.txt");
        requestsPath = GetDatabasePath("requests.txt");

        // Assign to the static pointers (non-const)
        FileManager::USERS_FILE = usersPath.c_str();
        FileManager::LOGS_FILE = logsPath.c_str();
        FileManager::DONORS_FILE = donorsPath.c_str();
        FileManager::INVENTORY_FILE = inventoryPath.c_str();
        FileManager::PATIENTS_FILE = patientsPath.c_str();
        FileManager::REQUESTS_FILE = requestsPath.c_str();

        pathsInit = true;
    }
}

// ============================================================
// countLines (private)
// ============================================================
int FileManager::countLines(const char* filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) return 0;

    int count = 0;
    char line[512];
    while (file.getline(line, 512))
    {
        if (strlen(line) > 0)
            count++;
    }
    return count;
}

// ============================================================
// parseLine (private) – expects 8 fields separated by '|'
// ============================================================
User FileManager::parseLine(const char* line)
{
    int len = static_cast<int>(strlen(line));
    char* copy = new char[len + 1];
    strcpy(copy, line);

    const char* fields[8] = { "", "", "", "", "0", "", "", "" };
    char* token = strtok(copy, "|");
    int i = 0;
    while (token != nullptr && i < 8)
    {
        fields[i++] = token;
        token = strtok(nullptr, "|");
    }

    int age = atoi(fields[4]);
    User u(fields[0], fields[1], fields[2], fields[3],
        age, fields[5], fields[6], fields[7]);

    delete[] copy;
    return u;
}

// ============================================================
// InitialiseStorage – creates Database folder and all needed files
// ============================================================
void FileManager::InitialiseStorage()
{
    InitFilePaths();

    // Create the Database folder (if not exists)
    char dbFolder[MAX_PATH];
    strcpy(dbFolder, GetDatabasePath("").c_str());
    char* lastSlash = strrchr(dbFolder, '\\');
    if (lastSlash) *lastSlash = '\0';
    _mkdir(dbFolder);

    // Array of all required files
    const char* files[] = {
        USERS_FILE, LOGS_FILE, DONORS_FILE, INVENTORY_FILE,
        PATIENTS_FILE, REQUESTS_FILE
    };

    for (int i = 0; i < 6; i++)
    {
        std::ifstream check(files[i]);
        if (!check.is_open())
        {
            std::ofstream create(files[i]);
            if (!create)
            {
                OutputDebugStringA("Failed to create file: ");
                OutputDebugStringA(files[i]);
                OutputDebugStringA("\n");
            }
            create.close();
        }
    }

    LogTransaction("SYSTEM", "Application started - storage ready.");
}

// ============================================================
// SaveUser
// ============================================================
bool FileManager::SaveUser(const User& u)
{
    std::ofstream file(USERS_FILE, std::ios::app);
    if (!file.is_open())
    {
        LogTransaction("SYSTEM", "ERROR: Cannot open users file for writing.");
        return false;
    }

    char line[512];
    u.serialize(line, 512);
    file << line << "\n";
    file.close();

    LogTransaction(u.getUsername(), "Registered new account.");
    return true;
}

// ============================================================
// UsernameExists
// ============================================================
bool FileManager::UsernameExists(const char* username)
{
    int count = 0;
    User* arr = LoadAllUsers(count);

    bool found = false;
    for (int i = 0; i < count; i++)
    {
        if (strcmp((arr + i)->getUsername(), username) == 0)
        {
            found = true;
            break;
        }
    }

    FreeUsers(arr);
    return found;
}

// ============================================================
// LoadAllUsers
// ============================================================
User* FileManager::LoadAllUsers(int& count)
{
    count = countLines(USERS_FILE);
    if (count == 0) return nullptr;

    User* arr = new User[count];
    std::ifstream file(USERS_FILE);
    if (!file.is_open())
    {
        count = 0;
        return arr;
    }

    char line[512];
    int index = 0;
    while (file.getline(line, 512) && index < count)
    {
        if (strlen(line) == 0) continue;
        arr[index] = parseLine(line);
        index++;
    }

    file.close();
    count = index;
    return arr;
}

// ============================================================
// FindUser
// ============================================================
const User* FileManager::FindUser(const char* username,
    const char* password,
    const User* arr,
    int count)
{
    if (arr == nullptr || count <= 0) return nullptr;

    for (int i = 0; i < count; i++)
    {
        const User* current = arr + i;
        if (strcmp(current->getUsername(), username) == 0 &&
            strcmp(current->getPassword(), password) == 0)
        {
            return current;
        }
    }
    return nullptr;
}

// ============================================================
// LogTransaction
// ============================================================
bool FileManager::LogTransaction(const char* actor, const char* action)
{
    std::ofstream file(LOGS_FILE, std::ios::app);
    if (!file.is_open()) return false;

    time_t now = time(nullptr);
    char* timeStr = ctime(&now);
    if (timeStr[strlen(timeStr) - 1] == '\n')
        timeStr[strlen(timeStr) - 1] = '\0';

    file << "[" << timeStr << "]  " << actor << " >> " << action << "\n";
    file.close();
    return true;
}

// ============================================================
// ExportToCSV – exports users (all roles)
// ============================================================
bool FileManager::ExportToCSV(const char* filename)
{
    std::ofstream out(filename);
    if (!out.is_open())
    {
        LogTransaction("Admin", "CSV export failed: cannot open " + std::string(filename));
        return false;
    }

    out << "Name,Username,Role,Age,Blood Group,City,Contact\n";

    int count = 0;
    User* arr = LoadAllUsers(count);
    if (arr == nullptr)
    {
        out.close();
        LogTransaction("Admin", "CSV export: no users found.");
        return false;
    }

    for (int i = 0; i < count; i++)
    {
        const User* u = arr + i;
        out << (u->getName() ? u->getName() : "") << ","
            << (u->getUsername() ? u->getUsername() : "") << ","
            << (u->getRole() ? u->getRole() : "") << ","
            << u->getAge() << ","
            << (u->getBloodGroup() ? u->getBloodGroup() : "") << ","
            << (u->getCity() ? u->getCity() : "") << ","
            << (u->getContact() ? u->getContact() : "") << "\n";
    }

    FreeUsers(arr);
    out.close();

    LogTransaction("Admin", "Exported user data to CSV: " + std::string(filename));
    return true;
}

// ============================================================
// ExportDonorsToCSV – exports donors from donors.txt
// ============================================================
bool FileManager::ExportDonorsToCSV(const char* filename)
{
    std::ofstream out(filename);
    if (!out.is_open())
    {
        LogTransaction("Admin", "Donor CSV export failed: cannot open " + std::string(filename));
        return false;
    }

    // Format: Name,Blood Group,Age,City,Contact,Last Donation Date,Total Donations
    out << "Name,Blood Group,Age,City,Contact,Last Donation Date,Total Donations\n";

    // TODO: Read from DONORS_FILE (format defined by Muhammad Ali)
    // For now, create a stub that writes a header only.
    // Actual implementation will be completed when donor file format is finalised.

    out.close();
    LogTransaction("Admin", "Exported donor data to CSV: " + std::string(filename));
    return true;
}

// ============================================================
// ExportInventoryToCSV – exports blood inventory from inventory.txt
// ============================================================
bool FileManager::ExportInventoryToCSV(const char* filename)
{
    std::ofstream out(filename);
    if (!out.is_open())
    {
        LogTransaction("Admin", "Inventory CSV export failed: cannot open " + std::string(filename));
        return false;
    }

    // Format: Blood Group,Units Available,Expiry Date (oldest),Status
    out << "Blood Group,Units Available,Expiry Date (oldest),Status\n";

    // TODO: Read from INVENTORY_FILE (format defined by Zara Shah)
    // Stub implementation for now.

    out.close();
    LogTransaction("Admin", "Exported inventory data to CSV: " + std::string(filename));
    return true;
}

// ============================================================
// FreeUsers
// ============================================================
void FileManager::FreeUsers(User* arr)
{
    delete[] arr;
}