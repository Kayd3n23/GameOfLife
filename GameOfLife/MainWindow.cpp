#include "MainWindow.h"
#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::OnSizeChange)
EVT_MENU(10001, MainWindow::OnPlay)
EVT_MENU(10002, MainWindow::OnPause)
EVT_MENU(10003, MainWindow::OnNext)
EVT_MENU(10004, MainWindow::OnClear)
EVT_TIMER(10005, MainWindow::OnTimer)
wxEND_EVENT_TABLE()

MainWindow::MainWindow()
    : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0, 0), wxSize(400, 400))
{
    sizer = new wxBoxSizer(wxVERTICAL);
    drawingPanel = new DrawingPanel(this, gameBoard);
    drawingPanel->SetSettings(&settings);  // Pass settings to DrawingPanel
    sizer->Add(drawingPanel, 1, wxEXPAND | wxALL);

    statusBar = CreateStatusBar();
    UpdateStatusBar();

    toolBar = CreateToolBar();

    wxBitmap playIcon(play_xpm);
    wxBitmap pauseIcon(pause_xpm);
    wxBitmap nextIcon(next_xpm);
    wxBitmap trashIcon(trash_xpm);

    toolBar->AddTool(10001, "Play", playIcon);
    toolBar->AddTool(10002, "Pause", pauseIcon);
    toolBar->AddTool(10003, "Next", nextIcon);
    toolBar->AddTool(10004, "Clear", trashIcon);

    toolBar->Realize();

    this->SetSizer(sizer);
    this->Layout();

    InitializeGrid();

    // Initialize the timer
    timer = new wxTimer(this, 10005);
}

MainWindow::~MainWindow()
{
    // Destructor
    if (timer)
    {
        timer->Stop();
        delete timer;
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
    gameBoard.resize(settings.gridSize);  // Use settings for grid size
    for (auto& row : gameBoard)
    {
        row.resize(settings.gridSize, false);
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
        for (int j = -1; i <= 1; ++j)
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

            if (gameBoard[row][col])
            {
                if (livingNeighbors == 2 || livingNeighbors == 3)
                {
                    sandbox[row][col] = true;
                    ++newLivingCellsCount;
                }
                else
                {
                    sandbox[row][col] = false;
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

    generationCount = 0;
    livingCellsCount = 0;

    UpdateStatusBar();
    drawingPanel->Refresh();
}

void MainWindow::OnTimer(wxTimerEvent& event)
{
    NextGeneration();
}
