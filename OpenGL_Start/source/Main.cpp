#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "ShaderUtil.h"

ShaderUtil shaderUtil;
unsigned int buffer;
unsigned int VAO;
unsigned int matrix_loc;

glm::mat4 ctm;

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	ctm = glm::transpose(glm::translate(glm::mat4(1.0f), glm::vec3(-0.3f,0.0f,0.0f)));
	glUniformMatrix4fv(matrix_loc, 1, GL_TRUE, value_ptr(ctm));
	glBindVertexArray(VAO);
	glDrawArrays(GL_QUADS, 0, 4);
	glutSwapBuffers();
}

void Vertexinit() {

	// Points for rectangle
	float points[8] = {

		// Left
		-0.6f, -0.6f,
		//Right
		0.4f, -0.6f,
		// Top
		0.4f, 0.4f,

		// Right
		-0.6f, 0.4f
	};


	// Create a buffer
	glGenBuffers(1, &buffer);

	// Bind the buffer to vertx attributes
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// Init buffer
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), points, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	unsigned int loc = glGetAttribLocation(shaderUtil.getProgram(), "position");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, 0);

}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 150);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Assn2");

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	else
	{
		fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

		// TODO: Create and compile shaders here (vertex and fragment shaders)
		// and finally draw something with modern OpenGL!
		shaderUtil.Load("shaders/vs.shader", "shaders/fs.shader");

		matrix_loc = glGetUniformLocation(shaderUtil.getProgram(), "transform");


		Vertexinit();
		shaderUtil.Use();
		glutDisplayFunc(renderScene);

		shaderUtil.Delete();

	}
	glutMainLoop();
	return 0;
}