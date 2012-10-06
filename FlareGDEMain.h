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
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

class FlareGDEFrame: public wxFrame
{
    public:

        FlareGDEFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~FlareGDEFrame();

    private:

        //(*Handlers(FlareGDEFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers(FlareGDEFrame)
        static const long idMenuNew;
        static const long idMenuOpen;
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
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // FLAREGDEMAIN_H
