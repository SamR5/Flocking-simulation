#ifndef FLOCK_H
#define FLOCK_H

#include "Boid.h"
#include "Vector2D.h"
#include <string>


extern Boid** flock;

extern int SEP_DISTANCE;
extern int ALI_DISTANCE;
extern int COH_DISTANCE;
extern float SEP_FORCE;
extern float ALI_FORCE;
extern float COH_FORCE;

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

