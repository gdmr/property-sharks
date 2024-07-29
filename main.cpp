#include <wx/wx.h>
#include "MainFrame.hpp"

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MainFrame* frame = new MainFrame("Property sharks");
    frame->Show(true);
    return true;
}