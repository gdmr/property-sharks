#include "gamepanel.hpp"
#include <wx/dcclient.h>
#include <wx/log.h>

wxBEGIN_EVENT_TABLE(Gamepanel, wxPanel)
    EVT_PAINT(Gamepanel::OnPaint)
    EVT_BUTTON(ID_COMPRABUTTON, Gamepanel::compraProprieta)
    EVT_BUTTON(ID_LANCIADADOBUTTON, Gamepanel::lanciaDado)
    EVT_BUTTON(ID_COMPRACASABUTTON, Gamepanel::compraCasa)
    EVT_BUTTON(ID_CLOSEBUTTON, Gamepanel::onClose)
wxEND_EVENT_TABLE()


Gamepanel::Gamepanel(wxWindow* parent, Giocatore* giocatore, wxBitmap selectedPawn) 
    : wxPanel(parent, wxID_ANY), giocatore(giocatore), tabellone(new Tabellone()), dado(new Dado()), currentPlayerPosition(0), playerPawn(selectedPawn)
{
    wxImage pawnImage = selectedPawn.ConvertToImage();
    int newWidth = 70;
    int newHeight = 70;
    pawnImage.Rescale(newWidth, newHeight);
    playerPawn = wxBitmap(pawnImage);
    tabellone->creaTabellone();
    
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* centerSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxVERTICAL);
    
    wxStaticText* nome = new wxStaticText(this, wxID_ANY, "nome giocatore: " + giocatore->getNome());
    saldo = new wxStaticText(this, wxID_ANY, "saldo giocatore: " + std::to_string(giocatore->getSaldo()));
    risultatolabel = new wxStaticText(this, wxID_ANY, "0" + std::to_string(dado->lanciaDadi()));
    
    wxButton* button = new wxButton(this, ID_COMPRABUTTON, "Compra");
    wxButton* lanciaDado = new wxButton(this, ID_LANCIADADOBUTTON, "Lancia i dadi");
    closeButton = new wxButton(this, ID_CLOSEBUTTON, "Chiudi");
    closeButton->Hide();
    buttonCompraCasa = new wxButton(this, ID_COMPRACASABUTTON, "Compra casa");
    
    tesseraInformativa = new wxStaticText(this, wxID_ANY, "Tessera corrente: Nessuna");
    wxBitmap gameOverBitmap(wxT("img/gameover.png"), wxBITMAP_TYPE_PNG);
    gameOverImage = new wxStaticBitmap(this, wxID_ANY, gameOverBitmap);
    gameOverImage->Hide();
    
    buttonSizer->Add(button, 0, wxALL | wxALIGN_CENTER, 5);
    buttonSizer->Add(lanciaDado, 0, wxALL | wxALIGN_CENTER, 5);
    buttonSizer->Add(buttonCompraCasa, 0, wxALL | wxALIGN_CENTER, 5);
    buttonSizer->Add(closeButton, 0, wxALL | wxALIGN_CENTER, 5);
    
    centerSizer->Add(buttonSizer, 0, wxALL | wxALIGN_CENTER, 5);
    centerSizer->Add(nome, 0, wxALL | wxALIGN_CENTER, 5);
    centerSizer->Add(saldo, 0, wxALL | wxALIGN_CENTER, 5);
    centerSizer->Add(risultatolabel, 0, wxALL | wxALIGN_CENTER, 5);
    centerSizer->Add(tesseraInformativa, 0, wxALL | wxALIGN_CENTER, 5);
    
    mainSizer->AddStretchSpacer();
    mainSizer->Add(centerSizer, 0, wxALL | wxALIGN_CENTER, 5);
    mainSizer->AddStretchSpacer();
    mainSizer->Add(gameOverImage, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    
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

    if (giocatore->getSaldo() < 0) {
        return;
    }

    wxSize clientSize = this->GetClientSize();
    int rows = 9;
    int cols = 9;
    int cellWidth = clientSize.GetWidth() / cols;
    int cellHeight = clientSize.GetHeight() / rows;
    int index = 0;
    wxBrush currentBrush = *wxBLUE_BRUSH;

    for (const auto& pos : boardPositions)
    {
        if (index >= 32) {
            break;
        }

        int x = pos.second * cellWidth;
        int y = pos.first * cellHeight;
        dc.DrawRectangle(x, y, cellWidth, cellHeight);

        wxString label = wxString::Format("R%dC%d", pos.first, pos.second);
        std::shared_ptr<Tessera> c = tabellone->getTessera(index);

        if (c) {
            label = c->getTitolo();
            if (index == 4) {
                label = "Opportunita";
            }
            if (index == 19) {
                label = "Inconvenienti";
            }
            dc.DrawText(label, x + 10, y + 10);
        }

        index++;
    }

    if (currentPlayerPosition < boardPositions.size()) {
        auto pos = boardPositions[currentPlayerPosition];
        int x = pos.second * cellWidth;
        int y = pos.first * cellHeight;
        //dc.DrawRectangle(x, y, cellWidth, cellHeight);

        dc.DrawBitmap(playerPawn, x + cellWidth / 2 - playerPawn.GetWidth() / 2, y + cellHeight / 2 - playerPawn.GetHeight() / 2, true);

        std::shared_ptr<Tessera> tesseraCorrente = tabellone->getTessera(currentPlayerPosition);
        if (tesseraCorrente) {
             int infoBoxWidth = 300;
            int infoBoxHeight = 150;
            int infoBoxX = this->GetClientSize().GetWidth() - infoBoxWidth - 200;
            int infoBoxY = this->GetClientSize().GetHeight() - infoBoxHeight - 100;
            wxColour darkGrey(169, 169, 169);
            dc.SetBrush(wxBrush(darkGrey));
            dc.DrawRectangle(infoBoxX, infoBoxY, infoBoxWidth, infoBoxHeight);

            wxString infoLabel = "Tessera corrente: " + tesseraCorrente->getTitolo();

            if (tesseraCorrente->getTipo() == "Proprieta") {
                Proprieta* proprieta = dynamic_cast<Proprieta*>(tesseraCorrente.get());
                if (proprieta) {
                    infoLabel += "\nCosto: " + std::to_string(proprieta->getCosto());
                    infoLabel += "\nCosto Casa: " + std::to_string(proprieta->getCostoCasa());
                    infoLabel += "\nProprietario: " + proprieta->getProprietario();
                    infoLabel += "\nCase: " + std::to_string(proprieta->getNumeroCase());

                    dc.DrawText(infoLabel, infoBoxX + 10, infoBoxY + 10);
                    tesseraInformativa->SetLabel(infoLabel);
                }
            } else if (tesseraCorrente->getTipo() == "opportunita") {
                Opportunita opportunitaCasuale = tabellone->getOpportunita();
                infoLabel += "\nTitolo: " + opportunitaCasuale.getTitolo();
                infoLabel += "\nGuadagno: " + std::to_string(opportunitaCasuale.getImporto());
                infoLabel += "\nBonus: " + std::to_string(opportunitaCasuale.isBonus());

                dc.DrawText(infoLabel, infoBoxX + 10, infoBoxY + 10);
                tesseraInformativa->SetLabel(infoLabel);

                wxMessageBox("Opportunità: " + opportunitaCasuale.getTitolo() + "\nImporto: " + std::to_string(opportunitaCasuale.getImporto()), "Avviso", wxOK | wxICON_INFORMATION);
            } else if (tesseraCorrente->getTipo() == "inconvenienti") {
                Inconvenienti inconvenienteCasuale = tabellone->getInconveniente();
                infoLabel += "\nTitolo: " + inconvenienteCasuale.getTitolo();
                infoLabel += "\nSpesa: " + std::to_string(inconvenienteCasuale.getImporto());

                dc.DrawText(infoLabel, infoBoxX + 10, infoBoxY + 10);
                tesseraInformativa->SetLabel(infoLabel);

                wxMessageBox("Imprevisto: " + inconvenienteCasuale.getTitolo() + "\nImporto: " + std::to_string(inconvenienteCasuale.getImporto()), "Avviso", wxOK | wxICON_INFORMATION);
            } else if (tesseraCorrente->getTipo() == "prigione") {
                wxMessageBox("Sei finito in prigione!", "Avviso", wxOK | wxICON_INFORMATION);
            }
        } else {
            tesseraInformativa->SetLabel("Tessera corrente: Nessuna");
        }
    }
}

