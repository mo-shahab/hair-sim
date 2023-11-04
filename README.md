# hair-sim

## the final rendition of the project


![ezgif com-video-to-gif](https://github.com/mo-shahab/hair-sim/assets/98043363/b9183a46-6c99-418a-bba9-06442dc3013a)
this is the whole idea behind this project

<<<<<-journal->>>>>
started this: 12-04-2023

hair simulation project, there are lot of things to be considered. the desired conclusion of this project is to
have the model rendered in the opengl context and implement some physics in the hair, like hair getting affected by
air and stuff and then also possible do some collision stuff with the hair like cutting it and such.
but looking at the complexity of the project i dont think that would be possible given the time we have in our hands.
all i think now is to render the model in the opengl context and then if time permits we will see.

<<<<<-journal->>>>>



to basically render anything in this project since we are using the obj (wavefront model);
this is the overview of the entire project (not entirely) but this is what the project is driven by:

To render and display an OBJ model in an OpenGL context, you'll need to follow these general steps:

1. Set up the OpenGL context: Initialize the GLFW library, create a window, and set the OpenGL context.

2. Load the OBJ model: Use a library like Assimp to load the OBJ file and extract the necessary data, such as vertices, normals, 
and texture coordinates.

3. Create and compile shaders: Write vertex and fragment shaders using GLSL to define how the model should be rendered. 
Compile the shaders and link them into a shader program.

4. Set up vertex buffers: Create vertex buffer objects (VBOs) to store the model's vertex data, normals, and texture coordinates. 
Bind the VBOs and upload the data.

5. Set up vertex attribute pointers: Configure the vertex attribute pointers to specify the layout of the vertex data in the VBOs.

6. Set up uniforms: Bind any necessary uniforms in the shader program, such as transformation matrices or material properties.

7. Render the model: In the rendering loop, clear the screen, bind the shader program, 
and issue draw calls to render the model using the vertex data and indices.

8. Display the result: Swap the front and back buffers to display the rendered model on the window.

Here's a simplified code snippet to give you an idea of the structure:

```cpp
// Step 1: Set up the OpenGL context (GLFW initialization and window creation)

// Step 2: Load the OBJ model using Assimp

// Step 3: Create and compile shaders (vertex and fragment shaders)

// Step 4: Set up vertex buffers (VBOs) and upload model data

// Step 5: Set up vertex attribute pointers

// Step 6: Set up uniforms (e.g., transformation matrices)

// Rendering loop:
while (!glfwWindowShouldClose(window)) {
    // Step 7a: Clear the screen

    // Step 7b: Bind the shader program

    // Step 7c: Set up any necessary uniforms

    // Step 7d: Issue draw calls to render the model

    // Step 8: Swap front and back buffers
    glfwSwapBuffers(window);

    // Check for events and handle user input
    glfwPollEvents();
}

// Clean up and exit
```

This is just a general outline, and you'll need to fill in the details and adapt the code to your specific requirements.
#### ====================================================================================================================
## the first step
![Screenshot (35)](https://github.com/mo-shahab/hair-sim/assets/98043363/a5321152-8d2b-4993-b4c6-a38a874ea732)
====================================================================================================================

To render and display a loaded model in OpenGL, you'll need to follow these steps:

1. Set up the Vertex Buffer Objects (VBOs) and Vertex Array Object (VAO):
 VBOs store the vertex data (positions, normals, texture coordinates, etc.),
 and the VAO specifies how the data is organized. 
You'll need to generate and bind the VBOs and VAO, and upload the model's vertex data to the VBOs.

2. Load and compile the vertex and fragment shaders: 
Shaders are programs that run on the GPU and define how vertices and fragments (pixels) are processed. 
You'll need to create vertex and fragment shader programs, load the shader source code, compile the shaders, 
and create a shader program by linking the compiled shaders together.

3. Define the rendering loop: In the rendering loop, you'll clear the screen, set up the camera and projection matrices,
 bind the shader program, and render the model by issuing draw calls.

4. Bind the VAO and set up attribute pointers: Before rendering, 
you'll need to bind the VAO and set up attribute
 pointers to specify how the vertex data is mapped to the shader input variables.

5. Set up the camera and projection matrices: 
You'll need to define a camera to view the model and set up the projection 
matrix to define the perspective or orthographic projection.

6. Issue draw calls to render the model: Finally, 
you'll issue draw calls using the appropriate OpenGL functions to render the model. 
This involves binding the appropriate textures, setting up uniforms, 
and calling functions such as `glDrawArrays` or `glDrawElements` to draw the geometry.

Remember that the specific implementation details may vary depending on the OpenGL version, 
the library or framework you're using, and your rendering pipeline setup. 
It's important to consult the documentation and tutorials for the specific tools you're working with.

Additionally, using a rendering engine or framework like Unity or 
Unreal Engine can simplify many of these steps and provide higher-level abstractions for rendering and displaying models.

=======================================================================================================================

## what does all this mean

1. Vertex Buffer Objects (VBOs): In OpenGL, a VBO is used to store vertex data, 
such as positions, normals, texture coordinates, and other attributes of the model. 
It's like a container that holds the vertex information. You'll need VBOs to provide the vertex data to OpenGL for rendering.

2. Vertex Array Object (VAO): A VAO is used to organize and manage the vertex data stored in VBOs. 
It keeps track of the attribute locations and their formats, allowing you to easily switch between 
different sets of vertex data when rendering different objects. 
It helps in reducing redundant code and simplifies the process of binding vertex attributes.

3. Shaders: Shaders are small programs written in a shading language (like GLSL in OpenGL) that run on the GPU. 
They define how the vertices and fragments (pixels) of the model are processed and shaded. Vertex shaders operate 
on each vertex of the model, transforming its position and other attributes, while fragment shaders determine 
the final color of each pixel. Shaders allow you to apply complex calculations and effects to the model during rendering.

Now, let's discuss why you need these concepts:

- VBOs and VAOs: By using VBOs and VAOs, you can efficiently store and manage the vertex data of your model. 
They allow you to separate the vertex data from the rendering code, making it easier to work with and modify 
the model's geometry. They also improve rendering performance by minimizing the data transfer between the CPU and GPU.

- Shaders: Shaders give you full control over the rendering process. They allow you to manipulate the 
vertex positions, apply lighting calculations, textures, and other visual effects to the model. 
Shaders are responsible for transforming the 3D model into 2D images on the screen and determine 
how each pixel is shaded. They enable you to achieve realistic lighting, textures, and other visual effects in your rendering.

By understanding and utilizing these concepts, you'll have the necessary tools to create 
visually appealing and interactive 3D graphics in OpenGL. It may take some time and practice 
to fully grasp these concepts, but with dedication and hands-on experience, 
you can gradually become proficient in OpenGL programming.

======================================================================================================================

## when binding the vao and vbo into our project

Here's a high-level overview of the process:

1. Generate and bind a VAO: First, you need to generate a VAO using `glGenVertexArrays` 
and bind it using `glBindVertexArray`. The VAO will keep track of the settings and configurations for your vertex data.

2. Generate and bind VBOs: Next, you need to generate VBOs for each type of vertex attribute 
data you have, such as positions, normals, texture coordinates, etc. 
Use `glGenBuffers` to generate VBO IDs and `glBindBuffer` to bind each VBO.

3. Upload data to VBOs: Once the VBOs are bound, you can use `glBufferData` or `glBufferSubData` 
to upload the actual vertex data to each VBO. This involves providing the data array and its size,
 as well as specifying the usage pattern (e.g., `GL_STATIC_DRAW` if the data won't change frequently).

4. Set up attribute pointers: After uploading the data, you need to specify how OpenGL should interpret 
the data stored in the VBOs. Use `glVertexAttribPointer` to define the layout and structure of the 
vertex attributes. This includes the attribute index, number of components, data type, stride, 
and offset within the VBO.

5. Enable attribute arrays: Finally, enable the attribute arrays using `glEnableVertexAttribArray` 
to inform OpenGL that the vertex attributes are stored in the VBOs and should be used during rendering.

By setting up the VBOs and VAO correctly, you'll be able to effectively organize and utilize your 
vertex data for rendering. It allows you to separate the vertex data from the rendering code, 
making it easier to work with and modify the geometry of the model.

Note that the exact implementation may vary depending on the specific OpenGL version and the libraries 
you're using (e.g., GLFW, FreeGLUT). It's important to refer to the documentation and tutorials specific
 to the version and library you're working with.

======================================================================================================================

## about the modularizing stuff for our project and all.

Modularizing your project is a great approach for organizing and maintaining your codebase. 
It allows for better separation of concerns and promotes code reusability.
 Based on the objectives of your project, here are some suggested modules you can consider:

1. Main Module: This module will contain the main entry point of your program, 
where you initialize the OpenGL context, create the window, and handle the main rendering loop. 
It will also coordinate the interaction between other modules.

2. Model Module: This module will handle loading and processing the 3D model. 
It can have functions to load the model file (e.g., OBJ or FBX) using a library like Assimp, 
extract the necessary data (vertices, normals, texture coordinates), 
and store them in appropriate data structures. This module can also handle any 
transformations or manipulations applied to the model.

3. Shader Module: This module will handle the creation, compilation, and linking of shaders. 
It can have functions to load shader source code from external files, compile the shaders, 
and create shader programs. This module can also handle setting shader uniforms for passing data to the shaders.

4. Renderer Module: This module will be responsible for rendering the model and any other objects 
in the scene. It can have functions to set up the necessary buffers (VBOs, VAO), 
define the rendering pipeline (vertex attributes, shader binding), and perform the actual 
rendering using appropriate OpenGL function calls.

5. Camera Module

=====================================================================================================================

The steps that I need to do for completing this project, i want this to be written for the documentation and all

1. Matrix Transformations: Write the necessary code to perform transformations such as translation, 
rotation, and scaling on your model. This can be done using the transformation matrices 
(modelMatrix, viewMatrix, and projectionMatrix) defined in the `renderer.cpp` file. 
Apply these transformations to the model vertices before rendering.

2. Camera: Implement the camera functionality to control the view of the scene. 
This involves updating the camera position, target, and up vector. You can handle 
camera movement using keyboard or mouse inputs and update the viewMatrix accordingly. 
This will allow you to navigate and explore the rendered scene.

3. Shaders: Write the vertex and fragment shader code to handle the rendering pipeline.
 Shaders define how vertices are transformed, how colors or textures are applied, and how 
lighting is calculated. Compile the shaders and create a shader program using OpenGL functions.

4. Link Shaders and Model: Bind the shader program and associate the attribute locations of 
your model vertices with the shader attributes. This allows the shaders to access the vertex 
data correctly. Also, bind the VAO and set the vertex attribute pointers.

5. Lighting: Implement lighting calculations in the shaders. You can define light positions, colors, 
and material properties to achieve the desired lighting effects. This can include ambient, diffuse, 
and specular lighting calculations. Update the shader program with the necessary uniform variables for lighting.

6. Render Loop: Modify the `display()` function in `rendering.cpp` to include the necessary 
steps for rendering the scene. This includes clearing the buffers, updating camera and
 transformation matrices, binding the shader program, rendering the model using the updated matrices, 
and swapping the buffers.

By following these steps, you'll be able to render and display the model with appropriate transformations, 
camera control, lighting, and shaders. Remember to make use of OpenGL functions and appropriate data bindings 
to ensure the correct rendering pipeline.

=====================================================================================================================
 about the shaders and stuff

To create and compile shaders in OpenGL, you can follow these steps:

1. Create the shader source code: Write the shader source code in GLSL (OpenGL Shading Language). 
You need to create at least two shaders: a vertex shader and a fragment shader. 
The vertex shader processes each vertex of the model, while the fragment shader processes each fragment (pixel) of the model.

2. Create the shader objects: In your code, create shader objects using `glCreateShader` function. 
You need to create a shader object for each type of shader (vertex and fragment).

3. Set the shader source code: Use the `glShaderSource` function to specify the shader source code 
for each shader object. Pass the shader source code as an array of strings.

4. Compile the shaders: After setting the shader source code, call `glCompileShader` to compile each 
shader object. Check for compilation errors using `glGetShaderiv` with `GL_COMPILE_STATUS`.

5. Create the shader program: Create a shader program object using `glCreateProgram`. This program 
object will link together the vertex and fragment shaders.

6. Attach the shaders to the program: Use `glAttachShader` to attach the vertex and fragment shaders 
to the shader program.

7. Link the program: Call `glLinkProgram` to link the shader program. Check for linking errors 
using `glGetProgramiv` with `GL_LINK_STATUS`.

8. Use the shader program: Activate the shader program using `glUseProgram` to start using the shaders for rendering.

Here's a simplified example code snippet:

```cpp
// Create shader objects
GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

// Set shader source code
const char* vertexShaderSource = "your_vertex_shader_source_code";
const char* fragmentShaderSource = "your_fragment_shader_source_code";
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

// Compile shaders
glCompileShader(vertexShader);
glCompileShader(fragmentShader);

// Check compilation status
int success;
char infoLog[512];
glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    // Handle compilation error
}

glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    // Handle compilation error
}

// Create shader program
GLuint shaderProgram = glCreateProgram();

// Attach shaders to the program
glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);

// Link the program
glLinkProgram(shaderProgram);

// Check linking status
glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    // Handle linking error
}

// Use the shader program
glUseProgram(shaderProgram);
```


Note that this is a basic example, and you may need to modify and expand upon it based on your specific requirements.

====================================================================================================================

## the complexity of the implementation would determine the things that you have to incorporate in your project

Here are some considerations and potential modifications you might need to make:

1. Vertex Attributes: Ensure that the vertex attributes in the shader code match the attributes of
 your "female_hair" model. For example, if your model has additional attributes like tangents or 
bitangents, you would need to include those in the shader code and modify the vertex data accordingly.

2. Model Representation: Assess how your "female_hair" model is represented. 
If it is a complex mesh composed of multiple vertices and faces, 
you may need to handle the model loading and vertex buffer setup appropriately. 
Consider using a suitable model loading library (such as Assimp) to load the model data and process it for rendering.

3. Texture Mapping: If your "female_hair" model includes texture coordinates, 
you may need to incorporate texture mapping in your shader code. 
This involves loading and binding texture images and applying them to the model's surface during rendering.

4. Lighting and Material: Determine how you want to light and shade your "female_hair" model. 
You might need to implement different lighting models (e.g., Phong or Blinn-Phong) and 
incorporate material properties (such as diffuse, specular, and ambient) to achieve realistic or desired visual effects.

5. Rendering Technique: Depending on the complexity of the "female_hair" model, 
you may need to explore more advanced rendering techniques, such as instancing or particle systems, 
to efficiently render and simulate the hair strands.

Remember, the implementation details can vary depending on your specific requirements and the libraries or frameworks you are using. 
It's essential to understand the underlying concepts and adapt the code accordingly to suit your needs.

<<<<<-journal->>>>>
12-05-2023
so, until now the loading of the model and other stuff like binding the vao and vbo are done perfectly.
on the next session i will try writing the shaders for the model and our project then first try to learn about it.
as i see the implementation upto the binding of vao's and vbo's were a general thing, but anything from further out
is the requirement based and because of the lack of resources online, even if there are its not what i want. 
but lets see if it is possible to do, i guess it will take some time, but if i do this everyday then i guess i can
get what i imagined while deciding on this topic

<<<<<-journal->>>>>

====================================================================================================================

the biggest setback is solved 

when debugged the project found out that the vao and vbo had some error

it appears that the crash is occurring when trying to
 generate the vertex array object (VAO) and vertex buffer object (VBO) in the `setupBuffers` function.
 The error message suggests an access violation at memory location 0x0000000000000000, 
which typically indicates a null pointer or uninitialized variable.

To troubleshoot this issue, you can try the following steps:

1. Ensure that you have included the necessary headers (`#include <GL/glew.h>` or similar) 
for OpenGL extension loading and that the OpenGL context is properly initialized before calling the 
`setupBuffers` function.

2. Check if the GLEW library (or equivalent) is properly initialized. Make sure you call `glewInit()`
 after creating the OpenGL context to load the necessary extensions.

3. Verify that you have a valid OpenGL context before calling any OpenGL functions. 
This can be done by checking the return value of `glGetString(GL_VERSION)` or using a 
context management library like GLFW or SDL.

4. Confirm that you have a compatible OpenGL version that supports vertex array objects. 
Check if `glewIsSupported("GL_ARB_vertex_array_object")` returns `GL_TRUE` before attempting to use VAOs.

5. Ensure that the `vertices` vector passed to the `setupBuffers` 
function is not empty and contains valid vertex data.

6. Double-check that you have the latest graphics drivers installed for your GPU. 
Outdated drivers can sometimes cause issues with OpenGL functionality.

By carefully reviewing and addressing these points, you should be able to narrow down 
the cause of the access violation and resolve the issue with the `setupBuffers` function.

===================================================================================================================

## the model has not been rendered still, there are few ways to make it work

Yes, that's definitely a step in the right direction! The fact that the OpenGL window no 
longer crashes and remains open is a positive sign. Now we need to focus on why the rendering isn't displaying anything other than a white background.

Here are a few things you can check to troubleshoot the rendering issue:

1. Ensure that the shaders are compiled and linked correctly:
   - Verify that the shader files are present and that their paths are correct.
   - Check if there are any compilation or linking errors reported during shader creation.
 You can add additional error logging code to the shader loading functions to print any
 potential errors to the console or a log file.

2. Verify that the vertex data is properly loaded:
   - Check if the `model.vertices` vector contains the expected vertex data.
   - Ensure that the vertex attributes (position, normal, texture coordinates) are correctly 
defined in the `Vertex` struct and aligned with the shader attributes.

3. Confirm that the rendering pipeline is properly set up:
   - Check if the VAO (Vertex Array Object) and VBO (Vertex Buffer Object) are bound correctly 
during rendering. Make sure they are bound before issuing the `glDrawArrays` or `glDrawElements` calls.
   - Verify that the attribute locations in the shader program match the attribute indices set by `glVertexAttribPointer` calls.

4. Double-check the OpenGL state and rendering parameters:
   - Ensure that the OpenGL depth testing is enabled (`glEnable(GL_DEPTH_TEST)`).
   - Verify that the clear color (`glClearColor`) and the viewport (`glViewport`) are set appropriately.
   - Check if any OpenGL error is reported during the rendering process. You can add error checking 
after each OpenGL function call to detect any potential errors.

By going through these steps and examining the specific areas mentioned, you should be able to identify 
the issue causing the rendering to show only a white background.

=================================================================================================================

the shaders were rewritten keeping the model in the mind

In the fragment shader, you have the line vec4 texColor = texture(sampler2D, fragTexCoord);. 
Make sure to replace sampler2D with the actual name of your texture sampler. 
If you haven't defined a sampler uniform in your shader code, you'll need to add it
 and bind the appropriate texture unit before rendering.

The vertex shader calculates the position of the vertex in the world space using the model matrix. 
Make sure you pass the correct model matrix uniform to the shader, which represents the transformation 
applied to the hair model.

Verify that the view and projection matrices are correctly passed to the shaders as uniforms. 
These matrices define the camera view and projection transformations and should be calculated appropriately 
based on your desired camera settings.

Overall, the shaders seem to handle lighting calculations, texture mapping, and transformation correctly, 
which are essential for rendering the hair model. Make sure to set up the necessary uniform variables and 
bind the texture properly in your code to make use of these shaders effectively.

===================================================================================================================

what is all this about the shaders in the first place, what is the projection and anything that is being 
discussed rn
and what is the model matrix and the transformation

In simple terms, the model matrix is a transformation matrix that defines the position, rotation, and scale 
of an object in the world space. It is used to convert the vertex positions of the hair model from local 
coordinates (relative to the model's own coordinate system) to world coordinates (relative to the global 
coordinate system).

In the vertex shader, the line `fragPos = vec3(model * vec4(position, 1.0));` applies the model matrix 
transformation to each vertex position (`position`) of the hair model. This transformed vertex position 
(`fragPos`) is then used for further calculations, such as lighting.

To ensure that the hair model is rendered correctly, you need to pass the correct model matrix as a 
uniform to the vertex shader. This model matrix represents the desired transformation applied to the 
hair model. Depending on your application, you might have a separate model matrix for each hair model
 or a shared model matrix for multiple instances of the same model.

You'll need to set up the model matrix in your code and pass it to the shader as a uniform variable
 before rendering the hair model. The specific implementation details will depend on your code structure 
and how you handle matrices and uniforms.

Overall, the model matrix allows you to position, rotate, and scale the hair model in the 3D world, 
so it appears in the desired location and orientation.

=====================================================================================================================

## the breakdown of the shaders and other stuff 

Here's a breakdown of the steps performed in the function:

Create shader objects:

Two shader objects are created: vertexShader and fragmentShader.
The shader source code for each shader is compiled using the CompileShader function (not shown in your code).
Create shader program:

A shader program object is created using glCreateProgram() function, and its ID is stored in the shaderProgram variable.
Attach shaders to the program:

The compiled vertex shader and fragment shader are attached to the shader program using glAttachShader() 
function.
Link the shader program:

The shader program is linked using glLinkProgram() function.
After linking, you retrieve the location of the model uniform using glGetUniformLocation() function
 and store it in modelMatrixLoc.
Check linking status:

The function retrieves the linking status using glGetProgramiv() and checks if it is GL_FALSE.
If linking fails, an error message is printed with the linking log obtained from glGetProgramInfoLog().
Clean up shader objects:

The compiled vertex shader and fragment shader objects are deleted using glDeleteShader() function.
Return the shader program:

The function returns the ID of the created shader program.

====================================================================================================================

<<<<<-journal->>>>>
13-05-2023

so there were lot of problems solved, the opengl window used to crash with a white background and nothing 
happening, and
 now it wont happen.
i had made a way to log the errors that are occuring in the opengl window, but as it was not running 
i mean as it was
 crashing whenever the project was run, the errors were just not logging. 
and now the crashing does not happen, but still the model has not been rendered, this leaves the 
internal implementation. that is that there is something wrong from my side, my shaders might not be working properly or
 something like that
and also since i can know the errors that are occuring while the opengl window is running that can be solved sooner or 
later. 
to setup up the buffers, that is getting the vertices from the obj file and then somehow managing it to be stored in the 
c++ data structure, and then making it be useful in rendering the model, setting up buffers becomes really important

i dont think there might be any problem with this, or maybe there is, i just have to find a proper way to link the 
shaders and let the shaders understand what it is supposed to do

## we can get there. 
<<<<<-journal->>>>>
=====================================================================================================================

so this is how it looked the for the first time ever when the model rendered into the opengl context
![Screenshot (39)](https://github.com/mo-shahab/hair-sim/assets/98043363/cef7e419-ce5c-454c-b848-6696abe35d46)
needs some working on this, projection!

=====================================================================================================================

tried with some other model
![Screenshot (41)](https://github.com/mo-shahab/hair-sim/assets/98043363/36aa72e2-897f-497d-b26d-ed322c52f2e8)

=====================================================================================================================


this is when i changed the drawing attribute from triangles to lines, something it is kinda working 
![Screenshot (44)](https://github.com/mo-shahab/hair-sim/assets/98043363/2c5d5540-3e5d-4a82-b32c-f56da2ab2e50)

![Screenshot (45)](https://github.com/mo-shahab/hair-sim/assets/98043363/cf845c94-dd25-4af1-b141-c283863054ae)


======================================================================================================================

so stuff now looks like this its very cool and all

![Untitled design](https://github.com/mo-shahab/hair-sim/assets/98043363/5c54c9cf-4a52-4bc2-8aae-b187720aea16)
=====================================================================================================================
final touches.
this is how the model is given a little dynamism that it has
there are a few points that need to be addressed to ensure proper rotation:

1. Move the model rotation calculation to the `renderScene` function, just before setting the model matrix uniform:

   ```cpp
   // Calculate the rotation angle based on the elapsed time
   float rotationAngle = glm::radians(10.0f) * glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

   // Calculate the new model matrix with rotation
   modelMatrix = glm::rotate(modelMatrix, rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));
   ```

   This code calculates the rotation angle based on the elapsed time and applies the rotation transformation to the model matrix.

2. Remove the `rotationAngle` declaration and initialization outside the `renderScene` function. Instead, declare it within the function before the rotation calculation:

   ```cpp
   void renderScene(const std::vector<Vertex>& vertices, GLuint shaderProgram, float aspectRatio) {
       // ...

       // Declare the rotation angle
       float rotationAngle;

       // Calculate the rotation angle based on the elapsed time
       rotationAngle = glm::radians(10.0f) * glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

       // Calculate the new model matrix with rotation
       modelMatrix = glm::rotate(modelMatrix, rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));

       // ...
   }
   ```

   This way, the rotation angle will be recalculated every frame.

3. Remove the `rotationAngle` increment at the end of the rendering loop since the rotation is handled by the calculation in step 1:

   ```cpp
   // updating the hair state in each frame
   // rotationAngle += 10.0f; // Remove this line
   ```

   The rotation will be handled by the `rotationAngle` calculation within the rendering loop.

With these changes, the model should rotate continuously. Let me know if you encounter any further issues.

To add a background in an OpenGL window, you can make use of the `glClear()` function to clear the color buffer with a specific color. Here's an example of how you can add a solid background color:

1. In the `renderScene` function, add the following line before `glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);`:

   ```cpp
   glClearColor(0.2f, 0.3f, 0.4f, 1.0f); // Set the background color (RGB values range from 0.0 to 1.0)
   ```

   This line sets the background color to a dark blue color (0.2, 0.3, 0.4).

2. If you want to add a textured background instead of a solid color, you can use an image as the background texture. You'll need to load the image and bind it as a texture to a quad that covers the entire viewport. Here are the general steps:

   - Load the image using an image loading library (e.g., SOIL, FreeImage, or stb_image).
   - Generate and bind a texture using `glGenTextures()` and `glBindTexture()`.
   - Set the texture parameters using `glTexParameteri()`. For example, you can set the texture wrapping behavior (`GL_REPEAT` or `GL_CLAMP_TO_EDGE`) and filtering options (`GL_LINEAR` or `GL_NEAREST`).
   - Upload the image data to the texture using `glTexImage2D()`.
   - Create a quad with texture coordinates that cover the entire viewport.
   - Bind the texture and render the quad using `glDrawArrays()`.

   The specific implementation details will depend on the image loading library and the format of the image you want to use.

Remember to enable texturing by calling `glEnable(GL_TEXTURE_2D);` before rendering the background quad.

the textures in this case are avoided because of the lot of complexity while rendering and 
to avoid a lot of computational resources 
================================================================================================

the project is still incomplete and lot of stuff is still left undocumented.....
