// ============================================================
//  style.cpp  --  Centralized Blood Bank & Donor Management System
//  Author  : Esha Qaisar (Team Lead)  |  Roll: 25L-2009
//  Team 12 | BSCY-2A | Semester 2
// ============================================================
#include <windows.h>
#include "style.h"

// ============================================================
//  IMPLEMENTATIONS
// ============================================================
namespace AppStyle
{
    // ---- Global theme state ----
    bool IsDarkMode = false;

    // ============================================================
    //  HELPER  (internal)
    // ============================================================
    static Color CurrentBg() { return IsDarkMode ? AppTheme::DarkBgCard : AppTheme::BgCard; }
    static Color CurrentText() { return IsDarkMode ? AppTheme::DarkTextPrimary : AppTheme::TextPrimary; }
    static Color CurrentPage() { return IsDarkMode ? AppTheme::DarkBgPage : AppTheme::BgPage; }
    static Color CurrentInput() { return IsDarkMode ? AppTheme::DarkBgInput : AppTheme::BgInput; }
    static Color CurrentBorder() { return IsDarkMode ? AppTheme::DarkBorder : AppTheme::BorderLight; }

    // ============================================================
    //  FORM / WINDOW
    // ============================================================

    void ApplyFormStyle(Form^ form)
    {
        form->BackColor = AppTheme::BgPage;
        form->ForeColor = AppTheme::TextPrimary;
        form->Font = AppFont::Body;
        form->FormBorderStyle = FormBorderStyle::FixedSingle;
        form->MaximizeBox = false;
        form->StartPosition = FormStartPosition::CenterScreen;
    }

    void ApplyDarkFormStyle(Form^ form)
    {
        form->BackColor = AppTheme::DarkBgPage;
        form->ForeColor = AppTheme::DarkTextPrimary;
        form->Font = AppFont::Body;
        form->FormBorderStyle = FormBorderStyle::FixedSingle;
        form->MaximizeBox = false;
        form->StartPosition = FormStartPosition::CenterScreen;
    }

    // ============================================================
    //  PANELS / CARDS
    // ============================================================

    void ApplyPanelCard(Panel^ panel)
    {
        panel->BackColor = CurrentBg();
        panel->Padding = Padding(16);
    }

    void ApplyPanelSidebar(Panel^ panel)
    {
        panel->BackColor = AppTheme::PrimaryRed;
        panel->ForeColor = AppTheme::TextOnRed;
        panel->Dock = DockStyle::Left;
    }

    void ApplyPanelHeader(Panel^ panel)
    {
        panel->BackColor = AppTheme::PrimaryRed;
        panel->ForeColor = AppTheme::TextOnRed;
        panel->Height = 70;
        panel->Dock = DockStyle::Top;
    }

    void ApplyPanelAlert(Panel^ panel)
    {
        panel->BackColor = AppTheme::EmergencyOrange;
        panel->ForeColor = Color::White;
        panel->Height = 40;
        panel->Dock = DockStyle::Top;
        panel->Visible = false;
    }

    // ============================================================
    //  BUTTONS
    // ============================================================

    static void SetBtnBase(Button^ btn)
    {
        btn->FlatStyle = FlatStyle::Flat;
        btn->Cursor = Cursors::Hand;
        btn->TextAlign = ContentAlignment::MiddleCenter;
        btn->UseVisualStyleBackColor = false;
        btn->FlatAppearance->BorderSize = 0;
        btn->Height = 38;
    }

    void ApplyBtnPrimary(Button^ btn)
    {
        SetBtnBase(btn);
        btn->BackColor = AppTheme::PrimaryRed;
        btn->ForeColor = AppTheme::TextOnRed;
        btn->Font = AppFont::BtnPrimary;
        btn->FlatAppearance->MouseOverBackColor = AppTheme::PrimaryRedHover;
        btn->FlatAppearance->MouseDownBackColor = Color::FromArgb(127, 29, 29);
    }

    void ApplyBtnSecondary(Button^ btn)
    {
        SetBtnBase(btn);
        btn->BackColor = Color::FromArgb(229, 231, 235);
        btn->ForeColor = AppTheme::TextPrimary;
        btn->Font = AppFont::BtnSecond;
        btn->FlatAppearance->MouseOverBackColor = Color::FromArgb(209, 213, 219);
        btn->FlatAppearance->MouseDownBackColor = Color::FromArgb(156, 163, 175);
    }

