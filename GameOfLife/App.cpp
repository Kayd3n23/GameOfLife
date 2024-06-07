#include "App.h"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    mainWindow = new MainWindow();
    mainWindow->Show(true);
    return true;
}
