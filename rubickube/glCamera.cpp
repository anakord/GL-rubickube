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

glm::vec3 OpenGL::glCamera::castRay(double mouse_x, double mouse_y)
{
    using namespace glm;
    vec3 ray_ndc = getNormalisedDeviceCoordinates(mouse_x, mouse_y);
    vec4 ray_clip = vec4(ray_ndc.x, ray_ndc.y, -1.0, 1.0);
    vec4 ray_eye = toEyeCoords(ray_clip);
    vec3 ray_world = toWorldCoords(ray_eye);
    return ray_world;
}

glCamera::~glCamera() {
	
}

glm::vec3 OpenGL::glCamera::getNormalisedDeviceCoordinates(float mouse_x, float mouse_y)
{
    using namespace glm;
    float ndc_x = (2.0f * mouse_x) / (double)screen_width - 1.0f;
    float ndc_y = 1.0f - (2.0f * mouse_y) / (double)screen_height;
    float ndc_z = 1.0;
    return vec3(ndc_x, ndc_y, ndc_z);
}

glm::vec4 OpenGL::glCamera::toEyeCoords(glm::vec4 ray_clip)
{
    using namespace glm;
    vec4 ray_eye = inverse(projection) * ray_clip;
    // Now, we only needed to un-project the x,y part, so let's manually set the z,w part to mean "forwards, and not a point"
    ray_eye = vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
    return ray_eye;
}

glm::vec3 OpenGL::glCamera::toWorldCoords(glm::vec4 ray_eye)
{
    using namespace glm;
    vec3 ray_world = inverse(projection) * ray_eye;
    ray_world = normalize(ray_world);
    return ray_world;
}
