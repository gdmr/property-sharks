#include "playerpanel.hpp"
#include "giocatore.hpp"
#include <wx/mstream.h>

wxDEFINE_EVENT(wxEVT_PLAYER_SUBMIT, wxCommandEvent);

wxBEGIN_EVENT_TABLE(Playerpanel, wxPanel)
    EVT_BUTTON(wxID_OK, Playerpanel::OnSubmit)
    EVT_BUTTON(wxID_BACKWARD, Playerpanel::OnPrevPawn)
    EVT_BUTTON(wxID_FORWARD, Playerpanel::OnNextPawn)
wxEND_EVENT_TABLE()

Playerpanel::Playerpanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY), textCtrl(nullptr), pawnDisplay(nullptr), currentPawnIndex(0)
{
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* label = new wxStaticText(this, wxID_ANY, "Inserisci nome del giocatore:");
    sizer->Add(label, 0, wxALL, 5);

    textCtrl = new wxTextCtrl(this, wxID_ANY);
    sizer->Add(textCtrl, 0, wxALL | wxEXPAND, 5);

    wxStaticText* choiceLabel = new wxStaticText(this, wxID_ANY, "Scegli una pedina:");
    sizer->Add(choiceLabel, 0, wxALL, 5);

    wxBoxSizer* pawnSizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton* prevButton = new wxButton(this, wxID_BACKWARD, "<--");
    pawnSizer->Add(prevButton, 0, wxALL, 5);

    wxImage pawn1Image("pedine/s1.png", wxBITMAP_TYPE_PNG);
    wxImage pawn2Image("pedine/s2.png", wxBITMAP_TYPE_PNG);
    wxImage pawn3Image("pedine/s3.png", wxBITMAP_TYPE_PNG);

    int newWidth = 150;
    int newHeight = 150;

    if (pawn1Image.IsOk()) pawns.push_back(wxBitmap(pawn1Image.Scale(newWidth, newHeight)));
    if (pawn2Image.IsOk()) pawns.push_back(wxBitmap(pawn2Image.Scale(newWidth, newHeight)));
    if (pawn3Image.IsOk()) pawns.push_back(wxBitmap(pawn3Image.Scale(newWidth, newHeight)));

    if (pawns.empty()) {
        wxLogError("Caricamento immagine non riuscito");
    } else {
        pawnDisplay = new wxStaticBitmap(this, wxID_ANY, pawns[currentPawnIndex]);
        pawnSizer->Add(pawnDisplay, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    }

    wxButton* nextButton = new wxButton(this, wxID_FORWARD, "-->");
    pawnSizer->Add(nextButton, 0, wxALL, 5);

    sizer->Add(pawnSizer, 0, wxALL | wxALIGN_CENTER, 5);

    wxButton* button = new wxButton(this, wxID_OK, "Inizia il gioco");
    sizer->Add(button, 0, wxALL | wxALIGN_CENTER, 5);

    SetSizer(sizer);
}

void Playerpanel::OnSubmit(wxCommandEvent& event)
{
    wxString userInput = textCtrl->GetValue();
    wxString selectedPawn = wxString::Format("Pedina %d", currentPawnIndex + 1); // Indice della pedina
    std::cout << "User input: " << userInput.ToStdString() << ", Pedina scelta: " << selectedPawn.ToStdString() << std::endl;

    wxCommandEvent submitEvent(wxEVT_PLAYER_SUBMIT);
    submitEvent.SetString(userInput + " - " + selectedPawn);
    wxPostEvent(GetParent(), submitEvent);
}

void Playerpanel::OnPrevPawn(wxCommandEvent& event)
{
    if (!pawns.empty()) {
        currentPawnIndex = (currentPawnIndex - 1 + pawns.size()) % pawns.size();
        pawnDisplay->SetBitmap(pawns[currentPawnIndex]);
        Layout();
    }
}

void Playerpanel::OnNextPawn(wxCommandEvent& event)
{
    if (!pawns.empty()) {
        currentPawnIndex = (currentPawnIndex + 1) % pawns.size();
        pawnDisplay->SetBitmap(pawns[currentPawnIndex]);
        Layout();
    }
}