#include "DrawingPanel.h"
#include "GameSettings.h"
#include "MainWindow.h"  // Include MainWindow header
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

DrawingPanel::DrawingPanel(wxWindow* parent, std::vector<std::vector<bool>>& gameBoard, std::vector<std::vector<int>>& neighborCounts)
    : wxPanel(parent), gameBoard(gameBoard), neighborCounts(neighborCounts)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
    this->Bind(wxEVT_LEFT_UP, &DrawingPanel::OnMouseUp, this);
}

void DrawingPanel::SetGridSize(int gridSize)
{
    this->gridSize = gridSize;
    Refresh();
}
 
void DrawingPanel::SetSettings(Settings* settings)
{
    this->settings = settings;
}

void DrawingPanel::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();

    wxGraphicsContext* context = wxGraphicsContext::Create(dc);
    if (!context)
        return;

    int cellWidth = GetSize().GetWidth() / gridSize;
    int cellHeight = GetSize().GetHeight() / gridSize;

    context->SetPen(wxPen(settings->showGrid ? *wxBLACK : wxNullPen));
    context->SetBrush(wxBrush(*wxWHITE));
    dc.SetPen(settings->showGrid ? wxPen(wxColor(0, 0, 0, 64)) : wxNullPen);

    for (int row = 0; row < gridSize; ++row)
    {
        for (int col = 0; col < gridSize; ++col)
        {
            int x = col * cellWidth;
            int y = row * cellHeight;

            if (gameBoard[row][col])
            {
                context->SetBrush(wxBrush(settings->GetLivingCellColor()));
            }
            else
            {
                context->SetBrush(wxBrush(settings->GetDeadCellColor()));
            }

            context->DrawRectangle(x, y, cellWidth, cellHeight);

            if (settings->showNeighborCount && neighborCounts[row][col] > 0)
            {
                context->SetFont(wxFontInfo(16), *wxRED);
                wxString text = wxString::Format("%d", neighborCounts[row][col]);
                double textWidth, textHeight;
                context->GetTextExtent(text, &textWidth, &textHeight);
                context->DrawText(text, x + (cellWidth - textWidth) / 2, y + (cellHeight - textHeight) / 2);
            }
        }
    }

    if (settings->showGrid)
    {
        for (int i = 1; i < gridSize; ++i)
        {
            int x = i * cellWidth;
            int y = i * cellHeight;

            dc.DrawLine(wxPoint(x, 0), wxPoint(x, GetSize().GetHeight()));
            dc.DrawLine(wxPoint(0, y), wxPoint(GetSize().GetWidth(), y));
        }

        if (settings->show10x10Grid)
        {
            int solidLines = gridSize / 10;

            dc.SetPen(wxPen(*wxBLACK, 2));

            for (int i = 1; i <= solidLines; ++i)
            {
                int x = i * cellWidth * 10;
                int y = i * cellHeight * 10;

                dc.DrawLine(wxPoint(x, 0), wxPoint(x, GetSize().GetHeight()));
                dc.DrawLine(wxPoint(0, y), wxPoint(GetSize().GetWidth(), y));
            }
        }
    }

    if (settings->showHUD)
    {
        MainWindow* mainWindow = dynamic_cast<MainWindow*>(GetParent());
        context->SetFont(wxFontInfo(14), *wxRED);
        wxString hudText = wxString::Format("Generations: %d\nLiving Cells: %d\nBoundary: %s\nUniverse Size: %dx%d",
            mainWindow->GetGenerationCount(),
            mainWindow->GetLivingCellsCount(),
            settings->universeType == UniverseType::Finite ? "Finite" : "Toroidal",
            settings->gridSize, settings->gridSize);

        double textWidth, textHeight;
        context->GetTextExtent(hudText, &textWidth, &textHeight);
        context->DrawText(hudText, 10, GetSize().GetHeight() - textHeight - 10);
    }

    delete context;
}

void DrawingPanel::OnMouseUp(wxMouseEvent& event)
{
    int x = event.GetX();
    int y = event.GetY();

    int cellWidth = GetSize().GetWidth() / gridSize;
    int cellHeight = GetSize().GetHeight() / gridSize;

    int col = x / cellWidth;
    int row = y / cellHeight;

    if (row >= 0 && row < gridSize && col >= 0 && col < gridSize)
    {
        gameBoard[row][col] = !gameBoard[row][col];
        Refresh();
    }
}
