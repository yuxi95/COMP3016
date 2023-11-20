#include "Fruit.h"
#include "Scene.h"

Fruit::Fruit(Scene* scene) : Object(scene)
{
    int n = rand() % 5;
    setType((FruitType) n);
    m_pos = Point(rand() % 800, rand() % 600);
    m_size = 10.0f;

    m_texture = loadTexture(scene->renderer(), "../soft.png");
}

Fruit::~Fruit()
{
    if (m_texture) {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }
}

// 获取类型
FruitType Fruit::getType() const
{
    return m_type;
}

// 设置类型
void Fruit::setType(FruitType type)
{
    m_type = type;

    switch (type) {
    case FruitType::Black:
        m_color = Color(0, 0, 0);
        break;
    case FruitType::Bronw:
        m_color = Color(128, 64, 0);
        break;
    case FruitType::Red:
        m_color = Color(255, 0, 0);
        break;
    case FruitType::Blue:
        m_color = Color(0, 0, 255);
        break;
    case FruitType::Green:
        m_color = Color(0, 128, 0);
        break;
    default:
        break;
    }
}

// 获取位置
Point Fruit::position() const
{
    return m_pos;
}

// 设置位置
void Fruit::setPosition(Point pos)
{
    m_pos = pos;
}

// 设置位置
void Fruit::setPosition(float x, float y)
{
    m_pos = Point(x, y);
}

// 返回大小
float Fruit::size() const
{
    return m_size;
}

// 设置大小
void Fruit::setSize(float value)
{
    m_size = value;
}

void Fruit::update(float delay)
{
}

void Fruit::draw()
{
    SDL_Renderer* renderer = scene()->renderer();

    SDL_Rect rect = { m_pos.x - m_size * 0.5f, m_pos.y - m_size * 0.5f, m_size, m_size };
    SDL_SetTextureColorMod(m_texture, m_color.r, m_color.g, m_color.b);
    SDL_SetTextureAlphaMod(m_texture, m_color.a);
    SDL_RenderCopy(renderer, m_texture, nullptr, &rect);
}