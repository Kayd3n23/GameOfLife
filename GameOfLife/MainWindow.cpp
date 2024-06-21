#include "MainWindow.h"
#include "SettingsDialog.h"
#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm" // Include the trash icon

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::OnSizeChange)
EVT_MENU(10001, MainWindow::OnPlay)
EVT_MENU(10002, MainWindow::OnPause)
EVT_MENU(10003, MainWindow::OnNext)
EVT_MENU(10004, MainWindow::OnClear)
EVT_MENU(10006, MainWindow::OnMenuSettings)  // Event for settings menu
EVT_MENU(10007, MainWindow::OnToggleShowNeighborCount) // Event for toggling neighbor count
EVT_TIMER(10005, MainWindow::OnTimer)
wxEND_EVENT_TABLE()

MainWindow::MainWindow()
    : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0, 0), wxSize(400, 400))
{
    // Load settings at startup
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
    wxBitmap clearIcon(trash_xpm); // Use the trash icon

    toolBar->AddTool(10001, "Play", playIcon);
    toolBar->AddTool(10002, "Pause", pauseIcon);
    toolBar->AddTool(10003, "Next", nextIcon);
    toolBar->AddTool(10004, "Clear", clearIcon);

    toolBar->Realize();

    // Create the menu bar
    menuBar = new wxMenuBar();

    // Create the options menu
    optionsMenu = new wxMenu();
    optionsMenu->Append(10006, "Settings");

    // Create the view menu
    viewMenu = new wxMenu();
    viewMenu->AppendCheckItem(10007, "Show Neighbor Count");

    // Add the options and view menus to the menu bar
    menuBar->Append(optionsMenu, "Options");
    menuBar->Append(viewMenu, "View");

    // Set the menu bar
    SetMenuBar(menuBar);

    this->SetSizer(sizer);
    this->Layout();

    InitializeGrid();

    // Set the initial state of the neighbor count menu item
    viewMenu->Check(10007, settings.showNeighborCount);

    timer = new wxTimer(this, 10005);
}

MainWindow::~MainWindow()  // Destructor definition
{
    if (timer)
    {
        timer->Stop();
        delete timer;
    }
}

void MainWindow::OnMenuSettings(wxCommandEvent& event)
{
    // Save current settings in case the user cancels
    Settings oldSettings = settings;

    SettingsDialog dlg(this, &settings);
    if (dlg.ShowModal() == wxID_OK)
    {
        InitializeGrid();
        UpdateStatusBar();
        drawingPanel->Refresh();
        // Save settings if OK was clicked
        settings.Save();
    }
    else
    {
        // Restore old settings if cancel was clicked
        settings = oldSettings;
    }
}

void MainWindow::OnToggleShowNeighborCount(wxCommandEvent& event)
{
    settings.showNeighborCount = !settings.showNeighborCount;
    settings.Save();
    drawingPanel->Refresh();
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
    gameBoard.resize(settings.gridSize);  // Use settings for grid size
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

            if (newRow >= 0 && newRow < settings.gridSize && newCol >= 0 && newCol < settings.gridSize)
            {
                if (gameBoard[newRow][newCol])
                    ++livingNeighbors;
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
                if (livingNeighbors < 2 || livingNeighbors > 3) // Rule 1 and 3
                {
                    sandbox[row][col] = false;
                }
                else // Rule 2
                {
                    sandbox[row][col] = true;
                    ++newLivingCellsCount;
                }
            }
            else
            {
                if (livingNeighbors == 3) // Rule 4
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
    timer->Start(settings.interval);  // Use settings for interval
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
