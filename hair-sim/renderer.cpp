// renderer.cpp

#include "renderer.h"
#include <glad.h>
#include <GL/freeglut.h>

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
void setupCamera(float aspectRatio) {
    // Set the view matrix
    viewMatrix = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

    // Set the projection matrix
    projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

    // Set the view and projection matrices in the shader program
    // ...
}

// Function to set up lighting
void setupLighting() {
    // Set the light position and color in the shader program
    // ...
}
