/***************************************************************
 * Name:      FlareGDEMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Igor Paliychuk (mansonigor@gmail.com)
 * Created:   2012-10-06
 * Copyright: Igor Paliychuk ()
 * License:
 * FlareGDE is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * FlareGDE is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * FlareGDE.  If not, see http://www.gnu.org/licenses/
 **************************************************************/

#include "FlareGDEMain.h"
#include "API/ItemManager.h"
#include <wx/msgdlg.h>
#include <wx/filename.h>
#include <wx/textdlg.h>
#include <wx/textfile.h>

//(*InternalHeaders(FlareGDEFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(FlareGDEFrame)
const long FlareGDEFrame::ID_LISTBOX1 = wxNewId();
const long FlareGDEFrame::ID_STATICTEXT1 = wxNewId();
const long FlareGDEFrame::ID_STATICTEXT2 = wxNewId();
const long FlareGDEFrame::ID_STATICTEXT3 = wxNewId();
const long FlareGDEFrame::ID_STATICTEXT4 = wxNewId();
const long FlareGDEFrame::ID_STATICTEXT5 = wxNewId();
const long FlareGDEFrame::ID_STATICTEXT6 = wxNewId();
const long FlareGDEFrame::ID_STATICTEXT7 = wxNewId();
const long FlareGDEFrame::ID_TEXTCTRL1 = wxNewId();
const long FlareGDEFrame::ID_COMBOBOX1 = wxNewId();
const long FlareGDEFrame::ID_SPINCTRL1 = wxNewId();
const long FlareGDEFrame::ID_COMBOBOX3 = wxNewId();
const long FlareGDEFrame::ID_SPINCTRL10 = wxNewId();
const long FlareGDEFrame::ID_SPINCTRL9 = wxNewId();
const long FlareGDEFrame::ID_SPINCTRL11 = wxNewId();
const long FlareGDEFrame::ID_SPINCTRL12 = wxNewId();
const long FlareGDEFrame::ID_SPINCTRL13 = wxNewId();
const long FlareGDEFrame::ID_SPINCTRL14 = wxNewId();
const long FlareGDEFrame::ID_STATICTEXT8 = wxNewId();
const long FlareGDEFrame::ID_STATICBITMAP1 = wxNewId();
const long FlareGDEFrame::ID_BUTTON4 = wxNewId();
const long FlareGDEFrame::ID_STATICTEXT9 = wxNewId();
const long FlareGDEFrame::ID_STATICTEXT11 = wxNewId();
const long FlareGDEFrame::ID_STATICTEXT12 = wxNewId();
const long FlareGDEFrame::ID_STATICTEXT14 = wxNewId();
const long FlareGDEFrame::ID_STATICTEXT17 = wxNewId();
const long FlareGDEFrame::ID_STATICTEXT16 = wxNewId();
const long FlareGDEFrame::ID_SPINCTRL15 = wxNewId();
const long FlareGDEFrame::ID_SPINCTRL16 = wxNewId();
const long FlareGDEFrame::ID_COMBOBOX5 = wxNewId();
const long FlareGDEFrame::ID_BUTTON5 = wxNewId();
const long FlareGDEFrame::ID_SPINCTRL2 = wxNewId();
const long FlareGDEFrame::ID_TEXTCTRL12 = wxNewId();
const long FlareGDEFrame::ID_SPINCTRL18 = wxNewId();
const long FlareGDEFrame::ID_STATICTEXT10 = wxNewId();
const long FlareGDEFrame::ID_STATICTEXT13 = wxNewId();
const long FlareGDEFrame::ID_STATICTEXT15 = wxNewId();
const long FlareGDEFrame::ID_STATICTEXT18 = wxNewId();
const long FlareGDEFrame::ID_STATICTEXT19 = wxNewId();
const long FlareGDEFrame::ID_STATICTEXT20 = wxNewId();
const long FlareGDEFrame::ID_COMBOBOX4 = wxNewId();
const long FlareGDEFrame::ID_TEXTCTRL7 = wxNewId();
const long FlareGDEFrame::ID_SPINCTRL5 = wxNewId();
const long FlareGDEFrame::ID_SPINCTRL6 = wxNewId();
const long FlareGDEFrame::ID_SPINCTRL7 = wxNewId();
const long FlareGDEFrame::ID_TEXTCTRL14 = wxNewId();
const long FlareGDEFrame::ID_SPINCTRL8 = wxNewId();
const long FlareGDEFrame::ID_SPINCTRL17 = wxNewId();
const long FlareGDEFrame::ID_STATICTEXT21 = wxNewId();
const long FlareGDEFrame::ID_STATICTEXT22 = wxNewId();
const long FlareGDEFrame::ID_STATICTEXT23 = wxNewId();
const long FlareGDEFrame::ID_STATICTEXT24 = wxNewId();
const long FlareGDEFrame::ID_STATICTEXT25 = wxNewId();
const long FlareGDEFrame::ID_BUTTON1 = wxNewId();
const long FlareGDEFrame::ID_BUTTON7 = wxNewId();
const long FlareGDEFrame::ID_TEXTCTRL15 = wxNewId();
const long FlareGDEFrame::ID_BUTTON6 = wxNewId();
const long FlareGDEFrame::ID_SPINCTRL3 = wxNewId();
const long FlareGDEFrame::ID_SPINCTRL4 = wxNewId();
const long FlareGDEFrame::ID_BUTTON2 = wxNewId();
const long FlareGDEFrame::ID_STATICBITMAP2 = wxNewId();
const long FlareGDEFrame::ID_BUTTON8 = wxNewId();
const long FlareGDEFrame::ID_BUTTON3 = wxNewId();
const long FlareGDEFrame::ID_PANEL1 = wxNewId();
const long FlareGDEFrame::idMenuNew = wxNewId();
const long FlareGDEFrame::idMenuOpen = wxNewId();
const long FlareGDEFrame::idMenuSave = wxNewId();
const long FlareGDEFrame::idMenuClose = wxNewId();
const long FlareGDEFrame::idMenuQuit = wxNewId();
const long FlareGDEFrame::idMenuNPC = wxNewId();
const long FlareGDEFrame::idMenuEnemy = wxNewId();
const long FlareGDEFrame::idMenuInventory = wxNewId();
const long FlareGDEFrame::idMenuCharacter = wxNewId();
const long FlareGDEFrame::idMenuPowers = wxNewId();
const long FlareGDEFrame::idMenuLog = wxNewId();
const long FlareGDEFrame::idMenuXPBar = wxNewId();
const long FlareGDEFrame::idMenuManaBar = wxNewId();
const long FlareGDEFrame::idMenuHPBar = wxNewId();
const long FlareGDEFrame::idMenuEnemyBar = wxNewId();
const long FlareGDEFrame::idMenuMiniMap = wxNewId();
const long FlareGDEFrame::ID_MENUITEM1 = wxNewId();
const long FlareGDEFrame::idMenuLoadGame = wxNewId();
const long FlareGDEFrame::idMenuNewGame = wxNewId();
const long FlareGDEFrame::idMenuSettings = wxNewId();
const long FlareGDEFrame::ID_MENUITEM2 = wxNewId();
const long FlareGDEFrame::idMenuAddPower = wxNewId();
const long FlareGDEFrame::idMenuAddItem = wxNewId();
const long FlareGDEFrame::idMenuAddMap = wxNewId();
const long FlareGDEFrame::idMenuOpenMap = wxNewId();
const long FlareGDEFrame::idMenuQuest = wxNewId();
const long FlareGDEFrame::idMenuAbout = wxNewId();
const long FlareGDEFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(FlareGDEFrame,wxFrame)
    //(*EventTable(FlareGDEFrame)
    //*)
