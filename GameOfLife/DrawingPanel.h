#ifndef DRAWINGPANEL_H
#define DRAWINGPANEL_H

#include "wx/wx.h"

class DrawingPanel : public wxPanel
{
public:
    DrawingPanel(wxWindow* parent);
    ~DrawingPanel();

    void OnPaint(wxPaintEvent& event);
    void SetSize(const wxSize& size); // New method

private:
    int gridSize = 15;  // Default grid size

    wxDECLARE_EVENT_TABLE();
};

#endif // DRAWINGPANEL_H
