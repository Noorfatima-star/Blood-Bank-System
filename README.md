# 🩸 Centralized Blood Bank & Donor Management System

**Team 12 | BSCY-2A | Semester 2 | OOP Project**

| Role | Name | Roll # | Domain |
|---|---|---|---|
| **Team Lead** | **Esha Qaisar** | **25L-2009** | Security, Auth, File I/O, Routing |
| Member 2 | Noor Fatima | 25L-2005 | Blood Requests & Compatibility |
| Member 3 | Zara Shah | 25L-2006 | Blood Inventory System |
| Member 4 | Muhammad Ali | 25L-2063 | OOP Architecture & Donor Management |

---

## 📁 Project Structure

```
BloodBankSystem/
│
├── main.cpp                   ← Esha (entry point + routing)
│
├── Models/                    ← Pure C++ OOP Classes (backend)
│   ├── Person.h / .cpp        ← Ali
│   ├── Donor.h / .cpp         ← Ali
│   ├── Patient.h / .cpp       ← Ali
│   ├── User.h / .cpp          ← Esha
│   ├── BloodBag.h / .cpp      ← Zara
│   └── BloodRequest.h / .cpp  ← Noor
│
├── UI_Forms/                  ← WinForms GUI Screens
│   ├── LandingPage.h          ← Esha
│   ├── LoginForm.h            ← Esha
│   ├── SignupForm.h           ← Esha
│   ├── AdminDashboard.h       ← Esha
│   ├── DonorDashboard.h       ← Ali
│   ├── PatientDashboard.h     ← Noor
│   ├── DonorRegistrationForm.h← Ali
│   ├── DonorListForm.h        ← Ali
│   ├── InventoryDashboard.h   ← Zara
│   ├── BloodRequestForm.h     ← Noor
│   └── RequestManagementForm.h← Noor
│
├── Utilities/                 ← Shared helpers
│   ├── FileManager.h / .cpp   ← Esha
│   ├── Compatibility.h / .cpp ← Noor
│   ├── style.h                ← Esha ⭐ READ THIS FIRST
│   └── style.cpp              ← Esha ⭐
│
└── Database/                  ← Auto-created on first run
    ├── users.txt
    ├── donors.txt
    ├── patients.txt
    ├── inventory.txt
    ├── requests.txt
    └── logs.txt
```

---

## 🎨 Using the Style System

> **Every team member must read this section before writing any UI code.**

All colours, fonts, and widget styles live in `Utilities/style.h` and `Utilities/style.cpp`.  
**Do NOT hard-code any colours or fonts in your own form files.**

### 1 — Include the style header in your form

```cpp
#include "../Utilities/style.h"
```

### 2 — Call Apply* functions in your form's constructor or Load event

```cpp
// ---- In your Form constructor ----

// Apply base form background & font
AppStyle::ApplyFormStyle(this);

// Red header banner at the top
AppStyle::ApplyPanelHeader(panelHeader);

// Primary action button (red)
AppStyle::ApplyBtnPrimary(btnSubmit);

// Cancel / back button (grey)
AppStyle::ApplyBtnSecondary(btnCancel);

// Standard text input
AppStyle::ApplyTextBox(txtName);

// Blood group dropdown
AppStyle::ApplyComboBox(cmbBloodGroup);
```

### 3 — Button reference (which button for which action)

| Function | Colour | Use for |
|---|---|---|
| `ApplyBtnPrimary` | 🔴 Red | Submit, Login, Register, Add |
| `ApplyBtnSecondary` | ⬜ Grey | Cancel, Back, Close |
| `ApplyBtnDanger` | 🟥 Dark Red | Delete, Reject |
| `ApplyBtnSuccess` | 🟢 Green | Approve, Mark Eligible |
| `ApplyBtnWarning` | 🟡 Amber | Export CSV, Low-Stock action |
| `ApplyBtnInfo` | 🔵 Blue | View Details, Search |
| `ApplyBtnNav` | 🔴 Red (sidebar) | Left sidebar navigation |
| `ApplyBtnDarkToggle` | ⬛ Dark | Dark / Light mode toggle |

### 4 — Dark Mode (Muhammad Ali)

When the dark mode toggle is clicked in your form:

```cpp
// Toggle the global state and re-apply to the whole form
AppStyle::ApplyThemeToForm(this, !AppStyle::IsDarkMode);
// Update toggle button text
AppStyle::ApplyBtnDarkToggle(btnDarkToggle);
```

### 5 — Inventory Progress Bars (Zara Shah)

```cpp
// percent = units_available as percentage of capacity
AppStyle::ApplyProgressBarStock(pbAPlus,  75);  // green  (>= 50%)
AppStyle::ApplyProgressBarStock(pbOMinus, 12);  // red    (< 20%) -- triggers alert
```

### 6 — Password Strength Bar (Esha — Login/Signup)

```cpp
// Call this inside the TextChanged event of the password TextBox
// strength: 1=Weak  2=Fair  3=Good  4=Strong
AppStyle::ApplyProgressBarPwd(pbPasswordStrength, strength);
```

### 7 — DataGridView (Muhammad Ali — Donor List)

```cpp
AppStyle::ApplyDataGridView(dgvDonorList);
```

---

## ⚠️ Git Rules (CRITICAL — read before your first push)

1. **Never push to `main` directly.** Create your own branch: `git checkout -b feature/your-name`
2. **Only edit files assigned to you** (see the table above). Editing someone else's `.h` form file corrupts the Visual Studio designer.
3. **Before pushing, always pull first:** `git pull origin main`
4. **Do not commit the `Database/` folder** — the `.gitignore` excludes the `.txt` files automatically, but the folder itself is tracked via `.gitkeep`.

---

## 🚀 Getting Started (clone & run)

```bash
git clone https://github.com/YOUR_USERNAME/BloodBankSystem.git
cd BloodBankSystem
```

Open `BloodBankSystem.sln` in **Visual Studio 2019 or 2022**, set the platform to **x86**, and press **F5**.

The `Database/` folder and all `.txt` files are created automatically on first run by `FileManager::InitialiseStorage()`.

---

## 🖥️ Screens & Ownership

| Screen | File | Owner |
|---|---|---|
| Landing Page | `LandingPage.h` | Esha |
| Login | `LoginForm.h` | Esha |
| Signup | `SignupForm.h` | Esha |
| Admin Dashboard | `AdminDashboard.h` | Esha |
| Donor Dashboard | `DonorDashboard.h` | Ali |
| Donor Registration | `DonorRegistrationForm.h` | Ali |
| Donor List / Search | `DonorListForm.h` | Ali |
| Inventory Dashboard | `InventoryDashboard.h` | Zara |
| Patient Dashboard | `PatientDashboard.h` | Noor |
| Blood Request Form | `BloodRequestForm.h` | Noor |
| Request Management | `RequestManagementForm.h` | Noor |