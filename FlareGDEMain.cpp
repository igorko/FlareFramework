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
const long FlareGDEFrame::idMenuNew = wxNewId();
const long FlareGDEFrame::idMenuOpen = wxNewId();
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
    wxMenuItem* MenuItem8;
    wxMenu* MenuItem19;
    wxMenuItem* MenuItem26;
    wxMenuItem* MenuItem7;
    wxMenuItem* MenuItem25;
    wxMenu* MenuItem9;
    wxMenuItem* MenuItem5;
    wxMenuItem* MenuItem2;
    wxMenu* Menu3;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem4;
    wxMenuItem* MenuItem14;
    wxMenuItem* MenuItem11;
    wxMenuItem* MenuItem15;
    wxMenuItem* MenuItem22;
    wxMenuItem* MenuItem17;
    wxMenuItem* MenuItem13;
    wxMenu* Menu1;
    wxMenuItem* MenuItem10;
    wxMenuItem* MenuItem12;
    wxMenuItem* MenuItem24;
    wxMenuItem* MenuItem3;
    wxMenu* Menu7;
    wxMenuItem* MenuItem6;
    wxMenuItem* MenuItem23;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem21;
    wxMenuItem* MenuItem16;
    wxMenu* Menu2;
    wxMenu* Menu6;
    wxMenuItem* MenuItem18;
    wxMenu* Menu5;
    wxMenu* Menu4;
    
    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu1, idMenuNew, _("New Mod\tAlt-N"), _("Create new mod"), wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItem4 = new wxMenuItem(Menu1, idMenuOpen, _("Open Mod\tAlt-O"), _("Open existing mod"), wxITEM_NORMAL);
    Menu1->Append(MenuItem4);
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu4 = new wxMenu();
    MenuItem7 = new wxMenuItem(Menu4, idMenuNPC, _("Add NPC"), _("Add new NPC"), wxITEM_NORMAL);
    Menu4->Append(MenuItem7);
    MenuItem8 = new wxMenuItem(Menu4, idMenuEnemy, _("Add Enemy"), _("Add new Enemy"), wxITEM_NORMAL);
    Menu4->Append(MenuItem8);
    MenuBar1->Append(Menu4, _("&Creatures"));
    Menu5 = new wxMenu();
    MenuItem9 = new wxMenu();
    MenuItem10 = new wxMenuItem(MenuItem9, idMenuInventory, _("Inventory"), _("Edit Inventory Menu Layout"), wxITEM_NORMAL);
    MenuItem9->Append(MenuItem10);
    MenuItem11 = new wxMenuItem(MenuItem9, idMenuCharacter, _("Character"), _("Edit Character Menu Layout"), wxITEM_NORMAL);
    MenuItem9->Append(MenuItem11);
    MenuItem12 = new wxMenuItem(MenuItem9, idMenuPowers, _("Powers"), _("Edit Powers Menu Layout"), wxITEM_NORMAL);
    MenuItem9->Append(MenuItem12);
    MenuItem13 = new wxMenuItem(MenuItem9, idMenuLog, _("Log"), _("Edit Log Menu Layout"), wxITEM_NORMAL);
    MenuItem9->Append(MenuItem13);
    MenuItem14 = new wxMenuItem(MenuItem9, idMenuXPBar, _("XP Bar"), _("Edit XP Bar Layout"), wxITEM_NORMAL);
    MenuItem9->Append(MenuItem14);
    MenuItem15 = new wxMenuItem(MenuItem9, idMenuManaBar, _("Mana Bar"), _("Edit Mana Bar Layout"), wxITEM_NORMAL);
    MenuItem9->Append(MenuItem15);
    MenuItem16 = new wxMenuItem(MenuItem9, idMenuHPBar, _("HP Bar"), _("Edit HP Bar Layout"), wxITEM_NORMAL);
    MenuItem9->Append(MenuItem16);
    MenuItem17 = new wxMenuItem(MenuItem9, idMenuEnemyBar, _("Enemy Bar"), _("Edit Enemy Bar Layout"), wxITEM_NORMAL);
    MenuItem9->Append(MenuItem17);
    MenuItem18 = new wxMenuItem(MenuItem9, idMenuMiniMap, _("MiniMap"), _("Edit MiniMap Layout"), wxITEM_NORMAL);
    MenuItem9->Append(MenuItem18);
    Menu5->Append(ID_MENUITEM1, _("&InGame"), MenuItem9, wxEmptyString);
    MenuItem19 = new wxMenu();
    MenuItem21 = new wxMenuItem(MenuItem19, idMenuLoadGame, _("Load Game"), _("Edit Load Game Menu Layout"), wxITEM_NORMAL);
    MenuItem19->Append(MenuItem21);
    MenuItem22 = new wxMenuItem(MenuItem19, idMenuNewGame, _("New Game"), _("Edit New Game Menu Layout"), wxITEM_NORMAL);
    MenuItem19->Append(MenuItem22);
    MenuItem23 = new wxMenuItem(MenuItem19, idMenuSettings, _("Settings Menu"), _("Edit Settings Menu Layout"), wxITEM_NORMAL);
    MenuItem19->Append(MenuItem23);
    Menu5->Append(ID_MENUITEM2, _("&Interface Menus"), MenuItem19, wxEmptyString);
    MenuBar1->Append(Menu5, _("&Menus"));
    Menu3 = new wxMenu();
    MenuItem5 = new wxMenuItem(Menu3, idMenuAddPower, _("Add Power"), _("Add new Power"), wxITEM_NORMAL);
    Menu3->Append(MenuItem5);
    MenuItem6 = new wxMenuItem(Menu3, idMenuAddItem, _("Add item"), _("Add new Item"), wxITEM_NORMAL);
    Menu3->Append(MenuItem6);
    MenuBar1->Append(Menu3, _("&Stuff"));
    Menu6 = new wxMenu();
    MenuItem24 = new wxMenuItem(Menu6, idMenuAddMap, _("Create map"), _("Create new map in Tiled"), wxITEM_NORMAL);
    Menu6->Append(MenuItem24);
    MenuItem25 = new wxMenuItem(Menu6, idMenuOpenMap, _("Open map"), _("Open existing map in Tiled"), wxITEM_NORMAL);
    Menu6->Append(MenuItem25);
    MenuBar1->Append(Menu6, _("&Maps"));
    Menu7 = new wxMenu();
    MenuItem26 = new wxMenuItem(Menu7, idMenuQuest, _("Add Quest"), _("Add new Quest"), wxITEM_NORMAL);
    Menu7->Append(MenuItem26);
    MenuBar1->Append(Menu7, _("&Story"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlareGDEFrame::OnAbout);
    //*)
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
