// renderer.cpp

#include "renderer.h"
#include <glad.h>

// Define the camera parameters
glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// Define the transformation matrices
glm::mat4 modelMatrix = glm::mat4(1.0f);
glm::mat4 viewMatrix;
glm::mat4 projectionMatrix;

// Define the light parameters
glm::vec3 lightPosition = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

// Function to set up the camera and projection matrices

void setupCamera(GLuint shaderProgram, float aspectRatio) {
    // Set the camera position, target, and up vectors
    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    // Set the view matrix
    glm::mat4 viewMatrix = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

    // Set the projection matrix
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

    // Obtain the uniform locations for viewMatrix and projectionMatrix
    GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
    GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");

    // Set the view matrix in the shader program
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Set the projection matrix in the shader program
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}


// Function to set up lighting
void setupLighting() {
    // Set the light position and color in the shader program
    // ...
}
