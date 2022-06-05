#include "glController.h"

using namespace OpenGL;

double glController::inputX = 0.0, glController::inputY = 0.0;
glCamera* glController::camera = nullptr;
glFigures* glController::figures = nullptr; // все фигуры
glFigure* glController::selected_figure = nullptr;
glController::Mode glController::current_mode = glController::Mode::NONE;

glController::glController(void* context, glCamera* camera, glFigures* figures)
{
    glController::camera = camera;
    glController::figures = figures;
}

glMouseController::glMouseController(GLFWwindow* window, glCamera* camera, glFigures* figures)
    :glController(window, camera, figures) {
    this->window = window;
    this->camera = camera;
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
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        current_mode = Mode::NONE;
        if(selected_figure)
            figures->stable(selected_figure); // стабизация вращения к ближайшему углу
        selected_figure = nullptr;
        return;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double mouseX = 0.0, mouseY = 0.0;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        selected_figure = figures->is_hit(camera->getPos(), camera->castRay(mouseX, mouseY));
        if (!selected_figure)
            current_mode = Mode::CAMERA;
        else {
            //std::cout << camera->getPos().x << "  " << camera->getPos().y << "  " << camera->getPos().z << "  " << std::endl;
            current_mode = Mode::SELECTED;
        }
        glfwGetCursorPos(window, &glController::inputX, &glController::inputY);
    }
}

void glMouseController::mouse_cursor_callback(GLFWwindow* window, double xpos, double ypos)
{
    float curX = inputX, curY = inputY;
    glfwGetCursorPos(window, &glController::inputX, &glController::inputY);
    float move_x = glController::inputX - curX,
          move_y = glController::inputY - curY;
    switch (current_mode) { // перемещение камеры
        case Mode::CAMERA: 
            camera->changeDegree(move_x, move_y);
            break;
        case Mode::SELECTED: 
            //std::cout << selected_figure->LOGICAL_POSITION.x << "  " << selected_figure->LOGICAL_POSITION.y << "  " << selected_figure->LOGICAL_POSITION.z << "  " << std::endl;
            if (abs(move_x) > abs(move_y))
                current_mode = Mode::HORIZONTAL_ROTATION;
            else current_mode = Mode::VERTICAL_ROTATION;
            
            break;
        case Mode::HORIZONTAL_ROTATION: 
            //if (abs(camera->getPos().y) < abs(camera->getPos().x) + abs(camera->getPos().z)) 
            //    figures->rotateLine(selected_figure, 0.0f, move_x, 0.0f);
            //else 
            //    figures->rotateLine(selected_figure, 0.0f, 0.0f, move_x);
            figures->rotateLine(selected_figure, 0.0f, move_x, 0.0f);
            break;
        case Mode::VERTICAL_ROTATION: 
            //if (abs(camera->getPos().x) < abs(camera->getPos().y) + abs(camera->getPos().z)) 
            //    figures->rotateLine(selected_figure, move_y, 0.0f, 0.0f);
            //else 
            //    figures->rotateLine(selected_figure, 0.0f, 0.0f, move_y);
            figures->rotateLine(selected_figure, move_y, 0.0f, 0.0f);
            break;
    }
}

void glMouseController::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera->changeScale(yoffset);
}

