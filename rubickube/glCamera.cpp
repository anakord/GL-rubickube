#include "glCamera.h"
#include "glController.h"
#include <iostream>

using namespace OpenGL;

glCamera::glCamera(int width, int heigth, unsigned char figure_size) { // перспективное отображение
    radius = 0.5f * figure_size - 0.5f;
    Pos.z = float(figure_size) * 3.0f;// отдалить камеру
    screen_width = width;
    screen_height = heigth;
    projection = glm::perspective(45.0f, (float)screen_width / (float)screen_height, 1.1f, 100.0f);
}

void glCamera::changeScale(double k) {
    
    Scale += ScaleSpeed * k;

    if (Scale < SCALE_MIN)
        Scale = SCALE_MIN;
    if (Scale > SCALE_MAX)
        Scale = SCALE_MAX;
}

void glCamera::changeDegree(double x_k, double y_k) {
    
    Yaw += x_k * Speed;
    Pitch += y_k * Speed;

    // TODO: в отдельный класс (поведение градусов)
    if (Pitch < .0f) Pitch = 360.0f + Pitch;
    if (Yaw < .0f) Yaw = 360.0f + Yaw;
    Pitch = Pitch - (int(Pitch) / 360) * 360.0f;// закольцовывание
    Yaw = Yaw - (int(Yaw) / 360) * 360.0f;
    
    //std::cout << Pitch << "  " << Yaw << std::endl;
    //std::cout << getPos().x << " # " << getPos().y << " # " << getPos().z << std::endl;
}

void glCamera::setPosition()
{
    using namespace glm;
    view = glm::scale(glm::lookAt(Pos, Pos + Front, Up), glm::vec3(Scale, Scale, Scale));
    view = glm::rotate(view, glm::radians(Pitch), glm::vec3(1.0f, .0f, .0f));
    view = glm::rotate(view, glm::radians(Yaw), glm::vec3(.0f, 1.0f, .0f));  
}

void glCamera::inverseRotation(float& pitch, float& yaw)
{
    //if (Pitch > 180.0f || Yaw > 180.0f)
    //    yaw = -yaw;
}

glm::vec3 glCamera::castRay(float mouse_x, float mouse_y)
{
    float norm_x = mouse_x / (screen_width * 0.5f) - 1.0f; // Ќормализаци€ позиции курсора
    float norm_y = mouse_y / (screen_height * 0.5f) - 1.0f;
    glm::mat4 invVP = glm::inverse(projection * view);
    glm::vec4 screenPos = glm::vec4(norm_x, -norm_y, 1.0f, 1.0f);
    glm::vec4 worldPos = invVP * screenPos;
    glm::vec3 dir = glm::normalize(glm::vec3(worldPos));
    return dir;
}

OpenGL::glCamera::~glCamera()
{
}
