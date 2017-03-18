#include <glfw/glfw3.h>

#include <iostream>
#include <myr.h>

#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main(int argc, char **argv)
{
	glfwInit();

	GLFWwindow *window = glfwCreateWindow(1024, 768, "Submarine", NULL, NULL);
	glfwMakeContextCurrent(window);

	myr::Renderer renderer = myr::Renderer(myr::Color(0.4f, 0.4f, 0.8f));
	
	while(!glfwWindowShouldClose(window))
	{
		renderer.render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}