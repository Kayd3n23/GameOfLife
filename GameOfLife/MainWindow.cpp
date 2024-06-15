// MainWindow.cpp
#include "MainWindow.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::OnSizeChange)
wxEND_EVENT_TABLE()

MainWindow::MainWindow()
    : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0, 0), wxSize(400, 400))
{
    sizer = new wxBoxSizer(wxVERTICAL);
    drawingPanel = new DrawingPanel(this, gameBoard);
    sizer->Add(drawingPanel, 1, wxEXPAND | wxALL);

    statusBar = CreateStatusBar();
    UpdateStatusBar();

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
    wxSize size = GetClientSize();
    drawingPanel->SetSize(size);
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
