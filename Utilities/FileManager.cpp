// ============================================================
// FileManager.cpp  -  FINAL CLEAN VERSION
// ============================================================

#define _CRT_SECURE_NO_WARNINGS

#include "FileManager.h"
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <direct.h>
#include <windows.h>
#include <string>

// ============================================================
// Static member definitions
// ============================================================
const char* FileManager::USERS_FILE = nullptr;
const char* FileManager::LOGS_FILE = nullptr;
const char* FileManager::DONORS_FILE = nullptr;
const char* FileManager::INVENTORY_FILE = nullptr;
const char* FileManager::PATIENTS_FILE = nullptr;
const char* FileManager::REQUESTS_FILE = nullptr;

// ============================================================
// Helper: Get EXE directory + Database path
// ============================================================
static std::string GetDatabasePath(const char* fileName)
{
    static char exeDir[MAX_PATH] = { 0 };
    static bool initialized = false;

    if (!initialized)
    {
        GetModuleFileNameA(NULL, exeDir, MAX_PATH);
        char* lastSlash = strrchr(exeDir, '\\');
        if (lastSlash) *lastSlash = '\0';
        initialized = true;
    }

    return std::string(exeDir) + "\\Database\\" + fileName;
}

// ============================================================
// FIXED: Now inside class scope (important)
// ============================================================
void FileManager::InitialiseStorage()
{
    static bool pathsInit = false;

    if (!pathsInit)
    {
        static std::string usersPath, logsPath, donorsPath, inventoryPath;
        static std::string patientsPath, requestsPath;

        usersPath = GetDatabasePath("users.txt");
        logsPath = GetDatabasePath("logs.txt");
        donorsPath = GetDatabasePath("donors.txt");
        inventoryPath = GetDatabasePath("inventory.txt");
        patientsPath = GetDatabasePath("patients.txt");
        requestsPath = GetDatabasePath("requests.txt");

        USERS_FILE = usersPath.c_str();
        LOGS_FILE = logsPath.c_str();
        DONORS_FILE = donorsPath.c_str();
        INVENTORY_FILE = inventoryPath.c_str();
        PATIENTS_FILE = patientsPath.c_str();
        REQUESTS_FILE = requestsPath.c_str();

        pathsInit = true;
    }

    // Create Database folder
    char dbFolder[MAX_PATH];
    strcpy(dbFolder, GetDatabasePath("").c_str());

    char* lastSlash = strrchr(dbFolder, '\\');
    if (lastSlash) *lastSlash = '\0';

    if (_mkdir(dbFolder) != 0)
    {
        // optional: check if already exists
        // ignore error safely
    }

    const char* files[] = {
        USERS_FILE, LOGS_FILE, DONORS_FILE,
        INVENTORY_FILE, PATIENTS_FILE, REQUESTS_FILE
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

    LogTransaction("SYSTEM", "Storage initialized successfully.");
}

// ============================================================
// countLines
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
// parseLine
// ============================================================
User FileManager::parseLine(const char* line)
{
    char* copy = _strdup(line);

    const char* fields[8] = { "", "", "", "", "0", "", "", "" };

    char* context = nullptr;
    char* token = strtok_s(copy, "|", &context);

    int i = 0;
    while (token && i < 8)
    {
        fields[i++] = token;
        token = strtok_s(nullptr, "|", &context);
    }

    int age = atoi(fields[4]);

    User u(fields[0], fields[1], fields[2], fields[3],
        age, fields[5], fields[6], fields[7]);

    free(copy);
    return u;
}

// ============================================================
// SaveUser
// ============================================================
bool FileManager::SaveUser(const User& u)
{
    std::ofstream file(USERS_FILE, std::ios::app);

    if (!file.is_open())
    {
        LogTransaction("SYSTEM", "ERROR: Cannot open users file.");
        return false;
    }

    char line[512];
    u.serialize(line, 512);

    file << line << "\n";
    file.close();

    LogTransaction(u.getUsername(), "New user registered.");
    return true;
}

// ============================================================
// UsernameExists
// ============================================================
bool FileManager::UsernameExists(const char* username)
{
    int count = 0;
    User* arr = LoadAllUsers(count);

    if (!arr) return false;

    for (int i = 0; i < count; i++)
    {
        if (strcmp(arr[i].getUsername(), username) == 0)
        {
            FreeUsers(arr);
            return true;
        }
    }

    FreeUsers(arr);
    return false;
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
        arr[index++] = parseLine(line);
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
    if (!arr || count <= 0) return nullptr;

    for (int i = 0; i < count; i++)
    {
        if (strcmp(arr[i].getUsername(), username) == 0 &&
            strcmp(arr[i].getPassword(), password) == 0)
        {
            return &arr[i];
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
    char timeStr[100];
    ctime_s(timeStr, sizeof(timeStr), &now);

    timeStr[strlen(timeStr) - 1] = '\0';

    file << "[" << timeStr << "]  "
        << actor << " >> "
        << action << "\n";

    file.close();
    return true;
}

// ============================================================
// ExportToCSV (FIXED .c_str())
// ============================================================
bool FileManager::ExportToCSV(const char* filename)
{
    std::ofstream out(filename);
    if (!out.is_open())
    {
        std::string msg = "CSV export failed: cannot open " + std::string(filename);
        LogTransaction("Admin", msg.c_str());
        return false;
    }

    out << "Name,Username,Role,Age,Blood Group,City,Contact\n";

    int count = 0;
    User* arr = LoadAllUsers(count);

    if (!arr)
    {
        out.close();
        LogTransaction("Admin", "No users found.");
        return false;
    }

    for (int i = 0; i < count; i++)
    {
        const User& u = arr[i];

        out << (u.getName() ? u.getName() : "") << ","
            << (u.getUsername() ? u.getUsername() : "") << ","
            << (u.getRole() ? u.getRole() : "") << ","
            << u.getAge() << ","
            << (u.getBloodGroup() ? u.getBloodGroup() : "") << ","
            << (u.getCity() ? u.getCity() : "") << ","
            << (u.getContact() ? u.getContact() : "") << "\n";
    }

    FreeUsers(arr);
    out.close();

    std::string msg = "Exported users to CSV: " + std::string(filename);
    LogTransaction("Admin", msg.c_str());

    return true;
}

// ============================================================
// FreeUsers
// ============================================================
void FileManager::FreeUsers(User* arr)
{
    delete[] arr;
}