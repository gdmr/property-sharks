#ifndef GAMEPANEL_HPP
#define GAMEPANEL_HPP

#include <wx/wx.h>
#include <wx/panel.h>
#include "giocatore.hpp"

class GamePanel : public wxPanel
{
public:
    GamePanel(wxWindow* parent, Giocatore* giocatore);

private:
    void OnPaint(wxPaintEvent& event);
    Giocatore* giocatore; 

    wxString playerName;

    wxDECLARE_EVENT_TABLE();
};

#endif // GAMEPANEL_HPP