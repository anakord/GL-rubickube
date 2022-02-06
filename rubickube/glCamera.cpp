#include "glCamera.h"
#include "glController.h"

using namespace OpenGL;

glCamera::glCamera(int width, int heigth, unsigned char figure_size) { // перспективное отображение
    center_k = 0.5 * figure_size - 0.5;
    Pos.z = figure_size * 3;
    projection = glm::perspective(45.0f, (float)width / (float)heigth, 0.1f, 100.0f);
    
}

void glCamera::changeScale(double k) {
    
    Scale += ScaleSpeed * k;

    if (Scale < SCALE_MIN)
        Scale = SCALE_MIN;
    if (Scale > SCALE_MAX)
        Scale = SCALE_MAX;
}

void glCamera::changeDegree(double x_k, double y_k) {
    
    Yaw += Speed * x_k;
    Pitch += Speed * y_k;

    if(Yaw >= 360.0)
        Yaw = 0.0;
    if(Pitch >= 360.0)
        Pitch = 0.0;
}

void glCamera::setPosition()
{
    view = glm::scale(glm::lookAt(Pos, Pos + Front, Up), glm::vec3(Scale));
    view = glm::rotate(view, GLfloat(Pitch), glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::rotate(view, GLfloat(Yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::translate(view, glm::vec3(-center_k)); // centralization
}

glCamera::~glCamera() {
	
}