// MainWindow.cpp
#include "MainWindow.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::OnSizeChange)
wxEND_EVENT_TABLE()

MainWindow::MainWindow()
    : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0, 0), wxSize(400, 400)) // Updated size
{
    drawingPanel = new DrawingPanel(this);

    sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(drawingPanel, 1, wxEXPAND | wxALL, 5);
    this->SetSizer(sizer);
    this->Layout(); // Ensure layout is updated

    InitializeGrid(); // Initialize the game grid
}

MainWindow::~MainWindow()
{
    // Destructor
}

void MainWindow::InitializeGrid()
{
    // Resize the game board to gridSize x gridSize
    gameBoard.resize(gridSize);
    for (int i = 0; i < gridSize; ++i)
    {
        gameBoard[i].resize(gridSize, false); // Initialize all cells to false (dead)
    }

    // Set grid size in DrawingPanel
    drawingPanel->SetGridSize(gridSize);

    // Refresh DrawingPanel to reflect changes
    drawingPanel->Refresh();
}

void MainWindow::OnSizeChange(wxSizeEvent& event)
{
    wxSize size = GetClientSize();
    drawingPanel->SetSize(size);
    event.Skip(); // Allow other handlers to process this event
}
