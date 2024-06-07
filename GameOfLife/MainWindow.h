#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "wx/wx.h"
#include "DrawingPanel.h"

class MainWindow : public wxFrame
{
public:
    MainWindow();
    ~MainWindow();

private:
    DrawingPanel* drawingPanel;
};

#endif // MAINWINDOW_H