    void ApplyBtnDanger(Button^ btn)
    {
        SetBtnBase(btn);
        btn->BackColor = Color::FromArgb(127, 29, 29);
        btn->ForeColor = Color::White;
        btn->Font = AppFont::BtnPrimary;
        btn->FlatAppearance->MouseOverBackColor = Color::FromArgb(153, 27, 27);
        btn->FlatAppearance->MouseDownBackColor = Color::FromArgb(69, 10, 10);
    }

    void ApplyBtnSuccess(Button^ btn)
    {
        SetBtnBase(btn);
        btn->BackColor = AppTheme::AccentGreen;
        btn->ForeColor = Color::White;
        btn->Font = AppFont::BtnPrimary;
        btn->FlatAppearance->MouseOverBackColor = Color::FromArgb(21, 128, 61);
        btn->FlatAppearance->MouseDownBackColor = Color::FromArgb(20, 83, 45);
    }

    void ApplyBtnWarning(Button^ btn)
    {
        SetBtnBase(btn);
        btn->BackColor = AppTheme::AccentGold;
        btn->ForeColor = Color::White;
        btn->Font = AppFont::BtnSecond;
        btn->FlatAppearance->MouseOverBackColor = Color::FromArgb(180, 83, 9);
        btn->FlatAppearance->MouseDownBackColor = Color::FromArgb(120, 53, 15);
    }

    void ApplyBtnInfo(Button^ btn)
    {
        SetBtnBase(btn);
        btn->BackColor = AppTheme::AccentBlue;
        btn->ForeColor = Color::White;
        btn->Font = AppFont::BtnSecond;
        btn->FlatAppearance->MouseOverBackColor = Color::FromArgb(29, 78, 216);
        btn->FlatAppearance->MouseDownBackColor = Color::FromArgb(30, 58, 138);
    }

    void ApplyBtnNav(Button^ btn)
    {
        btn->FlatStyle = FlatStyle::Flat;
        btn->Cursor = Cursors::Hand;
        btn->BackColor = AppTheme::PrimaryRed;
        btn->ForeColor = AppTheme::TextOnRed;
        btn->Font = AppFont::BodyBold;
        btn->TextAlign = ContentAlignment::MiddleLeft;
        btn->Padding = Padding(12, 0, 0, 0);
        btn->Height = 48;
        btn->Dock = DockStyle::Top;
        btn->FlatAppearance->BorderSize = 0;
        btn->FlatAppearance->MouseOverBackColor = Color::FromArgb(153, 27, 27);
        btn->UseVisualStyleBackColor = false;
    }

    void ApplyBtnDarkToggle(Button^ btn)
    {
        SetBtnBase(btn);
        btn->BackColor = Color::FromArgb(55, 65, 81);
        btn->ForeColor = Color::White;
        btn->Font = AppFont::Small;
        btn->Text = IsDarkMode ? L"☀  Light Mode" : L"🌙  Dark Mode";
        btn->Width = 120;
        btn->Height = 30;
        btn->FlatAppearance->MouseOverBackColor = Color::FromArgb(75, 85, 99);
    }

    // ============================================================
    //  LABELS
    // ============================================================

    void ApplyLabelTitle(Label^ lbl)
    {
        lbl->Font = AppFont::Title;
        lbl->ForeColor = AppTheme::PrimaryRed;
        lbl->AutoSize = true;
    }

    void ApplyLabelHeading(Label^ lbl)
    {
        lbl->Font = AppFont::Heading1;
        lbl->ForeColor = CurrentText();
        lbl->AutoSize = true;
    }

    void ApplyLabelSubtitle(Label^ lbl)
    {
        lbl->Font = AppFont::Subtitle;
        lbl->ForeColor = IsDarkMode ? AppTheme::DarkTextSecondary : AppTheme::TextSecondary;
        lbl->AutoSize = true;
    }

    void ApplyLabelBody(Label^ lbl)
    {
        lbl->Font = AppFont::Body;
        lbl->ForeColor = CurrentText();
        lbl->AutoSize = true;
    }

    void ApplyLabelAlert(Label^ lbl)
    {
        lbl->Font = AppFont::Alert;
        lbl->ForeColor = Color::White;
        lbl->BackColor = AppTheme::EmergencyOrange;
        lbl->TextAlign = ContentAlignment::MiddleCenter;
        lbl->Dock = DockStyle::Fill;
        lbl->Padding = Padding(8, 4, 8, 4);
    }

    void ApplyLabelSuccess(Label^ lbl)
    {
        lbl->Font = AppFont::BodyBold;
        lbl->ForeColor = AppTheme::AccentGreen;
        lbl->AutoSize = true;
    }

