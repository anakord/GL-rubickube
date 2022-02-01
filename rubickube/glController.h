#pragma once

#include "glCamera.h"

namespace OpenGL {
	
	class glController  {
	public:
		glController(void* context ,glCamera* camera);
		virtual void loadEvents() =0;
	protected:
		void* context =nullptr;
		glCamera* camera =nullptr;
	};

	class glMouseController :
		public glController {
	public:
		glMouseController(GLFWwindow* window, glCamera* camera);
		void loadEvents();
	private:

		GLFWwindow* window =nullptr;

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

		static double mouseX, mouseY;
		static void mouse_cursor_callback(GLFWwindow* window, double xpos, double ypos);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	};
}