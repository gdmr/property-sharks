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
    ID_LANCIADADOBUTTON = 2
};

class Gamepanel : public wxPanel
{
public:
    Gamepanel(wxWindow* parent, Giocatore* giocatore);

private:
    void OnPaint(wxPaintEvent& event);
    void onSubmit(wxCommandEvent& event);
    void lanciaDado(wxCommandEvent& event);
    std::pair<int, int> GetPositionForIndex(int index) const;

    wxStaticText* saldo;
    wxStaticText* risultatolabel;
    Giocatore* giocatore;
    std::unique_ptr<Tabellone> tabellone;
    std::unique_ptr<Dado> dado;

    int currentPlayerPosition;
    std::vector<std::pair<int, int>> boardPositions;

    wxDECLARE_EVENT_TABLE();
};




#endif // GAMEPANEL_HPP