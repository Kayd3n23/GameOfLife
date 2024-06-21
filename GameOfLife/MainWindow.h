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
    ~MainWindow();  // Destructor declaration

    void OnSizeChange(wxSizeEvent& event);
    void InitializeGrid();
    void UpdateStatusBar();
    void OnPlay(wxCommandEvent& event);
    void OnPause(wxCommandEvent& event);
    void OnNext(wxCommandEvent& event);
    void OnClear(wxCommandEvent& event);
    void OnSettings(wxCommandEvent& event); // New method for settings dialog
    int GetLivingNeighbors(int row, int col);
    void NextGeneration();
    void OnTimer(wxTimerEvent& event);

private:
    DrawingPanel* drawingPanel;
    wxBoxSizer* sizer;
    wxToolBar* toolBar;
    std::vector<std::vector<bool>> gameBoard;

    wxStatusBar* statusBar;
    int generationCount = 0;
    int livingCellsCount = 0;

    wxTimer* timer;
    Settings settings;  // Settings object

    wxDECLARE_EVENT_TABLE();
};

#endif // MAINWINDOW_H
