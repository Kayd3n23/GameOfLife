// DrawingPanel.cpp
#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
EVT_PAINT(DrawingPanel::OnPaint)
EVT_LEFT_UP(DrawingPanel::OnMouseUp) // Bind the mouse event
wxEND_EVENT_TABLE()

DrawingPanel::DrawingPanel(wxWindow* parent, std::vector<std::vector<bool>>& gameBoard)
    : wxPanel(parent, wxID_ANY), gameBoardRef(gameBoard) // Initialize reference
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
}

DrawingPanel::~DrawingPanel()
{
    // Empty destructor for now
}

void DrawingPanel::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();

    wxGraphicsContext* context = wxGraphicsContext::Create(dc);
    if (!context)
    {
        return;
    }

    // Set the pen for drawing
    context->SetPen(*wxBLACK);

    // Get the size of the drawing panel
    wxSize panelSize = GetClientSize();
    int panelWidth = panelSize.GetWidth();
    int panelHeight = panelSize.GetHeight();

    // Calculate the size of each cell
    int cellWidth = panelWidth / gridSize;
    int cellHeight = panelHeight / gridSize;

    // Draw the grid
    for (int row = 0; row < gridSize; ++row)
    {
        for (int col = 0; col < gridSize; ++col)
        {
            int x = col * cellWidth;
            int y = row * cellHeight;

            // Set the brush color based on cell state
            if (gameBoardRef[row][col])
            {
                context->SetBrush(*wxLIGHT_GREY); // Alive cell
            }
            else
            {
                context->SetBrush(*wxWHITE); // Dead cell
            }

            context->DrawRectangle(x, y, cellWidth, cellHeight);
        }
    }

    delete context;
}

void DrawingPanel::SetSize(const wxSize& size)
{
    wxPanel::SetSize(size); // Call base class SetSize
    Refresh(); // Trigger repaint
}

void DrawingPanel::SetGridSize(int size)
{
    gridSize = size;
    Refresh(); // Trigger repaint
}

void DrawingPanel::OnMouseUp(wxMouseEvent& event)
{
    int mouseX = event.GetX();
    int mouseY = event.GetY();

    wxSize panelSize = GetClientSize();
    int panelWidth = panelSize.GetWidth();
    int panelHeight = panelSize.GetHeight();

    // Calculate cell width and height
    int cellWidth = panelWidth / gridSize;
    int cellHeight = panelHeight / gridSize;

    // Determine which cell was clicked
    int col = mouseX / cellWidth;
    int row = mouseY / cellHeight;

    if (col >= 0 && col < gridSize && row >= 0 && row < gridSize)
    {
        // Toggle cell state
        gameBoardRef[row][col] = !gameBoardRef[row][col];
        Refresh(); // Trigger repaint
    }
}
