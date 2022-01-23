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
	class glFigure {
	public:
		glFigure();
		virtual void draw() = 0;
		~glFigure();
	protected:
		GLuint VAO =0, VBO =0, EBO =0;
	};
	
	
	// glFigure REALIZATIONS
	class Cube :
		public glFigure
	{
	public:
		Cube(GLuint program_handler);
		void draw() override;
		~Cube();
	private:

		static const unsigned char POINTS = 8;
		static const unsigned char INDICES = 12;

	};
}


