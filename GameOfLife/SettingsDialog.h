#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "wx/wx.h"
#include "wx/spinctrl.h"
#include "wx/clrpicker.h"
#include "GameSettings.h"

class SettingsDialog : public wxDialog
{
public:
    SettingsDialog(wxWindow* parent, Settings* settings);

private:
    void OnOK(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);

    wxSpinCtrl* gridSizeCtrl;
    wxSpinCtrl* intervalCtrl;
    wxColourPickerCtrl* livingCellColorPicker;
    wxColourPickerCtrl* deadCellColorPicker;

    Settings* settings;

    wxDECLARE_EVENT_TABLE();
};

#endif // SETTINGSDIALOG_H
