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
    void OnMouseUp(wxMouseEvent& event); // Mouse event handler

private:
    int gridSize = 15;  // Default grid size
    std::vector<std::vector<bool>>& gameBoardRef; // Reference to game board

    wxDECLARE_EVENT_TABLE();
};

#endif // DRAWINGPANEL_H
