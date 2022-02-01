#pragma once

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glTexture.h"
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
		glFigure();
		virtual void draw() = 0;
		~glFigure();
	protected:
		GLuint VAO =0, VBO =0, EBO =0;

		glTexture* texture;
	};
	
	
	// glFigure REALIZATIONS
	class Cube :
		public glFigure
	{
	public:
		// 1 - 6 - colors of cube sides
		Cube(glm::vec3 BACK_COLOR, glm::vec3 FRONT_COLOR,
			glm::vec3 LEFT_COLOR, glm::vec3 RIGHT_COLOR,
			glm::vec3 BOTTOM_COLOR, glm::vec3 TOP_COLOR);

		void draw() override;
		~Cube();
	private:
		
	};
}