void Gamepanel::compraProprieta(wxCommandEvent& event)
{
    std::shared_ptr tesseraCorrente = tabellone->getTessera(currentPlayerPosition);
    Proprieta* proprieta = dynamic_cast<Proprieta*>(tesseraCorrente.get());
    if (proprieta) {
        if (proprieta->getProprietario() == giocatore->getNome()) {
            wxMessageBox("Sei già il proprietario di questa proprietà", "Attento", wxOK | wxICON_ERROR);
            return;
        }
        if (giocatore->getSaldo() < proprieta->getCosto()) {
            wxMessageBox("Il tuo saldo non è sufficiente per acquistare la proprietà", "Mi dispiace", wxOK | wxICON_ERROR);
            return;
        }
    giocatore->acquistaProprieta(*proprieta);
    saldo->SetLabel("saldo giocatore: " + std::to_string(giocatore->getSaldo()));
    Refresh();}
}

void Gamepanel::compraCasa(wxCommandEvent& event){
    std::shared_ptr tesseraCorrente = tabellone->getTessera(currentPlayerPosition);
    Proprieta* proprieta = dynamic_cast<Proprieta*>(tesseraCorrente.get());
    if (proprieta) {
    switch (giocatore->acquistaCasa(*proprieta))
    {
    case 0:
        wxMessageBox("Casa acquistata", "Complimenti", wxOK | wxICON_INFORMATION);
        break;
     case 1:
        wxMessageBox("Numero massimo di case raggiunto", "Attento", wxOK | wxICON_ERROR);
        break;
     case 2:
        wxMessageBox("Saldo insufficiente", "Attento", wxOK | wxICON_ERROR);
        break;
     case 3:
        wxMessageBox("Proprietario non corrisponde", "Attento", wxOK | wxICON_ERROR);
        break;
    }
    }
}

