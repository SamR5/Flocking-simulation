#ifndef FLOCK_H
#define FLOCK_H

#include "Boid.h"
#include "Vector2D.h"

extern Boid** flock;
float rand_range(int lower, int upper);
void init_field(int h, int w);
void init_flock(int amount);
Vector2D separation(Boid* B, int index);
Vector2D cohesion(Boid* B, int index);
Vector2D alignment(Boid* B, int index);
void apply_all_forces();
void reset_accelerations();
void fly_all();

#endif

