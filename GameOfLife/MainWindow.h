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
    void OnNew(wxCommandEvent& event);
    void OnOpen(wxCommandEvent& event);
    void OnImport(wxCommandEvent& event); // New event handler for importing
    void OnSave(wxCommandEvent& event);
    void OnSaveAs(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnFinite(wxCommandEvent& event);
    void OnToroidal(wxCommandEvent& event);
    void OnResetSettings(wxCommandEvent& event);
    void RandomizeGrid(int seed);
    void SaveToFile(const wxString& filename);
    void LoadFromFile(const wxString& filename);
    void ImportFromFile(const wxString& filename); // New method for importing

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
    wxMenuItem* finiteMenuItem;
    wxMenuItem* toroidalMenuItem;
    std::vector<std::vector<bool>> gameBoard;
    std::vector<std::vector<int>> neighborCounts;

    wxStatusBar* statusBar;
    int generationCount = 0;
    int livingCellsCount = 0;

    wxTimer* timer;
    Settings settings;
    wxString currentFileName;

    wxDECLARE_EVENT_TABLE();
};

#endif // MAINWINDOW_H
