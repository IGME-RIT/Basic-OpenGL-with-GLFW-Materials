/*
Title: Materials
File Name: main.cpp
Copyright � 2016, 2019
Author: David Erbelding, Niko Procopi
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"
#include "FreeImage.h"
#include <vector>
#include "mesh.h"
#include "fpsController.h"
#include "transform3d.h"
#include "material.h"
#include "texture.h"
#include <iostream>




// Store the current dimensions of the viewport.
glm::vec2 viewportDimensions = glm::vec2(800, 600);
glm::vec2 mousePosition = glm::vec2();


// Window resize callback
void resizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
    viewportDimensions = glm::vec2(width, height);
}

// This will get called when the mouse moves.
void mouseMoveCallback(GLFWwindow *window, GLdouble mouseX, GLdouble mouseY)
{
    mousePosition = glm::vec2(mouseX, mouseY);
}


int main(int argc, char **argv)
{
	// Initialize GLFW
	glfwInit();

	// Initialize window
	GLFWwindow* window = glfwCreateWindow(viewportDimensions.x, viewportDimensions.y, "Materials", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set window callbacks
	glfwSetFramebufferSizeCallback(window, resizeCallback);
    glfwSetCursorPosCallback(window, mouseMoveCallback);

	// Initialize glew
	glewInit();


	// Make a Cube
    //    [C]------[G]
	// [D]------[H] |
	//	|  |     |  |
	//	|  |     |  |
	//	| [A]----|-[E]
	// [B]------[F]
	std::vector<Vertex3dUV> vertices;
    
    // Here we need to create all of the vertices of our cube.
    // Any vertices that have different texture coordinates need to be repeated with them.
    // The vertices below are organized into quads to avoid as many repetitions as possible.

    // ABCD
	vertices.push_back(Vertex3dUV(glm::vec3(-1, -1, -1), glm::vec2(0, 0)));
    vertices.push_back(Vertex3dUV(glm::vec3(-1, -1, 1), glm::vec2(1, 0)));
    vertices.push_back(Vertex3dUV(glm::vec3(-1, 1, -1), glm::vec2(0, 1)));
    vertices.push_back(Vertex3dUV(glm::vec3(-1, 1, 1), glm::vec2(1, 1)));
    // FEHG
    vertices.push_back(Vertex3dUV(glm::vec3(1, -1, 1), glm::vec2(0, 0)));
    vertices.push_back(Vertex3dUV(glm::vec3(1, -1, -1), glm::vec2(1, 0)));
    vertices.push_back(Vertex3dUV(glm::vec3(1, 1, 1), glm::vec2(0, 1)));
    vertices.push_back(Vertex3dUV(glm::vec3(1, 1, -1), glm::vec2(1, 1)));
    // BFAE
    vertices.push_back(Vertex3dUV(glm::vec3(1, -1, -1), glm::vec2(0, 0)));
    vertices.push_back(Vertex3dUV(glm::vec3(-1, -1, -1), glm::vec2(1, 0)));
    vertices.push_back(Vertex3dUV(glm::vec3(1, -1, 1), glm::vec2(0, 1)));
    vertices.push_back(Vertex3dUV(glm::vec3(-1, -1, 1), glm::vec2(1, 1)));
    // CDGH
    vertices.push_back(Vertex3dUV(glm::vec3(-1, 1, 1), glm::vec2(0, 0)));
    vertices.push_back(Vertex3dUV(glm::vec3(1, 1, 1), glm::vec2(1, 0)));
    vertices.push_back(Vertex3dUV(glm::vec3(-1, 1, -1), glm::vec2(0, 1)));
    vertices.push_back(Vertex3dUV(glm::vec3(1, 1, -1), glm::vec2(1, 1)));
    // ACEG
    vertices.push_back(Vertex3dUV(glm::vec3(1, -1, -1), glm::vec2(0, 0)));
    vertices.push_back(Vertex3dUV(glm::vec3(-1, -1, -1), glm::vec2(1, 0)));
    vertices.push_back(Vertex3dUV(glm::vec3(1, 1, -1), glm::vec2(0, 1)));
    vertices.push_back(Vertex3dUV(glm::vec3(-1, 1, -1), glm::vec2(1, 1)));
    // BDFH
    vertices.push_back(Vertex3dUV(glm::vec3(-1, -1, 1), glm::vec2(0, 0)));
    vertices.push_back(Vertex3dUV(glm::vec3(1, -1, 1), glm::vec2(1, 0)));
    vertices.push_back(Vertex3dUV(glm::vec3(-1, 1, 1), glm::vec2(0, 1)));
    vertices.push_back(Vertex3dUV(glm::vec3(1, 1, 1), glm::vec2(1, 1)));


	std::vector<unsigned int> indices;
    // The vertices are ordered as quads, so we can just add 6 indices for each.
    for (int i = 0; i < 6; i++)
    {
        indices.push_back(i * 4 + 0);
        indices.push_back(i * 4 + 1);
        indices.push_back(i * 4 + 2);
        indices.push_back(i * 4 + 3);
        indices.push_back(i * 4 + 2);
        indices.push_back(i * 4 + 1);
    }



	// Create shape object
    Mesh* cube = new Mesh(vertices, indices);
	
    // The transform being used to draw our shape
    Transform3D transform;
	transform.SetPosition(glm::vec3(0, 0, -5));

    // The transform being used to draw our second shape.
    Transform3D transform2;
    transform2.SetPosition(glm::vec3(3, 0, -5));


    // Make a first person controller for the camera.
    FPSController controller = FPSController();


	// Create Shaders
    Shader* vertexShader = new Shader("../Assets/vertex.glsl", GL_VERTEX_SHADER);
    Shader* fragmentShader = new Shader("../Assets/fragment.glsl", GL_FRAGMENT_SHADER);

	// fields that are used in the shader, on the graphics card
	char cameraViewVS[] = "cameraView";
	char worldMatrixVS[] = "worldMatrix";
	char textureFS[] = "tex";

	// files that we want to open
	char textureFile1[] = "../Assets/texture.png";
	char textureFile2[] = "../Assets/texture2.png";

    // Create A Shader Program
    // The class wraps all of the functionality of a gl shader program.
    ShaderProgram* shaderProgram = new ShaderProgram();
    shaderProgram->AttachShader(vertexShader);
    shaderProgram->AttachShader(fragmentShader);


    // Here we create a material.
    // Materials are in no way specific to OpenGL.
    // A material is an object that describes and manages the way that something is rendered.
    // This basic material class has shaders, textures, and matrices.
    // This basically turns all of our previous binding code before rendering a mesh into a single line.
    Material* material = new Material(shaderProgram);
    // tex here refers to the uniform variable in the shader that the texture is to be used with.

    material->SetTexture(textureFS, new Texture(textureFile1));

    // Create another material
    Material* material2 = new Material(shaderProgram);
    material2->SetTexture(textureFS, new Texture(textureFile2));

    // Print instructions to the console.
    std::cout << "Use WASD to move, and the mouse to look around." << std::endl;
    std::cout << "Press escape or alt-f4 to exit." << std::endl;



	// Main Loop
	while (!glfwWindowShouldClose(window))
	{
        // Exit when escape is pressed.
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;

        // Calculate delta time.
        float dt = glfwGetTime();
        // Reset the timer.
        glfwSetTime(0);
        

        // Update the player controller
        controller.Update(window, viewportDimensions, mousePosition, dt);

        // rotate cube transform
        transform.RotateY(1.0f * dt);



        // View matrix.
        glm::mat4 view = controller.GetTransform().GetInverseMatrix();
        // Projection matrix.
        glm::mat4 projection = glm::perspective(.75f, viewportDimensions.x / viewportDimensions.y, 1.f, 100.f);
        // Compose view and projection.
        glm::mat4 viewProjection = projection * view;


        // Clear the color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.0, 0.0, 0.0, 0.0);


        // Set the camera and world matrices to the shader
        // The string names correspond directly to the uniform names within the shader.
        material->SetMatrix(cameraViewVS, viewProjection);
        material->SetMatrix(worldMatrixVS, transform.GetMatrix());
        // Bind the material
        material->Bind();
        // Draw
        cube->Draw();
        // Unbind material. (Not required if you have no bugs, but good practice for when you do.)
        material->Unbind();


        // Sec
        material2->SetMatrix(cameraViewVS, viewProjection);
        material2->SetMatrix(worldMatrixVS, transform2.GetMatrix());
        material2->Bind();
        cube->Draw();

		// Stop using the shader program.
        material2->Unbind();

		// Swap the backbuffer to the front.
		glfwSwapBuffers(window);

		// Poll input and window events.
		glfwPollEvents();
	}

    // Free material should free all objects used by material
    delete material;
    delete material2;

	// Free memory from shape object
	delete cube;

	// Free GLFW memory.
	glfwTerminate();

	// End of Program.
	return 0;
}
