#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#define SCALE_MIN 0.8
#define SCALE_MAX 1.2

namespace OpenGL {
	class glCamera {
	public:
		glCamera(int width, int heigth, unsigned char figure_size);
		glm::mat4 getView() const { return view; };
		glm::mat4 getProjection() const { return projection; };
		
		glm::vec3 getPos() {
			glm::mat4 viewModel = glm::inverse(view);
			return viewModel[3];
		};

		void changeScale(double k);
		void changeDegree(double x_k, double y_k);
		void setPosition(); // загрузка позиции камеры в шейдер
		void inverseRotation(float& pitch, float& yaw); // в зависимости от угла взгляда камеры, инверсирует врашение рядов
		glm::vec3 castRay(float mouse_x, float mouse_y);
		~glCamera();
	private:

		glm::mat4 view =glm::mat4(1.0f);
		glm::mat4 projection =glm::mat4(1.0f);

		glm::vec3 Pos =glm::vec3(.0f, .0f, 3.0f); 
		glm::vec3 Front =glm::vec3(.0f, .0f, -1.0f); // горизонтальный коэффициент
		glm::vec3 Up = glm::vec3(.0f, 1.0f, .0f); // вертикальный коэффициент
		
		double screen_width =0.0, screen_height =0.0;

		GLfloat radius = .0f; // пересчитывается при создании камеры
		
		float Scale =1.0f;
		float ScaleSpeed = 0.08f;
		
		float Pitch =.0f, Yaw =.0f;
		float Speed = 0.5f;
	};
}
