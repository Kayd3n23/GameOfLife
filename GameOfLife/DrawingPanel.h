#ifndef DRAWINGPANEL_H
#define DRAWINGPANEL_H

#include "wx/wx.h"
#include "GameSettings.h"
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
    void SetSettings(Settings* settings);  // Setter for settings pointer

private:
    std::vector<std::vector<bool>>& gameBoardRef;
    Settings* settings;  // Settings pointer

    wxDECLARE_EVENT_TABLE();
};

#endif // DRAWINGPANEL_H
