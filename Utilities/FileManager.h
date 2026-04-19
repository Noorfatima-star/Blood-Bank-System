#pragma once
#include "../Models/User.h"
#include <fstream>

// ============================================================
// FileManager.h  -  all fstream read/write logic for the system
// Author : Esha Qaisar | Roll: 25L-2009
//
// IMPORTANT: Every team member's file logic flows through here.
//   - Esha  : users.txt, logs.txt
//   - Ali   : donors.txt, patients.txt
//   - Zara  : inventory.txt
//   - Noor  : requests.txt
//
// OOP Concepts Demonstrated:
//   Static members    : no object needed, just call directly
//   Encapsulation     : all file paths hidden as private constants
//   Dynamic arrays    : LoadAllUsers returns User* (heap array)
//   Pointer to const  : FindUser takes const User* (read-only)
//   Pass by reference : count filled via int& in LoadAllUsers
// ============================================================

class FileManager
{
private:
    // File paths - will be initialised at runtime with absolute paths
    // NOTE: Not const because we set them in InitialiseStorage()
    static const char* USERS_FILE;
    static const char* LOGS_FILE;
    static const char* DONORS_FILE;
    static const char* INVENTORY_FILE;
    static const char* PATIENTS_FILE;   // added for completeness
    static const char* REQUESTS_FILE;   // added for completeness

    // Count non-empty lines in a file (tells us array size needed)
    static int countLines(const char* filename);

    // Parse one pipe-delimited line -> User object
    static User parseLine(const char* line);

public:
    // Create Database/ folder + all .txt files on first run
    static void InitialiseStorage();

    // Append a new user record to users.txt
    static bool SaveUser(const User& u);

    // Check if a username already exists (for signup validation)
    static bool UsernameExists(const char* username);

    // Load all users from users.txt into a dynamic heap array
    // CALLER MUST CALL FreeUsers() when done to avoid memory leak
    static User* LoadAllUsers(int& count);

    // Search a User array for matching username+password
    static const User* FindUser(const char* username,
        const char* password,
        const User* arr,
        int count);

    // Append a timestamped entry to logs.txt
    static bool LogTransaction(const char* actor, const char* action);

    // Write all users to a CSV file (Admin's one-click export)
    static bool ExportToCSV(const char* filename);

    // Free a dynamic User array created by LoadAllUsers
    static void FreeUsers(User* arr);

    // ============================================================
    // ADDITIONAL EXPORT FUNCTIONS (required by project specs)
    // ============================================================
    static bool ExportDonorsToCSV(const char* filename);
    static bool ExportInventoryToCSV(const char* filename);
};