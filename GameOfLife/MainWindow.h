#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "wx/wx.h"
#include "DrawingPanel.h"

class MainWindow : public wxFrame
{
public:
    MainWindow();
    ~MainWindow();

private:
    DrawingPanel* drawingPanel;
    wxBoxSizer* sizer;

    void OnSizeChange(wxSizeEvent& event);

    wxDECLARE_EVENT_TABLE();
};

#endif // MAINWINDOW_H
