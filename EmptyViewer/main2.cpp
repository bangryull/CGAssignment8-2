#define _CRT_SECURE_NO_WARNINGS
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <vector>
#include <string>

void load_mesh(std::string fileName);
void setup_buffers();
void init_timer();
void display();

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1280, 1280);
    glutCreateWindow("Assignment 8 - Q2");

    glewInit();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 1000.0);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    load_mesh("bunny.obj");
    init_timer();
    setup_buffers();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}