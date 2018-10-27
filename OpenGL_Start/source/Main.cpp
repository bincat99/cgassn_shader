#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

#include "ShaderUtil.h"

ShaderUtil shaderUtil;
unsigned int buffer;
unsigned int VAO;

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(VAO);
	glDrawArrays(GL_QUADS, 0, 4);
	glutSwapBuffers();
}

void Vertexinit() {

	// Points for rectangle
	float points[8] = {

		// Left
		-0.8f, -0.5f,
		//Right
		0.8f, -0.5f,
		// Top
		0.8f, 0.9f,

		// Right
		-0.8f, 0.9f
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
	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

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


		Vertexinit();
		shaderUtil.Use();
		glutDisplayFunc(renderScene);

		shaderUtil.Delete();

	}
	glutMainLoop();
	return 0;
}