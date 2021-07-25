#pragma once
#include "common.h"


class Camera
{
public:
    Camera(Point pos);

    void move(float x, float y, float z);
    void rotate(float x, float y);

    float x() const { return m_pos.x; }
    float y() const { return m_pos.y; }
    float z() const { return m_pos.z; }

    float va() const { return m_va; }
    float ha() const { return m_ha; }

private:
    Point m_pos;
    // horizontal angle & vertical angle
    float m_ha{ 0.f }, m_va{ 0.f };
};

