#ifndef COLOR_H
#define COLOR_H

typedef enum {
    BLACK = 0,
    RED = 1,
    GREEN = 2,
    YELLOW = 3,
    BLUE = 4,
    MAGENTA = 5,
    CYAN = 6,
    WHITE = 7
} Color;

void setColor(Color color);
void resetColor(void);
void setBackgroundColor(Color color);
void setColorAndBackground(Color textColor, Color backgroundColor);

#endif