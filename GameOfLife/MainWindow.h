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
    void OnPlay(wxCommandEvent& event);
    void OnPause(wxCommandEvent& event);
    void OnNext(wxCommandEvent& event);
    void OnClear(wxCommandEvent& event);
    int GetLivingNeighbors(int row, int col);
    void NextGeneration();  // New method for calculating next generation

private:
    DrawingPanel* drawingPanel;
    wxBoxSizer* sizer;
    wxToolBar* toolBar;
    std::vector<std::vector<bool>> gameBoard;
    int gridSize = 15;

    wxStatusBar* statusBar;
    int generationCount = 0;
    int livingCellsCount = 0;

    wxDECLARE_EVENT_TABLE();
};

#endif // MAINWINDOW_H
