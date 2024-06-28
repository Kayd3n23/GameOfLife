#ifndef SETTINGS_H
#define SETTINGS_H

#include <wx/colour.h>
#include <fstream>

enum class UniverseType
{
    Finite,
    Toroidal
};

struct Settings
{
    unsigned int livingCellRed = 128;
    unsigned int livingCellGreen = 128;
    unsigned int livingCellBlue = 128;
    unsigned int livingCellAlpha = 255;
    unsigned int deadCellRed = 255;
    unsigned int deadCellGreen = 255;
    unsigned int deadCellBlue = 255;
    unsigned int deadCellAlpha = 255;
    int gridSize = 15;
    int interval = 50;
    bool showNeighborCount = false;
    UniverseType universeType = UniverseType::Finite; // Add universeType member

    wxColor GetLivingCellColor() const
    {
        return wxColor(livingCellRed, livingCellGreen, livingCellBlue, livingCellAlpha);
    }

    wxColor GetDeadCellColor() const
    {
        return wxColor(deadCellRed, deadCellGreen, deadCellBlue, deadCellAlpha);
    }

    void SetLivingCellColor(const wxColor& color)
    {
        livingCellRed = color.Red();
        livingCellGreen = color.Green();
        livingCellBlue = color.Blue();
        livingCellAlpha = color.Alpha();
    }

    void SetDeadCellColor(const wxColor& color)
    {
        deadCellRed = color.Red();
        deadCellGreen = color.Green();
        deadCellBlue = color.Blue();
        deadCellAlpha = color.Alpha();
    }

    void Save()
    {
        std::ofstream file("settings.bin", std::ios::out | std::ios::binary);
        if (file.is_open())
        {
            file.write((char*)this, sizeof(Settings));
            file.close();
        }
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

#endif // SETTINGS_H
