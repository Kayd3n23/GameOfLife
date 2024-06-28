#include "MainWindow.h"
#include "SettingsDialog.h"
#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm"
#include <ctime>
#include <cstdlib>
#include <wx/numdlg.h>
#include <wx/filedlg.h>
#include <wx/textfile.h>

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::OnSizeChange)
EVT_MENU(10001, MainWindow::OnPlay)
EVT_MENU(10002, MainWindow::OnPause)
EVT_MENU(10003, MainWindow::OnNext)
EVT_MENU(10004, MainWindow::OnClear)
EVT_MENU(10006, MainWindow::OnMenuSettings)
EVT_MENU(10007, MainWindow::OnToggleShowNeighborCount)
EVT_MENU(10008, MainWindow::OnRandomize)
EVT_MENU(10009, MainWindow::OnRandomizeWithSeed)
EVT_MENU(10010, MainWindow::OnSave)
EVT_MENU(10011, MainWindow::OnOpen)
EVT_MENU(10012, MainWindow::OnNew)
EVT_MENU(10013, MainWindow::OnOpen)
EVT_MENU(10014, MainWindow::OnSave)
EVT_MENU(10015, MainWindow::OnSaveAs)
EVT_MENU(10016, MainWindow::OnExit)
EVT_MENU(10017, MainWindow::OnFinite)
EVT_MENU(10018, MainWindow::OnToroidal)
EVT_MENU(10019, MainWindow::OnResetSettings) // New event for resetting settings
EVT_TIMER(10005, MainWindow::OnTimer)
wxEND_EVENT_TABLE()

MainWindow::MainWindow()
    : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0, 0), wxSize(400, 400))
{
    settings.Load();

    sizer = new wxBoxSizer(wxVERTICAL);
    drawingPanel = new DrawingPanel(this, gameBoard, neighborCounts);
    drawingPanel->SetSettings(&settings);
    sizer->Add(drawingPanel, 1, wxEXPAND | wxALL);

    statusBar = CreateStatusBar();
    UpdateStatusBar();

    toolBar = CreateToolBar();

    wxBitmap playIcon(play_xpm);
    wxBitmap pauseIcon(pause_xpm);
    wxBitmap nextIcon(next_xpm);
    wxBitmap clearIcon(trash_xpm);

    toolBar->AddTool(10001, "Play", playIcon);
    toolBar->AddTool(10002, "Pause", pauseIcon);
    toolBar->AddTool(10003, "Next", nextIcon);
    toolBar->AddTool(10004, "Clear", clearIcon);

    toolBar->Realize();

    // Create the menu bar
    menuBar = new wxMenuBar();

    // Create the file menu
    fileMenu = new wxMenu();
    fileMenu->Append(10012, "New");
    fileMenu->Append(10013, "Open");
    fileMenu->Append(10014, "Save");
    fileMenu->Append(10015, "Save As");
    fileMenu->Append(10016, "Exit");

    // Create the options menu
    optionsMenu = new wxMenu();
    optionsMenu->Append(10006, "Settings");
    optionsMenu->Append(10008, "Randomize");
    optionsMenu->Append(10009, "Randomize with Seed");
    optionsMenu->Append(10019, "Reset Settings"); // Add Reset Settings option

    // Create the view menu
    viewMenu = new wxMenu();
    finiteMenuItem = new wxMenuItem(viewMenu, 10017, "Finite", "", wxITEM_CHECK);
    toroidalMenuItem = new wxMenuItem(viewMenu, 10018, "Toroidal", "", wxITEM_CHECK);
    finiteMenuItem->SetCheckable(true);
    toroidalMenuItem->SetCheckable(true);
    viewMenu->Append(finiteMenuItem);
    viewMenu->Append(toroidalMenuItem);
    finiteMenuItem->Check(settings.universeType == UniverseType::Finite);
    toroidalMenuItem->Check(settings.universeType == UniverseType::Toroidal);

    viewMenu->AppendCheckItem(10007, "Show Neighbor Count");

    // Add the file, options, and view menus to the menu bar
    menuBar->Append(fileMenu, "File");
    menuBar->Append(optionsMenu, "Options");
    menuBar->Append(viewMenu, "View");

    // Set the menu bar
    SetMenuBar(menuBar);

    this->SetSizer(sizer);
    this->Layout();

    InitializeGrid();
    viewMenu->Check(10007, settings.showNeighborCount);

    timer = new wxTimer(this, 10005);
}

