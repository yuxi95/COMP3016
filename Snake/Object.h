#pragma once

#include "pch.h"

class Scene;

//
// ����������
//

class Object
{
public:
    Object(Scene* scene);
    ~Object();

    Scene* scene() const;

    virtual void update(float delay) {}
    virtual void draw() {}

private:
    Scene* m_scene;
};
