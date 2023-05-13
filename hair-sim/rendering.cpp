// rendering.cpp

// the libs custdef
#include "rendering.h"
#include <GL/glut.h>

// standard libs
#include <fstream>
#include <sstream>

static GLuint vao;

// Function to create and bind the VAO and VBO
void setupBuffers(const std::vector<Vertex>& vertices) {
    GLuint vbo;

    // Generate VAO and bind it
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao); //possible error

    // Generate VBO and bind it
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Set the VBO data (vertices)
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // Specify the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(2);

    // Unbind VAO and VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Function to render the scene
void renderScene(const std::vector<Vertex>& vertices, GLuint shaderProgram, float aspectRatio) {
    // Read the shader source code from the vertex and fragment shader files
    std::ifstream vertexShaderFile("vertShaders.vert");
    std::ifstream fragmentShaderFile("fragShaders.frag");
    std::stringstream vertexShaderStream, fragmentShaderStream;
    vertexShaderStream << vertexShaderFile.rdbuf();
    fragmentShaderStream << fragmentShaderFile.rdbuf();
    std::string vertexShaderSource = vertexShaderStream.str();
    std::string fragmentShaderSource = fragmentShaderStream.str();

    // creating the shader program
    shaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Bind the shader program
    glUseProgram(shaderProgram);

    // Set up your model-view-projection matrices
    // ...

    // Set up the camera and projection matrices
    setupCamera(shaderProgram, aspectRatio); // Pass the shader program and aspect ratio here

    // Apply transformations (e.g., translation, rotation, scaling) to the model matrix
    // ...

    // Set up your lighting parameters (if applicable)
    // ...

    // Bind the VAO and draw the model
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);

    // Disable depth testing
    glDisable(GL_DEPTH_TEST);
}