    void ApplyLabelCaptcha(Label^ lbl)
    {
        lbl->Font = AppFont::Captcha;
        lbl->ForeColor = AppTheme::PrimaryRed;
        lbl->BackColor = AppTheme::PrimaryRedLight;
        lbl->TextAlign = ContentAlignment::MiddleCenter;
        lbl->BorderStyle = BorderStyle::FixedSingle;
        lbl->Width = 160;
        lbl->Height = 42;
    }

    // ============================================================
    //  TEXT INPUTS
    // ============================================================

    static void SetInputBase(Control^ ctrl)
    {
        ctrl->Font = AppFont::InputFont;
        ctrl->ForeColor = CurrentText();
        ctrl->BackColor = CurrentInput();
    }

    void ApplyTextBox(TextBox^ tb)
    {
        SetInputBase(tb);
        tb->BorderStyle = BorderStyle::FixedSingle;
        tb->Height = 34;
    }

    void ApplyPasswordBox(TextBox^ tb)
    {
        ApplyTextBox(tb);
        tb->UseSystemPasswordChar = true;
    }

    void ApplyComboBox(ComboBox^ cb)
    {
        SetInputBase(cb);
        cb->FlatStyle = FlatStyle::Flat;
        cb->DropDownStyle = ComboBoxStyle::DropDownList;
        cb->Height = 34;
    }

    void ApplyDatePicker(DateTimePicker^ dtp)
    {
        dtp->Font = AppFont::InputFont;
        dtp->CalendarForeColor = AppTheme::TextPrimary;
        dtp->CalendarMonthBackground = AppTheme::BgCard;
        dtp->CalendarTitleBackColor = AppTheme::PrimaryRed;
        dtp->CalendarTitleForeColor = Color::White;
        dtp->Height = 34;
    }

    // ============================================================
    //  PROGRESS BARS
    // ============================================================

    void ApplyProgressBarStock(ProgressBar^ pb, int percent)
    {
        pb->Minimum = 0;
        pb->Maximum = 100;
        pb->Value = Math::Min(percent, 100);
        pb->Height = 22;
        pb->Style = ProgressBarStyle::Continuous;

        int color;
        if (percent >= 50)
            color = ColorTranslator::ToWin32(AppTheme::StockHigh);
        else if (percent >= 20)
            color = ColorTranslator::ToWin32(AppTheme::StockMedium);
        else
            color = ColorTranslator::ToWin32(AppTheme::StockLow);

        SendMessage(
            static_cast<HWND>(pb->Handle.ToPointer()),
            0x0409, 0,
            static_cast<LPARAM>(color)
        );
    }

    void ApplyProgressBarPwd(ProgressBar^ pb, int strength)
    {
        pb->Minimum = 0;
        pb->Maximum = 4;
        pb->Value = Math::Min(Math::Max(strength, 0), 4);
        pb->Height = 10;
        pb->Style = ProgressBarStyle::Continuous;

        Color c;
        switch (strength)
        {
        case 1:  c = AppTheme::PwdWeak;   break;
        case 2:  c = AppTheme::PwdFair;   break;
        case 3:  c = AppTheme::PwdGood;   break;
        default: c = AppTheme::PwdStrong; break;
        }

        SendMessage(
            static_cast<HWND>(pb->Handle.ToPointer()),
            0x0409, 0,
            static_cast<LPARAM>(ColorTranslator::ToWin32(c))
        );
    }

    // ============================================================
    //  DATA GRID VIEW
    // ============================================================

    void ApplyDataGridView(DataGridView^ dgv)
    {
        dgv->Font = AppFont::GridFont;
        dgv->BackgroundColor = CurrentBg();
        dgv->BorderStyle = BorderStyle::None;
        dgv->CellBorderStyle = DataGridViewCellBorderStyle::SingleHorizontal;
        dgv->GridColor = AppTheme::BorderLight;
        dgv->RowHeadersVisible = false;
        dgv->AllowUserToAddRows = false;
        dgv->AllowUserToDeleteRows = false;
        dgv->ReadOnly = true;
        dgv->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
        dgv->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
        dgv->MultiSelect = false;

        dgv->ColumnHeadersDefaultCellStyle->BackColor = AppTheme::PrimaryRed;
        dgv->ColumnHeadersDefaultCellStyle->ForeColor = Color::White;
        dgv->ColumnHeadersDefaultCellStyle->Font = AppFont::GridHeader;
        dgv->ColumnHeadersDefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleLeft;
        dgv->ColumnHeadersBorderStyle = DataGridViewHeaderBorderStyle::None;
        dgv->ColumnHeadersHeight = 36;
        dgv->ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode::DisableResizing;

        dgv->DefaultCellStyle->BackColor = CurrentBg();
        dgv->DefaultCellStyle->ForeColor = CurrentText();
        dgv->DefaultCellStyle->Padding = Padding(4, 6, 4, 6);
        dgv->RowTemplate->Height = 34;

        dgv->AlternatingRowsDefaultCellStyle->BackColor =
            IsDarkMode ? Color::FromArgb(31, 41, 55) : Color::FromArgb(249, 250, 251);

        dgv->DefaultCellStyle->SelectionBackColor = AppTheme::PrimaryRedLight;
        dgv->DefaultCellStyle->SelectionForeColor = AppTheme::PrimaryRed;

        dgv->EnableHeadersVisualStyles = false;
    }

