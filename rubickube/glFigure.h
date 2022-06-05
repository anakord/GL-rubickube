#pragma once

#include <vector>
#include <array>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glTexture.h"
#include "glShader.h"

#include "typedef.h"

namespace OpenGL {
	
	class glShaderProgram;

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
		glFigure(glm::vec3 center);
		glm::mat4 getModel() { return model; };
		virtual void draw() =0;
		double is_hit(glm::vec3 ray_origin_wor, glm::vec3 ray_direction_wor);
		void addOrbitRotate(float pitch, float yaw, float roll); // изменяет вращение на отколнение
		glm::vec3 getCenter() {
			glm::mat4 viewModel = glm::inverse(model);
			return viewModel[3];
		}
		glm::vec4* center; // Реальный центр в пространстве координат
		glm::vec3 LOGICAL_POSITION = glm::vec3(0.0f); // Логическая позиция
		float d_pitch = 0.0f, d_yaw = 0.0f, d_roll; // углы отклонения от нормы
		~glFigure();
	protected:
		glm::mat4 model =glm::mat4(1.0f);
		GLuint VAO =0, VBO =0, EBO =0;
		static const float SIZE;
		glTexture* texture;
	};
	
	// грань
	class Face {
	public:
		Face(glm::vec3 point, glm::vec3 normal);
		glm::vec3 point; // точка
		glm::vec3 normal; // вектор нормали
		void addFigure(glFigure* figure);
		double is_hit(glm::vec3 ray_origin_wor, glm::vec3 ray_direction_wor);
		~Face();
	private:
		std::vector<glFigure*> figures; // фигуры, принадлежащие данной грани
	};

	// абстрактная фигура
	class glFigures {
	public:
		glFigures(uchar n); // размерность фигуры
		glFigure* is_hit(glm::vec3 ray_origin_wor, glm::vec3 ray_direction_wor); // null - если ничего не выбрано
		void stable(glFigure* selected_figure);
		void rotateLine(glFigure* selected_figure, float yaw, float pitch, float roll);
		virtual void draw(glShaderProgram* sh_program) =0; 
		~glFigures();
	protected:
		uchar n_row =0; // количество фигур в ряду
		float min = 0.0f, max = 0.0f;
		std::vector<Face*> faces;
		std::vector<glFigure*> figures; // фигуры на экране
	};



	// glFigure(s) REALIZATIONS
	class glCube :
		public glFigure
	{
	public:
		/*
		    1 - position, 
			2 - 7 - colors of cube sides
		*/
		glCube(glm::vec3 center,
			glm::vec3 back_color, glm::vec3 front_color,
			glm::vec3 left_color, glm::vec3 right_color,
			glm::vec3 bottom_color, glm::vec3 top_color);
		
		void draw() override;
		
		~glCube();
	private:
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

		const uchar N_FACES = 6;
		enum D_FACES {
			BACK,
			FRONT,
			LEFT,
			RIGHT,
			BOTTOM,
			TOP
		};
	};
}