void Gamepanel::lanciaDado(wxCommandEvent& event)
{
    int risultato = dado->lanciaDadi();
    risultatolabel->SetLabel("esito lancio: " + std::to_string(risultato));
    int posizionePrecedente = giocatore->getPosizione();
    giocatore->muoviGiocatore(risultato);
    currentPlayerPosition = giocatore->getPosizione();
    if (currentPlayerPosition < posizionePrecedente) {
        giocatore->modificaSaldo(100);
        //wxMessageBox("Hai passato lo start! Bonus di 100 denti squalo");
        saldo->SetLabel("saldo giocatore: " + std::to_string(giocatore->getSaldo()));
        checkGameOver(); 
    }
    currentPlayerPosition = giocatore->getPosizione();
    Refresh();
}

void Gamepanel::checkGameOver()
{
    if (giocatore->getSaldo() < 0)
    {
        saldo->Hide();
        risultatolabel->Hide();
        tesseraInformativa->Hide();
        FindWindowById(ID_COMPRABUTTON)->Hide();
        FindWindowById(ID_LANCIADADOBUTTON)->Hide();
        FindWindowById(ID_COMPRACASABUTTON)->Hide();
        gameOverImage->Show();
        closeButton->Show();

        
        this->Layout();
        Refresh();
    }
}


void Gamepanel::onClose(wxCommandEvent& event)
{
    // Chiudi la finestra
    this->GetParent()->Close();
}
