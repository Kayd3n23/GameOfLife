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
}

MainWindow::~MainWindow()
{
    // Destructor
}

void MainWindow::OnSizeChange(wxSizeEvent& event)
{
    wxSize size = GetClientSize();
    drawingPanel->SetSize(size);
    event.Skip(); // Allow other handlers to process this event
}