END_EVENT_TABLE()

FlareGDEFrame::FlareGDEFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(FlareGDEFrame)
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer6;
    wxGridSizer* GridSizer4;
    wxMenu* MenuHelp;
    wxBoxSizer* BoxSizer15;
    wxMenuItem* MenuItemAbout;
    wxBoxSizer* BoxSizer5;
    wxBoxSizer* BoxSizer10;
    wxBoxSizer* BoxSizer7;
    wxBoxSizer* BoxSizer8;
    wxBoxSizer* BoxSizer13;
    wxGridSizer* GridSizer10;
    wxMenuBar* MainMenuBar;
    wxGridSizer* GridSizer13;
    wxGridSizer* GridSizer11;
    wxGridSizer* GridSizer5;
    wxGridSizer* GridSizer7;
    wxGridSizer* GridSizer8;
    wxGridSizer* GridSizerGlobal;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer11;
    wxBoxSizer* BoxSizer16;
    wxBoxSizer* BoxSizer12;
    wxGridSizer* GridSizer9;
    wxBoxSizer* BoxSizer14;
    wxGridSizer* GridSizer6;
    wxMenuItem* MenuItemQuit;
    wxGridSizer* GridSizer1;
    wxMenu* MenuMaps;
    wxGridSizer* GridSizer3;
    wxMenu* MenuFile;
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer9;
    wxGridSizer* GridSizer12;
    wxMenu* MenuStory;
    wxBoxSizer* BoxSizer3;
    wxGridSizer* GridSizer2;
    wxMenu* MenuMenus;
    wxMenu* MenuStuff;
    wxMenu* MenuCreatures;
    
    Create(parent, wxID_ANY, _("FlareGDE"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    GridSizerGlobal = new wxGridSizer(0, 1, 0, 0);
    PanelItems = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    PanelItems->Disable();
    PanelItems->Hide();
    GridSizer1 = new wxGridSizer(2, 6, 0, 0);
    ListBoxItems = new wxListBox(PanelItems, ID_LISTBOX1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
    GridSizer1->Add(ListBoxItems, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer3 = new wxGridSizer(7, 1, 5, 5);
    StaticTextItemName = new wxStaticText(PanelItems, ID_STATICTEXT1, _("Item Name"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    GridSizer3->Add(StaticTextItemName, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextItemType = new wxStaticText(PanelItems, ID_STATICTEXT2, _("Item Type"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    GridSizer3->Add(StaticTextItemType, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextItemLevel = new wxStaticText(PanelItems, ID_STATICTEXT3, _("Item Level"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    GridSizer3->Add(StaticTextItemLevel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextItemQuality = new wxStaticText(PanelItems, ID_STATICTEXT4, _("Item Quality"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    GridSizer3->Add(StaticTextItemQuality, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextItemMelDmg = new wxStaticText(PanelItems, ID_STATICTEXT5, _("Melee Damage"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    GridSizer3->Add(StaticTextItemMelDmg, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextItemRanDmg = new wxStaticText(PanelItems, ID_STATICTEXT6, _("Ranged Damage"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    GridSizer3->Add(StaticTextItemRanDmg, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextItemMentDmg = new wxStaticText(PanelItems, ID_STATICTEXT7, _("Mental Damage"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    GridSizer3->Add(StaticTextItemMentDmg, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(GridSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer2 = new wxGridSizer(7, 1, 5, 5);
    TextCtrlItemName = new wxTextCtrl(PanelItems, ID_TEXTCTRL1, _("ItemName"), wxDefaultPosition, wxSize(110,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    GridSizer2->Add(TextCtrlItemName, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ComboBoxItemType = new wxComboBox(PanelItems, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxSize(110,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
    GridSizer2->Add(ComboBoxItemType, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrlItemLevel = new wxSpinCtrl(PanelItems, ID_SPINCTRL1, _T("0"), wxDefaultPosition, wxSize(110,21), 0, 0, 100, 0, _T("ID_SPINCTRL1"));
    SpinCtrlItemLevel->SetValue(_T("0"));
    GridSizer2->Add(SpinCtrlItemLevel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ComboBoxItemQuality = new wxComboBox(PanelItems, ID_COMBOBOX3, wxEmptyString, wxDefaultPosition, wxSize(110,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX3"));
    ComboBoxItemQuality->Append(_("low"));
    ComboBoxItemQuality->Append(_("high"));
    ComboBoxItemQuality->Append(_("epic"));
    GridSizer2->Add(ComboBoxItemQuality, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer12 = new wxBoxSizer(wxHORIZONTAL);
    SpinCtrlItemMelDmgMin = new wxSpinCtrl(PanelItems, ID_SPINCTRL10, _T("0"), wxDefaultPosition, wxSize(50,21), 0, 0, 500, 0, _T("ID_SPINCTRL10"));
    SpinCtrlItemMelDmgMin->SetValue(_T("0"));
    BoxSizer12->Add(SpinCtrlItemMelDmgMin, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrlItemMelDmgMax = new wxSpinCtrl(PanelItems, ID_SPINCTRL9, _T("0"), wxDefaultPosition, wxSize(50,21), 0, 0, 500, 0, _T("ID_SPINCTRL9"));
    SpinCtrlItemMelDmgMax->SetValue(_T("0"));
    BoxSizer12->Add(SpinCtrlItemMelDmgMax, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer2->Add(BoxSizer12, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer14 = new wxBoxSizer(wxHORIZONTAL);
    SpinCtrlItemRanDmgMin = new wxSpinCtrl(PanelItems, ID_SPINCTRL11, _T("0"), wxDefaultPosition, wxSize(50,21), 0, 0, 500, 0, _T("ID_SPINCTRL11"));
    SpinCtrlItemRanDmgMin->SetValue(_T("0"));
    BoxSizer14->Add(SpinCtrlItemRanDmgMin, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrlItemRanDmgMax = new wxSpinCtrl(PanelItems, ID_SPINCTRL12, _T("0"), wxDefaultPosition, wxSize(50,21), 0, 0, 500, 0, _T("ID_SPINCTRL12"));
    SpinCtrlItemRanDmgMax->SetValue(_T("0"));
    BoxSizer14->Add(SpinCtrlItemRanDmgMax, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer2->Add(BoxSizer14, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer15 = new wxBoxSizer(wxHORIZONTAL);
    SpinCtrlItemMentDmgMin = new wxSpinCtrl(PanelItems, ID_SPINCTRL13, _T("0"), wxDefaultPosition, wxSize(50,21), 0, 0, 500, 0, _T("ID_SPINCTRL13"));
    SpinCtrlItemMentDmgMin->SetValue(_T("0"));
    BoxSizer15->Add(SpinCtrlItemMentDmgMin, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrlItemMentDmgMax = new wxSpinCtrl(PanelItems, ID_SPINCTRL14, _T("0"), wxDefaultPosition, wxSize(50,21), 0, 0, 500, 0, _T("ID_SPINCTRL14"));
    SpinCtrlItemMentDmgMax->SetValue(_T("0"));
    BoxSizer15->Add(SpinCtrlItemMentDmgMax, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer2->Add(BoxSizer15, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(GridSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer4 = new wxGridSizer(7, 1, 5, 5);
    StaticTextItemIcon = new wxStaticText(PanelItems, ID_STATICTEXT8, _("Item Icon"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    GridSizer4->Add(StaticTextItemIcon, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBitmapItemIcon = new wxStaticBitmap(PanelItems, ID_STATICBITMAP1, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER, _T("ID_STATICBITMAP1"));
    GridSizer4->Add(StaticBitmapItemIcon, 1, wxALL|wxSHAPED|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonItemIcon = new wxButton(PanelItems, ID_BUTTON4, _("Assign Icon"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    GridSizer4->Add(ButtonItemIcon, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(GridSizer4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer5 = new wxGridSizer(7, 1, 5, 5);
    StaticTextItemAbs = new wxStaticText(PanelItems, ID_STATICTEXT9, _("Absorbtion"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    GridSizer5->Add(StaticTextItemAbs, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextItemSfx = new wxStaticText(PanelItems, ID_STATICTEXT11, _("ItemSFX"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    GridSizer5->Add(StaticTextItemSfx, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextItemGfx = new wxStaticText(PanelItems, ID_STATICTEXT12, _("ItemGFX"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    GridSizer5->Add(StaticTextItemGfx, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextItemPower = new wxStaticText(PanelItems, ID_STATICTEXT14, _("Attached Power"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
    GridSizer5->Add(StaticTextItemPower, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextItemPowerDesc = new wxStaticText(PanelItems, ID_STATICTEXT17, _("Power Description"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
    GridSizer5->Add(StaticTextItemPowerDesc, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextItemPowerMod = new wxStaticText(PanelItems, ID_STATICTEXT16, _("Power Modificator"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
    GridSizer5->Add(StaticTextItemPowerMod, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    GridSizer5->Add(BoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(GridSizer5, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer6 = new wxGridSizer(7, 1, 5, 5);
    BoxSizer16 = new wxBoxSizer(wxHORIZONTAL);
    SpinCtrlItemAbsMin = new wxSpinCtrl(PanelItems, ID_SPINCTRL15, _T("0"), wxDefaultPosition, wxSize(50,21), 0, 0, 500, 0, _T("ID_SPINCTRL15"));
    SpinCtrlItemAbsMin->SetValue(_T("0"));
    BoxSizer16->Add(SpinCtrlItemAbsMin, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrlItemAbsMax = new wxSpinCtrl(PanelItems, ID_SPINCTRL16, _T("0"), wxDefaultPosition, wxSize(50,21), 0, 0, 500, 0, _T("ID_SPINCTRL16"));
    SpinCtrlItemAbsMax->SetValue(_T("0"));
    BoxSizer16->Add(SpinCtrlItemAbsMax, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer6->Add(BoxSizer16, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ComboBoxItemSfx = new wxComboBox(PanelItems, ID_COMBOBOX5, wxEmptyString, wxDefaultPosition, wxSize(110,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX5"));
    ComboBoxItemSfx->Append(_("book"));
    ComboBoxItemSfx->Append(_("cloth"));
    ComboBoxItemSfx->Append(_("coins"));
    ComboBoxItemSfx->Append(_("gem"));
    ComboBoxItemSfx->Append(_("leather"));
    ComboBoxItemSfx->Append(_("metal"));
    ComboBoxItemSfx->Append(_("page"));
    ComboBoxItemSfx->Append(_("maille"));
    ComboBoxItemSfx->Append(_("object"));
    ComboBoxItemSfx->Append(_("heavy"));
    ComboBoxItemSfx->Append(_("wood"));
    ComboBoxItemSfx->Append(_("potion"));
    GridSizer6->Add(ComboBoxItemSfx, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonitemGfx = new wxButton(PanelItems, ID_BUTTON5, _("Assign GFX"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    GridSizer6->Add(ButtonitemGfx, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrlItemPower = new wxSpinCtrl(PanelItems, ID_SPINCTRL2, _T("0"), wxDefaultPosition, wxSize(110,-1), 0, 0, 500, 0, _T("ID_SPINCTRL2"));
    SpinCtrlItemPower->SetValue(_T("0"));
    GridSizer6->Add(SpinCtrlItemPower, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlItemPowerDesc = new wxTextCtrl(PanelItems, ID_TEXTCTRL12, wxEmptyString, wxDefaultPosition, wxSize(110,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL12"));
    GridSizer6->Add(TextCtrlItemPowerDesc, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrlItemPowerMod = new wxSpinCtrl(PanelItems, ID_SPINCTRL18, _T("0"), wxDefaultPosition, wxSize(110,21), 0, 0, 100, 0, _T("ID_SPINCTRL18"));
    SpinCtrlItemPowerMod->SetValue(_T("0"));
    GridSizer6->Add(SpinCtrlItemPowerMod, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    GridSizer6->Add(BoxSizer5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(GridSizer6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer9 = new wxGridSizer(7, 1, 5, 5);
    StaticTextItemRequires = new wxStaticText(PanelItems, ID_STATICTEXT10, _("Item requires"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    GridSizer9->Add(StaticTextItemRequires, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextitemBonus = new wxStaticText(PanelItems, ID_STATICTEXT13, _("Bonus"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    GridSizer9->Add(StaticTextitemBonus, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextItemPrice = new wxStaticText(PanelItems, ID_STATICTEXT15, _("Price"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    GridSizer9->Add(StaticTextItemPrice, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextItemPriceSell = new wxStaticText(PanelItems, ID_STATICTEXT18, _("Sell Price"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
    GridSizer9->Add(StaticTextItemPriceSell, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextItemQuan = new wxStaticText(PanelItems, ID_STATICTEXT19, _("Max Quantity"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
    GridSizer9->Add(StaticTextItemQuan, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextItemPickup = new wxStaticText(PanelItems, ID_STATICTEXT20, _("Pickup Status"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
    GridSizer9->Add(StaticTextItemPickup, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer13 = new wxBoxSizer(wxHORIZONTAL);
    GridSizer9->Add(BoxSizer13, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(GridSizer9, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer10 = new wxGridSizer(7, 1, 5, 5);
    ComboBoxitemRequires = new wxComboBox(PanelItems, ID_COMBOBOX4, wxEmptyString, wxDefaultPosition, wxSize(110,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX4"));
    ComboBoxitemRequires->Append(_("Physical"));
    ComboBoxitemRequires->Append(_("Mental"));
    ComboBoxitemRequires->Append(_("Offense"));
    ComboBoxitemRequires->Append(_("Defense"));
    GridSizer10->Add(ComboBoxitemRequires, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlitemBonus = new wxTextCtrl(PanelItems, ID_TEXTCTRL7, wxEmptyString, wxDefaultPosition, wxSize(110,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL7"));
    GridSizer10->Add(TextCtrlitemBonus, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrlItemPrice = new wxSpinCtrl(PanelItems, ID_SPINCTRL5, _T("0"), wxDefaultPosition, wxSize(110,21), 0, 0, 20000, 0, _T("ID_SPINCTRL5"));
    SpinCtrlItemPrice->SetValue(_T("0"));
    GridSizer10->Add(SpinCtrlItemPrice, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrlItemSell = new wxSpinCtrl(PanelItems, ID_SPINCTRL6, _T("0"), wxDefaultPosition, wxSize(110,21), 0, 0, 20000, 0, _T("ID_SPINCTRL6"));
    SpinCtrlItemSell->SetValue(_T("0"));
    GridSizer10->Add(SpinCtrlItemSell, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrlItemMaxQuan = new wxSpinCtrl(PanelItems, ID_SPINCTRL7, _T("0"), wxDefaultPosition, wxSize(110,21), 0, 0, 500, 0, _T("ID_SPINCTRL7"));
    SpinCtrlItemMaxQuan->SetValue(_T("0"));
    GridSizer10->Add(SpinCtrlItemMaxQuan, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlItemPickup = new wxTextCtrl(PanelItems, ID_TEXTCTRL14, wxEmptyString, wxDefaultPosition, wxSize(110,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL14"));
    GridSizer10->Add(TextCtrlItemPickup, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    GridSizer10->Add(BoxSizer8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(GridSizer10, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer7 = new wxGridSizer(7, 1, 0, 0);
    SpinCtrlItemRequires = new wxSpinCtrl(PanelItems, ID_SPINCTRL8, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 100, 0, _T("ID_SPINCTRL8"));
    SpinCtrlItemRequires->SetValue(_T("0"));
    GridSizer7->Add(SpinCtrlItemRequires, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrlItemBonus = new wxSpinCtrl(PanelItems, ID_SPINCTRL17, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 100, 0, _T("ID_SPINCTRL17"));
    SpinCtrlItemBonus->SetValue(_T("0"));
    GridSizer7->Add(SpinCtrlItemBonus, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    GridSizer7->Add(BoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    GridSizer7->Add(BoxSizer6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    GridSizer7->Add(BoxSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    GridSizer7->Add(BoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    GridSizer7->Add(BoxSizer7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(GridSizer7, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer8 = new wxGridSizer(7, 1, 5, 5);
    StaticTextLootAnim = new wxStaticText(PanelItems, ID_STATICTEXT21, _("Loot Animation"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT21"));
    GridSizer8->Add(StaticTextLootAnim, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextItemClass = new wxStaticText(PanelItems, ID_STATICTEXT22, _("Class"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT22"));
    GridSizer8->Add(StaticTextItemClass, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextItemStep = new wxStaticText(PanelItems, ID_STATICTEXT23, _("StepFX"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT23"));
    GridSizer8->Add(StaticTextItemStep, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextItemRan_loot = new wxStaticText(PanelItems, ID_STATICTEXT24, _("Max Amount in Loot Stack"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT24"));
    GridSizer8->Add(StaticTextItemRan_loot, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextItemRan_ven = new wxStaticText(PanelItems, ID_STATICTEXT25, _("Max Amount in Vendor Stack"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT25"));
    GridSizer8->Add(StaticTextItemRan_ven, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
    GridSizer8->Add(BoxSizer9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonItemPush = new wxButton(PanelItems, ID_BUTTON1, _("Push"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    GridSizer8->Add(ButtonItemPush, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(GridSizer8, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer11 = new wxGridSizer(7, 1, 5, 5);
    ButtonItemLootAnim = new wxButton(PanelItems, ID_BUTTON7, _("Assign Animation"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
    GridSizer11->Add(ButtonItemLootAnim, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlItemClass = new wxTextCtrl(PanelItems, ID_TEXTCTRL15, wxEmptyString, wxDefaultPosition, wxSize(110,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL15"));
    GridSizer11->Add(TextCtrlItemClass, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonItemStepFX = new wxButton(PanelItems, ID_BUTTON6, _("Assign StepFX"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    GridSizer11->Add(ButtonItemStepFX, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrlItemRan_loot = new wxSpinCtrl(PanelItems, ID_SPINCTRL3, _T("0"), wxDefaultPosition, wxSize(110,21), 0, 0, 100, 0, _T("ID_SPINCTRL3"));
    SpinCtrlItemRan_loot->SetValue(_T("0"));
    GridSizer11->Add(SpinCtrlItemRan_loot, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrlItemRan_ven = new wxSpinCtrl(PanelItems, ID_SPINCTRL4, _T("0"), wxDefaultPosition, wxSize(110,21), 0, 0, 100, 0, _T("ID_SPINCTRL4"));
    SpinCtrlItemRan_ven->SetValue(_T("0"));
    GridSizer11->Add(SpinCtrlItemRan_ven, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer11 = new wxBoxSizer(wxHORIZONTAL);
    GridSizer11->Add(BoxSizer11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonItemClear = new wxButton(PanelItems, ID_BUTTON2, _("Clear"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    GridSizer11->Add(ButtonItemClear, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(GridSizer11, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer12 = new wxGridSizer(7, 1, 5, 5);
    StaticBitmap1 = new wxStaticBitmap(PanelItems, ID_STATICBITMAP2, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER, _T("ID_STATICBITMAP2"));
    GridSizer12->Add(StaticBitmap1, 1, wxALL|wxSHAPED|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer13 = new wxGridSizer(3, 1, 5, 5);
    BoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
    GridSizer13->Add(BoxSizer10, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonItemAdd = new wxButton(PanelItems, ID_BUTTON8, _("Add empty item"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON8"));
    GridSizer13->Add(ButtonItemAdd, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonItemCLose = new wxButton(PanelItems, ID_BUTTON3, _("Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    GridSizer13->Add(ButtonItemCLose, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer12->Add(GridSizer13, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(GridSizer12, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    PanelItems->SetSizer(GridSizer1);
    GridSizer1->Fit(PanelItems);
    GridSizer1->SetSizeHints(PanelItems);
    GridSizerGlobal->Add(PanelItems, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
    SetSizer(GridSizerGlobal);
    MainMenuBar = new wxMenuBar();
    MenuFile = new wxMenu();
    MenuItemCreate = new wxMenuItem(MenuFile, idMenuNew, _("New Mod\tAlt-N"), _("Create new mod"), wxITEM_NORMAL);
    MenuFile->Append(MenuItemCreate);
    MenuItemOpen = new wxMenuItem(MenuFile, idMenuOpen, _("Open Mod\tAlt-O"), _("Open existing mod"), wxITEM_NORMAL);
    MenuFile->Append(MenuItemOpen);
    MenuItemSaveMod = new wxMenuItem(MenuFile, idMenuSave, _("Save Mod\tF2"), _("Save opened mod"), wxITEM_NORMAL);
    MenuFile->Append(MenuItemSaveMod);
    MenuItemCloseMod = new wxMenuItem(MenuFile, idMenuClose, _("Close Mod\tAlt-X"), _("Close opened Mod"), wxITEM_NORMAL);
    MenuFile->Append(MenuItemCloseMod);
    MenuItemQuit = new wxMenuItem(MenuFile, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    MenuFile->Append(MenuItemQuit);
    MainMenuBar->Append(MenuFile, _("&File"));
    MenuCreatures = new wxMenu();
    MenuItemNPC = new wxMenuItem(MenuCreatures, idMenuNPC, _("Add NPC"), _("Add new NPC"), wxITEM_NORMAL);
    MenuCreatures->Append(MenuItemNPC);
    MenuItemNPC->Enable(false);
    MenuItemEnemy = new wxMenuItem(MenuCreatures, idMenuEnemy, _("Add Enemy"), _("Add new Enemy"), wxITEM_NORMAL);
    MenuCreatures->Append(MenuItemEnemy);
    MenuItemEnemy->Enable(false);
    MainMenuBar->Append(MenuCreatures, _("&Creatures"));
    MenuMenus = new wxMenu();
    MenuItemInGame = new wxMenu();
    MenuItemInventory = new wxMenuItem(MenuItemInGame, idMenuInventory, _("Inventory"), _("Edit Inventory Menu Layout"), wxITEM_NORMAL);
    MenuItemInGame->Append(MenuItemInventory);
    MenuItemInventory->Enable(false);
    MenuItemCharacter = new wxMenuItem(MenuItemInGame, idMenuCharacter, _("Character"), _("Edit Character Menu Layout"), wxITEM_NORMAL);
    MenuItemInGame->Append(MenuItemCharacter);
    MenuItemCharacter->Enable(false);
    MenuItemPowersMenu = new wxMenuItem(MenuItemInGame, idMenuPowers, _("Powers"), _("Edit Powers Menu Layout"), wxITEM_NORMAL);
    MenuItemInGame->Append(MenuItemPowersMenu);
    MenuItemPowersMenu->Enable(false);
    MenuItemLog = new wxMenuItem(MenuItemInGame, idMenuLog, _("Log"), _("Edit Log Menu Layout"), wxITEM_NORMAL);
    MenuItemInGame->Append(MenuItemLog);
    MenuItemLog->Enable(false);
    MenuItemXPBar = new wxMenuItem(MenuItemInGame, idMenuXPBar, _("XP Bar"), _("Edit XP Bar Layout"), wxITEM_NORMAL);
    MenuItemInGame->Append(MenuItemXPBar);
    MenuItemXPBar->Enable(false);
    MenuItemManaBar = new wxMenuItem(MenuItemInGame, idMenuManaBar, _("Mana Bar"), _("Edit Mana Bar Layout"), wxITEM_NORMAL);
    MenuItemInGame->Append(MenuItemManaBar);
    MenuItemManaBar->Enable(false);
    MenuItemHPBar = new wxMenuItem(MenuItemInGame, idMenuHPBar, _("HP Bar"), _("Edit HP Bar Layout"), wxITEM_NORMAL);
    MenuItemInGame->Append(MenuItemHPBar);
    MenuItemHPBar->Enable(false);
    MenuItemEnemyBar = new wxMenuItem(MenuItemInGame, idMenuEnemyBar, _("Enemy Bar"), _("Edit Enemy Bar Layout"), wxITEM_NORMAL);
    MenuItemInGame->Append(MenuItemEnemyBar);
    MenuItemEnemyBar->Enable(false);
    MenuItemMiniMap = new wxMenuItem(MenuItemInGame, idMenuMiniMap, _("MiniMap"), _("Edit MiniMap Layout"), wxITEM_NORMAL);
    MenuItemInGame->Append(MenuItemMiniMap);
    MenuItemMiniMap->Enable(false);
    MenuMenus->Append(ID_MENUITEM1, _("&InGame"), MenuItemInGame, wxEmptyString);
    MenuItemInterface = new wxMenu();
    MenuItemLoadGame = new wxMenuItem(MenuItemInterface, idMenuLoadGame, _("Load Game"), _("Edit Load Game Menu Layout"), wxITEM_NORMAL);
    MenuItemInterface->Append(MenuItemLoadGame);
    MenuItemLoadGame->Enable(false);
    MenuItemNewGame = new wxMenuItem(MenuItemInterface, idMenuNewGame, _("New Game"), _("Edit New Game Menu Layout"), wxITEM_NORMAL);
    MenuItemInterface->Append(MenuItemNewGame);
    MenuItemNewGame->Enable(false);
    MenuItemSettings = new wxMenuItem(MenuItemInterface, idMenuSettings, _("Settings Menu"), _("Edit Settings Menu Layout"), wxITEM_NORMAL);
    MenuItemInterface->Append(MenuItemSettings);
    MenuItemSettings->Enable(false);
    MenuMenus->Append(ID_MENUITEM2, _("&Interface Menus"), MenuItemInterface, wxEmptyString);
    MainMenuBar->Append(MenuMenus, _("&Menus"));
    MenuStuff = new wxMenu();
    MenuItemPower = new wxMenuItem(MenuStuff, idMenuAddPower, _("Add Power"), _("Add new Power"), wxITEM_NORMAL);
    MenuStuff->Append(MenuItemPower);
    MenuItemPower->Enable(false);
    MenuItemItem = new wxMenuItem(MenuStuff, idMenuAddItem, _("Add item"), _("Add new Item"), wxITEM_NORMAL);
    MenuStuff->Append(MenuItemItem);
    MenuItemItem->Enable(false);
    MainMenuBar->Append(MenuStuff, _("&Stuff"));
    MenuMaps = new wxMenu();
    MenuItemAddMap = new wxMenuItem(MenuMaps, idMenuAddMap, _("Create map"), _("Create new map in Tiled"), wxITEM_NORMAL);
    MenuMaps->Append(MenuItemAddMap);
    MenuItemOpenMap = new wxMenuItem(MenuMaps, idMenuOpenMap, _("Open map"), _("Open existing map in Tiled"), wxITEM_NORMAL);
    MenuMaps->Append(MenuItemOpenMap);
    MainMenuBar->Append(MenuMaps, _("&Maps"));
    MenuStory = new wxMenu();
    MenuItemQuest = new wxMenuItem(MenuStory, idMenuQuest, _("Add Quest"), _("Add new Quest"), wxITEM_NORMAL);
    MenuStory->Append(MenuItemQuest);
    MenuItemQuest->Enable(false);
    MainMenuBar->Append(MenuStory, _("&Story"));
    MenuHelp = new wxMenu();
    MenuItemAbout = new wxMenuItem(MenuHelp, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    MenuHelp->Append(MenuItemAbout);
    MainMenuBar->Append(MenuHelp, _("Help"));
    SetMenuBar(MainMenuBar);
    StatusBar = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar);
    ModDirDialog = new wxDirDialog(this, _("Select directory for mod creation"), wxEmptyString, wxDD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxDirDialog"));
    GridSizerGlobal->Fit(this);
    GridSizerGlobal->SetSizeHints(this);
    
    Connect(ID_LISTBOX1,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnListBoxItemsSelect);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FlareGDEFrame::OnButtonItemPushClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FlareGDEFrame::OnButtonItemClearClick);
    Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FlareGDEFrame::OnButtonItemAddClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FlareGDEFrame::OnButtonItemCLoseClick);
    Connect(idMenuNew,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnMenuItemCreateSelected);
    Connect(idMenuOpen,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnMenuItemOpenSelected);
    Connect(idMenuSave,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnMenuItemSaveModSelected);
    Connect(idMenuClose,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnMenuItemCloseModSelected);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnQuit);
    Connect(idMenuNPC,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnMenuItemNPCSelected);
    Connect(idMenuEnemy,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnMenuItemEnemySelected);
    Connect(idMenuInventory,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnMenuItemInventorySelected);
    Connect(idMenuCharacter,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnMenuItemCharacterSelected);
    Connect(idMenuPowers,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnMenuItemPowersMenuSelected);
    Connect(idMenuLog,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnMenuItemLogSelected);
    Connect(idMenuXPBar,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnMenuItemXPBarSelected);
    Connect(idMenuManaBar,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnMenuItemManaBarSelected);
    Connect(idMenuHPBar,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnMenuItemHPBarSelected);
    Connect(idMenuEnemyBar,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnMenuItemEnemyBarSelected);
    Connect(idMenuMiniMap,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnMenuItemMiniMapSelected);
    Connect(idMenuLoadGame,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnMenuItemLoadGameSelected);
    Connect(idMenuNewGame,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnMenuItemNewGameSelected);
    Connect(idMenuSettings,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnMenuItemSettingsSelected);
    Connect(idMenuAddPower,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnMenuItemPowerSelected);
    Connect(idMenuAddItem,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnMenuItemItemSelected);
    Connect(idMenuAddMap,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnMenuItemAddMapSelected);
    Connect(idMenuOpenMap,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnMenuItemOpenMapSelected);
    Connect(idMenuQuest,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnMenuItemQuestSelected);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnAbout);
    //*)
    
    modPath = "";
}

FlareGDEFrame::~FlareGDEFrame()
{
    //(*Destroy(FlareGDEFrame)
    //*)
}

void FlareGDEFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void FlareGDEFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = "FLARE Game Development Environment v0.1";
    wxMessageBox(msg, _("About FlareGDE"));
}

void FlareGDEFrame::OnMenuItemCreateSelected(wxCommandEvent& event)
{
	newMod = true;
	if (ModDirDialog->ShowModal() == wxID_OK){
		modPath = ModDirDialog->GetPath();
		modName = wxGetTextFromUser (wxT("Enter mod name"), wxT("Enter mod name"), wxT("new_mod"), NULL, wxDefaultCoord, wxDefaultCoord, true);
		modPath = modPath + wxT("/") + modName;
		if (!wxFileName::DirExists(modPath))
			wxFileName::Mkdir(modPath);
		EnableMenus();
		MenuItemCreate->Enable(false);
		MenuItemOpen->Enable(false);
	}
}

void FlareGDEFrame::OnMenuItemOpenSelected(wxCommandEvent& event)
{
	newMod = false;
	if (ModDirDialog->ShowModal() == wxID_OK){
		modPath = ModDirDialog->GetPath();
		EnableMenus();
		MenuItemCreate->Enable(false);
		MenuItemOpen->Enable(false);
	}
}

void FlareGDEFrame::OnMenuItemSaveModSelected(wxCommandEvent& event)
{
	wxString filename = modPath + wxT("/") + "items" + wxT("/") + wxT("items.txt");
	std::string path = std::string(filename.mb_str());
	items->save(path);

	ToDo();
}

void FlareGDEFrame::OnMenuItemCloseModSelected(wxCommandEvent& event)
{
	if (modPath == "") return;
	wxMessageDialog saveQuestion(this, wxT("Save mod before closing?"), wxT("Save mod"), wxYES_DEFAULT|wxYES_NO|wxCANCEL|wxICON_INFORMATION);
	int answer = saveQuestion.ShowModal();
	if (answer == wxID_YES)
		{
			wxString filename = modPath + wxT("/") + "items" + wxT("/") + wxT("items.txt");
			std::string path = std::string(filename.mb_str());
			items->save(path);
			ToDo();
		}
	else if (answer == wxID_CANCEL)
		{
			return;
		}
	modName = "";
	modPath = "";
	DisableMenus();
	MenuItemOpen->Enable(true);
	MenuItemCreate->Enable(true);
	CloseAll();
}

void FlareGDEFrame::EnableMenus()
{
	MenuItemNPC->Enable(true);
	MenuItemEnemy->Enable(true);
	MenuItemInventory->Enable(true);
	MenuItemCharacter->Enable(true);
	MenuItemPowersMenu->Enable(true);
	MenuItemLog->Enable(true);
	MenuItemXPBar->Enable(true);
	MenuItemManaBar->Enable(true);
	MenuItemHPBar->Enable(true);
	MenuItemEnemyBar->Enable(true);
	MenuItemMiniMap->Enable(true);
	MenuItemLoadGame->Enable(true);
	MenuItemNewGame->Enable(true);
	MenuItemSettings->Enable(true);
	MenuItemPower->Enable(true);
	MenuItemItem->Enable(true);
	MenuItemQuest->Enable(true);
}

void FlareGDEFrame::DisableMenus()
{
	MenuItemNPC->Enable(false);
	MenuItemEnemy->Enable(false);
	MenuItemInventory->Enable(false);
	MenuItemCharacter->Enable(false);
	MenuItemPowersMenu->Enable(false);
	MenuItemLog->Enable(false);
	MenuItemXPBar->Enable(false);
	MenuItemManaBar->Enable(false);
	MenuItemHPBar->Enable(false);
	MenuItemEnemyBar->Enable(false);
	MenuItemMiniMap->Enable(false);
	MenuItemLoadGame->Enable(false);
	MenuItemNewGame->Enable(false);
	MenuItemSettings->Enable(false);
	MenuItemPower->Enable(false);
	MenuItemItem->Enable(false);
	MenuItemQuest->Enable(false);
}

void FlareGDEFrame::CloseAll()
{
	PanelItems->Enable(false);
	PanelItems->Show(false);
	delete items;
	ToDo();
}

void FlareGDEFrame::ToDo()
{
    wxString msg = "Not yet implemented";
    wxMessageBox(msg, _("TODO"));
}

void FlareGDEFrame::OnMenuItemNPCSelected(wxCommandEvent& event)
{
	ToDo();
}

void FlareGDEFrame::OnMenuItemEnemySelected(wxCommandEvent& event)
{
	ToDo();
}

void FlareGDEFrame::OnMenuItemInventorySelected(wxCommandEvent& event)
{
	ToDo();
}

void FlareGDEFrame::OnMenuItemCharacterSelected(wxCommandEvent& event)
{
	ToDo();
}

void FlareGDEFrame::OnMenuItemPowersMenuSelected(wxCommandEvent& event)
{
	ToDo();
}

void FlareGDEFrame::OnMenuItemLogSelected(wxCommandEvent& event)
{
	ToDo();
}

void FlareGDEFrame::OnMenuItemXPBarSelected(wxCommandEvent& event)
{
	ToDo();
}

void FlareGDEFrame::OnMenuItemManaBarSelected(wxCommandEvent& event)
{
	ToDo();
}

void FlareGDEFrame::OnMenuItemHPBarSelected(wxCommandEvent& event)
{
	ToDo();
}

void FlareGDEFrame::OnMenuItemEnemyBarSelected(wxCommandEvent& event)
{
	ToDo();
}

void FlareGDEFrame::OnMenuItemMiniMapSelected(wxCommandEvent& event)
{
	ToDo();
}

void FlareGDEFrame::OnMenuItemLoadGameSelected(wxCommandEvent& event)
{
	ToDo();
}

void FlareGDEFrame::OnMenuItemNewGameSelected(wxCommandEvent& event)
{
	ToDo();
}

void FlareGDEFrame::OnMenuItemSettingsSelected(wxCommandEvent& event)
{
	ToDo();
}

void FlareGDEFrame::OnMenuItemPowerSelected(wxCommandEvent& event)
{
	ToDo();
}

void FlareGDEFrame::OnMenuItemItemSelected(wxCommandEvent& event)
{
	PanelItems->Show(true);
	PanelItems->Enable(true);
	if (!wxFileName::DirExists(modPath + wxT("/") + "items"))
		wxFileName::Mkdir(modPath + wxT("/") + "items");
    wxString filename = modPath + wxT("/") + "items" + wxT("/") + wxT("items.txt");

	wxTextFile itemsFile(filename);
	if (!itemsFile.Exists())
		itemsFile.Create();

	std::string path = std::string(filename.mb_str());
	items = new ItemManager(path);
	for (unsigned i = 1;i<items->items.size();i++) {
		ListBoxItems->Append(items->items[i].name.c_str());
	}

}

void FlareGDEFrame::OnMenuItemAddMapSelected(wxCommandEvent& event)
{
	ToDo();
}

void FlareGDEFrame::OnMenuItemOpenMapSelected(wxCommandEvent& event)
{
	ToDo();
}

void FlareGDEFrame::OnMenuItemQuestSelected(wxCommandEvent& event)
{
	ToDo();
}

void FlareGDEFrame::OnButtonItemCLoseClick(wxCommandEvent& event)
{
	PanelItems->Enable(false);
	PanelItems->Show(false);

}

void FlareGDEFrame::OnButtonItemClearClick(wxCommandEvent& event)
{
	TextCtrlItemName->Clear();
	TextCtrlItemName->AppendText("ItemName");
	TextCtrlItemClass->Clear();
	TextCtrlItemClass->AppendText("unimlemented");
	TextCtrlitemBonus->Clear();
	TextCtrlitemBonus->AppendText("unimlemented");
	TextCtrlItemPickup->Clear();
	TextCtrlItemPowerDesc->Clear();

	ComboBoxItemType->SetValue("");
	ComboBoxitemRequires->SetValue("");
	ComboBoxItemQuality->SetValue("");
	ComboBoxItemSfx->SetValue("");

	SpinCtrlItemLevel->SetValue(0);
	SpinCtrlItemBonus->SetValue(0);
	SpinCtrlItemSell->SetValue(0);
	SpinCtrlItemAbsMax->SetValue(0);
	SpinCtrlItemAbsMin->SetValue(0);
	SpinCtrlItemMaxQuan->SetValue(0);
	SpinCtrlItemMelDmgMax->SetValue(0);
	SpinCtrlItemMelDmgMin->SetValue(0);
	SpinCtrlItemMentDmgMax->SetValue(0);
	SpinCtrlItemMentDmgMin->SetValue(0);
	SpinCtrlItemPower->SetValue(0);
	SpinCtrlItemPowerMod->SetValue(0);
	SpinCtrlItemPrice->SetValue(0);
	SpinCtrlItemRanDmgMax->SetValue(0);
	SpinCtrlItemRanDmgMin->SetValue(0);
	SpinCtrlItemRan_loot->SetValue(0);
	SpinCtrlItemRan_ven->SetValue(0);
	SpinCtrlItemRequires->SetValue(0);

}

void FlareGDEFrame::OnListBoxItemsSelect(wxCommandEvent& event)
{
	int index = ListBoxItems->GetSelection() + 1;
	wxString temp0(items->items[index].name.c_str(), wxConvUTF8);

	TextCtrlItemName->Clear();
	TextCtrlItemName->AppendText(temp0);
	//wxString temp1(items->items[index].bonus_stat.c_str(), wxConvUTF8);
	TextCtrlitemBonus->Clear();
	TextCtrlitemBonus->AppendText("unimplemented");
	wxString temp2(items->items[index].pickup_status.c_str(), wxConvUTF8);
	TextCtrlItemPickup->Clear();
	TextCtrlItemPickup->AppendText(temp2);
	wxString temp3(items->items[index].power_desc.c_str(), wxConvUTF8);
	TextCtrlItemPowerDesc->Clear();
	TextCtrlItemPowerDesc->AppendText(temp3);

	TextCtrlItemClass->Clear();
	TextCtrlItemClass->AppendText("unimplemented");

	wxString temp4(items->items[index].type.c_str(), wxConvUTF8);
	ComboBoxItemType->SetValue(temp4);
	ComboBoxitemRequires->SetSelection(items->items[index].req_stat);
	ComboBoxItemQuality->SetSelection(items->items[index].quality);
	ComboBoxItemSfx->SetSelection(items->items[index].sfx);

	SpinCtrlItemLevel->SetValue(items->items[index].level);
	//SpinCtrlItemBonus->SetValue(items->items[index].bonus_val);
	SpinCtrlItemBonus->SetValue(0);
	SpinCtrlItemPrice->SetValue(items->items[index].price);
	SpinCtrlItemSell->SetValue(items->items[index].price_sell);
	SpinCtrlItemAbsMax->SetValue(items->items[index].abs_max);
	SpinCtrlItemAbsMin->SetValue(items->items[index].abs_min);
	SpinCtrlItemMaxQuan->SetValue(items->items[index].max_quantity);
	SpinCtrlItemMelDmgMax->SetValue(items->items[index].dmg_melee_max);
	SpinCtrlItemMelDmgMin->SetValue(items->items[index].dmg_melee_min);
	SpinCtrlItemMentDmgMax->SetValue(items->items[index].dmg_ment_max);
	SpinCtrlItemMentDmgMin->SetValue(items->items[index].dmg_ment_min);
	SpinCtrlItemPower->SetValue(items->items[index].power);
	SpinCtrlItemPowerMod->SetValue(items->items[index].power_mod);
	SpinCtrlItemRanDmgMax->SetValue(items->items[index].dmg_ranged_max);
	SpinCtrlItemRanDmgMin->SetValue(items->items[index].dmg_ranged_min);
	SpinCtrlItemRan_loot->SetValue(items->items[index].rand_loot);
	SpinCtrlItemRan_ven->SetValue(items->items[index].rand_vendor);
	SpinCtrlItemRequires->SetValue(items->items[index].req_val);
}

void FlareGDEFrame::OnButtonItemPushClick(wxCommandEvent& event)
{
	int index = ListBoxItems->GetSelection() + 1;
	items->items[index].name = TextCtrlItemName->GetLineText(0);
	//items->items[index].bonus_stat = TextCtrlitemBonus->GetLineText(0);
	items->items[index].pickup_status = TextCtrlItemPickup->GetLineText(0);
	items->items[index].power_desc = TextCtrlItemPowerDesc->GetLineText(0);

	items->items[index].type = ComboBoxItemType->GetValue();

	items->items[index].req_stat = ComboBoxitemRequires->GetSelection();
	items->items[index].quality = ComboBoxItemQuality->GetSelection();
	items->items[index].sfx = ComboBoxItemSfx->GetSelection();

	items->items[index].level = SpinCtrlItemLevel->GetValue();
	//items->items[index].bonus_val = SpinCtrlItemBonus->GetValue();
	items->items[index].price = SpinCtrlItemPrice->GetValue();
	items->items[index].price_sell = SpinCtrlItemSell->GetValue();
	items->items[index].abs_max = SpinCtrlItemAbsMax->GetValue();
	items->items[index].abs_min = SpinCtrlItemAbsMin->GetValue();
	items->items[index].max_quantity = SpinCtrlItemMaxQuan->GetValue();
	items->items[index].dmg_melee_max = SpinCtrlItemMelDmgMax->GetValue();
	items->items[index].dmg_melee_min = SpinCtrlItemMelDmgMin->GetValue();
	items->items[index].dmg_ment_max = SpinCtrlItemMentDmgMax->GetValue();
	items->items[index].dmg_ment_min = SpinCtrlItemMentDmgMin->GetValue();
	items->items[index].power = SpinCtrlItemPower->GetValue();
	items->items[index].power_mod = SpinCtrlItemPowerMod->GetValue();
	items->items[index].dmg_ranged_max = SpinCtrlItemRanDmgMax->GetValue();
	items->items[index].dmg_ranged_min = SpinCtrlItemRanDmgMin->GetValue();
	items->items[index].rand_loot = SpinCtrlItemRan_loot->GetValue();
	items->items[index].rand_vendor = SpinCtrlItemRan_ven->GetValue();
	items->items[index].req_val = SpinCtrlItemRequires->GetValue();

	//Update ListBox
	ListBoxItems->SetString(ListBoxItems->GetSelection(), items->items[index].name.c_str());
}

void FlareGDEFrame::OnButtonItemAddClick(wxCommandEvent& event)
{
	items->items.resize(items->items.size()+1);
	ListBoxItems->Append("");
}
