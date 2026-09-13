#include <windows.h>
#include <GL/glut.h>

// Window IDs
int window1, window2;

// --- 1ST WINDOW VARIABLES (For mouse rotation) ---
float angleX = 0.0f;
float angleY = 0.0f;
int lastMouseX, lastMouseY;
bool isDragging = false;

// --- 2ND WINDOW VARIABLES (For menu) ---
int currentView = 1; // Initial view: 1 (Top)

// === ADVANCED LIGHTING AND MATERIAL SETTINGS ===
void initLighting() {
    glEnable(GL_DEPTH_TEST); // Enable depth testing (Front object occludes the back one)
    glEnable(GL_LIGHTING);   // Activate general lighting system
    glEnable(GL_LIGHT0);     // Add the main light source 0 to the scene

    // Settings that perfect light calculations and make the surface smooth
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    // 1. Light Properties
    GLfloat lightPos[] = { 10.0f, 10.0f, 10.0f, 0.0f };    // Light position (far top right)
    GLfloat lightAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };   // Ambient dim light (Low so shadows are dark)
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };   // Main diffuse light hitting the surface
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // Specular highlight (Pure white)

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    // 2. Surface Material Properties (For porcelain shine)
    GLfloat matSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat matShininess[] = { 100.0f }; // High value = smaller and sharper highlight          

    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

    // Enabling Colors to Work with Light
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

// === COMMON CAMERA SETTING ===
void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / (float)h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// ==========================================
//          1ST WINDOW FUNCTIONS
// ==========================================
void display1() {
    glutSetWindow(window1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Camera position
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Rotate model according to mouse movement
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    glColor3f(1.0f, 1.0f, 1.0f); // Teapot Color: White
    glutSolidTeapot(1.0);        // Solid Teapot to react with light

    glutSwapBuffers();
}

void mouse1(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON || button == GLUT_RIGHT_BUTTON || button == GLUT_MIDDLE_BUTTON) {
        if (state == GLUT_DOWN) {
            isDragging = true;
            lastMouseX = x;
            lastMouseY = y;
        }
        else {
            isDragging = false;
        }
    }
}

void motion1(int x, int y) {
    if (isDragging) {
        angleY += (x - lastMouseX);
        angleX += (y - lastMouseY);
        lastMouseX = x;
        lastMouseY = y;

        glutSetWindow(window1);
        glutPostRedisplay(); // Refresh screen
    }
}

// ==========================================
//          2ND WINDOW FUNCTIONS
// ==========================================
void display2() {
    glutSetWindow(window2);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Change view and color according to the value selected from the menu
    switch (currentView) {
    case 1: // From Top
        gluLookAt(0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
        glColor3f(0.0f, 1.0f, 0.0f); // Green
        break;
    case 2: // From Bottom
        gluLookAt(0.0, -5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
        glColor3f(1.0f, 1.0f, 0.0f); // Yellow
        break;
    case 3: // From Left
        gluLookAt(-5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glColor3f(0.0f, 0.0f, 1.0f); // Blue
        break;
    case 4: // From Right
        gluLookAt(5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glColor3f(0.0f, 1.0f, 1.0f); // Turquoise
        break;
    }

    glutSolidTeapot(1.0); // Solid Teapot to react with light
    glutSwapBuffers();
}

void menu(int value) {
    currentView = value;
    glutSetWindow(window2);
    glutPostRedisplay();
}

// ==========================================
//               MAIN FUNCTION
// ==========================================
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // --- 1ST WINDOW SETUP ---
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(50, 100);
    window1 = glutCreateWindow("First Window - Perspective View");

    initLighting(); // Activate lights for the 1st window

    glutDisplayFunc(display1);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse1);
    glutMotionFunc(motion1);

    // --- 2ND WINDOW SETUP ---
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(600, 100);
    window2 = glutCreateWindow("Second Window - Left/Right/Top/Down View");

    initLighting(); // Activate lights for the 2nd window

    glutDisplayFunc(display2);
    glutReshapeFunc(reshape);

    // Create and attach right-click menu
    glutCreateMenu(menu);
    glutAddMenuEntry("Top View (Green)", 1);
    glutAddMenuEntry("Bottom View (Yellow)", 2);
    glutAddMenuEntry("Left View (Blue)", 3);
    glutAddMenuEntry("Right View (Turquoise)", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    // Start the infinite loop
    glutMainLoop();
    return 0;
}