#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace OpenGL {
	class glCamera
	{
	public:
		glCamera(int width, int heigth);
		glm::mat4 getModel() const { return model; };
		glm::mat4 getView() const { return view; };
		glm::mat4 getProjection() const { return projection; };
		
		void SetPosition(GLuint sh_handler); // загрузка позиции камеры в шейдер

		~glCamera();

	private:
		glm::mat4 model =glm::mat4(1.0f);
		glm::mat4 view =glm::mat4(1.0f);
		glm::mat4 projection =glm::mat4(1.0f);

		glm::vec3 Pos =glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 Front =glm::vec3(0.0f, 0.0f, -1.0f); // горизонтальный коэффициент
		glm::vec3 Up =glm::vec3(0.0f, 1.0f, 0.0f); // вертикальный коэффициент
	};
}
