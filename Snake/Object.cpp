#include "Object.h"

Object::Object(Scene* scene) : m_scene(scene)
{
}

Object::~Object()
{
}

Scene* Object::scene() const
{
    return m_scene;
}