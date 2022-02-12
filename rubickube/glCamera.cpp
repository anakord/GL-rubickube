#include "glCamera.h"
#include "glController.h"
#include <iostream>
using namespace OpenGL;

glCamera::glCamera(int width, int heigth, unsigned char figure_size) { // перспективное отображение
    center_k = 0.5f * figure_size - 0.5f;
    Pos.z = float(figure_size) * 3.0f;
    screen_width = width;
    screen_height = heigth;
    projection = glm::perspective(45.0f, (float)screen_width / (float)screen_height, 0.1f, 100.0f);
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

    if(Yaw > 360.0)
        Yaw = 0.0;
    if(Pitch > 360.0)
        Pitch = 0.0;
}

void glCamera::setPosition()
{
    view = glm::scale(glm::lookAt(Pos, Pos + Front, Up), glm::vec3(Scale, Scale, Scale));
    view = glm::rotate(view, GLfloat(Pitch), glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::rotate(view, GLfloat(Yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::translate(view, glm::vec3(-center_k)); // centralization
}

void OpenGL::glCamera::castRay(double mouse_x, double mouse_y)
{
    std::cout << "RAY POINTS" << std::endl;
    // Необходимо получить нормализованное направление
    mouse_x *= 2.0; // Расширить диапазон в + и -
    mouse_y *= 2.0;
    mouse_x /= screen_width; // Нормализовать к диапазону [-1, 1]
    mouse_y /= screen_height;
    glm::vec3 ray_direction = glm::vec3(mouse_x - 1.0f, 
                                        1.0f - mouse_y, 
                                        1.0f);
    glm::vec4 ray_clip = glm::vec4(ray_direction.x, ray_direction.y, -1.0, 1.0); // обрезанные в камере координаты
    glm::vec4 ray_eye = glm::inverse(projection) * ray_clip;
    ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
    glm::vec3 ray_world = glm::vec3(glm::inverse(view) * ray_eye);
    ray_world = glm::normalize(ray_world);
    //for (float z = -1.0f; z < 1.0f; z += 0.05f) {
        //ray_world.z = z;
        std::cout << "x=" << ray_world.x << " y=" << ray_world.y << " z=" << ray_world.z << std::endl;
    //}
}

glCamera::~glCamera() {
	
}