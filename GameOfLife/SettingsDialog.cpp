#include "SettingsDialog.h"

wxBEGIN_EVENT_TABLE(SettingsDialog, wxDialog)
EVT_BUTTON(wxID_OK, SettingsDialog::OnOK)
EVT_BUTTON(wxID_CANCEL, SettingsDialog::OnCancel)
wxEND_EVENT_TABLE()

SettingsDialog::SettingsDialog(wxWindow* parent, Settings* settings)
    : wxDialog(parent, wxID_ANY, "Settings", wxDefaultPosition, wxDefaultSize), settings(settings)
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(mainSizer);

    // Grid Size
    wxBoxSizer* gridSizeSizer = new wxBoxSizer(wxHORIZONTAL);
    gridSizeSizer->Add(new wxStaticText(this, wxID_ANY, "Grid Size: "), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    gridSizeCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(60, -1));
    gridSizeSizer->Add(gridSizeCtrl, 0, wxALIGN_CENTER_VERTICAL);
    mainSizer->Add(gridSizeSizer, 0, wxEXPAND | wxALL, 5);

    // Interval
    wxBoxSizer* intervalSizer = new wxBoxSizer(wxHORIZONTAL);
    intervalSizer->Add(new wxStaticText(this, wxID_ANY, "Interval (ms): "), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    intervalCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(60, -1));
    intervalSizer->Add(intervalCtrl, 0, wxALIGN_CENTER_VERTICAL);
    mainSizer->Add(intervalSizer, 0, wxEXPAND | wxALL, 5);

    // Living Cell Color
    wxBoxSizer* livingCellColorSizer = new wxBoxSizer(wxHORIZONTAL);
    livingCellColorSizer->Add(new wxStaticText(this, wxID_ANY, "Living Cell Color: "), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    livingCellColorPicker = new wxColourPickerCtrl(this, wxID_ANY, wxColour(128, 128, 128, 255));
    livingCellColorSizer->Add(livingCellColorPicker, 0, wxALIGN_CENTER_VERTICAL);
    mainSizer->Add(livingCellColorSizer, 0, wxEXPAND | wxALL, 5);

    // Dead Cell Color
    wxBoxSizer* deadCellColorSizer = new wxBoxSizer(wxHORIZONTAL);
    deadCellColorSizer->Add(new wxStaticText(this, wxID_ANY, "Dead Cell Color: "), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    deadCellColorPicker = new wxColourPickerCtrl(this, wxID_ANY, wxColour(255, 255, 255, 255));
    deadCellColorSizer->Add(deadCellColorPicker, 0, wxALIGN_CENTER_VERTICAL);
    mainSizer->Add(deadCellColorSizer, 0, wxEXPAND | wxALL, 5);

    // Button Sizer
    wxSizer* buttonSizer = CreateButtonSizer(wxOK | wxCANCEL);
    mainSizer->Add(buttonSizer, 0, wxEXPAND | wxALL, 5);

    // Set initial values from settings
    gridSizeCtrl->SetValue(settings->gridSize);
    intervalCtrl->SetValue(settings->interval);
    livingCellColorPicker->SetColour(settings->GetLivingCellColor());
    deadCellColorPicker->SetColour(settings->GetDeadCellColor());
}

void SettingsDialog::OnOK(wxCommandEvent& event)
{
    // Update settings from controls
    settings->gridSize = gridSizeCtrl->GetValue();
    settings->interval = intervalCtrl->GetValue();
    settings->SetLivingCellColor(livingCellColorPicker->GetColour());
    settings->SetDeadCellColor(deadCellColorPicker->GetColour());

    EndModal(wxID_OK);
}

void SettingsDialog::OnCancel(wxCommandEvent& event)
{
    EndModal(wxID_CANCEL);
}
