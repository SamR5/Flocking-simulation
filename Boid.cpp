#include "Boid.h"
#include "Vector2D.h"
#include <cmath>


Boid::Boid(float x, float y, float Vx, float Vy,
           float limX, float limY, float maxV, float sight) {
    m_position = Vector2D(x, y);
    m_velocity = Vector2D(Vx, Vy);
    m_acceleration = Vector2D(0.0, 0.0);
    m_xLim = limX;
    m_yLim = limY;
    m_maxV = maxV;
    m_demiSight = sight/2;
}

float Boid::distance(Boid* other) {
    float diffx(other->get_x_pos() - m_position.get_x());
    float diffy(other->get_y_pos() - m_position.get_y());
    return std::sqrt(diffx*diffx + diffy*diffy);
}

float Boid::get_x_pos() {
    return m_position.get_x();
}

float Boid::get_y_pos() {
    return m_position.get_y();
}

Vector2D Boid::get_position() {
    return m_position;
}

float Boid::get_x_vel() {
    return m_velocity.get_x();
}

float Boid::get_y_vel() {
    return m_velocity.get_y();
}

Vector2D Boid::get_xy_velocity() {
    return m_velocity;
}

float Boid::get_velocity() {
    return m_velocity.length();
}

float Boid::get_heading() {
    if (m_velocity.get_y() >= 0)
        return std::acos(m_velocity.get_x() / m_velocity.length());
    else
        return -std::acos(m_velocity.get_x() / m_velocity.length());
}

bool Boid::in_sight(Boid* other) {
    Vector2D otherPos(other->get_position());
    float diff(std::abs(m_position.angle() - otherPos.angle()));
    if (diff < m_demiSight)
        return true;
    return false;
}

void Boid::check_out_of_field() {
    if (m_position.get_x() > m_xLim)
        m_position -= Vector2D(m_xLim, 0.0);
    if (m_position.get_x() < 0)
        m_position += Vector2D(m_xLim, 0.0);
    if (m_position.get_y() > m_yLim)
        m_position -= Vector2D(0.0, m_yLim);
    if (m_position.get_y() < 0)
        m_position += Vector2D(0.0, m_yLim);
}

void Boid::reset_acceleration() {
    m_acceleration = Vector2D(0.0, 0.0);
}

void Boid::add_acceleration(Vector2D acc) {
    m_acceleration += acc;
}

void Boid::fly() {
    m_velocity += m_acceleration;
    m_velocity.limit_to(m_maxV);
    m_position += m_velocity;
    check_out_of_field();
}
