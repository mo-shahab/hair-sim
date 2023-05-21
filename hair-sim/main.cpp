#include <iostream>
#include <fstream>
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

// this is the defn for the hair vertices
std::vector<Vertex> hairVertices;

Model model("C:/Users/User/OneDrive/Documents/opengl_rend/untitled.obj");

// isolating the hair vertices from the vertices of the sphere
// Calculate the square of the sphere radius
float sphereRadiusSquared = 1.0f * 1.0f; // the value of the radius in here would be changed
                                         // as according to the radius of the sphere implemented!

// Assuming the center of the sphere is at the origin (0, 0, 0)
glm::vec3 sphereCenter(0.0f, 0.0f, 0.0f);

float lengthSquared(const glm::vec3& vec) {
    return glm::dot(vec, vec);
}

// Function to isolate hair vertices from the model vertices
void IsolateHairVertices(const std::vector<Vertex>& allVertices, std::vector<Vertex>& hairVertices) {
    // Iterate through all vertices and identify the hair vertices based on your desired criteria
    for (const auto& vertex : allVertices) {
    // Calculate the distance from the vertex to the sphere center
        float distanceSquared = glm::dot(vertex.position - sphereCenter, vertex.position - sphereCenter);

        // Check if the vertex is outside the sphere (i.e., greater than the sphere radius)
        if (distanceSquared > sphereRadiusSquared) {
        // Add the vertex to the hair strand vertices array
            hairVertices.push_back(vertex);
        }
    }
    // for debugging purposes
    for (int i = 0; i < 5 && i < hairVertices.size(); ++i) {
        const Vertex& vertex = hairVertices[i];
        std::cout << "Hair Vertex Position: (" << vertex.position.x << ", " << vertex.position.y << ", " << vertex.position.z << ")" << std::endl;
    }
}

// Now 'hairVertices' will contain the isolated hair strand vertices

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
    currentKey = key;
    //std::cout << currentKey << std::endl;
    processKeyboardInput(currentKey, x, y);
}

void keyboardUpCallback(unsigned char key, int x, int y) {
    //currentKey = 0;
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
    IsolateHairVertices(model.vertices, hairVertices);
    // implementing physics into the loaded vertices
    int numHairVertices = 600;// Number of hair vertices
    int numHairSprings = 300;// Number of hair springs

    HairStrand hairStrand = createHairStrand(numHairVertices, numHairSprings);


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
    processKeyboardInput(currentKey, 0, 0);



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
    //logOpenGLErrors();

    // Start the main loop
    glutMainLoop();

    cleanup();

    return 0;
}