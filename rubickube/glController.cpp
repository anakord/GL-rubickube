#include "glController.h"

using namespace OpenGL;

glController::glController(void* context, glCamera* camera)
{

}


// glController REALIZATION

double glMouseController::mouseX = 0.0;
double glMouseController::mouseY = 0.0;

glMouseController::glMouseController(GLFWwindow* window, glCamera* camera)
    :glController(window, camera) {
    this->camera = camera;
    this->window = window;
    glfwMakeContextCurrent(this->window);
    glfwSetWindowUserPointer(window, camera); // push contoller data to callback functions
    loadEvents();
}

// Mouse Controller
void glMouseController::loadEvents()
{
    glfwSetCursorPosCallback(window, mouse_cursor_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);
}

// callbacks
void glMouseController::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    glCamera* context = static_cast<glCamera*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_W)
        context->changeDegree(0, 5);
    if (key == GLFW_KEY_S)
        context->changeDegree(0, -5);
    if (key == GLFW_KEY_A)
        context->changeDegree(-5, 0);
    if (key == GLFW_KEY_D)
        context->changeDegree(-5, 0);
}

void glMouseController::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    glCamera* context = static_cast<glCamera*>(glfwGetWindowUserPointer(window));
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        context->is_camera_move = false;
        return;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        context->castRay(glMouseController::mouseX, glMouseController::mouseX);
        context->is_camera_move = true;
        glfwGetCursorPos(window, &glMouseController::mouseX, &glMouseController::mouseX);
    }
}

void glMouseController::mouse_cursor_callback(GLFWwindow* window, double xpos, double ypos)
{
    glCamera* context = static_cast<glCamera*>(glfwGetWindowUserPointer(window));
    double curX = glMouseController::mouseX, curY = glMouseController::mouseY;
    glfwGetCursorPos(window, &glMouseController::mouseX, &glMouseController::mouseY);
    if (context->is_camera_move) {   
        context->changeDegree(glMouseController::mouseX - curX, glMouseController::mouseY - curY);
    }
}

void glMouseController::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    glCamera* context = static_cast<glCamera*>(glfwGetWindowUserPointer(window));
    context->changeScale(yoffset);
}

