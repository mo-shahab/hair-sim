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
int window;
unsigned char g_key = 0;

Model model("C:/Users/User/OneDrive/Documents/opengl_rend/Mustang.obj");

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

// this is to update the value so that i can pass this in the rendering.cpp file
void keyboardCallback(unsigned char key, int x, int y) {
    g_key = key;
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
    window = glutCreateWindow("hair simulation");

    // Set the keyboard callback function for special keys
    //glutSpecialFunc(processKeyboardInput);
    //glutKeyboardFunc(processKeyboardInput);
    glutKeyboardFunc(keyboardCallback);
    glutKeyboardUpFunc(processKeyboardRelease);
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
    renderScene(model.vertices, shaderProgram, aspectRatio, g_key);

    // Swap buffers (if using double buffering)
    glutSwapBuffers();

    // checking errors, mostly logging them in a separate file
    checkGLErrors("rendering");
}


// debugging funcitions!!! for dev
void validateModelData(const std::vector<Vertex>& vertices)
{
    for (const Vertex& vertex : vertices)
    {
        // Print position
        std::cout << "Position: (" << vertex.position.x << ", " << vertex.position.y << ", " << vertex.position.z << ")" << std::endl;

        // Print normal
        std::cout << "Normal: (" << vertex.normal.x << ", " << vertex.normal.y << ", " << vertex.normal.z << ")" << std::endl;

        // Print texture coordinates
        //std::cout << "Texture Coordinates: (" << vertex.texCoord.x << ", " << vertex.texCoord.y << ")" << std::endl;

        std::cout << std::endl;
    }
}


int main(int argc, char** argv) {
    // Initialize GLUT and create a window
    initializeOpenGL(argc, argv);

    // Set the display function
    glutDisplayFunc(display);
    //logOpenGLErrors();

    /*
    
    // Setup buffers
    if (!model.vertices.empty()) {
        setupBuffers(model.vertices);
    }
    else {
        std::cout << "Unable to load the model. Exiting..." << std::endl;
        return 1;

    }
    */
    //validateModelData(model.vertices);

    // Start the main loop
    glutMainLoop();

    cleanup();

    return 0;
}