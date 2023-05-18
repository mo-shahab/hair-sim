#include "physics.h"					   // including necessary headers 
#include <chrono>
extern std::vector<Vertex> loadedVertices; // Declare the variable from main.cpp
extern std::vector<Vertex> hairVertices;          // Store the hair strand vertices
float hairMass;                            // Mass of each hair strand
float hairElasticity;                      // Elasticity of the hair strands
float hairFriction;                        // Friction coefficient for the hair strands
// Define other necessary variables

void initializeHairSimulation(const std::vector<Vertex>& vertices)
{
    // Assign the loaded model vertices to the hair vertices
    hairVertices = vertices;

    // Assign physical properties to the hair strands
    hairMass = 1.0f;         // Adjust the mass value as per your requirements
    hairElasticity = 0.5f;   // Adjust the elasticity value as per your requirements
    hairFriction = 0.2f;     // Adjust the friction coefficient as per your requirements

    // Set up other necessary initialization steps
}

void ApplyGravity(std::vector<Vertex>& hairVertices, float gravity) {
    // Define the gravitational force vector
    glm::vec3 gravityVector(0.0f, -gravity, 0.0f);

    // Apply gravitational force to each hair vertex
    for (unsigned int i = 0; i < hairVertices.size(); i++) {
        // Update the position of the hair vertex based on gravity
        hairVertices[i].position += gravityVector;
    }
}

void updateHairSimulation()
{
    // this is the first try lets see if this works 
    float gravity = 9.8f; // Define the gravity value


    // Set the desired simulation duration (in seconds)
    float simulationDuration = 10.0f;

    // Get the current time
    auto startTime = std::chrono::steady_clock::now();

    // Update the hair simulation in your main loop
    while (true) {
        // Get the current time
        auto currentTime = std::chrono::steady_clock::now();

        // Calculate the elapsed time since the start of the simulation
        float elapsedTime = std::chrono::duration<float>(currentTime - startTime).count();

        // Check if the simulation duration has been reached
        if (elapsedTime >= simulationDuration)
        {
            break;  // Exit the loop when the duration is reached
        }

        // Apply gravitational forces to the hair vertices
        ApplyGravity(hairVertices, gravity);

        // Update other physics calculations or simulations

        // ...
    }
}