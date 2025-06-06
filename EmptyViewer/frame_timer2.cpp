#define _CRT_SECURE_NO_WARNINGS

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <vector>
#include <string>
#include <cmath>

struct Vector3 {
    float x, y, z;
};

struct Triangle {
    unsigned int indices[3];
};

extern std::vector<Vector3> gPositions;
extern std::vector<Vector3> gNormals;
extern std::vector<Triangle> gTriangles;

GLuint gVBO[2];
GLuint gVAO;
GLuint gTimer;
float gTotalTimeElapsed = 0;
int gTotalFrames = 0;

void load_mesh(std::string fileName);
void init_timer();
void setup_buffers();
void display();

void init_timer() {
    glGenQueries(1, &gTimer);
}

void start_timing() {
    glBeginQuery(GL_TIME_ELAPSED, gTimer);
}

float stop_timing() {
    glEndQuery(GL_TIME_ELAPSED);
    GLint available = GL_FALSE;
    while (available == GL_FALSE)
        glGetQueryObjectiv(gTimer, GL_QUERY_RESULT_AVAILABLE, &available);

    GLint result;
    glGetQueryObjectiv(gTimer, GL_QUERY_RESULT, &result);
    return result / (1000.0f * 1000.0f * 1000.0f); // ns -> s
}

void setup_buffers() {
    std::vector<Vector3> vertexData;
    std::vector<Vector3> normalData;

    for (const auto& tri : gTriangles) {
        for (int i = 0; i < 3; ++i) {
            vertexData.push_back(gPositions[tri.indices[i]]);
            normalData.push_back(gNormals[tri.indices[i]]);
        }
    }

    glGenVertexArrays(1, &gVAO);
    glBindVertexArray(gVAO);

    glGenBuffers(2, gVBO);

    // Vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, gVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(Vector3), vertexData.data(), GL_STATIC_DRAW);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glEnableClientState(GL_VERTEX_ARRAY);

    // Normal buffer
    glBindBuffer(GL_ARRAY_BUFFER, gVBO[1]);
    glBufferData(GL_ARRAY_BUFFER, normalData.size() * sizeof(Vector3), normalData.data(), GL_STATIC_DRAW);
    glNormalPointer(GL_FLOAT, 0, 0);
    glEnableClientState(GL_NORMAL_ARRAY);

    glBindVertexArray(0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);

    // Light setup
    GLfloat globalAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

    GLfloat light_pos[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    GLfloat ka[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat kd[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat ks[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ka);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, kd);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ks);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    glPushMatrix();
    glTranslatef(0.1f, -1.0f, -1.5f);
    glScalef(10.0f, 10.0f, 10.0f);

    start_timing();

    glBindVertexArray(gVAO);
    glDrawArrays(GL_TRIANGLES, 0, gTriangles.size() * 3);
    glBindVertexArray(0);

    float timeElapsed = stop_timing();
    gTotalFrames++;
    gTotalTimeElapsed += timeElapsed;
    float fps = gTotalFrames / gTotalTimeElapsed;

    char title[128];
    sprintf(title, "OpenGL Bunny Q2 (VAO): %.2f FPS", fps);
    glutSetWindowTitle(title);

    glPopMatrix();
    glutSwapBuffers();
    glutPostRedisplay();
}

