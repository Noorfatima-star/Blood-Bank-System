// ============================================================
//  main.cpp  --  Centralized Blood Bank & Donor Management System
//  Author  : Esha Qaisar (Team Lead)  |  Roll: 25L-2009
//  Team 12 | BSCY-2A | Semester 2
// ============================================================

#pragma comment(lib, "user32.lib")     // required for SendMessage in style.cpp

// --- CLR / WinForms headers ---
#include <windows.h>

#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

// --- Project headers (Esha's domain) ---
#include "Utilities/style.h" // Ensure this matches exactly where your file is located, e.g., "Utilities/style.h" if it's in a folder
// #include "UI_Forms/LandingPage.h"
// #include "Utilities/FileManager.h"

using namespace System;
using namespace System::Windows::Forms;

// ============================================================
//  APPLICATION ENTRY POINT
// ============================================================
[STAThread]
int main(array<System::String^>^ args)
{
    // --- WinForms bootstrap ---
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    try
    {
        // --- TEMPORARILY COMMENTED OUT UNTIL FILES ARE ADDED ---
        // FileManager::InitialiseStorage();
        // FileManager::LogTransaction("SYSTEM", "Application started.");
        // Application::Run(gcnew LandingPage());

        // --- TEMPORARY TEST WINDOW ---
        // This just proves your environment and style system are working!
        Form^ testForm = gcnew Form();
        testForm->Text = "Blood Bank System - Master Build Test";
        testForm->Width = 500;
        testForm->Height = 350;

        // Create a test label to prove the fonts and colours are linked
        Label^ welcomeLabel = gcnew Label();
        welcomeLabel->Text = "Welcome to Blood Bank System!\nYour style system is successfully integrated.";
        welcomeLabel->AutoSize = true;
        welcomeLabel->Location = Drawing::Point(40, 50);
        testForm->Controls->Add(welcomeLabel);

        // Apply your newly fixed centralized styles!
        AppStyle::ApplyFormStyle(testForm);
        AppStyle::ApplyLabelHeading(welcomeLabel);

        // Run the test window
        Application::Run(testForm);

        // FileManager::LogTransaction("SYSTEM", "Application exited normally.");
    }
    catch (Exception^ ex)
    {
        // FileManager::LogTransaction("FATAL_ERROR", "Application crashed: " + ex->Message);

        // Show a professional error to the user before closing
        MessageBox::Show(
            "A critical error occurred. Please check the system logs for details.\n\nError: " + ex->Message,
            "System Error",
            MessageBoxButtons::OK,
            MessageBoxIcon::Error
        );
    }

    return 0;
}