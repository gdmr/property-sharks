#include "GamePanel.hpp"
#include <wx/dcclient.h>
#include <wx/log.h>

wxBEGIN_EVENT_TABLE(GamePanel, wxPanel)
    EVT_PAINT(GamePanel::OnPaint)
wxEND_EVENT_TABLE()

GamePanel::GamePanel(wxWindow* parent, Giocatore* giocatore) : wxPanel(parent, wxID_ANY), giocatore(giocatore)
{
wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
wxStaticText* label = new wxStaticText(this, wxID_ANY, "nome giocatore: " + giocatore->getNome());
topSizer->AddStretchSpacer();
topSizer->Add(label, 0, wxALL, 5);
mainSizer->Add(topSizer, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
this->SetSizer(mainSizer);
}

void GamePanel::OnPaint(wxPaintEvent& event)
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