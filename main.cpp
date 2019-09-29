/*

Flocking simulation

*/

#include <GL/gl.h>
#include <GL/glut.h>

#include <iostream>
#include <cmath>
#include <chrono>
#include <string>
#include "Constants.h"
#include "Boid.h"
#include "Flock.h"


void draw_arrowR(float x, float y, float height, float angle);
void draw_tiles();
void draw_boids();
void draw_quarter_circle(int radius);
void draw_distances();

void init();
void display_callback();
void reshape_callback(int width, int height);
void timer_callback(int);
void keyboard_special_callback(int special, int x, int y);
void keybaord_callback(unsigned char key, int x, int y);

// selection index to change settings
int selectedRow;
int selectedCol;


void write_string(std::string str, float x, float y) {
    glRasterPos2f(x, y);
    // pointer to beginning of the string to the end char
    //for (const char *c=str; *c != '\0'; c++)  {
    for (char c : str) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }
}

void draw_text_labels() {
    glColor3f(0, 0, 0);
    int col0(10), col1(100), col2(200), col3(300);
    int row0(20), row1(45), row2(70);
    // draw labels
    write_string("DISTANCE", col0, row0);
    write_string("FORCE", col0, row1);
    write_string("SEPARATION", col1, row2);
    write_string("ALIGNMENT", col2, row2);
    write_string("COHESION", col3, row2);
    // draw values
    write_string(std::to_string(SEP_DISTANCE), col1, row0);
    write_string(std::to_string(ALI_DISTANCE), col2, row0);
    write_string(std::to_string(COH_DISTANCE), col3, row0);
    write_string(std::to_string(SEP_FORCE), col1, row1);
    write_string(std::to_string(ALI_FORCE), col2, row1);
    write_string(std::to_string(COH_FORCE), col3, row1);
    // rectangle selected value
    int x1, y1;
    switch (selectedRow) {
      case 0: y1 = row0; break;
      case 1: y1 = row1; break;
    }
    switch (selectedCol) {
      case 0: x1 = col1; break;
      case 1: x1 = col2; break;
      case 2: x1 = col3; break;
    }
    glColor3f(0, 1, 0);
    glBegin(GL_LINE_LOOP);
      glVertex2f(x1, y1-5);
      glVertex2f(x1+75, y1-5);
      glVertex2f(x1+75, y1+25-5);
      glVertex2f(x1, y1+25-5);
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

void draw_tiles() {
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

void draw_boids() {
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
        draw_arrowR(tempX, tempY, BOID_SIZE, b->get_heading());
    }
}

void draw_quarter_circle(int radius) {
    glBegin(GL_LINE_STRIP);
      for (float i=PI/2; i<PI+0.2; i+=PI/100) {
          glVertex2f(WIDTH+radius*std::cos(i), radius*std::sin(i));
      }
    glEnd();
}

void draw_distances() {
    glColor3f(0, 0, 0);
    draw_quarter_circle(SEP_DISTANCE);
    draw_quarter_circle(ALI_DISTANCE);
    draw_quarter_circle(COH_DISTANCE);
}

void init() {
    glClearColor (1.0f, 1.0f, 1.0f, 0.0f);
    selectedRow = 0;
    selectedCol = 0;
    init_field(HEIGHT, WIDTH);
    init_flock(BOID_AMOUNT);
}

void display_callback() {
    glClear (GL_COLOR_BUFFER_BIT);
    
    draw_boids();
    //draw_tiles();
    draw_text_labels();
    draw_distances();
    
    glutSwapBuffers();
}

void reshape_callback(int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei) height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int margin(0);
    glOrtho(0.0-margin, (double)WIDTH+margin, 0.0-margin, (double)HEIGHT+margin, -1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer_callback(int) {
    auto start(std::chrono::steady_clock::now());
    apply_all_forces();
    fly_all();
    glutPostRedisplay(); // run the display_callback function
    auto stop(std::chrono::steady_clock::now());
    auto duration(std::chrono::duration_cast<std::chrono::milliseconds>(stop-start));
    float sleep(1000.0/FPS - duration.count());
    glutTimerFunc((sleep>0) ? sleep : 0, timer_callback, 0);
}

void keyboard_special_callback(int special, int x, int y) {
    switch (special) {
        case GLUT_KEY_LEFT:
          selectedCol--; break;
        case GLUT_KEY_RIGHT:
          selectedCol++; break;
        case GLUT_KEY_UP:
          selectedRow--; break;
        case GLUT_KEY_DOWN:
          selectedRow++; break;
    }
    if (selectedRow<0)
        selectedRow = 1;
    if (selectedCol<0)
        selectedCol = 2;
    selectedRow %= 2;
    selectedCol %= 3;
}

void keybaord_callback(unsigned char key, int x, int y) {
    float add = (selectedRow==0) ? 1 : 0.05;
    if (key == '-')
        add *= -1;
    else if (key != '+')
        return;
    switch (selectedCol) {
      case 0:
        (selectedRow==0) ? SEP_DISTANCE += add : SEP_FORCE += add;
        break;
      case 1:
        (selectedRow==0) ? ALI_DISTANCE += add : ALI_FORCE += add;
        break;
      case 2:
        (selectedRow==0) ? COH_DISTANCE += add : COH_FORCE += add;
        break;
    }
}


int main(int argc, char **argv) {
    glutInit(&argc, argv); // initialize
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(15, 15); // optional
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Flocking Simulation");
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutTimerFunc(1000/FPS, timer_callback, 0);
    glutKeyboardFunc(keybaord_callback);
    glutSpecialFunc(keyboard_special_callback);
    init();
    glutMainLoop();
    return 0;
}
