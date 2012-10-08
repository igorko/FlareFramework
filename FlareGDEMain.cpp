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
#include <wx/msgdlg.h>
#include <wx/filename.h>
#include <wx/textdlg.h>

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
const long FlareGDEFrame::ID_COMBOBOX2 = wxNewId();
const long FlareGDEFrame::ID_COMBOBOX3 = wxNewId();
const long FlareGDEFrame::ID_TEXTCTRL2 = wxNewId();
const long FlareGDEFrame::ID_TEXTCTRL3 = wxNewId();
const long FlareGDEFrame::ID_TEXTCTRL4 = wxNewId();
const long FlareGDEFrame::ID_BUTTON1 = wxNewId();
const long FlareGDEFrame::ID_BUTTON2 = wxNewId();
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
    wxMenu* MenuHelp;
    wxMenuItem* MenuItemAbout;
    wxMenuBar* MainMenuBar;
    wxGridSizer* GridSizerGlobal;
    wxMenuItem* MenuItemQuit;
    wxGridSizer* GridSizer1;
    wxMenu* MenuMaps;
    wxGridSizer* GridSizer3;
    wxMenu* MenuFile;
    wxMenu* MenuStory;
    wxGridSizer* GridSizer2;
    wxMenu* MenuMenus;
    wxMenu* MenuStuff;
    wxMenu* MenuCreatures;
    
    Create(parent, wxID_ANY, _("FlareGDE"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    GridSizerGlobal = new wxGridSizer(0, 1, 0, 0);
    PanelItems = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    PanelItems->Disable();
    PanelItems->Hide();
    GridSizer1 = new wxGridSizer(4, 3, 0, 0);
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
    ComboBoxItemLevel = new wxComboBox(PanelItems, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxSize(110,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
    GridSizer2->Add(ComboBoxItemLevel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ComboBoxItemQuality = new wxComboBox(PanelItems, ID_COMBOBOX3, wxEmptyString, wxDefaultPosition, wxSize(110,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX3"));
    ComboBoxItemQuality->Append(_("low"));
    ComboBoxItemQuality->Append(_("high"));
    ComboBoxItemQuality->Append(_("epic"));
    GridSizer2->Add(ComboBoxItemQuality, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlItemMelDmg = new wxTextCtrl(PanelItems, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(110,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    GridSizer2->Add(TextCtrlItemMelDmg, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlItemRanDmg = new wxTextCtrl(PanelItems, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxSize(110,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    GridSizer2->Add(TextCtrlItemRanDmg, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlItemMentDmg = new wxTextCtrl(PanelItems, ID_TEXTCTRL4, wxEmptyString, wxDefaultPosition, wxSize(110,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    GridSizer2->Add(TextCtrlItemMentDmg, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(GridSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonItemPush = new wxButton(PanelItems, ID_BUTTON1, _("Push"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    GridSizer1->Add(ButtonItemPush, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonItemClear = new wxButton(PanelItems, ID_BUTTON2, _("Clear"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    GridSizer1->Add(ButtonItemClear, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonItemCLose = new wxButton(PanelItems, ID_BUTTON3, _("Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    GridSizer1->Add(ButtonItemCLose, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
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
	if (ModDirDialog->ShowModal() == wxID_OK){
		modPath = ModDirDialog->GetPath();
		wxString modName = wxGetTextFromUser (wxT("Enter mod name"), wxT("Enter mod name"), wxT("new_mod"), NULL, wxDefaultCoord, wxDefaultCoord, true);
		if (wxFileName::Mkdir(modPath + "\\" + modName)) {
			EnableMenus();
			MenuItemCreate->Enable(false);
			MenuItemOpen->Enable(false);
			
		}
	}
}

void FlareGDEFrame::OnMenuItemOpenSelected(wxCommandEvent& event)
{
	if (ModDirDialog->ShowModal() == wxID_OK){
		modPath = ModDirDialog->GetPath();
		EnableMenus();
		MenuItemCreate->Enable(false);
		MenuItemOpen->Enable(false);
	}
}

void FlareGDEFrame::OnMenuItemSaveModSelected(wxCommandEvent& event)
{
	ToDo();
}

void FlareGDEFrame::OnMenuItemCloseModSelected(wxCommandEvent& event)
{
	if (modPath == "") return;
	wxMessageDialog saveQuestion(this, wxT("Save mod before closing?"), wxT("Save mod"), wxYES_DEFAULT|wxYES_NO|wxCANCEL|wxICON_INFORMATION);
	int answer = saveQuestion.ShowModal();
	if (answer == wxID_YES)
		{
			ToDo();
		}
	else if (answer == wxID_CANCEL)
		{
			return;
		}
	modPath = "";
	DisableMenus();
	MenuItemOpen->Enable(true);
	MenuItemCreate->Enable(true);
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
