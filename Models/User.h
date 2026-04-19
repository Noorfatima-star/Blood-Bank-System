#pragma once
#include <cstring>
#include <cstdlib>

// ============================================================
// User.h  -  User account data model (FIXED)
// Author : Esha Qaisar | Roll: 25L-2009
// ============================================================

class User
{
private:
    char* m_name;
    char* m_username;
    char* m_password;
    char* m_role;
    char* m_bloodGroup;
    char* m_city;
    char* m_contact;
    int   m_age;

    // Helper: safe string duplication (handles nullptr)
    char* cloneStr(const char* src) const;

public:
    // Default constructor (all pointers nullptr, age 0)
    User();

    // Parameterised constructor
    User(const char* name, const char* username, const char* password,
        const char* role, int age,
        const char* bloodGroup, const char* city, const char* contact);

    // Copy constructor (deep copy)
    User(const User& other);

    // Copy assignment operator (deep copy) – REQUIRED
    User& operator=(const User& other);

    // Destructor
    ~User();

    // Accessors
    const char* getName()       const;
    const char* getUsername()   const;
    const char* getPassword()   const;
    const char* getRole()       const;
    const char* getBloodGroup() const;
    const char* getCity()       const;
    const char* getContact()    const;
    int         getAge()        const;

    // Mutator
    void setPassword(const char* newPass);

    // Serialize to pipe-delimited string (fits in bufSize)
    void serialize(char* outBuffer, int bufSize) const;
};