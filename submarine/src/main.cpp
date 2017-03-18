#include <glfw/glfw3.h>

#include <iostream>
#include <myr.h>

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main(int argc, char **argv)
{
	glfwInit();

	GLFWwindow *window = glfwCreateWindow(1024, 768, "Submarine", NULL, NULL);
	glfwMakeContextCurrent(window);

	myr::Renderer renderer = myr::Renderer(myr::Color(0.5f, 0.3f, 0.7f));

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