MainWindow::~MainWindow()
{
    if (timer)
    {
        timer->Stop();
        delete timer;
    }
}

void MainWindow::OnMenuSettings(wxCommandEvent& event)
{
    Settings oldSettings = settings;

    SettingsDialog dlg(this, &settings);
    if (dlg.ShowModal() == wxID_OK)
    {
        InitializeGrid();
        UpdateStatusBar();
        drawingPanel->Refresh();
        settings.Save();
    }
    else
    {
        settings = oldSettings;
    }
}

void MainWindow::OnToggleShowNeighborCount(wxCommandEvent& event)
{
    settings.showNeighborCount = !settings.showNeighborCount;
    settings.Save();
    drawingPanel->Refresh();
}

void MainWindow::OnRandomize(wxCommandEvent& event)
{
    RandomizeGrid(static_cast<int>(time(nullptr)));
}

void MainWindow::OnRandomizeWithSeed(wxCommandEvent& event)
{
    long seed = wxGetNumberFromUser("Enter a seed value:", "Seed:", "Randomize with Seed", 0, 0, LONG_MAX, this);
    if (seed != -1) // If user did not cancel
    {
        RandomizeGrid(static_cast<int>(seed));
    }
}

void MainWindow::RandomizeGrid(int seed)
{
    srand(seed);

    for (int row = 0; row < settings.gridSize; ++row)
    {
        for (int col = 0; col < settings.gridSize; ++col)
        {
            gameBoard[row][col] = (rand() % 100 < 50); // 50% chance of being alive
        }
    }

    generationCount = 0;
    UpdateStatusBar();
    drawingPanel->Refresh();
}

void MainWindow::OnSave(wxCommandEvent& event)
{
    if (currentFileName.IsEmpty())
    {
        OnSaveAs(event);
    }
    else
    {
        SaveToFile(currentFileName);
    }
}

void MainWindow::OnSaveAs(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, _("Save CELLS file"), "", "",
        "CELLS files (*.cells)|*.cells", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;

    currentFileName = saveFileDialog.GetPath();
    SaveToFile(currentFileName);
}

