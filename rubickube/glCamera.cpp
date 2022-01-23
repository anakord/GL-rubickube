#include "glCamera.h"

using namespace OpenGL;

glCamera::glCamera(int width, int heigth) { // перспективное отображение

	model = glm::rotate(model, -30.0f, glm::vec3(1.0f, 0.5f, 0.0f));
	view = glm::lookAt(Pos, Pos + Front, Up);
	projection = glm::perspective(45.0f, (float)width / (float)heigth, 0.1f, 100.0f);
}

void glCamera::SetPosition(GLuint sh_handler)
{
    GLint loc; // указатель на uniform шейдера
    loc = glGetUniformLocation(sh_handler, "model");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(model));

    loc = glGetUniformLocation(sh_handler, "view");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(view));

    loc = glGetUniformLocation(sh_handler, "projection");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(projection));
}

glCamera::~glCamera() {
	
}