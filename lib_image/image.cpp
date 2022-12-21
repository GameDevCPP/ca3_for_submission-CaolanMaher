#include "image.h"

/*
unsigned char* readBMP(char* filename)
{
    int i;
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];

    // read the 54-byte header
    fread(info, sizeof(unsigned char), 54, f);

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    // allocate 3 bytes per pixel
    int size = 3 * width * height;
    unsigned char* data = new unsigned char[size];

    // read the rest of the data at once
    fread(data, sizeof(unsigned char), size, f);
    fclose(f);

    for(i = 0; i < size; i += 3)
    {
        // flip the order of every 3 bytes
        unsigned char tmp = data[i];
        data[i] = data[i+2];
        data[i+2] = tmp;
    }

    return data;
}
*/

using namespace std;
using namespace sf;

std::unique_ptr<ImageReader::Tile[]> ImageReader::_tiles;
size_t ImageReader::_width;
size_t ImageReader::_height;

float ImageReader::_tileSize(100.0f);
Vector2f ImageReader::_offset(0.0f, 30.0f);
vector<std::unique_ptr<sf::RectangleShape>> ImageReader::_sprites;

void ImageReader::loadLevelFile(char* path, float tileSize) {
    _tileSize = tileSize;
    size_t w = 0;
    size_t h = 0;
    string buffer;

    int i;
    FILE* f = fopen(path, "rb");

    buffer.resize(f->_bufsiz);

    unsigned char info[54];

    // read the 54-byte header
    fread(info, sizeof(unsigned char), 54, f);

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    // allocate 3 bytes per pixel
    int size = 3 * width * height;
    unsigned char* data = new unsigned char[size];

    // read the rest of the data at once
    fread(data, sizeof(unsigned char), size, f);
    fclose(f);

    std::vector<Tile> temp_tiles;

    for(i = 0; i < size; i += 3)
    {
        // flip the order of every 3 bytes
        // b, g, r -> r, g, b
        unsigned char tmp = data[i];
        data[i] = data[i+2];
        data[i+2] = tmp;

        Color c = Color(data[i], data[i + 1], data[i + 2]);

        // if white
        if(c.r == 255 && c.g == 255 && c.b == 255) {
            temp_tiles.push_back(EMPTY);
        }
        else if(c.r == 0 && c.g == 0 && c.b == 0) {
            temp_tiles.push_back(WALL);
        }
    }

    /*
    for(i = 0; i < size / 3; i++) {
        temp_tiles[i] = Color(data[i], data[i + 1], data[i + 2]).toInteger();
    }
    */

    _tiles = std::make_unique<Tile[]>(w * h);
    _width = w;
    _height = h;
    cout << "Level " << path << " Loaded. " << w << "x" << h << std::endl;

    for(int x = 0; x < temp_tiles.size(); x++) {
        cout << x << " " << temp_tiles[x] << endl;
    }
}

