#include <iostream>
#include <fstream>
#include <GL/glut.h>

// including the opengl
// 
// the addi header files
#include "model.h"
#include "rendering.h"

std::ofstream errorLog;// Declare the error log file stream
GLuint shaderProgram;


Model model("C:/Users/User/OneDrive/Documents/opengl_rend/cube.obj");

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

    // Cleanup other resources and exit
    // ...
}

void initializeGLAD() {
    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }
}

void initializeOpenGL(int argc, char** argv)
{
    // Initialize GLUT and create a window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("hair simulation");

    // Initialize GLAD
    initializeGLAD();
    // Open the error log file
    errorLog.open("opengl_errors.txt");
}


void logOpenGLErrors()
{
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        errorLog << "OpenGL Error: " << error << std::endl;
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

    // Call your rendering function with the aspectRatio parameter
    renderScene(model.vertices, shaderProgram, aspectRatio);

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
    //logOpenGLErrors();

    // Setup buffers
    if (!model.vertices.empty()) {
        setupBuffers(model.vertices);
    }
    else {
        std::cout << "Unable to load the model. Exiting..." << std::endl;
        return 1;
    }

    // Start the main loop
    glutMainLoop();

    cleanup();

    return 0;
}