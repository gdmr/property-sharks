#ifndef GAMEPANEL_HPP
#define GAMEPANEL_HPP

#include <wx/wx.h>
#include <wx/panel.h>
#include "giocatore.hpp"
#include "dado.hpp"
#include "tabellone.hpp"
#include "tessera.hpp"

enum
{
    ID_COMPRABUTTON = 1,
    ID_LANCIADADOBUTTON = 2,
    ID_COMPRACASABUTTON = 3,
    ID_CLOSEBUTTON = 4
};

class Gamepanel : public wxPanel
{
public:
    Gamepanel(wxWindow* parent, Giocatore* giocatore, Giocatore* bot, wxBitmap selectedPawn, wxBitmap botPawn);

private:
    void OnPaint(wxPaintEvent& event);
    void compraProprieta(wxCommandEvent& event);
    void lanciaDado(wxCommandEvent& event);
    void compraCasa(wxCommandEvent& event);
    void compraAlbergo(wxCommandEvent& event);
    void checkGameOver();
    void onClose(wxCommandEvent& event);
    void eseguiTurnoBot();
    void turnoBot();
    void onTimer(wxTimerEvent& event);

    Giocatore* giocatore;
    Giocatore* bot;
    std::unique_ptr<Tabellone> tabellone;
    std::unique_ptr<Dado> dado;
    int currentPlayerPosition;
    int botPosition;
    wxBitmap playerPawn;
    wxBitmap botPawn;
    wxBitmap houseIcon1;
    wxBitmap houseIcon2; 
    wxBitmap houseIcon3; 
    wxBitmap houseIcon4; 
    wxStaticText* saldo;
    wxStaticText* risultatolabel;
    wxStaticText* tesseraInformativa;
    wxStaticBitmap* gameOverImage;
    wxPanel* infoPanel;
    wxButton* buttonCompra;
    wxButton* buttonLanciaDado;
    wxButton* buttonCompraCasa;
    wxButton* buttonCompraAlbergo;
    wxButton* closeButton;
    wxTimer* m_timer;
    int m_moveSteps;
    bool m_isBotTurn;
    
    std::vector<std::pair<int, int>> boardPositions;
    std::vector<std::pair<int, int>> housePositions;
    std::vector<int> houseCount;
    std::vector<int> logicalToPhysical;

    wxDECLARE_EVENT_TABLE();
};

#endif // GAMEPANEL_HPP