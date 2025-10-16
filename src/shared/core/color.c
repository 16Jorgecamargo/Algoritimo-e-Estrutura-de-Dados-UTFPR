#include <stdio.h>
#include "../headlers/color.h"

#ifdef _WIN32
    #include <windows.h>
#endif

void setColor(Color color) {
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        WORD windowsColor;
        switch(color) {
            case BLACK:   windowsColor = 0; break;
            case RED:     windowsColor = FOREGROUND_RED; break;
            case GREEN:   windowsColor = FOREGROUND_GREEN; break;
            case YELLOW:  windowsColor = FOREGROUND_RED | FOREGROUND_GREEN; break;
            case BLUE:    windowsColor = FOREGROUND_BLUE; break;
            case MAGENTA: windowsColor = FOREGROUND_RED | FOREGROUND_BLUE; break;
            case CYAN:    windowsColor = FOREGROUND_GREEN | FOREGROUND_BLUE; break;
            case WHITE:   windowsColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break;
            default:      windowsColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break;
        }
        SetConsoleTextAttribute(hConsole, windowsColor | FOREGROUND_INTENSITY);
    #else
        printf("\033[3%dm", color);
    #endif
}

void resetColor(void) {
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    #else
        printf("\033[0m");
    #endif
}

void setBackgroundColor(Color color) {
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        
        WORD windowsBackgroundColor;
        switch(color) {
            case BLACK:   windowsBackgroundColor = 0; break;
            case RED:     windowsBackgroundColor = BACKGROUND_RED; break;
            case GREEN:   windowsBackgroundColor = BACKGROUND_GREEN; break;
            case YELLOW:  windowsBackgroundColor = BACKGROUND_RED | BACKGROUND_GREEN; break;
            case BLUE:    windowsBackgroundColor = BACKGROUND_BLUE; break;
            case MAGENTA: windowsBackgroundColor = BACKGROUND_RED | BACKGROUND_BLUE; break;
            case CYAN:    windowsBackgroundColor = BACKGROUND_GREEN | BACKGROUND_BLUE; break;
            case WHITE:   windowsBackgroundColor = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE; break;
            default:      windowsBackgroundColor = 0; break;
        }
        
        SetConsoleTextAttribute(hConsole, (csbi.wAttributes & 0x0F) | windowsBackgroundColor | BACKGROUND_INTENSITY);
    #else
        printf("\033[4%dm", color);
    #endif
}

void setColorAndBackground(Color textColor, Color backgroundColor) {
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        WORD windowsTextColor;
        switch(textColor) {
            case BLACK:   windowsTextColor = 0; break;
            case RED:     windowsTextColor = FOREGROUND_RED; break;
            case GREEN:   windowsTextColor = FOREGROUND_GREEN; break;
            case YELLOW:  windowsTextColor = FOREGROUND_RED | FOREGROUND_GREEN; break;
            case BLUE:    windowsTextColor = FOREGROUND_BLUE; break;
            case MAGENTA: windowsTextColor = FOREGROUND_RED | FOREGROUND_BLUE; break;
            case CYAN:    windowsTextColor = FOREGROUND_GREEN | FOREGROUND_BLUE; break;
            case WHITE:   windowsTextColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break;
            default:      windowsTextColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break;
        }

        WORD windowsBackgroundColor;
        switch(backgroundColor) {
            case BLACK:   windowsBackgroundColor = 0; break;
            case RED:     windowsBackgroundColor = BACKGROUND_RED; break;
            case GREEN:   windowsBackgroundColor = BACKGROUND_GREEN; break;
            case YELLOW:  windowsBackgroundColor = BACKGROUND_RED | BACKGROUND_GREEN; break;
            case BLUE:    windowsBackgroundColor = BACKGROUND_BLUE; break;
            case MAGENTA: windowsBackgroundColor = BACKGROUND_RED | BACKGROUND_BLUE; break;
            case CYAN:    windowsBackgroundColor = BACKGROUND_GREEN | BACKGROUND_BLUE; break;
            case WHITE:   windowsBackgroundColor = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE; break;
            default:      windowsBackgroundColor = 0; break;
        }

        SetConsoleTextAttribute(hConsole, windowsTextColor | FOREGROUND_INTENSITY | windowsBackgroundColor | BACKGROUND_INTENSITY);
    #else
        printf("\033[3%d;4%dm", textColor, backgroundColor);
    #endif
}