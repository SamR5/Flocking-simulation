/**************************
 * Includes
 *
 **************************/

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <fstream>
#include <cmath>
#include <chrono>
#include "Constants.h"
#include "Boid.h"
#include "Flock.h"


/**************************
 * Function 2D
 *
 **************************/

void draw_arrow(float x, float y, float height, float width) {
    glBegin(GL_POLYGON);
      glVertex2f(x, y + height/2);
      glVertex2f(x - width/2, y - height/2);
      glVertex2f(x, y - height/5);
      glVertex2f(x + width/2, y - height/2);
    glEnd();
}

void draw_arrowR(float x, float y, float height, float angle) {
    float h2(height / 2);
    float h4(height / 4);
    glBegin(GL_POLYGON);
      glVertex2f(x + std::cos(angle)*h2, y + std::sin(angle)*h2);
      glVertex2f(x + std::cos(angle+0.8*PI)*h2, y + std::sin(angle+0.8*PI)*h2);
      glVertex2f(x + std::cos(angle+PI)*h4, y + std::sin(angle+PI)*h4);
      glVertex2f(x + std::cos(angle-0.8*PI)*h2, y + std::sin(angle-0.8*PI)*h2);
    glEnd();
}

void draw_oval(float x, float y, float xLen, float yLen) {
    glBegin(GL_POLYGON);
    for (float i=0; i<2*PI; i+=OVAL_PRECISION) {
        glVertex2f(x + std::cos(i) * BOID_SIZE, y + std::sin(i) * BOID_SIZE);
    }
    glEnd();
}

void draw_all() {
    float tempX;
    float tempY;
    float relatVel;
    Boid* b;
    for (int i=0; i<BOID_AMOUNT-1; i++) {
        b = flock[i];
        b->check_out_of_field();
        tempX = b->get_x_pos();
        tempY = b->get_y_pos();
        relatVel = b->get_velocity() / 2.0;
        glColor3f(1.0, 1 - relatVel, 1 - relatVel);
        //glRectf(tempX-BOID_SIZE, tempY-BOID_SIZE,
        //        tempX+BOID_SIZE, tempY+BOID_SIZE);
        //draw_oval(tempX, tempY, BOID_SIZE/2, BOID_SIZE/2);
        //draw_arrow(tempX, tempY, BOID_SIZE, BOID_SIZE/2);
        draw_arrowR(tempX, tempY, BOID_SIZE, b->get_heading());
    }
    glColor3f(0.0, 0.0, 0.0);
    for (int i=0; i<WIDTH; i+=100) {
        glBegin(GL_LINES);
          glVertex2f(i, 0.0);
          glVertex2f(i, HEIGHT);
        glEnd();
    }
    for (int i=0; i<HEIGHT; i+=100) {
        glBegin(GL_LINES);
          glVertex2f(0.0, i);
          glVertex2f(WIDTH, i);
        glEnd();
    }
}

void init() {
    init_field(HEIGHT, WIDTH);
    init_flock(BOID_AMOUNT);
}

void display_callback() {
    auto start(std::chrono::steady_clock::now());

    glClearColor (1.0f, 1.0f, 1.0f, 0.0f);
    glClear (GL_COLOR_BUFFER_BIT);

    apply_all_forces();
    fly_all();

    draw_all();
    glutSwapBuffers();

    auto stop(std::chrono::steady_clock::now());
    auto duration(std::chrono::duration_cast<std::chrono::milliseconds>(stop-start));
    //sleep(std::abs(1000.0/FPS - duration.count()))
}

void reshape_callback(int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei) height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (double)WIDTH, 0.0, (double)HEIGHT, -1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer_callback(int) {
    glutPostRedisplay(); // run the display_callback function
    glutTimerFunc(1000.0/FPS, timer_callback, 0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv); // initialize
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(15, 15); // optional
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Flocking Simulation");
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutTimerFunc(1000/FPS, timer_callback, 0);
    init();
    glutMainLoop();
    return 0;
}
