#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
EVT_PAINT(DrawingPanel::OnPaint)
EVT_LEFT_UP(DrawingPanel::OnMouseUp) // Bind mouse up event
wxEND_EVENT_TABLE()

DrawingPanel::DrawingPanel(wxWindow* parent, std::vector<std::vector<bool>>& gameBoard, const std::vector<std::vector<int>>& neighborCounts)
    : wxPanel(parent), gameBoard(gameBoard), neighborCounts(neighborCounts), settings(nullptr), gridSize(15)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void DrawingPanel::SetSettings(Settings* settings)
{
    this->settings = settings;
}

void DrawingPanel::SetGridSize(int gridSize)
{
    this->gridSize = gridSize;
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

    context->SetPen(*wxBLACK);

    wxSize size = GetClientSize();
    int cellWidth = size.GetWidth() / gridSize;
    int cellHeight = size.GetHeight() / gridSize;

    for (int row = 0; row < gridSize; ++row)
    {
        for (int col = 0; col < gridSize; ++col)
        {
            if (gameBoard[row][col])
            {
                context->SetBrush(settings->GetLivingCellColor());
            }
            else
            {
                context->SetBrush(settings->GetDeadCellColor());
            }

            int x = col * cellWidth;
            int y = row * cellHeight;
            context->DrawRectangle(x, y, cellWidth, cellHeight);

            if (settings->showNeighborCount && neighborCounts[row][col] > 0)
            {
                wxString text = wxString::Format("%d", neighborCounts[row][col]);
                double textWidth, textHeight;
                context->SetFont(wxFontInfo(16), *wxRED);
                context->GetTextExtent(text, &textWidth, &textHeight);
                context->DrawText(text, x + (cellWidth - textWidth) / 2, y + (cellHeight - textHeight) / 2);
            }
        }
    }

    delete context;
}

void DrawingPanel::OnMouseUp(wxMouseEvent& event)
{
    if (!settings) return;

    wxPoint pos = event.GetPosition();
    wxSize size = GetClientSize();
    int cellWidth = size.GetWidth() / gridSize;
    int cellHeight = size.GetHeight() / gridSize;

    int col = pos.x / cellWidth;
    int row = pos.y / cellHeight;

    if (col >= 0 && col < gridSize && row >= 0 && row < gridSize)
    {
        gameBoard[row][col] = !gameBoard[row][col]; // Toggle cell state
        Refresh();
    }
}
