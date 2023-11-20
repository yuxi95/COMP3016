#pragma once

#include "Object.h"

const int INIT_NODES = 3;           // initial length
const float SNAKE_SPEED = 32.0f;    // base speed

//
// snack
//

class Snake : public Object
{
public:
    Snake(Scene* scene, int style);
    ~Snake();

    void init();

    Point head() const;         // Get the head node position
    int size() const;           // return length
    void setDir(Point dir);     // set direction
    float speed() const;        // return speed
    void setSpeed(float value); // set speed
    void grow(int n);           // grow
    bool hitSelf() const;       // Determine whether you have touched yourself

    void update(float delay);
    void draw();

private:
    SDL_Texture* texHead;
    SDL_Texture* texBody;
    SDL_Texture* texTail;

    Point m_dir;        // Current snake direction
    float m_speed;      // speed

    std::vector<Point> m_nodes; // nodes
    std::deque<Point> m_path;   // path

    // drawNode
    void drawNode(int index);
};

