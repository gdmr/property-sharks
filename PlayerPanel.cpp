#include "PlayerPanel.hpp"
#include "giocatore.hpp"

wxDEFINE_EVENT(wxEVT_PLAYER_SUBMIT, wxCommandEvent);

wxBEGIN_EVENT_TABLE(PlayerPanel, wxPanel)
    EVT_BUTTON(wxID_OK, PlayerPanel::OnSubmit)
wxEND_EVENT_TABLE()

PlayerPanel::PlayerPanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY), textCtrl(nullptr)
{
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* label = new wxStaticText(this, wxID_ANY, "Inserisci nome del giocatore:");
    sizer->Add(label, 0, wxALL, 5);

    textCtrl = new wxTextCtrl(this, wxID_ANY);
    sizer->Add(textCtrl, 0, wxALL | wxEXPAND, 5);

    wxButton* button = new wxButton(this, wxID_OK, "Inizia il gioco");
    sizer->Add(button, 0, wxALL | wxALIGN_CENTER, 5);

    SetSizer(sizer);
}

void PlayerPanel::OnSubmit(wxCommandEvent& event)
{
    wxString userInput = textCtrl->GetValue();
    std::cout << "User input: " << userInput.ToStdString() << std::endl;

    wxCommandEvent submitEvent(wxEVT_PLAYER_SUBMIT);
    submitEvent.SetString(userInput);
    wxPostEvent(GetParent(), submitEvent);
}