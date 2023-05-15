#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include "model.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glut.h>

void setupCamera(GLuint shaderProgram, float aspectRatio);
void setupCamera(GLuint shaderProgram, float aspectRatio);
void setupLight(GLuint shaderProgram, const glm::vec3& lightPos, const glm::vec3& viewPos);

#endif