// ============================================================
//  main.cpp  --  Centralized Blood Bank & Donor Management System
//  Author  : Esha Qaisar (Team Lead)  |  Roll: 25L-2009
//  Team 12 | BSCY-2A | Semester 2
// ============================================================

#pragma comment(lib, "user32.lib")     // required for SendMessage in style.cpp

// --- Windows & C++/CLI headers ---
#include <windows.h>
#include <msclr/marshal.h>

#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

// --- Project headers ---
#include "Utilities/style.h"
#include "Utilities/FileManager.h"
// #include "UI_Forms/LandingPage.h"   // <-- Uncomment when LandingPage is ready

using namespace System;
using namespace System::Windows::Forms;
using namespace msclr::interop;

// ============================================================
//  Helper: Convert String^ to const char* (for FileManager)
//  The marshal_context must stay alive for the lifetime of the
//  returned pointer. We keep it as a static local.
// ============================================================
const char* ToConstChar(String^ str)
{
    msclr::interop::marshal_context ctx;
    return ctx.marshal_as<const char*>(str);
}
const char* ToConstChar(String^ str)
{
    if (_ctx == nullptr)
        _ctx = gcnew marshal_context();
    return _ctx->marshal_as<const char*>(str);
}

// ============================================================
//  APPLICATION ENTRY POINT
// ============================================================
[STAThread]
int main(array<String^>^ args)
{
    // --- WinForms bootstrap ---
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // --- Global initialisation ---
    FileManager::InitialiseStorage();          // creates Database/ folder and all .txt files
    FileManager::LogTransaction("SYSTEM", "Application started.");

    try
    {
        // --- Launch the main form (replace with LandingPage when ready) ---
        // Application::Run(gcnew LandingPage());

        // --- Temporary test form to verify everything works ---
        Form^ testForm = gcnew Form();
        testForm->Text = L"Blood Bank System - Master Build Test";
        testForm->Size = Drawing::Size(600, 400);
        testForm->StartPosition = FormStartPosition::CenterScreen;

        Label^ infoLabel = gcnew Label();
        infoLabel->Text = L"✅ FileManager initialised successfully\n"
            L"✅ Database folder and text files created\n"
            L"✅ Style system loaded\n"
            L"✅ Dark/Light mode toggle ready\n\n"
            L"👉 Replace this test form with LandingPage when ready.";
        infoLabel->AutoSize = true;
        infoLabel->Location = Drawing::Point(50, 50);
        testForm->Controls->Add(infoLabel);

        // Apply your style system
        AppStyle::ApplyFormStyle(testForm);
        AppStyle::ApplyLabelHeading(infoLabel);

        // Optional: Add a dark mode toggle button to test the feature
        Button^ toggleBtn = gcnew Button();
        toggleBtn->Text = L"🌙 Dark Mode";
        toggleBtn->Size = Drawing::Size(120, 35);
        toggleBtn->Location = Drawing::Point(50, 200);
        toggleBtn->Click += gcnew EventHandler([](Object^ sender, EventArgs^ e) {
            Button^ btn = safe_cast<Button^>(sender);
            Form^ parent = safe_cast<Form^>(btn->FindForm());
            bool newMode = !AppStyle::IsDarkMode;
            AppStyle::ApplyThemeToForm(parent, newMode);
            btn->Text = newMode ? L"☀ Light Mode" : L"🌙 Dark Mode";
            });
        testForm->Controls->Add(toggleBtn);
        AppStyle::ApplyBtnInfo(toggleBtn);

        Application::Run(testForm);
        FileManager::LogTransaction("SYSTEM", "Application exited normally.");
    }
    catch (Exception^ ex)
    {
        // Convert exception message for logging
        const char* errorMsg = ToConstChar(ex->Message);
        FileManager::LogTransaction("FATAL_ERROR", errorMsg);

        // Show user-friendly error
        MessageBox::Show(
            L"A critical error occurred.\n\nError: " + ex->Message,
            L"System Error",
            MessageBoxButtons::OK,
            MessageBoxIcon::Error
        );
        return 1;
    }

    // Clean up marshal context (optional, but good practice)
    delete _ctx;
    return 0;
}