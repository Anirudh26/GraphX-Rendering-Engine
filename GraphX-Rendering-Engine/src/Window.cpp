#include "Window.h"

#include "ErrorHandler.h"
#include "GLFW/glfw3.h"
#include <iostream>

namespace engine
{
	Window::Window(std::string title, int width, int height)
		: m_Title(title), m_Width(width), m_Height(height)
	{
		bool res = Init();
		if (!res)
		{
			std::cout << "Error while creating the window" << std::endl;
		}
	}

	bool Window::Init()
	{
		if (!glfwInit())
		{
			return false;
		}

		// Set the context version and the core profile for the opengl
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Create the window
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);

		if (!m_Window)
		{
			glfwTerminate();
			return false;
		}

		// Make the context current
		glfwMakeContextCurrent(m_Window);

		// Setting the swap interval
		glfwSwapInterval(1);

		// Set the error callback for glfw
		glfwSetErrorCallback(&GlfwErrorCallback);

		return true;
	}

	bool Window::IsClosed() const
	{
		if (m_Window)
		{
			if (!glfwWindowShouldClose(m_Window))
			{
				return false;
			}
		}

		return true;
	}

	void Window::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void Window::Resize()
	{
		int width, height;
	
		// Get the new width and height of the window
		glfwGetFramebufferSize(m_Window, &width, &height);

		// Set the new size of the window
		glViewport(0, 0, width, height);
	}

	void Window::Clear()
	{
		/* Clear the color buffer */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Clear the depth buffer */
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void Window::Update()
	{
		/* Swap the front and back buffers */
		glfwSwapBuffers(m_Window);

		/* Poll for events */
		glfwPollEvents();
	}

	Window::~Window()
	{
		/* Destroy the window */
		glfwDestroyWindow(m_Window);

		/* Terminate */
		glfwTerminate();
	}

}