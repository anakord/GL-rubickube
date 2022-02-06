#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#define SCALE_MIN 0.8
#define SCALE_MAX 1.2

namespace OpenGL {

	class glCamera
	{
	public:
		glCamera(int width, int heigth, unsigned char figure_size);
		glm::mat4 getView() const { return view; };
		glm::mat4 getProjection() const { return projection; };
		
		void changeScale(double k);
		void changeDegree(double x_k, double y_k);
		void setPosition(); // загрузка позиции камеры в шейдер

		bool is_camera_move =false;

		~glCamera();

	private:
		glm::mat4 view =glm::mat4(1.0f);
		glm::mat4 projection =glm::mat4(1.0f);

		glm::vec3 Pos =glm::vec3(0.0f, 0.0f, 8.0f); 
		glm::vec3 Front =glm::vec3(0.0f, 0.0f, -1.0f); // горизонтальный коэффициент
		glm::vec3 Up =glm::vec3(0.0f, 1.0f, 0.0f); // вертикальный коэффициент

		GLfloat center_k = 0.0f; // пересчитывается при создании камеры

		double Scale =1.0;
		double ScaleSpeed = 0.08;
		
		double Pitch =0.0, Yaw =0.0;
		double Speed = 0.05;
	};
}
