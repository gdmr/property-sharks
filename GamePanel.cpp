#include "gamepanel.hpp"
#include <wx/dcclient.h>
#include <wx/log.h>
#include <wx/dcbuffer.h>  

wxBEGIN_EVENT_TABLE(Gamepanel, wxPanel)
    EVT_PAINT(Gamepanel::OnPaint)
    EVT_BUTTON(ID_COMPRABUTTON, Gamepanel::compraProprieta)
    EVT_BUTTON(ID_LANCIADADOBUTTON, Gamepanel::lanciaDado)
    EVT_BUTTON(ID_COMPRACASABUTTON, Gamepanel::compraCasa)
    EVT_BUTTON(ID_CLOSEBUTTON, Gamepanel::onClose)
    EVT_BUTTON(ID_PASSABUTTON, Gamepanel::passa)
    EVT_BUTTON(ID_COMPRAALBERGOBUTTON, Gamepanel::compraAlbergo)
    EVT_TIMER(wxID_ANY, Gamepanel::onTimer) 
wxEND_EVENT_TABLE()


Gamepanel::Gamepanel(wxWindow* parent, Giocatore* giocatore, Giocatore* bot, wxBitmap selectedPawn, wxBitmap botPawn)
    : wxPanel(parent, wxID_ANY), 
      giocatore(giocatore), 
      bot(bot), 
      tabellone(new Tabellone()), 
      dado(new Dado()), 
      currentPlayerPosition(0), 
      playerPawn(selectedPawn), 
      botPawn(botPawn), 
      m_timer(new wxTimer(this)), 
      m_moveSteps(0), 
      m_isBotTurn(false),
      turniInPrigioneGiocatore(0),
      turniInPrigioneBot(0),
      giocatoreInPrigione(false),
      botInPrigione(false){
    wxImage pawnImage = selectedPawn.ConvertToImage();
    int newWidth = 70;
    int newHeight = 70;
    pawnImage.Rescale(newWidth, newHeight);
    playerPawn = wxBitmap(pawnImage);
    wxImage botPawnImage = botPawn.ConvertToImage();
    botPawnImage.Rescale(newWidth, newHeight);
    this->botPawn = wxBitmap(botPawnImage);
    tabellone->creaTabellone();
   
    Bind(wxEVT_TIMER, &Gamepanel::onTimer, this);




    wxImage houseImage1(wxT("img/house1.png"), wxBITMAP_TYPE_PNG);
    houseImage1.Rescale(150, 150);
    houseIcon1 = wxBitmap(houseImage1);
    wxImage houseImage2(wxT("img/house2.png"), wxBITMAP_TYPE_PNG);
    houseImage2.Rescale(150, 150);
    houseIcon2 = wxBitmap(houseImage2);
     wxImage houseImage3(wxT("img/house3.png"), wxBITMAP_TYPE_PNG);
    houseImage3.Rescale(150, 150);
    houseIcon3 = wxBitmap(houseImage3);
     wxImage houseImage4(wxT("img/house4.png"), wxBITMAP_TYPE_PNG);
    houseImage4.Rescale(150, 150);
    houseIcon4 = wxBitmap(houseImage4);
    wxImage hotelImage(wxT("img/hotel.png"), wxBITMAP_TYPE_PNG);
    hotelImage.Rescale(100, 100);
    hotelIcon = wxBitmap(hotelImage);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* centerSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxVERTICAL);
    
    wxStaticText* nome = new wxStaticText(this, wxID_ANY, "nome giocatore: " + giocatore->getNome());
    saldo = new wxStaticText(this, wxID_ANY, "saldo giocatore: " + std::to_string(giocatore->getSaldo()));
    risultatolabel = new wxStaticText(this, wxID_ANY, "dado non lanciato");
    saldoBot = new wxStaticText(this, wxID_ANY, "saldo bot: " + std::to_string(bot->getSaldo()));

    wxButton* button = new wxButton(this, ID_COMPRABUTTON, "Compra proprietà");
    wxButton* lanciaDado = new wxButton(this, ID_LANCIADADOBUTTON, "Lancia i dadi");
    wxButton* passaTurno = new wxButton(this, ID_PASSABUTTON, "Passa");
    closeButton = new wxButton(this, ID_CLOSEBUTTON, "Chiudi");
    closeButton->Hide();
    buttonCompraCasa = new wxButton(this, ID_COMPRACASABUTTON, "Compra casa");
    wxButton* buttonCompraAlbergo = new wxButton(this, ID_COMPRAALBERGOBUTTON, "Compra albergo");
    
    tesseraInformativa = new wxStaticText(this, wxID_ANY, "Tessera corrente: Nessuna");
    wxBitmap gameOverBitmap(wxT("img/gameover.png"), wxBITMAP_TYPE_PNG);
    gameOverImage = new wxStaticBitmap(this, wxID_ANY, gameOverBitmap);
    gameOverImage->Hide();
    
    wxColour buttonColor(0x1E, 0x90, 0xFF);
    wxColour buttonTextColor(0xFF, 0xFF, 0xFF);
    wxColour buttonHoverColor(0x00, 0x7A, 0xCC);
    wxColour buttonBorderColor(0x00, 0x54, 0x89);
    
    auto setButtonStyle = [&](wxButton* btn) {
        btn->SetBackgroundColour(buttonColor);
        btn->SetForegroundColour(buttonTextColor);
        btn->SetWindowStyleFlag(wxBORDER_NONE);
        btn->SetBackgroundStyle(wxBG_STYLE_PAINT);
        
        btn->Bind(wxEVT_PAINT, [=](wxPaintEvent& event) {
            wxAutoBufferedPaintDC dc(btn);
            wxRect rect = btn->GetClientRect();
            
            dc.SetPen(wxPen(buttonBorderColor, 2));
            dc.SetBrush(wxBrush(buttonColor));
            dc.DrawRoundedRectangle(rect, 10);
            
            dc.SetTextForeground(buttonTextColor);
            dc.DrawLabel(btn->GetLabel(), rect, wxALIGN_CENTER);
        });
        
        btn->Bind(wxEVT_ENTER_WINDOW, [=](wxMouseEvent& event) {
            btn->SetBackgroundColour(buttonHoverColor);
            btn->Refresh();
        });
        
        btn->Bind(wxEVT_LEAVE_WINDOW, [=](wxMouseEvent& event) {
            btn->SetBackgroundColour(buttonColor);
            btn->Refresh();
        });
    };
    
    setButtonStyle(button);
    setButtonStyle(lanciaDado);
    setButtonStyle(buttonCompraCasa);
    setButtonStyle(closeButton);
    setButtonStyle(passaTurno);
    setButtonStyle(buttonCompraAlbergo);

    buttonSizer->Add(button, 0, wxALL | wxALIGN_CENTER, 5);
    buttonSizer->Add(lanciaDado, 0, wxALL | wxALIGN_CENTER, 5);
    buttonSizer->Add(buttonCompraCasa, 0, wxALL | wxALIGN_CENTER, 5);
    buttonSizer->Add(passaTurno, 0, wxALL | wxALIGN_CENTER, 5);
    buttonSizer->Add(closeButton, 0, wxALL | wxALIGN_CENTER, 5);
    buttonSizer->Add(buttonCompraAlbergo, 0, wxALL | wxALIGN_CENTER, 5);
    
    centerSizer->Add(buttonSizer, 0, wxALL | wxALIGN_CENTER, 5);
    
    
    wxColour centralTextColor(0x00, 0x00, 0x00);
    nome->SetForegroundColour(centralTextColor);
    saldo->SetForegroundColour(centralTextColor);
    saldoBot->SetForegroundColour(centralTextColor);
    risultatolabel->SetForegroundColour(centralTextColor);
    tesseraInformativa->SetForegroundColour(centralTextColor);

    centerSizer->Add(nome, 0, wxALL | wxALIGN_CENTER, 5);
    centerSizer->Add(saldo, 0, wxALL | wxALIGN_CENTER, 5);
    centerSizer->Add(saldoBot, 0, wxALL | wxALIGN_CENTER, 5);
    centerSizer->Add(risultatolabel, 0, wxALL | wxALIGN_CENTER, 5);
    centerSizer->Add(tesseraInformativa, 0, wxALL | wxALIGN_CENTER, 5);
    
    
    mainSizer->AddStretchSpacer();
    mainSizer->Add(centerSizer, 0, wxALL | wxALIGN_CENTER, 5);
    mainSizer->AddStretchSpacer();
    mainSizer->Add(gameOverImage, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    buttonCompraAlbergo->Hide();
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
    wxColour boardBackground(0xF2, 0xF2, 0xF2);
    wxColour tileBorder(0x33, 0x33, 0x33);
    wxColour normalTile(0xAD, 0xD8, 0xE6);
    wxColour opportunitaTile(0xFF, 0xD7, 0x00);
    wxColour inconvenientiTile(0xFF, 0x63, 0x47);
    wxColour prigioneTile(0xDD, 0xA0, 0xDD);
    wxColour infoBackground(0xA9, 0xA9, 0xA9);
    wxColour infoText(0x00, 0x00, 0x00);
    wxColour infoBoxBackground(0xFF, 0xFF, 0xFF);
    wxColour verdeTile(0, 255, 0); 
    wxColour rossoTile(255, 0, 0); 
    
    dc.SetBackground(wxBrush(boardBackground));
    dc.Clear();

    wxSize clientSize = this->GetClientSize();
    int rows = 9;
    int cols = 9;
    int cellWidth = clientSize.GetWidth() / cols;
    int cellHeight = clientSize.GetHeight() / rows;
    int index = 0;

    dc.SetPen(wxPen(tileBorder));

    for (const auto& pos : boardPositions)
    {
        if (index >= 32) {
            break;
        }

        int x = pos.second * cellWidth;
        int y = pos.first * cellHeight;

        std::shared_ptr<Tessera> c = tabellone->getTessera(index);
        if (c) {
            if (c->getTipo() == "Proprieta") {
                if (c->getProprietario() == giocatore->getNome()) {
                    dc.SetBrush(wxBrush(verdeTile));
                } else if (c->getProprietario() == bot->getNome()) {
                    dc.SetBrush(wxBrush(rossoTile));
                } else {
                    dc.SetBrush(wxBrush(normalTile));
                }
            } else if (c->getTipo() == "opportunita") {
                dc.SetBrush(wxBrush(opportunitaTile));
            } else if (c->getTipo() == "inconvenienti") {
                dc.SetBrush(wxBrush(inconvenientiTile));
            } else if (c->getTipo() == "prigione") {
                dc.SetBrush(wxBrush(prigioneTile));
            }
        } else {
            dc.SetBrush(wxBrush(normalTile));
        }

        dc.DrawRectangle(x, y, cellWidth, cellHeight);

        dc.SetTextForeground(infoText);
        wxString label = wxString::Format("R%dC%d", pos.first, pos.second);
        if (c) {
            label = c->getTitolo();
            if (index == 4) {
                label = "Opportunita";
            }
            if (index == 20) {
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

        dc.DrawBitmap(playerPawn, x + cellWidth / 2 - playerPawn.GetWidth() / 2, y + cellHeight / 2 - playerPawn.GetHeight() / 2, true);
    }
    if (botPosition < boardPositions.size()) {
        auto botPos = boardPositions[botPosition];
        int botX = botPos.second * cellWidth;
        int botY = botPos.first * cellHeight;

        dc.DrawBitmap(botPawn, botX + cellWidth / 2 - botPawn.GetWidth() / 2, botY + cellHeight / 2 - botPawn.GetHeight() / 2, true);
    }

     std::shared_ptr<Tessera> tesseraCorrente = tabellone->getTessera(currentPlayerPosition);
    if (tesseraCorrente && (tesseraCorrente->getTipo() == "opportunita" || tesseraCorrente->getTipo() == "inconvenienti")) {
        int infoBoxWidth = clientSize.GetWidth() * 0.3;
        int infoBoxHeight = clientSize.GetHeight() * 0.2;
        int infoBoxX = clientSize.GetWidth() - infoBoxWidth - 200;
        int infoBoxY = clientSize.GetHeight() - infoBoxHeight - 200;

        dc.SetBrush(wxBrush(infoBoxBackground));
        dc.DrawRectangle(infoBoxX, infoBoxY, infoBoxWidth, infoBoxHeight);

        dc.SetTextForeground(infoText);
        wxString infoLabel = "Tessera corrente: " + tesseraCorrente->getTitolo();

        if (tesseraCorrente->getTipo() == "opportunita") {
            Opportunita opportunitaCasuale = tabellone->getOpportunita();
            infoLabel += "\nTitolo: " + opportunitaCasuale.getTitolo();
            int guadagno = opportunitaCasuale.getImporto();
            infoLabel += "\nGuadagno: " + std::to_string(guadagno);
            infoLabel += "\nBonus: " + std::to_string(opportunitaCasuale.isBonus());
        } else if (tesseraCorrente->getTipo() == "inconvenienti") {
            Inconvenienti inconvenienteCasuale = tabellone->getInconveniente();
            infoLabel += "\nTitolo: " + inconvenienteCasuale.getTitolo();
            int spesa = inconvenienteCasuale.getImporto();
            infoLabel += "\nSpesa: " + std::to_string(spesa);
        }

        dc.DrawText(infoLabel, infoBoxX + 10, infoBoxY + 10);
        tesseraInformativa->SetLabel(infoLabel);
        tesseraInformativa->Show();
    } else {
        tesseraInformativa->Hide();
    }

    for (int i = 0; i < boardPositions.size(); ++i) {
        std::shared_ptr<Tessera> tessera = tabellone->getTessera(i);
        if (!tessera || tessera->getTipo() != "Proprieta") {
            continue;
        }

        Proprieta* proprieta = dynamic_cast<Proprieta*>(tessera.get());
        if (proprieta && proprieta->getNumeroCase() > 0) {
            int numCase = proprieta->getNumeroCase();
            wxBitmap* houseIcon = nullptr;
            wxBitmap* buildingIcon = nullptr;
              if (proprieta->hasAlbergo()) {
            buildingIcon = &hotelIcon;
        } else {
             switch (numCase) {
                case 1:
                    buildingIcon = &houseIcon1;
                    break;
                case 2:
                    buildingIcon = &houseIcon2;
                    break;
                case 3:
                    buildingIcon = &houseIcon3;
                    break;
                case 4:
                    buildingIcon = &houseIcon4;
                    break;
                default:
                    break;
            }
                }

            if (buildingIcon) {
            auto pos = boardPositions[i];
            int buildingX = pos.second * cellWidth + cellWidth / 2 - buildingIcon->GetWidth() / 2;
            int buildingY = (pos.first * cellHeight + cellHeight / 2 - buildingIcon->GetHeight() / 2) + 30;
            dc.DrawBitmap(*buildingIcon, buildingX, buildingY, true);
        }
        }
    }
}


void Gamepanel::compraProprieta(wxCommandEvent& event)
{
    std::shared_ptr tesseraCorrente = tabellone->getTessera(currentPlayerPosition);
    Proprieta* proprieta = dynamic_cast<Proprieta*>(tesseraCorrente.get());
    if (proprieta) {
        if (proprieta->getTitolo() == "START") {
            wxMessageBox("Non puoi comprare la proprietà", "Attento", wxOK | wxICON_ERROR);
            return;
        }
        if (proprieta->getProprietario() == giocatore->getNome()) {
            wxMessageBox("Sei già il proprietario di questa proprietà", "Attento", wxOK | wxICON_ERROR);
            return;
        }
        if (proprieta->getProprietario() != "banca") {
            wxMessageBox("Non puoi acquistare questa proprietà appartiene alla banca", "Attento", wxOK | wxICON_ERROR);
            return;
        }
        if (giocatore->getSaldo() < proprieta->getCosto()) {
            wxMessageBox("Il tuo saldo non è sufficiente per acquistare la proprietà", "Mi dispiace", wxOK | wxICON_ERROR);
            return;
        }
        giocatore->acquistaProprieta(*proprieta);
        saldo->SetLabel("saldo giocatore: " + std::to_string(giocatore->getSaldo()));
        Refresh();
    }
    fineTurnoGiocatore();
}

void Gamepanel::compraCasa(wxCommandEvent& event) {
    std::shared_ptr tesseraCorrente = tabellone->getTessera(currentPlayerPosition);
    Proprieta* proprieta = dynamic_cast<Proprieta*>(tesseraCorrente.get());
    if (proprieta) {
        switch (giocatore->acquistaCasa(*proprieta)) {
        case 0:
            wxMessageBox("Casa acquistata", "Complimenti", wxOK | wxICON_INFORMATION);
            housePositions.push_back(boardPositions[currentPlayerPosition]);

            if (proprieta->getNumeroCase() == 4) {
                buttonCompraAlbergo->Show();
                this->Layout();
            }
            break;
        case 1:
            wxMessageBox("Numero massimo di case raggiunto", "Attento", wxOK | wxICON_ERROR);
            return;
        case 2:
            wxMessageBox("Saldo insufficiente", "Attento", wxOK | wxICON_ERROR);
            break;
        case 3:
            wxMessageBox("Proprietario non corrisponde", "Attento", wxOK | wxICON_ERROR);
            break;
        }
        Refresh();
    }
    fineTurnoGiocatore();
}

void Gamepanel::lanciaDado(wxCommandEvent& event)
{
    checkGameOver();
    int risultato = dado->lanciaDadi();
    risultatolabel->SetLabel("esito lancio: " + std::to_string(risultato));
    FindWindowById(ID_COMPRABUTTON)->Disable();
    FindWindowById(ID_LANCIADADOBUTTON)->Disable();
    FindWindowById(ID_COMPRACASABUTTON)->Disable();

    m_moveSteps = risultato;
    m_isBotTurn = false;
    m_timer->Start(200);
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

void Gamepanel::eseguiTurnoBot()
{
    int risultato = dado->lanciaDadi();
    m_moveSteps = risultato;
    m_timer->Start(200);
}

void Gamepanel::turnoBot()
{
    std::shared_ptr<Tessera> tesseraCorrente = tabellone->getTessera(bot->getPosizione());
    if (!tesseraCorrente) {
        wxLogDebug("tesseraCorrente è nullptr");
        return;
    }

    Proprieta* proprieta = dynamic_cast<Proprieta*>(tesseraCorrente.get());
    if (!proprieta) {
        wxLogDebug("dynamic_cast fallito, tessera non è Proprieta");
        return;
    }

    std::cout << "TURNO BOT\n";
    std::cout << "SALDO " << bot->getSaldo() << "\n";
    std::cout << "tessera " << proprieta->getTitolo() << "\n";

    if (proprieta->getProprietario() == "banca") {
        if (proprieta->getTitolo() == "START") {
            return;
        }
        if (proprieta->getTipo() == "opportunita") {
            return;
        }
        if (proprieta->getTipo() == "inconvenienti") {
            return;
        }
        if (bot->getSaldo() >= proprieta->getCosto() && proprieta->getProprietario() == "banca") {
            std::cout << "BOT ACQUISTA PROPRIETA\n";
            bot->acquistaProprieta(*proprieta);
        } else if((bot->getSaldo() >= proprieta->getCosto()) && proprieta->getProprietario() == bot->getNome()) {
            std::cout << "BOT ACQUISTA casa";
            bot->acquistaCasa(*proprieta);
            housePositions.push_back(boardPositions[botPosition]); }
    } else if ((proprieta->getProprietario() != bot->getNome()) && (proprieta->getProprietario() !="banca")) {
        int affitto = proprieta->calcolaPagamento();
        std::cout << " affitto calcolato " << affitto <<"\n";
        bot->pagaAffitto(*proprieta);
        giocatore->modificaSaldo(affitto);
        std::cout<<"bot paga"<<"\n";
        saldo->SetLabel("saldo giocatore: " + std::to_string(giocatore->getSaldo()));
        // bot->pagaAffitto(*tabellone->getGiocatore(proprieta->getProprietario()), affitto);
    }
    for (Proprieta& prop : bot->getProprietaPossedute()) {
        if (bot->getSaldo() >= prop.getCostoCasa() && prop.getNumeroCase() < 4) {
            bot->acquistaCasa(prop);
        }
    }

    saldoBot->SetLabel("saldo bot: " + std::to_string(bot->getSaldo()));
    controllavittoria();
    Refresh();
    Update();
}

void Gamepanel::fineTurnoGiocatore()
{
    aggiornaBottoni(false); 
    
    if (m_isBotTurn) {
        if (botInPrigione) {
            turniInPrigioneBot--;
            if (turniInPrigioneBot <= 0) {
                botInPrigione = false;
            }
        }
    } else {
        if (giocatoreInPrigione) {
            turniInPrigioneGiocatore--;
            if (turniInPrigioneGiocatore <= 0) {
                giocatoreInPrigione = false;
            }
        }
    }

    m_isBotTurn = !m_isBotTurn;
    if (m_isBotTurn) {
        eseguiTurnoBot();
    } else {
        aggiornaBottoni(true);
        FindWindowById(ID_COMPRABUTTON)->Enable();
        FindWindowById(ID_LANCIADADOBUTTON)->Enable();
        FindWindowById(ID_COMPRACASABUTTON)->Enable();
    }
}

void Gamepanel::onTimer(wxTimerEvent& event)
{
    if (m_isBotTurn) {
        if (m_moveSteps > 0) {
            bot->muoviGiocatore(1);
            botPosition = bot->getPosizione();
            m_moveSteps--;
        }
        
        if (m_moveSteps <= 0) {
            m_timer->Stop();

            std::shared_ptr<Tessera> tesseraCorrente = tabellone->getTessera(botPosition);
            if (tesseraCorrente && tesseraCorrente->getTipo() == "prigione") {
                botInPrigione = true;
                turniInPrigioneBot = 2;
                wxLogDebug("Il bot è finito in prigione per 2 turni!");
                fineTurnoGiocatore();
                return;
            }

            turnoBot();
            aggiornaBottoni(true);
        }
    } else {
        if (m_moveSteps > 0) {
            giocatore->muoviGiocatore(1);
            currentPlayerPosition = giocatore->getPosizione();
            m_moveSteps--;
        }
        
        if (m_moveSteps <= 0) {
            m_timer->Stop();
            std::shared_ptr<Tessera> tesseraCorrente = tabellone->getTessera(currentPlayerPosition);
            if (tesseraCorrente && tesseraCorrente->getTipo() == "prigione") {
                giocatoreInPrigione = true;
                turniInPrigioneGiocatore = 2;
                wxMessageBox("Sei finito in prigione per 2 turni!", "Attento", wxOK | wxICON_INFORMATION);
                fineTurnoGiocatore();
                return;
            }

            FindWindowById(ID_COMPRABUTTON)->Enable();
            FindWindowById(ID_LANCIADADOBUTTON)->Enable();
            FindWindowById(ID_COMPRACASABUTTON)->Enable();

            if (tesseraCorrente) {
                Proprieta* proprieta = dynamic_cast<Proprieta*>(tesseraCorrente.get());
                if (proprieta && proprieta->getProprietario() == bot->getNome()) {
                    giocatore->pagaAffitto(*proprieta);
                    bot->modificaSaldo(proprieta->calcolaPagamento());
                    saldo->SetLabel("saldo giocatore: " + std::to_string(giocatore->getSaldo()));
                }
            }
        }
    }

    Refresh();
    Update();
}

void Gamepanel::onClose(wxCommandEvent& event)
{
    this->GetParent()->Close();
}

void Gamepanel::passa(wxCommandEvent& event)
{
   fineTurnoGiocatore();
}

void Gamepanel::controllavittoria()
{
    if (bot->getSaldo() < 0)
    {
        saldo->Hide();
        risultatolabel->Hide();
        tesseraInformativa->Hide();
        FindWindowById(ID_COMPRABUTTON)->Hide();
        FindWindowById(ID_LANCIADADOBUTTON)->Hide();
        FindWindowById(ID_COMPRACASABUTTON)->Hide();
        gameOverImage->Hide();
        closeButton->Show();

        wxBitmap winBitmap(wxT("img/win.png"), wxBITMAP_TYPE_PNG);
        wxStaticBitmap* winImage = new wxStaticBitmap(this, wxID_ANY, winBitmap);
        this->GetSizer()->Add(winImage, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
        this->Layout();
        Refresh();
    }
}

void Gamepanel::compraAlbergo(wxCommandEvent& event)
{
    std::shared_ptr tesseraCorrente = tabellone->getTessera(currentPlayerPosition);
    Proprieta* proprieta = dynamic_cast<Proprieta*>(tesseraCorrente.get());
    
    if (proprieta) {
        if (proprieta->hasAlbergo()) {
            wxMessageBox("Questa proprietà ha già un albergo!", "Attento", wxOK | wxICON_ERROR);
            return;
        }

        if (proprieta->getNumeroCase() == 4) {
            if (giocatore->getSaldo() >= proprieta->getCostoAlbergo()) {
                giocatore->modificaSaldo(-proprieta->getCostoAlbergo());
                proprieta->costruisciAlbergo();
                wxMessageBox("Albergo acquistato", "Complimenti", wxOK | wxICON_INFORMATION);
            } else {
                wxMessageBox("Saldo insufficiente", "Attento", wxOK | wxICON_ERROR);
            }
        } else {
            wxMessageBox("Devi prima avere 4 case", "Attento", wxOK | wxICON_ERROR);
        }

        Refresh();
    }

    fineTurnoGiocatore();
}

void Gamepanel::aggiornaBottoni(bool turnoGiocatore) {
    if (turnoGiocatore) {
        FindWindowById(ID_COMPRABUTTON)->Show();
        FindWindowById(ID_LANCIADADOBUTTON)->Show();
        FindWindowById(ID_COMPRACASABUTTON)->Show();
        FindWindowById(ID_PASSABUTTON)->Show();
        std::shared_ptr<Tessera> tesseraCorrente = tabellone->getTessera(currentPlayerPosition);
        Proprieta* proprieta = dynamic_cast<Proprieta*>(tesseraCorrente.get());
        if (proprieta && proprieta->getNumeroCase() == 4 && !proprieta->hasAlbergo()) {
            FindWindowById(ID_COMPRAALBERGOBUTTON)->Show();
        } else {
            FindWindowById(ID_COMPRAALBERGOBUTTON)->Hide();
        }
    } else {
        FindWindowById(ID_COMPRABUTTON)->Hide();
        FindWindowById(ID_LANCIADADOBUTTON)->Hide();
        FindWindowById(ID_COMPRACASABUTTON)->Hide();
        FindWindowById(ID_PASSABUTTON)->Hide();
        FindWindowById(ID_COMPRAALBERGOBUTTON)->Hide();
    }

    this->Layout();
}



void Gamepanel::controllaPrigione()
{
    std::shared_ptr<Tessera> tesseraCorrente = tabellone->getTessera(currentPlayerPosition);
    if (tesseraCorrente && tesseraCorrente->getTipo() == "prigione") {
        giocatoreInPrigione = true;
        turniInPrigioneGiocatore = 2;
        wxMessageBox("Sei finito in prigione per 2 turni!", "Attento", wxOK | wxICON_INFORMATION);
        fineTurnoGiocatore();
    }
}