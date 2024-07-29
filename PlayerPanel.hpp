#ifndef PLAYERPANEL_HPP
#define PLAYERPANEL_HPP

#include <wx/wx.h>

wxDECLARE_EVENT(wxEVT_PLAYER_SUBMIT, wxCommandEvent);

class Playerpanel : public wxPanel
{
public:
    Playerpanel(wxWindow* parent);

private:
    void OnSubmit(wxCommandEvent& event);

    wxTextCtrl* textCtrl;
    wxDECLARE_EVENT_TABLE();
};

#endif // PLAYERPANEL_HPP