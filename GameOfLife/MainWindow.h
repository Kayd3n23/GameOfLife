#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "wx/wx.h"
#include "DrawingPanel.h"
#include "GameSettings.h"
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
    void OnMenuSettings(wxCommandEvent& event);
    void OnToggleShowNeighborCount(wxCommandEvent& event);
    void OnRandomize(wxCommandEvent& event);            // Event handler for randomize
    void OnRandomizeWithSeed(wxCommandEvent& event);    // Event handler for randomize with seed
    void RandomizeGrid(int seed);                       // Method to randomize the grid

    int GetLivingNeighbors(int row, int col);
    void NextGeneration();
    void OnTimer(wxTimerEvent& event);

private:
    DrawingPanel* drawingPanel;
    wxBoxSizer* sizer;
    wxToolBar* toolBar;
    wxMenuBar* menuBar;
    wxMenu* optionsMenu;
    wxMenu* viewMenu;
    std::vector<std::vector<bool>> gameBoard;
    std::vector<std::vector<int>> neighborCounts;

    wxStatusBar* statusBar;
    int generationCount = 0;
    int livingCellsCount = 0;

    wxTimer* timer;
    Settings settings;

    wxDECLARE_EVENT_TABLE();
};

#endif // MAINWINDOW_H
