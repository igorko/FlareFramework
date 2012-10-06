/***************************************************************
 * Name:      FlareGDEApp.cpp
 * Purpose:   Code for Application Class
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

#include "FlareGDEApp.h"

//(*AppHeaders
#include "FlareGDEMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(FlareGDEApp);

bool FlareGDEApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    FlareGDEFrame* Frame = new FlareGDEFrame(0);
	Frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    Frame->Show();
    SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
