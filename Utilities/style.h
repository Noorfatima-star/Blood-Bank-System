#pragma once
// ============================================================
//  style.h  --  Centralized Blood Bank & Donor Management System
//  Author  : Esha Qaisar (Team Lead)  |  Roll: 25L-2009
//  Team 12 | BSCY-2A | Semester 2
// ============================================================

#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

// ============================================================
//  MANAGED CLASSES WITH STATIC CONSTRUCTORS
// ============================================================
public ref class AppTheme
{
public:
    static Color PrimaryRed;
    static Color PrimaryRedHover;
    static Color PrimaryRedLight;
    static Color AccentGold;
    static Color AccentGreen;
    static Color AccentGreenLight;
    static Color AccentBlue;
    static Color EmergencyOrange;
    static Color BgPage;
    static Color BgCard;
    static Color BgInput;
    static Color BorderLight;
    static Color TextPrimary;
    static Color TextSecondary;
    static Color TextOnRed;
    static Color DarkBgPage;
    static Color DarkBgCard;
    static Color DarkBgInput;
    static Color DarkBorder;
    static Color DarkTextPrimary;
    static Color DarkTextSecondary;
    static Color StockHigh;
    static Color StockMedium;
    static Color StockLow;
    static Color PwdWeak;
    static Color PwdFair;
    static Color PwdGood;
    static Color PwdStrong;

    // --- STATIC CONSTRUCTOR ---
    // Automatically assigns all values safely at runtime
    static AppTheme()
    {
        PrimaryRed = Color::FromArgb(180, 28, 28);
        PrimaryRedHover = Color::FromArgb(153, 27, 27);
        PrimaryRedLight = Color::FromArgb(254, 226, 226);
        AccentGold = Color::FromArgb(217, 119, 6);
        AccentGreen = Color::FromArgb(22, 163, 74);
        AccentGreenLight = Color::FromArgb(220, 252, 231);
        AccentBlue = Color::FromArgb(37, 99, 235);
        EmergencyOrange = Color::FromArgb(234, 88, 12);
        BgPage = Color::FromArgb(249, 250, 251);
        BgCard = Color::White;
        BgInput = Color::White;
        BorderLight = Color::FromArgb(209, 213, 219);
        TextPrimary = Color::FromArgb(17, 24, 39);
        TextSecondary = Color::FromArgb(107, 114, 128);
        TextOnRed = Color::White;
        DarkBgPage = Color::FromArgb(17, 24, 39);
        DarkBgCard = Color::FromArgb(31, 41, 55);
        DarkBgInput = Color::FromArgb(55, 65, 81);
        DarkBorder = Color::FromArgb(75, 85, 99);
        DarkTextPrimary = Color::FromArgb(243, 244, 246);
        DarkTextSecondary = Color::FromArgb(156, 163, 175);
        StockHigh = Color::FromArgb(22, 163, 74);
        StockMedium = Color::FromArgb(217, 119, 6);
        StockLow = Color::FromArgb(220, 38, 38);
        PwdWeak = Color::FromArgb(220, 38, 38);
        PwdFair = Color::FromArgb(234, 179, 8);
        PwdGood = Color::FromArgb(59, 130, 246);
        PwdStrong = Color::FromArgb(22, 163, 74);
    }
};

public ref class AppFont
{
public:
    static String^ Family;
    static Font^ Title;
    static Font^ Heading1;
    static Font^ Heading2;
    static Font^ Subtitle;
    static Font^ Body;
    static Font^ BodyBold;
    static Font^ Small;
    static Font^ BtnPrimary;
    static Font^ BtnSecond;
    static Font^ InputFont;
    static Font^ GridFont;
    static Font^ GridHeader;
    static Font^ Alert;
    static Font^ Captcha;

    // --- STATIC CONSTRUCTOR ---
    static AppFont()
    {
        Family = "Segoe UI";
        Title = gcnew Font("Segoe UI", 26, FontStyle::Bold);
        Heading1 = gcnew Font("Segoe UI", 18, FontStyle::Bold);
        Heading2 = gcnew Font("Segoe UI", 14, FontStyle::Bold);
        Subtitle = gcnew Font("Segoe UI", 12, FontStyle::Regular);
        Body = gcnew Font("Segoe UI", 10, FontStyle::Regular);
        BodyBold = gcnew Font("Segoe UI", 10, FontStyle::Bold);
        Small = gcnew Font("Segoe UI", 8, FontStyle::Regular);
        BtnPrimary = gcnew Font("Segoe UI", 11, FontStyle::Bold);
        BtnSecond = gcnew Font("Segoe UI", 10, FontStyle::Regular);
        InputFont = gcnew Font("Segoe UI", 10, FontStyle::Regular);
        GridFont = gcnew Font("Segoe UI", 9, FontStyle::Regular);
        GridHeader = gcnew Font("Segoe UI", 9, FontStyle::Bold);
        Alert = gcnew Font("Segoe UI", 11, FontStyle::Bold);
        Captcha = gcnew Font("Courier New", 16, FontStyle::Bold);
    }
};

// ============================================================
//  STYLE FUNCTIONS  --  Declarations
// ============================================================
namespace AppStyle
{
    extern bool IsDarkMode;

    void ApplyFormStyle(Form^ form);
    void ApplyDarkFormStyle(Form^ form);
    void ApplyPanelCard(Panel^ panel);
    void ApplyPanelSidebar(Panel^ panel);
    void ApplyPanelHeader(Panel^ panel);
    void ApplyPanelAlert(Panel^ panel);
    void ApplyBtnPrimary(Button^ btn);
    void ApplyBtnSecondary(Button^ btn);
    void ApplyBtnDanger(Button^ btn);
    void ApplyBtnSuccess(Button^ btn);
    void ApplyBtnWarning(Button^ btn);
    void ApplyBtnInfo(Button^ btn);
    void ApplyBtnNav(Button^ btn);
    void ApplyBtnDarkToggle(Button^ btn);
    void ApplyLabelTitle(Label^ lbl);
    void ApplyLabelHeading(Label^ lbl);
    void ApplyLabelSubtitle(Label^ lbl);
    void ApplyLabelBody(Label^ lbl);
    void ApplyLabelAlert(Label^ lbl);
    void ApplyLabelSuccess(Label^ lbl);
    void ApplyLabelCaptcha(Label^ lbl);
    void ApplyTextBox(TextBox^ tb);
    void ApplyPasswordBox(TextBox^ tb);
    void ApplyComboBox(ComboBox^ cb);
    void ApplyDatePicker(DateTimePicker^ dtp);
    void ApplyProgressBarStock(ProgressBar^ pb, int percent);
    void ApplyProgressBarPwd(ProgressBar^ pb, int strength);
    void ApplyDataGridView(DataGridView^ dgv);
    void ApplyCaptchaBox(TextBox^ tb);
    void ApplySearchBar(TextBox^ tb);
    void ApplyDivider(Label^ lbl);
    void ApplyThemeToForm(Form^ form, bool darkMode);
    void ApplyThemeToPanel(Panel^ panel, bool darkMode);
}