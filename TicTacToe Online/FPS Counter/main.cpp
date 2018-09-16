#include "Application.h"
#include <Windows.h>
#include <GLFW/glfw3.h>
#include <GL/GLU.h>

void onWindowResized(GLFWwindow* window, int width, int height)
{
	if (height == 0) height = 1;						// Prevent A Divide By Zero By making Height Equal One

	glViewport(0, 0, width, height);					// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	gluOrtho2D(-width/2, width/2, -height / 2, height / 2);					// Calculate The Aspect Ratio Of The Window

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

int main(void)
{
	GLFWwindow *window;

	/* Initialize the Library */
	if (!glfwInit())
		return -1;

	/*Create a windowed mode window and its OpenGL context*/
	window = glfwCreateWindow(RESOLUTION_X, RESOLUTION_Y, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetWindowSizeCallback(window, onWindowResized);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	onWindowResized(window, RESOLUTION_X, RESOLUTION_Y);

	Application::GetInstance().Start();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		if (glfwGetKey(window, GLFW_KEY_W))
			Application::GetInstance().OnKeyPress(GLFW_KEY_W);

		if (glfwGetKey(window, GLFW_KEY_S))
			Application::GetInstance().OnKeyPress(GLFW_KEY_S);

		if (glfwGetKey(window, GLFW_KEY_A))
			Application::GetInstance().OnKeyPress(GLFW_KEY_A);

		if (glfwGetKey(window, GLFW_KEY_D))
			Application::GetInstance().OnKeyPress(GLFW_KEY_D);

		int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		if (state == GLFW_PRESS)
		{
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			Application::GetInstance().OnMousePress(GLFW_MOUSE_BUTTON_LEFT, xpos, ypos);
		}
		else if (state == GLFW_RELEASE)
		{
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			Application::GetInstance().OnMouseRelease(GLFW_MOUSE_BUTTON_LEFT, xpos, ypos);
		}

		Application::GetInstance().Update();
		Application::GetInstance().Draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

	}

	glfwTerminate();
	return 0;
}