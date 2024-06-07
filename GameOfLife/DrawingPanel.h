#ifndef DRAWINGPANEL_H
#define DRAWINGPANEL_H

#include "wx/wx.h"

class DrawingPanel : public wxPanel
{
public:
    DrawingPanel(wxWindow* parent);
    ~DrawingPanel();

    void OnPaint(wxPaintEvent& event);

private:
    wxDECLARE_EVENT_TABLE();
};

#endif // DRAWINGPANEL_H
