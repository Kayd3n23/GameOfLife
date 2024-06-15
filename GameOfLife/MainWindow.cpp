// MainWindow.cpp
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
EVT_MENU(10004, MainWindow::OnClear)  // Add event for clear button
wxEND_EVENT_TABLE()

MainWindow::MainWindow()
    : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0, 0), wxSize(400, 400))
{
    sizer = new wxBoxSizer(wxVERTICAL);
    drawingPanel = new DrawingPanel(this, gameBoard);
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
}

MainWindow::~MainWindow()
{
    // Empty destructor for now
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
    gameBoard.resize(gridSize);
    for (auto& row : gameBoard)
    {
        row.resize(gridSize, false);
    }

    drawingPanel->SetGridSize(gridSize);
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

    // Iterate over the 3x3 grid centered on (row, col)
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            if (i == 0 && j == 0)
                continue; // Skip the cell itself

            int newRow = row + i;
            int newCol = col + j;

            // Ensure indices are within bounds
            if (newRow >= 0 && newRow < gridSize && newCol >= 0 && newCol < gridSize)
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
    // Create a sandbox for the next generation
    std::vector<std::vector<bool>> sandbox(gridSize, std::vector<bool>(gridSize, false));

    // Count the number of living cells
    int newLivingCellsCount = 0;

    // Iterate over the game board
    for (int row = 0; row < gridSize; ++row)
    {
        for (int col = 0; col < gridSize; ++col)
        {
            int livingNeighbors = GetLivingNeighbors(row, col);

            // Apply the rules of the Game of Life
            if (gameBoard[row][col])
            {
                if (livingNeighbors == 2 || livingNeighbors == 3)
                {
                    sandbox[row][col] = true; // Cell survives
                    ++newLivingCellsCount;
                }
                else
                {
                    sandbox[row][col] = false; // Cell dies
                }
            }
            else
            {
                if (livingNeighbors == 3)
                {
                    sandbox[row][col] = true; // Cell becomes alive
                    ++newLivingCellsCount;
                }
            }
        }
    }

    // Swap the sandbox with the game board
    std::swap(gameBoard, sandbox);

    // Update generation count and living cells count
    ++generationCount;
    livingCellsCount = newLivingCellsCount;

    // Update the status bar and refresh the panel
    UpdateStatusBar();
    drawingPanel->Refresh();
}

void MainWindow::OnPlay(wxCommandEvent& event)
{
    // Implement play functionality
}

void MainWindow::OnPause(wxCommandEvent& event)
{
    // Implement pause functionality
}

void MainWindow::OnNext(wxCommandEvent& event)
{
    NextGeneration();
}

void MainWindow::OnClear(wxCommandEvent& event)
{
    // Reset the game board
    for (auto& row : gameBoard)
    {
        std::fill(row.begin(), row.end(), false);
    }

    // Reset generation and living cells count
    generationCount = 0;
    livingCellsCount = 0;

    // Update the status bar and refresh the panel
    UpdateStatusBar();
    drawingPanel->Refresh();
}
