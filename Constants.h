#ifndef CONSTANTS_H
#define CONSTANTS_H

const int SEP_DISTANCE = 20;
const int ALI_DISTANCE = 50;
const int COH_DISTANCE = 100;
const float SEP_FORCE = 1.7;
const float ALI_FORCE = 1;
const float COH_FORCE = 1;

const float MAX_VELOCITY = 2.0;
const float MAX_ACCELERATION = 0.03;
const float PI = 3.1415926;
const float BOID_SIGHT = 30 * PI / 180.0;

const int OVAL_STEPS = 20;
const float OVAL_PRECISION = 2 * PI / OVAL_STEPS;
const int BOID_SIZE = 10;

const int BOID_AMOUNT = 100;
const int WIDTH = 800;
const int HEIGHT = 600;
const int FPS = 40;


#endif // CONSTANTS_H
