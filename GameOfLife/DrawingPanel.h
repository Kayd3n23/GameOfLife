// DrawingPanel.h
#ifndef DRAWINGPANEL_H
#define DRAWINGPANEL_H

#include "wx/wx.h"
#include <vector>

class DrawingPanel : public wxPanel
{
public:
    DrawingPanel(wxWindow* parent, std::vector<std::vector<bool>>& gameBoard);
    ~DrawingPanel();

    void OnPaint(wxPaintEvent& event);
    void SetSize(const wxSize& size);
    void SetGridSize(int size);
    void OnMouseUp(wxMouseEvent& event);

private:
    int gridSize = 15;
    std::vector<std::vector<bool>>& gameBoardRef;

    wxDECLARE_EVENT_TABLE();
};

#endif // DRAWINGPANEL_H
