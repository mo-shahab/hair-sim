// rendering.cpp

// the libs custdef
#include "rendering.h"
//#include "main.h"
#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>

// standard libs
#include <fstream>
#include <sstream>

// to access the global variable
extern int window;
// extern unsigned char currentKey;

// the stuff for the camera control
glm::vec3 cameraPosition = glm::vec3(0.0f, 250.0f, 40.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);

// Calculate the camera's front vector based on the camera position and target
//glm::vec3 cameraFront = glm::normalize(cameraTarget - cameraPosition);

float cameraSpeed = 5.05f;  // Adjust the camera movement speed as needed
float cameraSensitivity = 0.1f;  // Adjust the camera rotation sensitivity as needed

float yaw = -90.0f;   // Yaw is initialized to -90 degrees to face the model initially
float pitch = 0.0f;   // Pitch is initialized to 0 degrees
bool firstMouse = true;
float lastX = 0.0f;   // Last mouse X position
float lastY = 0.0f;   // Last mouse Y position


// camera being controlled by the function
void processKeyboardInput(unsigned char key, int x, int y) {
    // Handle keyboard input
    switch (key) {
    case 'w':
        cameraPosition += cameraSpeed * cameraFront;
        break;
    case 's':
        cameraPosition -= cameraSpeed * cameraFront;
        break;
    case 'a':
        cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        break;
    case 'd':
        cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        break;
    }
}

void processKeyboardRelease(unsigned char key, int x, int y) {
    // Handle keyboard key release
    switch (key) {
    case 'w':
        cameraSpeed = 0.0f; // Set camera speed to 0 to stop moving forward
        break;
    case 's':
        cameraSpeed = 0.0f; // Set camera speed to 0 to stop moving backward
        break;
    case 'a':
        // Handle 'a' key release (optional)
        break;
    case 'd':
        // Handle 'd' key release (optional)
        break;
        // Handle other keys as needed
    }
}


void processMouseMovement(int x, int y) {
    static bool firstMouse = true;
    static float lastX = x;
    static float lastY = y;

    if (firstMouse) {
        lastX = x;
        lastY = y;
        firstMouse = false;
    }

    float xoffset = x - lastX;
    float yoffset = lastY - y;
    lastX = x;
    lastY = y;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // Limit the camera's pitch to avoid flipping
    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

// Function to render the scene
void renderScene(const std::vector<Vertex>& vertices, GLuint shaderProgram, float aspectRatio) {
    // Generate and bind VAO and VBO
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // Specify vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(2);

    // Read the shader source code from the vertex and fragment shader files
    std::string vertexShaderSource = LoadShaderSource("vertShaders.vert");
    std::string fragmentShaderSource = LoadShaderSource("fragShaders.frag");

    // Create the shader program
    shaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);

    // Clear the screen and enable depth testing
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // Bind the shader program
    glUseProgram(shaderProgram);

    // Recalculate the camera target based on the lifted camera position
    cameraTarget = cameraPosition + cameraFront;

    float fov = 60.0f;  // Aspect ratio of the viewport
    float nearPlane = 0.1f;         // Near clipping plane
    float farPlane = 150.0f;        // Far clipping plane


    // Set up the model-view-projection matrices
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -4.0f, -10.0f)); // Translate the model
    modelMatrix = glm::rotate(modelMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate the model
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f, 1.0f, 1.0f)); // Scale the model

    // Update the view matrix using the new camera position and target
    glm::mat4 viewMatrix = glm::mat4(4.0f);
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);

    // Set the uniform values for the model, view, and projection matrices
    GLuint modelMatrixLoc = glGetUniformLocation(shaderProgram, "model");
    GLuint viewMatrixLoc = glGetUniformLocation(shaderProgram, "view");
    GLuint projectionMatrixLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Obtain the uniform locations for viewMatrix and projectionMatrix
    GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "view");
    GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projection");

    // Set the view matrix in the shader program
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Set the projection matrix in the shader program
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix)); // Implement this function to set up the camera matrices

    // Set up the lighting parameters
    glm::vec3 lightPos(1.0f, 1.0f, 1.0f);
    glm::vec3 viewPos(0.0f, 0.0f, 3.0f);
    GLuint lightPosLoc = glGetUniformLocation(shaderProgram, "lightPos");
    GLuint viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");
    glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));
    glUniform3fv(viewPosLoc, 1, glm::value_ptr(viewPos));

    // the camera is controlled by this function
    // Input handling
    // Define a variable to store the previous frame's time
    static float previousFrame = 0.0f;

    // Get the current frame's time
    float currentFrame = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

    // Calculate deltaTime
    float deltaTime = currentFrame - previousFrame;

    // Update the previous frame's time for the next frame
    previousFrame = currentFrame;

    // Call the keyboard input handling functions
    // Pass the appropriate key values obtained from GLUT
    processKeyboardInput(currentKey, 0, 0);

    // update on any camera movement
    viewMatrix = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
       

    //std::cout << GLUT_KEY_UP << std::endl;
    
    std::cout << currentKey << std::endl;
    if (currentKey == 101) {
        std::cout << "the thing is working" << std::endl;
    }
    //processCameraMovement(window, cameraPosition, cameraFront, cameraUp, cameraSpeed, deltaTime);

    // Bind the VAO and draw the model
    glBindVertexArray(vao);
    glDrawArrays(GL_LINES, 0, vertices.size());
    glBindVertexArray(0);

   // processKeyboardRelease(currentKey, 0, 0);

    // Disable depth testing
    glDisable(GL_DEPTH_TEST);

    // Cleanup: delete VBO and VAO
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}