#include <wx/wx.h>
#include "mainframe.hpp"

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();
    Mainframe* frame = new Mainframe("Property sharks");
    frame->Show(true);
    return true;
}