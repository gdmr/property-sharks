#include "mainframe.hpp"

wxBEGIN_EVENT_TABLE(Mainframe, wxFrame)
    EVT_COMMAND(wxID_ANY, wxEVT_PLAYER_SUBMIT, Mainframe::OnPlayerSubmit)
wxEND_EVENT_TABLE()

Mainframe::Mainframe(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600),
              wxDEFAULT_FRAME_STYLE | wxFULL_REPAINT_ON_RESIZE), giocatore(nullptr), bot(nullptr)
{
    playerPanel = new Playerpanel(this);
    SetSizer(new wxBoxSizer(wxVERTICAL));
    GetSizer()->Add(playerPanel, 1, wxEXPAND);
    Layout();
    MaximizeWithoutFullScreen();
}

void Mainframe::OnPlayerSubmit(wxCommandEvent& event)
{
    wxString playerName = event.GetString();
    int pawnIndex = event.GetInt();
    ShowGamePanel(playerName, pawnIndex);
}




void Mainframe::ShowGamePanel(const wxString& playerName, int pawnIndex)
{
    if (playerPanel)
    {
        playerPanel->Hide();
        GetSizer()->Detach(playerPanel);
        playerPanel->Destroy();
        playerPanel = nullptr;
    }

    // Carica la pedina selezionata in base all'indice
    wxBitmap selectedPawn;
    switch (pawnIndex) {
        case 0:
            selectedPawn.LoadFile("pedine/s1.png", wxBITMAP_TYPE_PNG);
            break;
        case 1:
            selectedPawn.LoadFile("pedine/s2.png", wxBITMAP_TYPE_PNG);
            break;
        case 2:
            selectedPawn.LoadFile("pedine/s3.png", wxBITMAP_TYPE_PNG);
            break;
        default:
            wxLogError("Indice della pedina non valido");
            return;
    }

    giocatore = new Giocatore(playerName.ToStdString(), 1000, false);
    wxBitmap botPawn;
    botPawn.LoadFile("img/squalorobot.png", wxBITMAP_TYPE_PNG); // Assicurati che questa immagine esista
    bot = new Giocatore("bot01", 1000, true);
    gamePanel = new Gamepanel(this, giocatore, bot, selectedPawn, botPawn);  
    GetSizer()->Add(gamePanel, 1, wxEXPAND);
    Layout();
}

void Mainframe::MaximizeWithoutFullScreen()
{
    wxDisplay display(wxDisplay::GetFromWindow(this));
    wxRect screenRect = display.GetClientArea();
    SetSize(screenRect);
}