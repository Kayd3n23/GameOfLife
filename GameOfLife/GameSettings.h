#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include "wx/wx.h"
#include <fstream>

struct Settings
{
    unsigned int livingCellColorR = 128;
    unsigned int livingCellColorG = 128;
    unsigned int livingCellColorB = 128;
    unsigned int livingCellColorA = 255;

    unsigned int deadCellColorR = 255;
    unsigned int deadCellColorG = 255;
    unsigned int deadCellColorB = 255;
    unsigned int deadCellColorA = 255;

    int gridSize = 15;
    int interval = 50;
    bool showNeighborCount = false; // New option for showing neighbor count

    wxColor GetLivingCellColor() const
    {
        return wxColor(livingCellColorR, livingCellColorG, livingCellColorB, livingCellColorA);
    }

    wxColor GetDeadCellColor() const
    {
        return wxColor(deadCellColorR, deadCellColorG, deadCellColorB, deadCellColorA);
    }

    void SetLivingCellColor(const wxColor& color)
    {
        livingCellColorR = color.Red();
        livingCellColorG = color.Green();
        livingCellColorB = color.Blue();
        livingCellColorA = color.Alpha();
    }

    void SetDeadCellColor(const wxColor& color)
    {
        deadCellColorR = color.Red();
        deadCellColorG = color.Green();
        deadCellColorB = color.Blue();
        deadCellColorA = color.Alpha();
    }

    void Save() const
    {
        std::ofstream file("settings.bin", std::ios::out | std::ios::binary);
        file.write((char*)this, sizeof(Settings));
        file.close();
    }

    void Load()
    {
        std::ifstream file("settings.bin", std::ios::binary | std::ios::in);
        if (file.is_open())
        {
            file.read((char*)this, sizeof(Settings));
            file.close();
        }
    }
};

#endif // GAMESETTINGS_H
