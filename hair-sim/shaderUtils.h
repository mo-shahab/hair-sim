#pragma once
#ifndef SHADER_UTILS_H
#define SHADER_UTILS_H

#include <string>
#include <glad.h>

// Function to load shader source code from a file
std::string LoadShaderSource(const std::string& filePath);

// Function to compile a shader
GLuint CompileShader(GLenum shaderType, const std::string& shaderSource);

// Function to create a shader program and link shaders
GLuint CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);


#endif