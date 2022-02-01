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
		bool status(); // ���������� ��������� ���������� � ����� ��������� � �������
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
		bool status(); // ���������� ��������� �������� � ����� ��������� � �������
		void loadModel(glm::mat4 model); // ��������� ����� ������
		void Use(glm::mat4 view, glm::mat4 projection); // ������������ ��������� ��������� � ����������� ������
		~glShaderProgram();
	
	private:
		std::vector<glShader> shaders;
		GLuint handle =0; // handle of this shader
	};
}

