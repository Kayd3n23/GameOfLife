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

    // Draw a rectangle (example)
    context->DrawRectangle(50, 50, 100, 100);

    delete context;
}
