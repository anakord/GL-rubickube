#include "glController.h"

using namespace OpenGL;

glController::glController(void* context, glCamera* camera, glFigures* figures)
{
    this->camera = camera;
    glController::figures = figures;
}


// glController REALIZATION
bool glController::is_camera_move = false;
double glController::inputX = 0.0, glController::inputY = 0.0;
glFigures* glController::figures = nullptr;

glMouseController::glMouseController(GLFWwindow* window, glCamera* camera, glFigures* figures)
    :glController(window, camera, figures) {
    this->window = window;
    glfwMakeContextCurrent(this->window);
    glfwSetWindowUserPointer(window, camera); // push contoller data to callback 
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
/*
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
*/

void glMouseController::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    glCamera* context = static_cast<glCamera*>(glfwGetWindowUserPointer(window));
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        glController::is_camera_move = false;
        return;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double mouseX = 0.0, mouseY = 0.0;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        glController::is_camera_move = true;
        figures->is_hit(context->getPos(), context->castRay(mouseX, mouseY));
        glfwGetCursorPos(window, &glController::inputX, &glController::inputY);
    }
}

void glMouseController::mouse_cursor_callback(GLFWwindow* window, double xpos, double ypos)
{
    glCamera* context = static_cast<glCamera*>(glfwGetWindowUserPointer(window));
    double curX = inputX, curY = inputY;
    glfwGetCursorPos(window, &glController::inputX, &glController::inputY);
    if (glController::is_camera_move) {
        context->changeDegree(glController::inputX - curX, glController::inputY - curY);
    }
}

void glMouseController::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    glCamera* context = static_cast<glCamera*>(glfwGetWindowUserPointer(window));
    context->changeScale(yoffset);
}

