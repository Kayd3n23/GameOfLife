#ifndef DRAWINGPANEL_H
#define DRAWINGPANEL_H

#include "wx/wx.h"
#include "GameSettings.h"
#include <vector>

// Forward declaration of MainWindow class
class MainWindow;

class DrawingPanel : public wxPanel
{
public:
    DrawingPanel(wxWindow* parent, std::vector<std::vector<bool>>& gameBoard, std::vector<std::vector<int>>& neighborCounts);

    void SetGridSize(int gridSize);
    void SetSettings(Settings* settings);

private:
    void OnPaint(wxPaintEvent& event);
    void OnMouseUp(wxMouseEvent& event);

    std::vector<std::vector<bool>>& gameBoard;
    std::vector<std::vector<int>>& neighborCounts;
    int gridSize;
    Settings* settings;
};

#endif // DRAWINGPANEL_H
