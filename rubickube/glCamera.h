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
		
		glm::vec3 getPos() { return Pos; };

		void changeScale(double k);
		void changeDegree(double x_k, double y_k);
		void setPosition(); // �������� ������� ������ � ������
		glm::vec3 castRay(double mouse_x, double mouse_y);

		~glCamera();
	private:
		glm::vec3 getNormalisedDeviceCoordinates(float mouse_x, float mouse_y);
		glm::vec3 toWorldCoords(glm::vec4 ray_eye);
		glm::vec4 toEyeCoords(glm::vec4 ray_clip);
		
		glm::mat4 view =glm::mat4(1.0f);
		glm::mat4 projection =glm::mat4(1.0f);

		glm::vec3 Pos =glm::vec3(0.0f, 0.0f, 8.0f); 
		glm::vec3 Front =glm::vec3(0.0f, 0.0f, -1.0f); // �������������� �����������
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f); // ������������ �����������
		
		double screen_width =0.0, screen_height =0.0;

		GLfloat center_k = 0.0f; // ��������������� ��� �������� ������
		
		double Scale =1.0;
		double ScaleSpeed = 0.08;
		
		double Pitch =0.0, Yaw =0.0;
		double Speed = 0.005;
	};
}
