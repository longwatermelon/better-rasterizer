#include "camera.h"


Camera::Camera(Point pos)
    : m_pos(pos) {}


void Camera::move(float x, float y, float z)
{
    m_pos.x += x;
    m_pos.y += y;
    m_pos.z += z;
}


void Camera::rotate(float x, float y)
{
    m_ha += x;
    m_va += y;
}

