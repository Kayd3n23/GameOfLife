#ifndef APP_H
#define APP_H

#include "wx/wx.h"
#include "MainWindow.h"

class App : public wxApp
{
public:
    virtual bool OnInit();
private:
    MainWindow* mainWindow;
};

#endif // APP_H
