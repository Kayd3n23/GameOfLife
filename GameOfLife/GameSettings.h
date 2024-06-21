#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include "wx/wx.h"

struct Settings {
    unsigned int livingCellRed = 200;
    unsigned int livingCellGreen = 100;
    unsigned int livingCellBlue = 100;
    unsigned int livingCellAlpha = 100;

    unsigned int deadCellRed = 255;
    unsigned int deadCellGreen = 255;
    unsigned int deadCellBlue = 255;
    unsigned int deadCellAlpha = 255;

    int gridSize = 20;
    int interval = 50;

    wxColor GetLivingCellColor() const {
        return wxColor(livingCellRed, livingCellGreen, livingCellBlue, livingCellAlpha);
    }

    wxColor GetDeadCellColor() const {
        return wxColor(deadCellRed, deadCellGreen, deadCellBlue, deadCellAlpha);
    }

    void SetLivingCellColor(const wxColor& color) {
        livingCellRed = color.Red();
        livingCellGreen = color.Green();
        livingCellBlue = color.Blue();
        livingCellAlpha = color.Alpha();
    }

    void SetDeadCellColor(const wxColor& color) {
        deadCellRed = color.Red();
        deadCellGreen = color.Green();
        deadCellBlue = color.Blue();
        deadCellAlpha = color.Alpha();
    }
};

#endif // GAMESETTINGS_H
