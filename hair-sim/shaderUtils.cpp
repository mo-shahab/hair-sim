#include "shaderUtils.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Function to load shader source code from a file
std::string LoadShaderSource(const std::string& filePath) {
    std::ifstream file(filePath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Function to compile a shader
GLuint CompileShader(GLenum shaderType, const std::string& shaderSource) {
    GLuint shader = glCreateShader(shaderType);
    const GLchar* shaderCode = shaderSource.c_str();
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);

    // Check compilation status
    GLint compileStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus == GL_FALSE) {
        // Shader compilation failed, handle the error
        // Retrieve the compilation log using glGetShaderInfoLog
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        std::string log(logLength, ' ');
        glGetShaderInfoLog(shader, logLength, nullptr, &log[0]);
        std::cerr << "Shader compilation failed:\n" << log << std::endl;
        // Optionally, you can throw an exception or return an error code here
    }

    return shader;
}

// Function to create a shader program and link shaders
GLuint CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
    // Create shader objects
    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    // Create shader program
    GLuint shaderProgram = glCreateProgram();

    // Attach shaders to the program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // Link the shader program
    glLinkProgram(shaderProgram);

    // Retrieve the location of the model uniform
    GLuint modelMatrixLoc = glGetUniformLocation(shaderProgram, "model");

    // Check linking status
    GLint linkStatus;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus);
    if (linkStatus == GL_FALSE) {
        // Shader program linking failed, handle the error
        // Retrieve the linking log using glGetProgramInfoLog
        GLint logLength;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);
        std::string log(logLength, ' ');
        glGetProgramInfoLog(shaderProgram, logLength, nullptr, &log[0]);
        std::cerr << "Shader program linking failed:\n" << log << std::endl;
        // Optionally, you can throw an exception or return an error code here
    }

    // Clean up shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}