#include "gamepanel.hpp"
#include <wx/dcclient.h>
#include <wx/log.h>

wxBEGIN_EVENT_TABLE(Gamepanel, wxPanel)
    EVT_PAINT(Gamepanel::OnPaint)
    EVT_BUTTON(ID_COMPRABUTTON, Gamepanel::onSubmit)
    EVT_BUTTON(ID_LANCIADADOBUTTON, Gamepanel::lanciaDado)
wxEND_EVENT_TABLE()

Gamepanel::Gamepanel(wxWindow* parent, Giocatore* giocatore) 
    : wxPanel(parent, wxID_ANY), giocatore(giocatore), tabellone(new Tabellone()), dado(new Dado()), currentPlayerPosition(0)
{
    tabellone->creaTabellone();
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* rightAlignedSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* textSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText* nome = new wxStaticText(this, wxID_ANY, "nome giocatore: " + giocatore->getNome());
    saldo = new wxStaticText(this, wxID_ANY, "saldo giocatore: " + std::to_string(giocatore->getSaldo()));
    risultatolabel = new wxStaticText(this, wxID_ANY, "0" + std::to_string(dado->lanciaDadi()));
    wxButton* button = new wxButton(this, ID_COMPRABUTTON, "Compra");
    wxButton* lanciaDado = new wxButton(this, ID_LANCIADADOBUTTON, "Lancia i dadi");
    
    tesseraInformativa = new wxStaticText(this, wxID_ANY, "Tessera corrente: Nessuna");

    textSizer->Add(button, 0, wxALL | wxALIGN_CENTER, 5);
    textSizer->Add(lanciaDado, 0, wxALL | wxALIGN_CENTER, 5);
    textSizer->Add(nome, 0, wxALL, 5);
    textSizer->Add(saldo, 0, wxALL, 5);
    textSizer->Add(risultatolabel, 0, wxALL, 5);
    textSizer->Add(tesseraInformativa, 0, wxALL, 5);

    rightAlignedSizer->AddStretchSpacer();
    rightAlignedSizer->Add(textSizer, 0, wxALL, 5);

    mainSizer->Add(rightAlignedSizer, 0, wxEXPAND | wxALL, 10);

    this->SetSizer(mainSizer);

    this->Layout();

    int cellSize = 115;
    int rows = 9;
    int cols = 9;

    for (int col = 0; col < cols; ++col) {
        boardPositions.push_back({0, col});
    }
    for (int row = 1; row < rows; ++row) {
        boardPositions.push_back({row, cols - 1});
    }
    for (int col = cols - 2; col >= 0; --col) {
        boardPositions.push_back({rows - 1, col});
    }
    for (int row = rows - 2; row > 0; --row) {
        boardPositions.push_back({row, 0});
    }
}

void Gamepanel::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    wxColour acquaGreen(127, 255, 212);
    dc.SetBrush(wxBrush(acquaGreen));
    dc.SetPen(*wxBLACK_PEN);

    int cellSize = 110;
    int rows = 9;
    int cols = 9;
    int index = 0;
    wxBrush currentBrush = *wxBLUE_BRUSH;

    for (const auto& pos : boardPositions)
    {
        if (index >= 32) {
            break;
        }

        int x = pos.second * cellSize;
        int y = pos.first * cellSize;
        dc.DrawRectangle(x, y, cellSize, cellSize);

        wxString label = wxString::Format("R%dC%d", pos.first, pos.second);
        std::shared_ptr<Tessera> c = tabellone->getTessera(index);
        std::cout << "num: " << index << " " << c->getTitolo() << "\n";

        if (c) {
            label = c->getTitolo();
            dc.DrawText(label, x + 10, y + 10);
        }

        index++;
    }

    if (currentPlayerPosition < boardPositions.size()) {
        auto pos = boardPositions[currentPlayerPosition];
        int x = pos.second * cellSize;
        int y = pos.first * cellSize;

        dc.SetBrush(*wxRED_BRUSH);
        dc.DrawCircle(x + cellSize / 2, y + cellSize / 2, 20);

        std::shared_ptr<Tessera> tesseraCorrente = tabellone->getTessera(currentPlayerPosition);
        if (tesseraCorrente) {
            std::cout << "tessera " << tesseraCorrente->getTitolo() << "\n";
            std::cout << "posizione " << giocatore->getPosizione() << "\n";

            Proprieta* proprieta = dynamic_cast<Proprieta*>(tesseraCorrente.get());
            if (proprieta) {
                int infoBoxWidth = 300;
                int infoBoxHeight = 150;
                int infoBoxX = this->GetClientSize().GetWidth() - infoBoxWidth - 10;
                int infoBoxY = this->GetClientSize().GetHeight() - infoBoxHeight - 10;
                wxColour darkGrey(169, 169, 169);
                dc.SetBrush(wxBrush(darkGrey));
                dc.DrawRectangle(infoBoxX, infoBoxY, infoBoxWidth, infoBoxHeight);
                wxString infoLabel = "Tessera corrente: " + tesseraCorrente->getTitolo();
                infoLabel += "\nCosto: " + std::to_string(proprieta->getCosto());
                infoLabel += "\nCosto Casa: " + std::to_string(proprieta->getCostoCasa());
                infoLabel += "\nProprietario: " + proprieta->getProprietario();
                infoLabel += "\nCase: " + std::to_string(proprieta->getNumeroCase());

                dc.DrawText(infoLabel, infoBoxX + 10, infoBoxY + 10);

                tesseraInformativa->SetLabel(infoLabel);
            } else {
                tesseraInformativa->SetLabel("Tessera corrente: Nessuna");
            }
        } else {
            tesseraInformativa->SetLabel("Tessera corrente: Nessuna");
        }
    }
}

void Gamepanel::onSubmit(wxCommandEvent& event)
{
    giocatore->modificaSaldo(100);
    saldo->SetLabel("saldo giocatore: " + std::to_string(giocatore->getSaldo()));
    this->Layout();
}

void Gamepanel::lanciaDado(wxCommandEvent& event)
{
    int risultato = dado->lanciaDadi();
    risultatolabel->SetLabel("esito lancio: " + std::to_string(risultato));
    
    giocatore->muoviGiocatore(risultato);
    currentPlayerPosition = giocatore->getPosizione();
    Refresh();
}