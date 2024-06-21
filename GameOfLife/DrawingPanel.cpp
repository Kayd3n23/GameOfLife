#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"
#include "MainWindow.h"

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
EVT_PAINT(DrawingPanel::OnPaint)
EVT_LEFT_UP(DrawingPanel::OnMouseUp)
wxEND_EVENT_TABLE()

DrawingPanel::DrawingPanel(wxWindow* parent, std::vector<std::vector<bool>>& gameBoard)
    : wxPanel(parent, wxID_ANY), gameBoardRef(gameBoard), settings(nullptr)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
}

DrawingPanel::~DrawingPanel()
{
    // Empty destructor for now
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
    {
        return;
    }

    context->SetPen(*wxBLACK);

    wxSize panelSize = GetClientSize();
    int panelWidth = panelSize.GetWidth();
    int panelHeight = panelSize.GetHeight();

    int cellWidth = panelWidth / settings->gridSize;
    int cellHeight = panelHeight / settings->gridSize;

    for (int row = 0; row < settings->gridSize; ++row)
    {
        for (int col = 0; col < settings->gridSize; ++col)
        {
            int x = col * cellWidth;
            int y = row * cellHeight;

            if (gameBoardRef[row][col])
            {
                context->SetBrush(wxBrush(settings->GetLivingCellColor()));
            }
            else
            {
                context->SetBrush(wxBrush(settings->GetDeadCellColor()));
            }

            context->DrawRectangle(x, y, cellWidth, cellHeight);
        }
    }

    delete context;
}

void DrawingPanel::SetSize(const wxSize& size)
{
    wxPanel::SetSize(size);
    Refresh();
}

void DrawingPanel::SetGridSize(int size)
{
    settings->gridSize = size;
    Refresh();
}

void DrawingPanel::OnMouseUp(wxMouseEvent& event)
{
    int mouseX = event.GetX();
    int mouseY = event.GetY();

    wxSize panelSize = GetClientSize();
    int panelWidth = panelSize.GetWidth();
    int panelHeight = panelSize.GetHeight();

    int cellWidth = panelWidth / settings->gridSize;
    int cellHeight = panelHeight / settings->gridSize;

    int col = mouseX / cellWidth;
    int row = mouseY / cellHeight;

    if (col >= 0 && col < settings->gridSize && row >= 0 && row < settings->gridSize)
    {
        gameBoardRef[row][col] = !gameBoardRef[row][col];

        MainWindow* parentWindow = dynamic_cast<MainWindow*>(GetParent());
        if (parentWindow)
        {
            parentWindow->UpdateStatusBar();
        }

        Refresh();
    }
}
