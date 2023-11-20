#pragma once

#include "Object.h"

//Different fruits correspond to different scores (corresponding scores increase the corresponding length of the snake body). There are 5 types in total.
enum class FruitType
{
    Black,      // black No points
    Bronw,      // Bronw No points
    Red,        // Red 3points
    Blue,       // Blue 2points
    Green,      // Green 1points
};

class Fruit : public Object
{
public:
    Fruit(Scene* scene);
    ~Fruit();

    FruitType getType() const;          // get type
    void setType(FruitType type);       // Set type   

    Point position() const;             // get type
    void setPosition(Point pos);        // Set type   

    void setPosition(float x, float y);

    float size() const; // Return size
    void setSize(float value); // set size

    void update(float delay);
    void draw();

private:
    FruitType m_type;   // type
    Color m_color;      // draw color
    Point m_pos;        // location
    float m_size;       // size

    SDL_Texture* m_texture; // texture
};

