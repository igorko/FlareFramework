/***************************************************************
 * Name:      FlareFrameworkApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Igor Paliychuk (mansonigor@gmail.com)
 * Created:   2012-10-06
 * Copyright: Igor Paliychuk ()
 * License:
 * FlareFramework is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * FlareFramework is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * FlareFramework.  If not, see http://www.gnu.org/licenses/
 **************************************************************/

#include "FlareFrameworkApp.h"

//(*AppHeaders
#include "FlareFrameworkMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(FlareFrameworkApp);

bool FlareFrameworkApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    FlareFrameworkFrame* Frame = new FlareFrameworkFrame(0);
    Frame->Show();
    SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
