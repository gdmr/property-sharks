#include "gamepanel.hpp"
#include <wx/dcclient.h>
#include <wx/log.h>

wxBEGIN_EVENT_TABLE(Gamepanel, wxPanel)
    EVT_PAINT(Gamepanel::OnPaint)
    EVT_BUTTON(wxID_OK, Gamepanel::onSubmit)
wxEND_EVENT_TABLE()

Gamepanel::Gamepanel(wxWindow* parent, Giocatore* giocatore) : wxPanel(parent, wxID_ANY), giocatore(giocatore)
{

// Creare il sizer verticale principale
wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

// Creare un sizer orizzontale per contenere i testi
wxBoxSizer* rightAlignedSizer = new wxBoxSizer(wxHORIZONTAL);

// Creare un sizer verticale per posizionare i testi uno sotto l'altro
wxBoxSizer* textSizer = new wxBoxSizer(wxVERTICAL);

// Creare i testi statici per nome e saldo
wxStaticText* nome = new wxStaticText(this, wxID_ANY, "nome giocatore: " + giocatore->getNome());
 saldo = new wxStaticText(this, wxID_ANY, "saldo giocatore: " + std::to_string(giocatore->getSaldo()));
 wxButton* button = new wxButton(this, wxID_OK, "Compra");
textSizer->Add(button, 0, wxALL | wxALIGN_CENTER, 5);

// Aggiungere i testi al sizer verticale
textSizer->Add(nome, 0, wxALL, 5);
textSizer->Add(saldo, 0, wxALL, 5);

// Aggiungere una porzione espandibile per spingere i testi a destra
rightAlignedSizer->AddStretchSpacer();
rightAlignedSizer->Add(textSizer, 0, wxALL, 5);

// Aggiungere il sizer orizzontale al sizer verticale principale
mainSizer->Add(rightAlignedSizer, 0, wxEXPAND | wxALL, 10);

// Impostare il sizer principale per il pannello o la finestra
this->SetSizer(mainSizer);

// Aggiornare il layout
this->Layout();
}

void Gamepanel::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    dc.SetBrush(*wxWHITE_BRUSH);
    dc.SetPen(*wxBLACK_PEN);

    int rows = 10;
    int cols = 15;
    int cellSize = 70;

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            if (row == 0 || row == rows - 1 || col == 0 || col == cols - 1)
            {
                int x = col * cellSize;
                int y = row * cellSize;
                dc.DrawRectangle(x, y, cellSize, cellSize);
            }
        }
    }
}

void Gamepanel::onSubmit(wxCommandEvent& event)
{
    giocatore->modificaSaldo(100);
    saldo->SetLabel("saldo giocatore: " + std::to_string(giocatore->getSaldo()));
    this->Layout();
}