    // ============================================================
    //  SPECIAL WIDGETS
    // ============================================================

    void ApplyCaptchaBox(TextBox^ tb)
    {
        ApplyTextBox(tb);
        tb->Font = AppFont::BodyBold;
        tb->TextAlign = HorizontalAlignment::Center;
        tb->Width = 160;
        tb->MaxLength = 5;
        tb->CharacterCasing = CharacterCasing::Upper;
    }

    void ApplySearchBar(TextBox^ tb)
    {
        ApplyTextBox(tb);
        tb->Font = AppFont::InputFont;
        tb->BackColor = IsDarkMode ? AppTheme::DarkBgInput : Color::FromArgb(243, 244, 246);
    }

    void ApplyDivider(Label^ lbl)
    {
        lbl->AutoSize = false;
        lbl->Height = 1;
        lbl->BackColor = AppTheme::BorderLight;
        lbl->Dock = DockStyle::Top;
        lbl->Margin = Padding(0, 8, 0, 8);
    }

    // ============================================================
    //  WHOLE-FORM THEME TOGGLE
    // ============================================================

    void ApplyThemeToPanel(Panel^ panel, bool darkMode)
    {
        Color bg = darkMode ? AppTheme::DarkBgCard : AppTheme::BgCard;
        Color text = darkMode ? AppTheme::DarkTextPrimary : AppTheme::TextPrimary;

        panel->BackColor = bg;
        panel->ForeColor = text;

        for each (Control ^ ctrl in panel->Controls)
        {
            if (Label^ lbl = dynamic_cast<Label^>(ctrl))
            {
                if (lbl->BackColor != AppTheme::EmergencyOrange &&
                    lbl->BackColor != AppTheme::PrimaryRedLight)
                {
                    lbl->ForeColor = text;
                    lbl->BackColor = bg;
                }
            }
            else if (TextBox^ tb = dynamic_cast<TextBox^>(ctrl))
            {
                tb->BackColor = darkMode ? AppTheme::DarkBgInput : AppTheme::BgInput;
                tb->ForeColor = text;
            }
            else if (ComboBox^ cb = dynamic_cast<ComboBox^>(ctrl))
            {
                cb->BackColor = darkMode ? AppTheme::DarkBgInput : AppTheme::BgInput;
                cb->ForeColor = text;
            }
            else if (Panel^ inner = dynamic_cast<Panel^>(ctrl))
            {
                ApplyThemeToPanel(inner, darkMode);
            }
            else if (DataGridView^ dgv = dynamic_cast<DataGridView^>(ctrl))
            {
                AppStyle::ApplyDataGridView(dgv);
            }
        }
    }

    void ApplyThemeToForm(Form^ form, bool darkMode)
    {
        IsDarkMode = darkMode;

        form->BackColor = darkMode ? AppTheme::DarkBgPage : AppTheme::BgPage;
        form->ForeColor = darkMode ? AppTheme::DarkTextPrimary : AppTheme::TextPrimary;

        for each (Control ^ ctrl in form->Controls)
        {
            if (Panel^ panel = dynamic_cast<Panel^>(ctrl))
            {
                if (panel->BackColor == AppTheme::PrimaryRed)
                    continue;

                ApplyThemeToPanel(panel, darkMode);
            }
            else if (Button^ btn = dynamic_cast<Button^>(ctrl))
            {
                if (btn->BackColor != AppTheme::PrimaryRed &&
                    btn->BackColor != AppTheme::AccentGreen &&
                    btn->BackColor != AppTheme::AccentBlue)
                {
                    ApplyBtnSecondary(btn);
                }
            }
        }
    }

} // namespace AppStyle