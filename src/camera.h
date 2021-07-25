#pragma once
#include "common.h"


class Camera
{
public:
    Camera(Point pos);

    void move(float x, float y, float z);

    float x() const { return m_pos.x; }
    float y() const { return m_pos.y; }
    float z() const { return m_pos.z; }

private:
    Point m_pos;
};

