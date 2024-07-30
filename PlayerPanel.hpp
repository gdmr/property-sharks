#ifndef PLAYERPANEL_HPP
#define PLAYERPANEL_HPP

#include <wx/wx.h>
#include <vector>

wxDECLARE_EVENT(wxEVT_PLAYER_SUBMIT, wxCommandEvent);

class Playerpanel : public wxPanel
{
public:
    Playerpanel(wxWindow* parent);

private:
    void OnSubmit(wxCommandEvent& event);
    void OnPrevPawn(wxCommandEvent& event);
    void OnNextPawn(wxCommandEvent& event);

    wxTextCtrl* textCtrl;
    wxStaticBitmap* pawnDisplay;
    std::vector<wxBitmap> pawns;
    int currentPawnIndex;
    wxDECLARE_EVENT_TABLE();
};

#endif // PLAYERPANEL_HPP