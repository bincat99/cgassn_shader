#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

#include "ShaderUtil.h"

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glutSwapBuffers();
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
		ShaderUtil shaderUtil;
		shaderUtil.Load("shaders/vs.shader", "shaders/fs.shader");

		// Points for triangle
		float points[6] = {

			// Left
			-0.8f, -0.5f,

			// Top
			0.0f, 0.9f,

			// Right
			0.5f, -0.7f
		};

		unsigned int buffer;

		// Create a buffer
		glGenBuffers(1, &buffer);

		// Bind the buffer to vertx attributes
		glBindBuffer(GL_ARRAY_BUFFER, buffer);

		// Init buffer
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), points, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

		shaderUtil.Use();
		glutDisplayFunc(renderScene);

		shaderUtil.Delete();

	}
	glutMainLoop();
	return 0;
}