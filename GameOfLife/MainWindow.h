// MainWindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "wx/wx.h"
#include "DrawingPanel.h"
#include <vector>

class MainWindow : public wxFrame
{
public:
    MainWindow();
    ~MainWindow();

private:
    DrawingPanel* drawingPanel;
    wxBoxSizer* sizer;
    int gridSize = 15; // Default grid size
    std::vector<std::vector<bool>> gameBoard;

    void InitializeGrid(); // Method to initialize the grid
    void OnSizeChange(wxSizeEvent& event);

    wxDECLARE_EVENT_TABLE();
};

#endif // MAINWINDOW_H
