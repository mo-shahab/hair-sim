#pragma once
// standard libraries
#include <iostream>
#include <vector>

// opengl mathematics library 3rd party
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// model loading libraries
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// data structure for loading the vertex info from the model
// and storing it in c++ (kinda)
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    float mass = 1.0f; // Assign the desired mass value
    glm::vec3 velocity = glm::vec3(0.0f); // Assign the desired velocity value
};

// encapsulating stuff
class Model {
public:
    std::vector<Vertex> vertices;

    Model(const std::string& filePath);

private:
    void ExtractMeshVertices(const aiMesh* mesh, std::vector<Vertex>& vertices);
};
