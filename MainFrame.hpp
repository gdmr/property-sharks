#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include <wx/wx.h>
#include <wx/display.h>
#include "playerpanel.hpp"
#include "gamepanel.hpp"
#include "giocatore.hpp"


class Mainframe : public wxFrame
{
public:
    Mainframe(const wxString& title);

private:
    void OnPlayerSubmit(wxCommandEvent& event);
    void ShowGamePanel(const wxString& playerName);
    void MaximizeWithoutFullScreen();

    Playerpanel* playerPanel;
    Gamepanel* gamePanel;
    Giocatore* giocatore;

    wxDECLARE_EVENT_TABLE();
};

#endif