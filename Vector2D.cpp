#include "Vector2D.h"
#include <cmath>


Vector2D::Vector2D() {
    m_x = 0.0;
    m_y = 0.0;
}

Vector2D::Vector2D(float x, float y) {
    m_x = x;
    m_y = y;
}

float Vector2D::get_x() {
    return m_x;
}

float Vector2D::get_y() {
    return m_y;
}

float Vector2D::length() {
    return std::sqrt(m_x*m_x + m_y*m_y);
}

float Vector2D::angle() {
    if (m_y >= 0)
        return std::acos(m_x / length());
    else
        return -std::acos(m_x / length());
}

void Vector2D::normalize() {
    float len(length());
    if (len == 0.0)
        return;
    m_x /= len;
    m_y /= len;
}

void Vector2D::limit_to(float lim) {
    if (length() > lim) {
        float ratio(lim / length());
        m_x *= ratio;
        m_y *= ratio;
    }
}

Vector2D Vector2D::operator+(Vector2D other) {
    *this += other;
    return *this;
}

Vector2D Vector2D::operator-(Vector2D other) {
    *this -= other;
    return *this;
}

Vector2D Vector2D::operator-(float n) {
    *this -= n;
    return *this;
}

Vector2D Vector2D::operator*(Vector2D other) {
    *this *= other;
    return *this;
}

Vector2D Vector2D::operator*(float n) {
    *this *= n;
    return *this;
}

Vector2D Vector2D::operator/(Vector2D other) {
    *this /= other;
    return *this;
}

Vector2D Vector2D::operator/(float n) {
    *this /= n;
    return *this;
}

void Vector2D::operator+=(Vector2D other) {
    m_x += other.get_x();
    m_y += other.get_y();
}

void Vector2D::operator-=(Vector2D other) {
    m_x -= other.get_x();
    m_y -= other.get_y();
}

void Vector2D::operator-=(float n) {
    m_x -= n;
    m_y -= n;
}

void Vector2D::operator*=(Vector2D other) {
    m_x *= other.get_x();
    m_y *= other.get_y();
}

void Vector2D::operator*=(float n) {
    m_x *= n;
    m_y *= n;
}

void Vector2D::operator/=(Vector2D other) {
    m_x /= other.get_x();
    m_y /= other.get_y();
}

void Vector2D::operator/=(float n) {
    m_x /= n;
    m_y /= n;
}


