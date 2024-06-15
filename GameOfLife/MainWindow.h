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

    void OnSizeChange(wxSizeEvent& event);
    void InitializeGrid();
    void UpdateStatusBar();

private:
    DrawingPanel* drawingPanel;
    wxBoxSizer* sizer;
    std::vector<std::vector<bool>> gameBoard;
    int gridSize = 15;

    wxStatusBar* statusBar;
    int generationCount = 0;
    int livingCellsCount = 0;

    wxDECLARE_EVENT_TABLE();
};

#endif // MAINWINDOW_H
