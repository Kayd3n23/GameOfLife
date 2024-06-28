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
    bool showGrid = true; // Add showGrid
    bool show10x10Grid = false; // Add show10x10Grid
    UniverseType universeType = UniverseType::Finite;

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

    void ResetToDefaults()
    {
        livingCellRed = 128;
        livingCellGreen = 128;
        livingCellBlue = 128;
        livingCellAlpha = 255;
        deadCellRed = 255;
        deadCellGreen = 255;
        deadCellBlue = 255;
        deadCellAlpha = 255;
        gridSize = 15;
        interval = 50;
        showNeighborCount = false;
        showGrid = true;
        show10x10Grid = false;
        universeType = UniverseType::Finite;
        Save();
    }
};

#endif // SETTINGS_H
