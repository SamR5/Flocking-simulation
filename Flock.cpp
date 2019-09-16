#include "Constants.h"
#include "Flock.h"
#include "Boid.h"
#include "Vector2D.h"
#include <random>
#include <ctime>
#include <fstream>
#include <string>



int height;
int width;
Boid** flock = nullptr;
int boidAmount;

float rand_range(int lower, int upper) {
    return lower + rand()%(upper - lower);
}

void init_field(int h, int w) {
    std::srand(std::time(0));
    height = h;
    width = w;
}

void init_flock(int amount) {
    boidAmount = amount;
    flock = new Boid* [boidAmount];
    for (int i=0; i<boidAmount; i++) {
        flock[i] = new Boid(rand_range(0, width), rand_range(0, height),
                            rand_range(-MAX_VELOCITY, MAX_VELOCITY),
                            rand_range(-MAX_VELOCITY, MAX_VELOCITY),
                            width, height, MAX_VELOCITY, BOID_SIGHT);
    }
}

Vector2D separation(Boid* B, int index) {
    float tempDist;
    Boid* other;
    int sepCounter(0);
    Vector2D steer(0.0, 0.0);
    for (int i=0; i<boidAmount; i++) {
        if (i == index)
            continue;
        other = flock[i];
        tempDist = B->distance(other);
        if (tempDist <= SEP_DISTANCE) {
            Vector2D diff(B->get_position());
            diff -= Vector2D(other->get_position()); // in cohesion +=
            diff.normalize();
            steer += diff / tempDist;
            sepCounter++;
        }
    }
    if (sepCounter > 0)
        steer /= (float)sepCounter;
    if (steer.length() > 0) {
        steer.normalize();
        steer *= (float)MAX_VELOCITY;
        steer -= B->get_xy_velocity();
        steer.limit_to(MAX_ACCELERATION);
    }
    return steer;
}

Vector2D cohesion(Boid* B, int index) {
    float tempDist;
    Boid* other;
    int cohCounter(0);
    Vector2D sum(0.0, 0.0);
    for (int i=0; i<boidAmount; i++) {
        if (i == index)
            continue;
        other = flock[i];
        tempDist = B->distance(other);
        if (tempDist <= COH_DISTANCE) {
            sum += other->get_position(); // in separation -=
            cohCounter++;
        }
    }
    if (cohCounter > 0) {
        sum /= (float)cohCounter;
        Vector2D desired(sum - B->get_position());
        desired.normalize();
        desired *= (float)MAX_VELOCITY;
        Vector2D steer(desired - B->get_xy_velocity());
        steer.limit_to(MAX_ACCELERATION);
        return steer;
    }
    else {
        return Vector2D(0.0, 0.0);
    }
}

Vector2D alignment(Boid* B, int index) {
    float tempDist;
    Vector2D sum(0.0, 0.0);
    float aliCounter(0);
    Boid* other;
    for (int i=0; i<boidAmount; i++) {
        if (i == index)
            continue;
        other = flock[i];
        tempDist = B->distance(other);
        if (tempDist <= ALI_DISTANCE) {
            if (B->in_sight(other)) {
                sum += other->get_xy_velocity();
                aliCounter++;
            }
        }
    }
    if (aliCounter > 0) {
        sum /= aliCounter;
        sum.normalize();
        sum *= MAX_VELOCITY;
        Vector2D steer(sum - B->get_xy_velocity());
        steer.limit_to(MAX_ACCELERATION);
        return steer;
    }
    else
        return Vector2D(0.0, 0.0);
}

void apply_all_forces() {
    Boid* current;
    for (int i=0; i<boidAmount; i++) {
        current = flock[i];
        current->reset_acceleration();
        Vector2D sep(separation(current, i) * SEP_FORCE);
        Vector2D coh(cohesion(current, i) * COH_FORCE);
        Vector2D ali(alignment(current, i) * ALI_FORCE);
        current->add_acceleration(sep + coh + ali);
    }
    for (int i=0; i<boidAmount; i++) {
        current->fly();
        current->check_out_of_field();
    }
}

void reset_accelerations() {
    for (int i=0; i<boidAmount; i++) {
        flock[i]->reset_acceleration();
    }
}

void fly_all() {
    for (int i=0; i<boidAmount; i++) {
        flock[i]->fly();
    }
}
