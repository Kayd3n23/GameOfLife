#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
EVT_PAINT(DrawingPanel::OnPaint)
wxEND_EVENT_TABLE()

DrawingPanel::DrawingPanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY)
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

    // Set the pen and brush for drawing
    context->SetPen(*wxBLACK);
    context->SetBrush(*wxWHITE);

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
