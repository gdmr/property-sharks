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
    void ShowGamePanel(const wxString& playerName, int pawnIndex);
    void MaximizeWithoutFullScreen();

    Playerpanel* playerPanel;
    Gamepanel* gamePanel;
    Giocatore* giocatore;
    Giocatore* bot;

    wxDECLARE_EVENT_TABLE();
};

#endif