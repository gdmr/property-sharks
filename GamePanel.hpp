#ifndef GAMEPANEL_HPP
#define GAMEPANEL_HPP

#include <wx/wx.h>
#include <wx/panel.h>
#include "giocatore.hpp"

class Gamepanel : public wxPanel
{
public:
    Gamepanel(wxWindow* parent, Giocatore* giocatore);

private:
    void OnPaint(wxPaintEvent& event);
    void onSubmit(wxCommandEvent& event);
    Giocatore* giocatore; 

    wxString playerName;
    wxStaticText* saldo;

    wxDECLARE_EVENT_TABLE();
};

#endif // GAMEPANEL_HPP