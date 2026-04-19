// ============================================================
//  main.cpp  --  Centralized Blood Bank & Donor Management System
// ============================================================

#pragma comment(lib, "user32.lib")

#include <windows.h>
#include <msclr/marshal.h>

#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

#include "Utilities/style.h"
#include "Utilities/FileManager.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace msclr::interop;

// ============================================================
// SAFE String^ → const char* conversion
// ============================================================
const char* ToConstChar(String^ str)
{
    marshal_context ctx;
    return ctx.marshal_as<const char*>(str);
}

// ============================================================
// FIXED: Event Handler (NO lambda now)
// ============================================================
void ToggleTheme(Object^ sender, EventArgs^ e)
{
    Button^ btn = safe_cast<Button^>(sender);
    Form^ parent = safe_cast<Form^>(btn->FindForm());

    bool newMode = !AppStyle::IsDarkMode;
    AppStyle::ApplyThemeToForm(parent, newMode);

    btn->Text = newMode ? L"☀ Light Mode" : L"🌙 Dark Mode";
}

// ============================================================
// ENTRY POINT
// ============================================================
[STAThread]
int main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // --- Initialize storage ---
    FileManager::InitialiseStorage();
    FileManager::LogTransaction("SYSTEM", "Application started.");

    try
    {
        // ====================================================
        // TEMP TEST FORM
        // ====================================================
        Form^ testForm = gcnew Form();
        testForm->Text = L"Blood Bank System - Master Build Test";
        testForm->Size = Drawing::Size(600, 400);
        testForm->StartPosition = FormStartPosition::CenterScreen;

        Label^ infoLabel = gcnew Label();
        infoLabel->Text =
            L"✅ FileManager initialised successfully\n"
            L"✅ Database folder and text files created\n"
            L"✅ Style system loaded\n"
            L"✅ Dark/Light mode toggle ready\n\n"
            L"👉 Replace this test form with LandingPage when ready.";

        infoLabel->AutoSize = true;
        infoLabel->Location = Drawing::Point(50, 50);

        testForm->Controls->Add(infoLabel);

        // Apply styles
        AppStyle::ApplyFormStyle(testForm);
        AppStyle::ApplyLabelHeading(infoLabel);

        // ====================================================
        // DARK MODE BUTTON (FIXED)
        // ====================================================
        Button^ toggleBtn = gcnew Button();
        toggleBtn->Text = L"🌙 Dark Mode";
        toggleBtn->Size = Drawing::Size(120, 35);
        toggleBtn->Location = Drawing::Point(50, 200);

        // FIXED EVENT HANDLER
        toggleBtn->Click += gcnew EventHandler(&ToggleTheme);

        testForm->Controls->Add(toggleBtn);
        AppStyle::ApplyBtnInfo(toggleBtn);

        // ====================================================
        // RUN APPLICATION
        // ====================================================
        Application::Run(testForm);

        FileManager::LogTransaction("SYSTEM", "Application exited normally.");
    }
    catch (Exception^ ex)
    {
        // Convert error message safely
        const char* errorMsg = ToConstChar(ex->Message);

        FileManager::LogTransaction("FATAL_ERROR", errorMsg);

        MessageBox::Show(
            L"A critical error occurred.\n\nError: " + ex->Message,
            L"System Error",
            MessageBoxButtons::OK,
            MessageBoxIcon::Error
        );

        return 1;
    }

    return 0;
}