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
    void OnRandomize(wxCommandEvent& event);
    void OnRandomizeWithSeed(wxCommandEvent& event);
    void OnNew(wxCommandEvent& event);       // Event handler for New
    void OnOpen(wxCommandEvent& event);      // Event handler for Open
    void OnSave(wxCommandEvent& event);      // Event handler for Save
    void OnSaveAs(wxCommandEvent& event);    // Event handler for Save As
    void OnExit(wxCommandEvent& event);      // Event handler for Exit
    void RandomizeGrid(int seed);
    void SaveToFile(const wxString& filename);
    void LoadFromFile(const wxString& filename);

    int GetLivingNeighbors(int row, int col);
    void NextGeneration();
    void OnTimer(wxTimerEvent& event);

private:
    DrawingPanel* drawingPanel;
    wxBoxSizer* sizer;
    wxToolBar* toolBar;
    wxMenuBar* menuBar;
    wxMenu* fileMenu;
    wxMenu* optionsMenu;
    wxMenu* viewMenu;
    std::vector<std::vector<bool>> gameBoard;
    std::vector<std::vector<int>> neighborCounts;

    wxStatusBar* statusBar;
    int generationCount = 0;
    int livingCellsCount = 0;

    wxTimer* timer;
    Settings settings;
    wxString currentFileName;  // Current file name for Save and Save As

    wxDECLARE_EVENT_TABLE();
};

#endif // MAINWINDOW_H
