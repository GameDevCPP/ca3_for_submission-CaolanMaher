//
// Created by caola on 20/12/2022.
//
#include "image.h"

#include <iostream>
#include <fstream>

Colour::Colour() {
    r = 0;
    g = 0;
    b = 0;
}

Colour::Colour(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

Image::Image(int width, int height) {
    m_width = width;
    m_height = height;
    m_colours = std::vector<Colour>(width * height);
}

Colour Image::getColour(int x, int y) {
    // read from left to right then by row
    return m_colours[y * m_width + x];
}

void Image::setColour(const Colour& colour, int x, int y) {
    m_colours[y * m_width + x].r = colour.r;
    m_colours[y * m_width + x].g = colour.g;
    m_colours[y * m_width + x].b = colour.b;
}

void Image::Export(const char *path) {
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);

    if(!f.is_open()) {
        std::cout << "File cannot be opened" << std::endl;
    }
}
