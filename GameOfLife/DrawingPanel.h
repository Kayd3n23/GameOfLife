#ifndef DRAWINGPANEL_H
#define DRAWINGPANEL_H

#include "wx/wx.h"
#include "GameSettings.h"
#include <vector>

class DrawingPanel : public wxPanel
{
public:
    DrawingPanel(wxWindow* parent, std::vector<std::vector<bool>>& gameBoard, const std::vector<std::vector<int>>& neighborCounts);
    void SetSettings(Settings* settings);
    void SetGridSize(int gridSize);

private:
    void OnPaint(wxPaintEvent& event);
    void OnMouseUp(wxMouseEvent& event); // Mouse event handler
    std::vector<std::vector<bool>>& gameBoard; // Make gameBoard modifiable
    const std::vector<std::vector<int>>& neighborCounts;
    Settings* settings;

    int gridSize;

    wxDECLARE_EVENT_TABLE();
};

#endif // DRAWINGPANEL_H
