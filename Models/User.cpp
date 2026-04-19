// ============================================================
// User.cpp  -  User class implementation (FULLY CORRECTED)
// Author : Esha Qaisar | Roll: 25L-2009
// ============================================================

#include "User.h"
#include <cstring>
#include <cstdio>    // snprintf

// ============================================================
// cloneStr (private helper)
// Allocates a fresh char[] on the heap and copies src into it.
// Returns a pointer to the new memory. Caller must delete[].
// ============================================================
char* User::cloneStr(const char* src) const
{
    if (src == nullptr) return nullptr;

    int len = static_cast<int>(strlen(src));
    char* dest = new char[len + 1];
    for (int i = 0; i <= len; i++)
        dest[i] = src[i];
    return dest;
}

// ============================================================
// Default constructor
// ============================================================
User::User()
    : m_name(nullptr), m_username(nullptr), m_password(nullptr),
    m_role(nullptr), m_bloodGroup(nullptr),
    m_city(nullptr), m_contact(nullptr), m_age(0)
{
}

// ============================================================
// Parameterised constructor
// ============================================================
User::User(const char* name, const char* username, const char* password,
    const char* role, int age,
    const char* bloodGroup, const char* city, const char* contact)
    : m_age(age)
{
    m_name = cloneStr(name);
    m_username = cloneStr(username);
    m_password = cloneStr(password);
    m_role = cloneStr(role);
    m_bloodGroup = cloneStr(bloodGroup);
    m_city = cloneStr(city);
    m_contact = cloneStr(contact);
}

// ============================================================
// Copy constructor  -  DEEP copy
// ============================================================
User::User(const User& other)
    : m_age(other.m_age)
{
    m_name = cloneStr(other.m_name);
    m_username = cloneStr(other.m_username);
    m_password = cloneStr(other.m_password);
    m_role = cloneStr(other.m_role);
    m_bloodGroup = cloneStr(other.m_bloodGroup);
    m_city = cloneStr(other.m_city);
    m_contact = cloneStr(other.m_contact);
}

// ============================================================
// Copy assignment operator  -  DEEP copy (REQUIRED)
// Without this, FileManager::LoadAllUsers will crash.
// ============================================================
User& User::operator=(const User& other)
{
    if (this == &other) return *this;   // self-assignment guard

    // Free existing memory
    delete[] m_name;        m_name = nullptr;
    delete[] m_username;    m_username = nullptr;
    delete[] m_password;    m_password = nullptr;
    delete[] m_role;        m_role = nullptr;
    delete[] m_bloodGroup;  m_bloodGroup = nullptr;
    delete[] m_city;        m_city = nullptr;
    delete[] m_contact;     m_contact = nullptr;

    // Deep copy from other
    m_name = cloneStr(other.m_name);
    m_username = cloneStr(other.m_username);
    m_password = cloneStr(other.m_password);
    m_role = cloneStr(other.m_role);
    m_bloodGroup = cloneStr(other.m_bloodGroup);
    m_city = cloneStr(other.m_city);
    m_contact = cloneStr(other.m_contact);
    m_age = other.m_age;

    return *this;
}

// ============================================================
// Destructor
// ============================================================
User::~User()
{
    delete[] m_name;        m_name = nullptr;
    delete[] m_username;    m_username = nullptr;
    delete[] m_password;    m_password = nullptr;
    delete[] m_role;        m_role = nullptr;
    delete[] m_bloodGroup;  m_bloodGroup = nullptr;
    delete[] m_city;        m_city = nullptr;
    delete[] m_contact;     m_contact = nullptr;
}

// ============================================================
// Accessors
// ============================================================
const char* User::getName()       const { return m_name; }
const char* User::getUsername()   const { return m_username; }
const char* User::getPassword()   const { return m_password; }
const char* User::getRole()       const { return m_role; }
const char* User::getBloodGroup() const { return m_bloodGroup; }
const char* User::getCity()       const { return m_city; }
const char* User::getContact()    const { return m_contact; }
int         User::getAge()        const { return m_age; }

// ============================================================
// setPassword
// ============================================================
void User::setPassword(const char* newPass)
{
    delete[] m_password;
    m_password = cloneStr(newPass);
}

// ============================================================
// serialize
// ============================================================
void User::serialize(char* outBuffer, int bufSize) const
{
    snprintf(outBuffer, bufSize,
        "%s|%s|%s|%s|%d|%s|%s|%s",
        m_name ? m_name : "",
        m_username ? m_username : "",
        m_password ? m_password : "",
        m_role ? m_role : "",
        m_age,
        m_bloodGroup ? m_bloodGroup : "",
        m_city ? m_city : "",
        m_contact ? m_contact : "");
}