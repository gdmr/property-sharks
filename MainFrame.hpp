#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include <wx/wx.h>
#include <wx/display.h>
#include "PlayerPanel.hpp"
#include "GamePanel.hpp"
#include "giocatore.hpp"

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title);

private:
    void OnPlayerSubmit(wxCommandEvent& event);
    void ShowGamePanel(const wxString& playerName);
    void MaximizeWithoutFullScreen();

    PlayerPanel* playerPanel;
    GamePanel* gamePanel;
    Giocatore* giocatore;

    wxDECLARE_EVENT_TABLE();
};

#endif