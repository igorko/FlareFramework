/***************************************************************
 * Name:      FlareGDEMain.h
 * Purpose:   Defines Application Frame
 * Author:    Igor Paliychuk (mansonigor@gmail.com)
 * Created:   2012-10-06
 * Copyright: Igor Paliychuk ()
 * License:
 **************************************************************/

#ifndef FLAREGDEMAIN_H
#define FLAREGDEMAIN_H

//(*Headers(FlareGDEFrame)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/listbox.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/dirdlg.h>
#include <wx/frame.h>
#include <wx/combobox.h>
#include <wx/statusbr.h>
//*)

class FlareGDEFrame: public wxFrame
{
    public:

        FlareGDEFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~FlareGDEFrame();
		wxString modPath;
		void EnableMenus();
		void DisableMenus();
		void ToDo();

    private:

        //(*Handlers(FlareGDEFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnMenuItemCreateSelected(wxCommandEvent& event);
        void OnMenuItemNPCSelected(wxCommandEvent& event);
        void OnMenuItemEnemySelected(wxCommandEvent& event);
        void OnMenuItemInventorySelected(wxCommandEvent& event);
        void OnMenuItemCharacterSelected(wxCommandEvent& event);
        void OnMenuItemPowersMenuSelected(wxCommandEvent& event);
        void OnMenuItemLogSelected(wxCommandEvent& event);
        void OnMenuItemXPBarSelected(wxCommandEvent& event);
        void OnMenuItemManaBarSelected(wxCommandEvent& event);
        void OnMenuItemHPBarSelected(wxCommandEvent& event);
        void OnMenuItemEnemyBarSelected(wxCommandEvent& event);
        void OnMenuItemMiniMapSelected(wxCommandEvent& event);
        void OnMenuItemLoadGameSelected(wxCommandEvent& event);
        void OnMenuItemNewGameSelected(wxCommandEvent& event);
        void OnMenuItemSettingsSelected(wxCommandEvent& event);
        void OnMenuItemPowerSelected(wxCommandEvent& event);
        void OnMenuItemItemSelected(wxCommandEvent& event);
        void OnMenuItemAddMapSelected(wxCommandEvent& event);
        void OnMenuItemOpenMapSelected(wxCommandEvent& event);
        void OnMenuItemQuestSelected(wxCommandEvent& event);
        void OnMenuItemOpenSelected(wxCommandEvent& event);
        void OnMenuItemSaveModSelected(wxCommandEvent& event);
        void OnMenuItemCloseModSelected(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnButtonItemCLoseClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(FlareGDEFrame)
        static const long ID_LISTBOX1;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_STATICTEXT3;
        static const long ID_STATICTEXT4;
        static const long ID_STATICTEXT5;
        static const long ID_STATICTEXT6;
        static const long ID_STATICTEXT7;
        static const long ID_TEXTCTRL1;
        static const long ID_COMBOBOX1;
        static const long ID_COMBOBOX2;
        static const long ID_COMBOBOX3;
        static const long ID_TEXTCTRL2;
        static const long ID_TEXTCTRL3;
        static const long ID_TEXTCTRL4;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_BUTTON3;
        static const long ID_PANEL1;
        static const long idMenuNew;
        static const long idMenuOpen;
        static const long idMenuSave;
        static const long idMenuClose;
        static const long idMenuQuit;
        static const long idMenuNPC;
        static const long idMenuEnemy;
        static const long idMenuInventory;
        static const long idMenuCharacter;
        static const long idMenuPowers;
        static const long idMenuLog;
        static const long idMenuXPBar;
        static const long idMenuManaBar;
        static const long idMenuHPBar;
        static const long idMenuEnemyBar;
        static const long idMenuMiniMap;
        static const long ID_MENUITEM1;
        static const long idMenuLoadGame;
        static const long idMenuNewGame;
        static const long idMenuSettings;
        static const long ID_MENUITEM2;
        static const long idMenuAddPower;
        static const long idMenuAddItem;
        static const long idMenuAddMap;
        static const long idMenuOpenMap;
        static const long idMenuQuest;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(FlareGDEFrame)
        wxListBox* ListBoxItems;
        wxStaticText* StaticTextItemQuality;
        wxDirDialog* ModDirDialog;
        wxMenuItem* MenuItemInventory;
        wxComboBox* ComboBoxItemQuality;
        wxMenuItem* MenuItemManaBar;
        wxStaticText* StaticTextItemMentDmg;
        wxMenuItem* MenuItemLoadGame;
        wxMenuItem* MenuItemHPBar;
        wxMenuItem* MenuItemEnemy;
        wxPanel* PanelItems;
        wxComboBox* ComboBoxItemLevel;
        wxMenuItem* MenuItemCloseMod;
        wxMenuItem* MenuItemCreate;
        wxTextCtrl* TextCtrlItemMelDmg;
        wxTextCtrl* TextCtrlItemRanDmg;
        wxButton* ButtonItemCLose;
        wxMenuItem* MenuItemItem;
        wxMenuItem* MenuItemOpen;
        wxButton* ButtonItemClear;
        wxStaticText* StaticTextItemLevel;
        wxMenuItem* MenuItemXPBar;
        wxButton* ButtonItemPush;
        wxTextCtrl* TextCtrlItemName;
        wxMenuItem* MenuItemQuest;
        wxMenuItem* MenuItemSaveMod;
        wxComboBox* ComboBoxItemType;
        wxMenuItem* MenuItemEnemyBar;
        wxMenuItem* MenuItemCharacter;
        wxMenuItem* MenuItemAddMap;
        wxStaticText* StaticTextItemMelDmg;
        wxMenuItem* MenuItemPowersMenu;
        wxMenu* MenuItemInterface;
        wxTextCtrl* TextCtrlItemMentDmg;
        wxMenuItem* MenuItemLog;
        wxStaticText* StaticTextItemType;
        wxMenuItem* MenuItemSettings;
        wxMenuItem* MenuItemMiniMap;
        wxMenu* MenuItemInGame;
        wxMenuItem* MenuItemOpenMap;
        wxStatusBar* StatusBar;
        wxMenuItem* MenuItemPower;
        wxMenuItem* MenuItemNewGame;
        wxMenuItem* MenuItemNPC;
        wxStaticText* StaticTextItemRanDmg;
        wxStaticText* StaticTextItemName;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // FLAREGDEMAIN_H
