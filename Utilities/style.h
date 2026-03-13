#pragma once
// ============================================================
//  style.h  --  Centralized Blood Bank & Donor Management System
//  Author  : Esha Qaisar (Team Lead)  |  Roll: 25L-2009
//  Team 12 | BSCY-2A | Semester 2
//
//  PURPOSE: This file is the SINGLE source of truth for every
//           colour, font, and widget style used across all
//           11 GUI screens.  Every team member must #include
//           this file and call its Apply* functions -- they
//           must NOT hard-code colours or fonts in their own
//           .h form files.
//
//  SCREENS COVERED:
//      Esha  : LandingPage, LoginForm, SignupForm, AdminDashboard
//      Ali   : DonorDashboard, DonorRegistrationForm, DonorListForm
//      Zara  : InventoryDashboard
//      Noor  : PatientDashboard, BloodRequestForm, RequestManagementForm
// ============================================================

#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

namespace AppTheme
{
    // --- Primary brand colours ---
    static Color PrimaryRed = Color::FromArgb(180, 28, 28);   // Deep blood-red
    static Color PrimaryRedHover = Color::FromArgb(153, 27, 27);   // Darker on hover
    static Color PrimaryRedLight = Color::FromArgb(254, 226, 226);   // Soft red tint

    // --- Accent / secondary ---
    static Color AccentGold = Color::FromArgb(217, 119, 6);   // Amber warning
    static Color AccentGreen = Color::FromArgb(22, 163, 74);   // Success / eligible
    static Color AccentGreenLight = Color::FromArgb(220, 252, 231);
    static Color AccentBlue = Color::FromArgb(37, 99, 235);    // Info / link
    static Color EmergencyOrange = Color::FromArgb(234, 88, 12);   // Low-stock alert

    // --- Neutrals (Light Mode) ---
    static Color BgPage = Color::FromArgb(249, 250, 251);   // Page background
    static Color BgCard = Color::White;                      // Card / panel bg
    static Color BgInput = Color::White;                      // TextBox bg
    static Color BorderLight = Color::FromArgb(209, 213, 219);   // Input border
    static Color TextPrimary = Color::FromArgb(17, 24, 39);   // Main body text
    static Color TextSecondary = Color::FromArgb(107, 114, 128);   // Muted text
    static Color TextOnRed = Color::White;                      // Text on red bg

    // --- Dark Mode overrides ---
    static Color DarkBgPage = Color::FromArgb(17, 24, 39);
    static Color DarkBgCard = Color::FromArgb(31, 41, 55);
    static Color DarkBgInput = Color::FromArgb(55, 65, 81);
    static Color DarkBorder = Color::FromArgb(75, 85, 99);
    static Color DarkTextPrimary = Color::FromArgb(243, 244, 246);
    static Color DarkTextSecondary = Color::FromArgb(156, 163, 175);

    // --- Progress bar colours (Inventory screen) ---
    static Color StockHigh = Color::FromArgb(22, 163, 74);   // >= 50 %
    static Color StockMedium = Color::FromArgb(217, 119, 6);   // 20-49 %
    static Color StockLow = Color::FromArgb(220, 38, 38);   // < 20 % (critical)

    // --- Password strength colours (Login / Signup screen) ---
    static Color PwdWeak = Color::FromArgb(220, 38, 38);
    static Color PwdFair = Color::FromArgb(234, 179, 8);
    static Color PwdGood = Color::FromArgb(59, 130, 246);
    static Color PwdStrong = Color::FromArgb(22, 163, 74);
}

namespace AppFont
{
    static String^ Family = "Segoe UI";

    // USING EXTERN HERE: Definitions and memory allocation moved to style.cpp
    extern Font^ Title;
    extern Font^ Heading1;
    extern Font^ Heading2;
    extern Font^ Subtitle;
    extern Font^ Body;
    extern Font^ BodyBold;
    extern Font^ Small;
    extern Font^ BtnPrimary;
    extern Font^ BtnSecond;
    extern Font^ InputFont;
    extern Font^ GridFont;
    extern Font^ GridHeader;
    extern Font^ Alert;
    extern Font^ Captcha;
}

// ============================================================
//  STYLE FUNCTIONS  --  declarations
//  Implementations are in style.cpp
// ============================================================
namespace AppStyle
{
    // ---- Theme state (toggled by Muhammad Ali's Dark Mode switch) ----
    extern bool IsDarkMode;

    // ---- FORM / WINDOW ----
    void ApplyFormStyle(Form^ form);
    void ApplyDarkFormStyle(Form^ form);

    // ---- PANELS / CARDS ----
    void ApplyPanelCard(Panel^ panel);
    void ApplyPanelSidebar(Panel^ panel);
    void ApplyPanelHeader(Panel^ panel);          // Top red banner strip
    void ApplyPanelAlert(Panel^ panel);          // Emergency orange banner

    // ---- BUTTONS ----
    void ApplyBtnPrimary(Button^ btn);           // Red  -- main actions
    void ApplyBtnSecondary(Button^ btn);           // Grey -- cancel / back
    void ApplyBtnDanger(Button^ btn);           // Dark red -- delete / reject
    void ApplyBtnSuccess(Button^ btn);           // Green  -- approve / eligible
    void ApplyBtnWarning(Button^ btn);           // Amber  -- export / alert
    void ApplyBtnInfo(Button^ btn);           // Blue   -- view / search
    void ApplyBtnNav(Button^ btn);           // Sidebar navigation button
    void ApplyBtnDarkToggle(Button^ btn);           // Dark/Light mode toggle

    // ---- LABELS ----
    void ApplyLabelTitle(Label^ lbl);             // Page title
    void ApplyLabelHeading(Label^ lbl);             // Section heading
    void ApplyLabelSubtitle(Label^ lbl);             // Muted sub-heading
    void ApplyLabelBody(Label^ lbl);             // Normal body text
    void ApplyLabelAlert(Label^ lbl);             // Emergency / error message
    void ApplyLabelSuccess(Label^ lbl);             // Eligible / OK message
    void ApplyLabelCaptcha(Label^ lbl);             // CAPTCHA display label

    // ---- TEXT INPUTS ----
    void ApplyTextBox(TextBox^ tb);
    void ApplyPasswordBox(TextBox^ tb);           // Same style + password char
    void ApplyComboBox(ComboBox^ cb);
    void ApplyDatePicker(DateTimePicker^ dtp);

    // ---- PROGRESS BARS ----
    void ApplyProgressBarStock(ProgressBar^ pb, int percent);  // Colour by fill level
    void ApplyProgressBarPwd(ProgressBar^ pb, int strength); // 1=weak 4=strong

    // ---- DATA GRID VIEW ----
    void ApplyDataGridView(DataGridView^ dgv);

    // ---- SPECIAL WIDGETS ----
    void ApplyCaptchaBox(TextBox^ tb);           // CAPTCHA entry field
    void ApplySearchBar(TextBox^ tb);           // Search / filter bar
    void ApplyDivider(Label^ lbl);             // Horizontal separator line

    // ---- WHOLE-FORM THEME TOGGLE ----
    // Pass the root form; function recursively updates all controls
    void ApplyThemeToForm(Form^ form, bool darkMode);
    void ApplyThemeToPanel(Panel^ panel, bool darkMode);  // helper
}