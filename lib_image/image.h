//
// Created by caola on 20/12/2022.
//

#ifndef GAMES_ENGINEERING_IMAGE_H
#define GAMES_ENGINEERING_IMAGE_H

#include <vector>

struct Colour {
    float r, g, b;

    Colour();
    Colour(float r, float g, float b);
};

class Image {
public:
    Image(int width, int height);
    ~Image();

    Colour getColour(int x, int y);
    void setColour(const Colour& colour, int x, int y);

    void Export(const char* path);

private:
    int m_width;
    int m_height;
    std::vector<Colour> m_colours;
};

#endif //GAMES_ENGINEERING_IMAGE_H
