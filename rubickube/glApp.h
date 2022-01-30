#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glFigure.h"
#include "glCamera.h"
#include "glShader.h"

#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGTH 480

// Windowed opengl Application Class
namespace OpenGL {

	class glApp {
	public:
		glApp(int width, int height);
		void run();
		
		~glApp();
	private:
		int width, height; // размеры окна
		GLFWwindow* window;	
		glShaderProgram* sh_program; // шейдерная программа
		glCamera* camera; // камера
		

		std::vector<glFigure*> figures; // фигуры на экране

		bool initWindow(); // создать окно
		bool linkGLEW(); // инициализировать GLEW
		void loadShaders(); // загрузить шейдер
		void loadCamera(); // установить камеру
		void loadFigures(); // загрузить фигуры

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
		static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	};
}
