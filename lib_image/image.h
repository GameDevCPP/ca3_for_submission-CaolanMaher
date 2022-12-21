//
// Created by caola on 20/12/2022.
//

#ifndef GAMES_ENGINEERING_IMAGE_H
#define GAMES_ENGINEERING_IMAGE_H

#include <string>
#include "SFML/Graphics/RenderWindow.hpp"
#include "maths.h"
#include <map>
#include <SFML/Graphics.hpp>

#define ir ImageReader

class ImageReader {
public:
    static void loadLevelFile(char*, float tileSize = 100.0f);
    static void unload();
    static void render(sf::RenderWindow& window);

    //typedef unsigned char Tile;
    typedef int Tile;

    // white is empty
    // black is walls
    // red is enemy
    // green is item
    // blue is end

    enum TILES {
        EMPTY = sf::Color(255.f, 255.f, 255.f).toInteger(),
        WALL = sf::Color(0.f, 0.f, 0.f).toInteger(),
        ENEMY = sf::Color(255.f, 0.f, 0.f).toInteger(),
        ITEM = sf::Color(0.f, 255.f, 0.f).toInteger(),
        END = sf::Color(0.f, 0.f, 255.f).toInteger()
    };

    static Tile getTile(sf::Vector2ul);

    static Tile getTileAt(sf::Vector2f);

    static size_t getWidth();

    static size_t getHeight();

    static sf::Vector2f getTilePosition(sf::Vector2ul);

    static std::vector<sf::Vector2ul> findTiles(Tile);

    static sf::Color getColor(Tile t);

    static void setColor(Tile t, sf::Color c);

    static void setOffset(const sf::Vector2f& _offset);

    static const sf::Vector2f& getOffset();

    static float getTileSize();

protected:
    static std::unique_ptr<Tile[]> _tiles;
    static std::unique_ptr<sf::Color[]> _tileColours;
    static size_t _width;
    static size_t _height;
    static sf::Vector2f _offset;

    static std::vector<std::unique_ptr<sf::RectangleShape>> _sprites;

    //static void buildSprites(bool optimise = true);
    static void buildSprites();

    static float _tileSize; // for rendering
    static std::map<Tile, sf::Color> _colours;

private:
    ImageReader() = delete;

    ~ImageReader() = delete;
};

#endif //GAMES_ENGINEERING_IMAGE_H
