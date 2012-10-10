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
#include <wx/spinctrl.h>
#include <wx/panel.h>
#include <wx/statbmp.h>
#include <wx/button.h>
#include <wx/dirdlg.h>
#include <wx/frame.h>
#include <wx/combobox.h>
#include <wx/statusbr.h>
//*)

class ItemManager;

class FlareGDEFrame: public wxFrame
{
    public:

        FlareGDEFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~FlareGDEFrame();
		wxString modPath;
		wxString modName;
		void EnableMenus();
		void DisableMenus();
		void ToDo();
		void CloseAll();
		bool newMod;
		ItemManager * items;

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
        void OnButtonItemClearClick(wxCommandEvent& event);
        void OnListBoxItemsSelect(wxCommandEvent& event);
        void OnButtonItemPushClick(wxCommandEvent& event);
        void OnButtonItemAddClick(wxCommandEvent& event);
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
        static const long ID_SPINCTRL1;
        static const long ID_COMBOBOX3;
        static const long ID_SPINCTRL10;
        static const long ID_SPINCTRL9;
        static const long ID_SPINCTRL11;
        static const long ID_SPINCTRL12;
        static const long ID_SPINCTRL13;
        static const long ID_SPINCTRL14;
        static const long ID_STATICTEXT8;
        static const long ID_STATICBITMAP1;
        static const long ID_BUTTON4;
        static const long ID_STATICTEXT9;
        static const long ID_STATICTEXT11;
        static const long ID_STATICTEXT12;
        static const long ID_STATICTEXT14;
        static const long ID_STATICTEXT17;
        static const long ID_STATICTEXT16;
        static const long ID_SPINCTRL15;
        static const long ID_SPINCTRL16;
        static const long ID_COMBOBOX5;
        static const long ID_BUTTON5;
        static const long ID_SPINCTRL2;
        static const long ID_TEXTCTRL12;
        static const long ID_SPINCTRL18;
        static const long ID_STATICTEXT10;
        static const long ID_STATICTEXT13;
        static const long ID_STATICTEXT15;
        static const long ID_STATICTEXT18;
        static const long ID_STATICTEXT19;
        static const long ID_STATICTEXT20;
        static const long ID_COMBOBOX4;
        static const long ID_TEXTCTRL7;
        static const long ID_SPINCTRL5;
        static const long ID_SPINCTRL6;
        static const long ID_SPINCTRL7;
        static const long ID_TEXTCTRL14;
        static const long ID_SPINCTRL8;
        static const long ID_SPINCTRL17;
        static const long ID_STATICTEXT21;
        static const long ID_STATICTEXT22;
        static const long ID_STATICTEXT23;
        static const long ID_STATICTEXT24;
        static const long ID_STATICTEXT25;
        static const long ID_BUTTON1;
        static const long ID_BUTTON7;
        static const long ID_TEXTCTRL15;
        static const long ID_BUTTON6;
        static const long ID_SPINCTRL3;
        static const long ID_SPINCTRL4;
        static const long ID_BUTTON2;
        static const long ID_STATICBITMAP2;
        static const long ID_BUTTON8;
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
        wxSpinCtrl* SpinCtrlItemPower;
        wxSpinCtrl* SpinCtrlItemAbsMin;
        wxSpinCtrl* SpinCtrlItemRanDmgMin;
        wxSpinCtrl* SpinCtrlItemRanDmgMax;
        wxListBox* ListBoxItems;
        wxStaticText* StaticTextItemQuality;
        wxDirDialog* ModDirDialog;
        wxMenuItem* MenuItemInventory;
        wxSpinCtrl* SpinCtrlItemSell;
        wxSpinCtrl* SpinCtrlItemLevel;
        wxStaticText* StaticTextItemRan_ven;
        wxSpinCtrl* SpinCtrlItemPrice;
        wxComboBox* ComboBoxItemQuality;
        wxButton* ButtonItemIcon;
        wxMenuItem* MenuItemManaBar;
        wxStaticText* StaticTextItemMentDmg;
        wxSpinCtrl* SpinCtrlItemMelDmgMin;
        wxSpinCtrl* SpinCtrlItemAbsMax;
        wxMenuItem* MenuItemLoadGame;
        wxButton* ButtonItemStepFX;
        wxStaticText* StaticTextItemRequires;
        wxStaticText* StaticTextItemClass;
        wxStaticText* StaticTextItemAbs;
        wxMenuItem* MenuItemHPBar;
        wxMenuItem* MenuItemEnemy;
        wxPanel* PanelItems;
        wxMenuItem* MenuItemCloseMod;
        wxStaticBitmap* StaticBitmap1;
        wxStaticText* StaticTextItemRan_loot;
        wxComboBox* ComboBoxItemSfx;
        wxMenuItem* MenuItemCreate;
        wxButton* ButtonItemAdd;
        wxStaticText* StaticTextitemBonus;
        wxStaticBitmap* StaticBitmapItemIcon;
        wxButton* ButtonItemCLose;
        wxSpinCtrl* SpinCtrlItemMentDmgMin;
        wxMenuItem* MenuItemItem;
        wxMenuItem* MenuItemOpen;
        wxTextCtrl* TextCtrlitemBonus;
        wxButton* ButtonItemClear;
        wxButton* ButtonitemGfx;
        wxStaticText* StaticTextItemLevel;
        wxMenuItem* MenuItemXPBar;
        wxButton* ButtonItemPush;
        wxTextCtrl* TextCtrlItemName;
        wxMenuItem* MenuItemQuest;
        wxStaticText* StaticTextItemPrice;
        wxStaticText* StaticTextItemPickup;
        wxStaticText* StaticTextItemPowerMod;
        wxStaticText* StaticTextItemIcon;
        wxMenuItem* MenuItemSaveMod;
        wxStaticText* StaticTextItemStep;
        wxSpinCtrl* SpinCtrlItemMelDmgMax;
        wxComboBox* ComboBoxItemType;
        wxStaticText* StaticTextLootAnim;
        wxSpinCtrl* SpinCtrlItemRan_loot;
        wxMenuItem* MenuItemEnemyBar;
        wxMenuItem* MenuItemCharacter;
        wxTextCtrl* TextCtrlItemPowerDesc;
        wxTextCtrl* TextCtrlItemClass;
        wxStaticText* StaticTextItemQuan;
        wxMenuItem* MenuItemAddMap;
        wxSpinCtrl* SpinCtrlItemBonus;
        wxStaticText* StaticTextItemMelDmg;
        wxStaticText* StaticTextItemPowerDesc;
        wxMenuItem* MenuItemPowersMenu;
        wxMenu* MenuItemInterface;
        wxStaticText* StaticTextItemGfx;
        wxSpinCtrl* SpinCtrlItemMentDmgMax;
        wxStaticText* StaticTextItemPower;
        wxMenuItem* MenuItemLog;
        wxStaticText* StaticTextItemType;
        wxSpinCtrl* SpinCtrlItemPowerMod;
        wxComboBox* ComboBoxitemRequires;
        wxSpinCtrl* SpinCtrlItemMaxQuan;
        wxMenuItem* MenuItemSettings;
        wxMenuItem* MenuItemMiniMap;
        wxMenu* MenuItemInGame;
        wxSpinCtrl* SpinCtrlItemRan_ven;
        wxMenuItem* MenuItemOpenMap;
        wxTextCtrl* TextCtrlItemPickup;
        wxStatusBar* StatusBar;
        wxStaticText* StaticTextItemPriceSell;
        wxMenuItem* MenuItemPower;
        wxMenuItem* MenuItemNewGame;
        wxButton* ButtonItemLootAnim;
        wxMenuItem* MenuItemNPC;
        wxSpinCtrl* SpinCtrlItemRequires;
        wxStaticText* StaticTextItemRanDmg;
        wxStaticText* StaticTextItemSfx;
        wxStaticText* StaticTextItemName;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // FLAREGDEMAIN_H
