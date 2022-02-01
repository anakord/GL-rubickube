#pragma once


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>

#include "glCamera.h"

namespace OpenGL {
	class glShader
	{
	public:
		glShader(const std::string& shader_name, GLint shader_type);
		GLuint getHandlde() { return handle; }
		bool read_from_file(const std::string& shader_name);
		void compile();
		bool status(); // возвращает результат компил€ции и пишет результат в консоль
		void delShader() { glDeleteShader(handle); }
		~glShader();
	private:
		std::string name ="";
		std::string source ="";
		GLint type =0; // type of handle
		GLuint handle =0; // handle of this shader
	};

	class glShaderProgram
	{
	public:
		glShaderProgram();
		GLuint getHandle() { return handle; }
		void link();
		bool status(); // возвращает результат линковки и пишет результат в консоль
		void loadModel(glm::mat4 model); // загружает место модели
		void Use(glm::mat4 view, glm::mat4 projection); // использовать шейдерную программу с параметрами камеры
		~glShaderProgram();
	
	private:
		std::vector<glShader> shaders;
		GLuint handle =0; // handle of this shader
	};
}

