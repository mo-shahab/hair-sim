#include <iostream>

// including the opengl
#include <GL/glut.h>
#include <GL/freeglut.h>

// the addi header files
#include "model.h"
#include "rendering.h"

Model model("C:/Users/User/OneDrive/Documents/opengl_rend/female_hair.obj");


void display() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Call your rendering function
    renderScene(model.vertices);

    // Swap buffers (if using double buffering)
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    // Initialize GLUT and create a window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Window");

    // Set the display function
    glutDisplayFunc(display);

    // Setup buffers
    if (!model.vertices.empty()) {
        setupBuffers(model.vertices);
    }
    else {
        std::cout << "Unable to load the model. Exiting..." << std::endl;
        return 1;
    }

    // Start the main loop
    glutMainLoop();

    return 0;
}