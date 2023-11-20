#include "Snake.h"
#include "Scene.h"


Snake::Snake(Scene* scene, int style) : Object(scene)
{
    if (style == 0) {
        texHead = loadTexture(scene->renderer(), "../snake_head.png");
        texBody = loadTexture(scene->renderer(), "../snake_body.png");
        texTail = loadTexture(scene->renderer(), "../snake_tail.png");
    }
    else {
        texHead = loadTexture(scene->renderer(), "../snake_head2.png");
        texBody = loadTexture(scene->renderer(), "../snake_body2.png");
        texTail = loadTexture(scene->renderer(), "../snake_tail2.png");
    }
}

Snake::~Snake()
{
    freeTexture(texHead);
    freeTexture(texBody);
    freeTexture(texTail);
}

void Snake::init()
{
    float x = 800 / 2;
    float y = 600 / 2;

    m_nodes.clear();
    m_path.clear();
    for (int i = 0; i < INIT_NODES; ++i) {
        Point pos = Point(x, y);
        m_nodes.push_back(pos);
        //y += 10.0f;
    }

    // initial direction and speed
    m_dir = Point(0.0f, -1.0f);
    m_speed = SNAKE_SPEED;
}

// Get the head node position
Point Snake::head() const
{
    return m_nodes[0];
}

// Return length
int Snake::size() const
{
    return (int) m_nodes.size();
}

// set direction
void Snake::setDir(Point dir)
{
    m_dir = dir * (1.0f / length(dir)); // normalized vector
}

// return speed
float Snake::speed() const
{
    return m_speed;
}

//Set speed
void Snake::setSpeed(float value)
{
    m_speed = value;
}

// increase snack
void Snake::grow(int n)
{
    Point node = m_nodes.back();
    for (int i = 0; i < n; ++i) {
        m_nodes.push_back(node);
    }
}

// Determine whether you have touched yourself
bool Snake::hitSelf() const
{
    Point p = m_nodes[0];
    for (size_t i = INIT_NODES; i < m_nodes.size(); ++i) {
        float d = length(m_nodes[i] - p);
        if (d < 20.0f) {// head size
            return true;
        }
    }
    return false;
}

void Snake::update(float delay)
{
    // move
    Point pos = m_nodes.front();
    Point v = m_dir * m_speed * delay;
    pos = pos + v;
    m_nodes[0] = pos;

    // through walls
    if (m_nodes[0].x < 0.0f) {
        m_nodes[0].x += 800;
    }
    else if (m_nodes[0].x >= 800) {
        m_nodes[0].x -= 800;
    }
    if (m_nodes[0].y < 0.0f) {
        m_nodes[0].y += 600;
    }
    else if (m_nodes[0].y >= 600) {
        m_nodes[0].y -= 600;
    }

    // path
    m_path.push_front(pos);

    const size_t n = 32;
    size_t id;
    for (size_t i = n; i < m_path.size(); ++i) {
        if ((i % n) == 0) {
            id = i / n;
            if (id < m_nodes.size()) {
                m_nodes[id] = m_path[i];
            }
            else {
                // Delete the following path
                m_path.erase(m_path.begin() + i, m_path.end());
                break;
            }
        }
    }
}

void Snake::draw()
{
    // draw trajectory
    SDL_SetRenderDrawColor(scene()->renderer(), 255, 0, 0, 128);
    for (size_t i = 1; i < m_path.size(); ++i) {
        //SDL_RenderDrawLineF(scene()->renderer(), m_path[i - 1].x, m_path[i - 1].y, m_path[i].x, m_path[i].y);
    }


    for (int i = (int) m_nodes.size() - 1; i >= 0; --i) {
        drawNode(i);
    }
}

// drawNode
void Snake::drawNode(int index)
{
    Point pos = m_nodes[index];
    SDL_Texture* tex;
    float angle;

    if (index == 0) {// head
        angle = degreeAngle(m_dir);
        tex = texHead;
    }
    else if (index == (int) m_nodes.size() - 1) { // tail
        angle = 0.0f;
        tex = texTail;
    }
    else {// body
        angle = 0.0f;
        tex = texBody;
    }

    int w, h;
    SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
    w /= 2;
    h /= 2;

    SDL_Rect dest = { pos.x - w / 2, pos.y - h / 2, w, h };
    SDL_SetTextureColorMod(tex, 255, 255, 255);
    SDL_SetTextureAlphaMod(tex, 255);
    SDL_RenderCopyEx(scene()->renderer(), tex, nullptr, &dest, angle, nullptr, SDL_FLIP_NONE);
}
