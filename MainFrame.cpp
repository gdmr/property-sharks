#include "MainFrame.hpp"

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_COMMAND(wxID_ANY, wxEVT_PLAYER_SUBMIT, MainFrame::OnPlayerSubmit)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600),
              wxDEFAULT_FRAME_STYLE | wxFULL_REPAINT_ON_RESIZE),
    giocatore(nullptr)
{
    playerPanel = new PlayerPanel(this);
    SetSizer(new wxBoxSizer(wxVERTICAL));
    GetSizer()->Add(playerPanel, 1, wxEXPAND);
    Layout();
    MaximizeWithoutFullScreen();
}

void MainFrame::OnPlayerSubmit(wxCommandEvent& event)
{
    wxString playerName = event.GetString();
    ShowGamePanel(playerName);
}

void MainFrame::ShowGamePanel(const wxString& playerName)
{
    if (playerPanel)
    {
        playerPanel->Hide();
        GetSizer()->Detach(playerPanel);
        playerPanel->Destroy();
        playerPanel = nullptr;
    }
    giocatore = new Giocatore(playerName.ToStdString(), 1000, false);
    gamePanel = new GamePanel(this, giocatore);  
    GetSizer()->Add(gamePanel, 1, wxEXPAND);
    Layout();
    
   
}

void MainFrame::MaximizeWithoutFullScreen()
{
    wxDisplay display(wxDisplay::GetFromWindow(this));
    wxRect screenRect = display.GetClientArea();
    SetSize(screenRect);
}