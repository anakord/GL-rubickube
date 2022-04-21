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
    
    Yaw += Speed * x_k;
    Pitch += Speed * y_k;
 
    if (Pitch > 360.0f)
        Pitch = 0.0f;
    
    if (Yaw > 360.0f)
        Yaw = 0.0f;
}

void glCamera::setPosition()
{
    using namespace glm;
    view = glm::scale(glm::lookAt(Pos, Pos + Front, Up), glm::vec3(Scale, Scale, Scale));
    view = glm::rotate(view, GLfloat(Pitch), glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::rotate(view, GLfloat(Yaw), glm::vec3(0.0f, 1.0f, 0.0f));  
}

glm::vec3 glCamera::castRay(double mouse_x, double mouse_y)
{
    glm::vec3 ray_ndc = getNormalisedDeviceCoordinates(mouse_x, mouse_y, screen_width, screen_height);
    // we want our ray's z to point forwards - this is usually the negative z direction in OpenGL style
    glm::vec4 ray_clip = glm::vec4(ray_ndc.x, ray_ndc.y, -1.0, 1.0);
    glm::vec4 ray_eye = toEyeCoords(ray_clip);
    glm::vec3 ray_world = toWorldCoords(ray_eye);
    return ray_world;
}
OpenGL::glCamera::~glCamera()
{
}
glm::vec3 glCamera::getNormalisedDeviceCoordinates(double mouse_x, double mouse_y, double screen_width, double screen_height)
{
    double ndc_x = (2.0f * mouse_x) / (double)screen_width - 1.0f;
    double ndc_y = 1.0f - (2.0f * mouse_y) / (double)screen_height;
    double ndc_z = 1.0;
    return glm::vec3(ndc_x, ndc_y, ndc_z);
}

/*
 * normally, to get into clip space from eye space we multiply the vector by a projection matrix
 * we can go backwards by multiplying by the inverse of this matrix
 */
glm::vec4 glCamera::toEyeCoords(glm::vec4 ray_clip)
{
    glm::vec4 ray_eye = projection * ray_clip;
    // Now, we only needed to un-project the x,y part, so let's manually set the z,w part to mean "forwards, and not a point"
    ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
    return ray_eye;

}

glm::vec3 glCamera::toWorldCoords(glm::vec4 ray_eye)
{
    glm::vec3 ray_world = projection * ray_eye;
    //ray_world = glm::normalize(ray_world);
    return ray_world;
}
