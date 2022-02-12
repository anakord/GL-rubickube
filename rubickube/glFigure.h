#pragma once

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glTexture.h"
#include "glShader.h"
#include "typedef.h"

namespace OpenGL {
	
	struct vertex {
		glm::vec3 coord;
		glm::vec3 color;
		glm::vec2 textCoord;
	};
	
	class glFigure {
	public:
		struct Color {
			static const glm::vec3 RED;
			static const glm::vec3 BLUE;
			static const glm::vec3 GREEN;
			static const glm::vec3 YELLOW;
			static const glm::vec3 PURPLE;
			static const glm::vec3 WHITE;
			static const glm::vec3 NONE;
		};
		glFigure(glm::mat4 position);
		
		glm::mat4 getModel() { return model; };
		virtual void draw() = 0;
		~glFigure();
	protected:
		glm::mat4 model = glm::mat4(1.0f);
		GLuint VAO =0, VBO =0, EBO =0;
		glTexture* texture;
	};
	

	class glFigures {
	public:
		glFigures(uchar n); // размерность фигуры
		void iterate(uchar& x, uchar& y, uchar& z);
		virtual void draw(glShaderProgram* sh_program) =0; 
		~glFigures();
	protected:
		uchar n_row =0; // количество фигур в ряде
		std::vector<glFigure*> figures; // фигуры на экране
		// хранятся порядно 
	};



	// glFigure(s) REALIZATIONS
	class Cube :
		public glFigure
	{
	public:
		/*
		    1 - position, 
			2 - 6 - colors of cube sides
		*/
		Cube(glm::mat4 position, 
			glm::vec3 back_color, glm::vec3 front_color,
			glm::vec3 left_color, glm::vec3 right_color,
			glm::vec3 bottom_color, glm::vec3 top_color);

		void draw() override;
		uchar getX() { return x; }
		uchar getY() { return y; }
		uchar getZ() { return z; }

		void setPos(uchar x, uchar y, uchar z) { 
			this->x = x;
			this->y = y;
			this->z = z;
		}
		~Cube();
	private:
		uchar x =0, y =0, z =0;
	};
	

	class glCubes :
		public glFigures
	{
	public:
		glCubes(uchar n);
		void draw(glShaderProgram* sh_program) override;
		~glCubes();
	private:
		struct Color { // стандартная закраска
			static const glm::vec3* BACK;
			static const glm::vec3* FRONT;
			static const glm::vec3* LEFT;
			static const glm::vec3* RIGHT;
			static const glm::vec3* BOTTOM;
			static const glm::vec3* TOP;
		};
	};
}


