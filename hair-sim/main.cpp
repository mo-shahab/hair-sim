#include <iostream>
#include <fstream>
#include <cstdlib>
#include <GL/glut.h>

// including the opengl
// 
// the addi header files
#include "model.h"
#include "rendering.h"
#include "physics.h"

std::ofstream errorLog;// Declare the error log file stream
GLuint shaderProgram;
int window;
unsigned char currentKey = 0;

// Assuming the center of the sphere is at the origin (0, 0, 0)
glm::vec3 sphereCenter(0.0f, 0.0f, 0.0f);

float lengthSquared(const glm::vec3& vec) {
    return glm::dot(vec, vec);
}


Model model("C:/Users/User/OneDrive/Documents/opengl_rend/hairfin.obj");

// Function to check and log OpenGL errors
void checkGLErrors(const std::string& message)
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        errorLog << "OpenGL Error (" << message << "): " << error << std::endl;
    }
}

// this would be handy if i ever dynamically allot mem
void cleanup()
{
    // Close the error log file
    errorLog.close();
}

// this is to update the value so that i can pass this in the rendering.cpp file
void keyboardCallback(unsigned char key, int x, int y) {
    currentKey = key;
    processKeyboard(currentKey, x, y);
}

void keyboardUpCallback(unsigned char key, int x, int y) {
    processKeyboardRelease(key, x, y);
}


void initializeGLAD() {
    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }
}

void initializeOpenGL(int argc, char** argv)
{
    // isolating the hair vertices and all the vertices
    //IsolateVertices(model.vertices, hairVertices, sphereVertices); 

    // Desired aspect ratio
    float aspectRatio = 16.0f / 9.0f;

    // Calculate the window width and height based on the aspect ratio
    int windowWidth = 800;  // Adjust the width as needed
    int windowHeight = static_cast<int>(windowWidth / aspectRatio);
    // Initialize GLUT and create a window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    window = glutCreateWindow("hair simulation");

    // Set the keyboard callback function for special keys
    //glutSpecialFunc(processKeyboardInput);
    glutKeyboardFunc(keyboardCallback);
    glutKeyboardUpFunc(keyboardUpCallback);

    // Initialize GLAD
    initializeGLAD();
    // Open the error log file
    errorLog.open("opengl_errors.txt");
    if (!errorLog.is_open()) {
        std::cerr << "Failed to open error log file" << std::endl;
        exit(-1);
    }
}

// Function to calculate the aspect ratio
float calculateAspectRatio() {
    // Calculate the aspect ratio based on the window size or desired value
    // Replace this with your own logic to calculate the aspect ratio
    int screenWidth = glutGet(GLUT_WINDOW_WIDTH);
    int screenHeight = glutGet(GLUT_WINDOW_HEIGHT);
    return static_cast<float>(screenWidth) / static_cast<float>(screenHeight);
}

void display() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Obtain the aspect ratio based on the window size or desired value
    float aspectRatio = calculateAspectRatio();

    // Call the keyboard input handling functions
    processKeyboard(currentKey, 0, 0);

    // Call your rendering function with the updated hair simulation data and the aspectRatio parameter
    renderScene(model.vertices, shaderProgram, aspectRatio);

    processKeyboardRelease(currentKey, 0, 0);

    // Swap buffers (if using double buffering)
    glutSwapBuffers();

    // checking errors, mostly logging them in a separate file
    checkGLErrors("rendering");
}

int main(int argc, char** argv) {
    // Initialize GLUT and create a window
    initializeOpenGL(argc, argv);

    // Set the display function
    glutDisplayFunc(display);
    // Register the mouse movement function
    glutMouseFunc(processMouseButton);
    glutMotionFunc(processMouseMovement);
    glutKeyboardFunc(keyboardCallback);

    // Start the main loop
    glutMainLoop();

    cleanup();

    return 0;
}