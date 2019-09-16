#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D {
    private:
        float m_x;
        float m_y;
    
    public:
        Vector2D();
        Vector2D(float x, float y);
        float get_x();
        float get_y();
        float length();
        float angle();
        void normalize();
        void limit_to(float lim);

        Vector2D operator+(Vector2D other);
        Vector2D operator-(Vector2D other);
        Vector2D operator-(float n);
        Vector2D operator*(Vector2D other);
        Vector2D operator*(float n);
        Vector2D operator/(Vector2D other);
        Vector2D operator/(float n);
        void operator+=(Vector2D other);
        void operator-=(Vector2D other);
        void operator-=(float n);
        void operator*=(Vector2D other);
        void operator*=(float n);
        void operator/=(Vector2D other);
        void operator/=(float n);

};


#endif
