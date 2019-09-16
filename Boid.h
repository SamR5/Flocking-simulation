#ifndef BOID_H
#define BOID_H

#include "Vector2D.h"

class Boid {
    private:
        Vector2D m_position;
        Vector2D m_velocity;
        Vector2D m_acceleration;
        float m_xLim; // screen limits
        float m_yLim;
        float m_maxV;
        float m_demiSight;
    
    public:
        Boid(float x, float y, float Vx, float Vy,
             float limX, float limY, float maxV, float sight);
        float distance(Boid* other);
        //
        float get_x_pos();
        float get_y_pos();
        Vector2D get_position();
        float get_x_vel();
        float get_y_vel();
        Vector2D get_xy_velocity();
        float get_velocity();
        float get_heading();
        bool in_sight(Boid* other);
        //
        void check_out_of_field();
        void reset_acceleration();
        void add_acceleration(Vector2D acc);
        void fly();
        
};


#endif

