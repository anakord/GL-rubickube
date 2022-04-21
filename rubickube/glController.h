#pragma once

#include "glCamera.h"
#include "glFigure.h"

namespace OpenGL {

	class glController  {
	public:
		glController(void* context, glCamera* camera, glFigures* figures);
		virtual void loadEvents() = 0;
		enum class Mode {NONE, // режим не выбран 
						 CAMERA, // вращение камеры
						 SELECTED, // фигура выбрана (промежуточный этап)
						 HORIZONTAL_ROTATION, // вращение по горизонтали
						 VERTICAL_ROTATION }; // вращение по вертикали 
		double getInputX() { return inputX; }
		double getInputY() { return inputY; }
	protected:
		//glCamera* camera =nullptr;
		static Mode current_mode; // мод взаимодействия со сценой
		static glCamera* camera; // камера 
		static glFigure* selected_figure; // выбранная фигура
		static glFigures* figures; // все фигуры
		static double inputX, inputY; // позиция последнего нажатия на экране
	};

	class glMouseController :
		public glController {
	public:
		glMouseController(GLFWwindow* window, glCamera* camera, glFigures* figures);
		void loadEvents();
	private:
		GLFWwindow* window = nullptr; // окно контроллера

		static void mouse_cursor_callback(GLFWwindow* window, double xpos, double ypos);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	};	
}