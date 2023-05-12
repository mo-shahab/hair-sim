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
};

// encapsulating stuff
class Model {
public:
    std::vector<Vertex> vertices;

    Model(const std::string& filePath);

private:
    void ExtractMeshVertices(const aiMesh* mesh, std::vector<Vertex>& vertices);
};