void MainWindow::OnOpen(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(this, _("Open CELLS file"), "", "",
        "CELLS files (*.cells)|*.cells", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    LoadFromFile(openFileDialog.GetPath());
}

void MainWindow::OnNew(wxCommandEvent& event)
{
    currentFileName.Clear();
    OnClear(event);
}

void MainWindow::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MainWindow::OnFinite(wxCommandEvent& event)
{
    finiteMenuItem->Check(true);
    toroidalMenuItem->Check(false);
    settings.universeType = UniverseType::Finite;
    settings.Save();
}

void MainWindow::OnToroidal(wxCommandEvent& event)
{
    finiteMenuItem->Check(false);
    toroidalMenuItem->Check(true);
    settings.universeType = UniverseType::Toroidal;
    settings.Save();
}

void MainWindow::OnResetSettings(wxCommandEvent& event)
{
    settings.ResetToDefaults();
    InitializeGrid();
    UpdateStatusBar();
    drawingPanel->Refresh();
    finiteMenuItem->Check(settings.universeType == UniverseType::Finite);
    toroidalMenuItem->Check(settings.universeType == UniverseType::Toroidal);
    viewMenu->Check(10007, settings.showNeighborCount);
}

void MainWindow::SaveToFile(const wxString& filename)
{
    wxTextFile file;
    if (file.Create(filename) || file.Open(filename))
    {
        file.Clear();

        file.AddLine("! Game of Life save file");

        for (const auto& row : gameBoard)
        {
            wxString line;
            for (bool cell : row)
            {
                line += (cell ? '*' : '.');
            }
            file.AddLine(line);
        }

        file.Write();
        file.Close();
    }
}

void MainWindow::LoadFromFile(const wxString& filename)
{
    wxTextFile file;
    if (file.Open(filename))
    {
        gameBoard.clear();

        for (wxString str = file.GetFirstLine(); !file.Eof(); str = file.GetNextLine())
        {
            if (str[0] == '!')
                continue;

            std::vector<bool> row;
            for (char ch : str.ToStdString())
            {
                if (ch == '*')
                    row.push_back(true);
                else if (ch == '.')
                    row.push_back(false);
            }
            gameBoard.push_back(row);
        }

        int newGridSize = gameBoard.size() > 0 ? gameBoard[0].size() : 0;
        settings.gridSize = newGridSize;
        InitializeGrid();

        generationCount = 0;
        UpdateStatusBar();
        drawingPanel->Refresh();
    }
}

void MainWindow::OnSizeChange(wxSizeEvent& event)
{
    if (drawingPanel)
    {
        wxSize size = GetClientSize();
        drawingPanel->SetSize(size);
    }
    event.Skip();
}

void MainWindow::InitializeGrid()
{
    gameBoard.resize(settings.gridSize);
    neighborCounts.resize(settings.gridSize);
    for (auto& row : gameBoard)
    {
        row.resize(settings.gridSize, false);
    }
    for (auto& row : neighborCounts)
    {
        row.resize(settings.gridSize, 0);
    }

    drawingPanel->SetGridSize(settings.gridSize);
}

void MainWindow::UpdateStatusBar()
{
    wxString status;
    status.Printf("Generations: %d | Living Cells: %d", generationCount, livingCellsCount);
    statusBar->SetStatusText(status);
}

int MainWindow::GetLivingNeighbors(int row, int col)
{
    int livingNeighbors = 0;

    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            if (i == 0 && j == 0)
                continue;

            int newRow = row + i;
            int newCol = col + j;

            if (settings.universeType == UniverseType::Toroidal) // Toroidal behavior
            {
                if (newRow < 0)
                {
                    newRow = settings.gridSize - 1;
                }
                else if (newRow >= settings.gridSize)
                {
                    newRow = 0;
                }

                if (newCol < 0)
                {
                    newCol = settings.gridSize - 1;
                }
                else if (newCol >= settings.gridSize)
                {
                    newCol = 0;
                }
            }

            if (newRow >= 0 && newRow < settings.gridSize && newCol >= 0 && newCol < settings.gridSize)
            {
                if (gameBoard[newRow][newCol])
                {
                    ++livingNeighbors;
                }
            }
        }
    }

    return livingNeighbors;
}

void MainWindow::NextGeneration()
{
    std::vector<std::vector<bool>> sandbox(settings.gridSize, std::vector<bool>(settings.gridSize, false));

    int newLivingCellsCount = 0;

    for (int row = 0; row < settings.gridSize; ++row)
    {
        for (int col = 0; col < settings.gridSize; ++col)
        {
            int livingNeighbors = GetLivingNeighbors(row, col);
            neighborCounts[row][col] = livingNeighbors;

            if (gameBoard[row][col])
            {
                if (livingNeighbors < 2 || livingNeighbors > 3)
                {
                    sandbox[row][col] = false;
                }
                else
                {
                    sandbox[row][col] = true;
                    ++newLivingCellsCount;
                }
            }
            else
            {
                if (livingNeighbors == 3)
                {
                    sandbox[row][col] = true;
                    ++newLivingCellsCount;
                }
            }
        }
    }

    std::swap(gameBoard, sandbox);

    ++generationCount;
    livingCellsCount = newLivingCellsCount;

    UpdateStatusBar();
    drawingPanel->Refresh();
}

void MainWindow::OnPlay(wxCommandEvent& event)
{
    timer->Start(settings.interval);
}

void MainWindow::OnPause(wxCommandEvent& event)
{
    timer->Stop();
}

void MainWindow::OnNext(wxCommandEvent& event)
{
    NextGeneration();
}

void MainWindow::OnClear(wxCommandEvent& event)
{
    for (auto& row : gameBoard)
    {
        std::fill(row.begin(), row.end(), false);
    }

    for (auto& row : neighborCounts)
    {
        std::fill(row.begin(), row.end(), 0);
    }

    generationCount = 0;
    livingCellsCount = 0;

    UpdateStatusBar();
    drawingPanel->Refresh();
}

void MainWindow::OnTimer(wxTimerEvent& event)
{
    NextGeneration();
}
