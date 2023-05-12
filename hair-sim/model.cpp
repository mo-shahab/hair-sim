// additional header files
#include "model.h"

Model::Model(const std::string& filePath) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);
    aiNode* rootNode = scene->mRootNode;

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !rootNode) {
        // Error loading the file
        std::cout << "Unable to load the model: " << filePath << std::endl;
        // Handle the error
    }
    else {
        aiMesh* mesh = scene->mMeshes[0];  // Assuming there is only one mesh in the scene
        ExtractMeshVertices(mesh, vertices);
        std::cout << "Model loaded successfully: " << filePath << std::endl;
    }
}

void Model::ExtractMeshVertices(const aiMesh* mesh, std::vector<Vertex>& vertices) {
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;

        // Extract position
        vertex.position.x = mesh->mVertices[i].x;
        vertex.position.y = mesh->mVertices[i].y;
        vertex.position.z = mesh->mVertices[i].z;

        // Extract normal
        vertex.normal.x = mesh->mNormals[i].x;
        vertex.normal.y = mesh->mNormals[i].y;
        vertex.normal.z = mesh->mNormals[i].z;

        // Extract texture coordinates
        if (mesh->HasTextureCoords(0)) {
            vertex.texCoords.x = mesh->mTextureCoords[0][i].x;
            vertex.texCoords.y = mesh->mTextureCoords[0][i].y;
        }

        // Add the vertex to the vertices vector
        vertices.push_back(vertex);
    }
    for (unsigned int i = 0; i < 5 && i < vertices.size(); ++i) {
        const Vertex& vertex = vertices[i];
        std::cout << "Position: (" << vertex.position.x << ", " << vertex.position.y << ", " << vertex.position.z << ")" << std::endl;
    }
}