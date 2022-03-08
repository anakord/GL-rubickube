#pragma once

#include "glCamera.h"

namespace OpenGL {

	class glController  {
	public:
		glController(void* context ,glCamera* camera);
		virtual void loadEvents() =0;
		static bool is_camera_move;
		double getInputX() { return inputX; }
		double getInputY() { return inputY; }
	protected:
		glCamera* camera =nullptr;
		static double inputX, inputY; // при позиционной передаче
	};

	class glMouseController :
		public glController {
	public:
		glMouseController(GLFWwindow* window, glCamera* camera);
		void loadEvents();
	private:
		GLFWwindow* window = nullptr;
	
		static void mouse_cursor_callback(GLFWwindow* window, double xpos, double ypos);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	};

	
}