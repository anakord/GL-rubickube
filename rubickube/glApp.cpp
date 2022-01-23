#include "glApp.h"

using namespace OpenGL;

App::App(int width, int height)
{
    this->width = width;
    this->height = height;

    if (initWindow()) {
        std::cout << "Application sucessfully run." << std::endl;
        linkGLEW();
        loadShaders();
        loadCamera();
        loadFigures();
    }
    else 
        std::cout << "Application doesn't run." << std::endl;
}

bool App::initWindow() 
{
    std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(width, height,
                              "Rubick's cube", nullptr, nullptr);
    
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwGetFramebufferSize(window, &width, &height);

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    return true;
}

bool App::linkGLEW()
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return false;
    } else
        std::cout << "GLEW is initialized" << std::endl;
    return true;
}

void App::loadShaders()
{
    sh_program = new glShaderProgram();
    sh_program->link();
    if(sh_program->status())
        std::cout << "INFO (PROGRAM): LINK_SUCCESS" << std::endl;
    else 
        std::cout << "ERROR (PROGRAM): LINK_FAILED" << std::endl;
}

void App::loadCamera() 
{
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);
    camera = new glCamera(width, height);
}

void App::loadFigures()
{
    if(sh_program)
        figures.push_back(new Cube(sh_program->getHandle()));
}


void App::run()
{
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents(); // запрос на ввод
        
        sh_program->Use(); // наложить шейдеры
        camera->SetPosition(sh_program->getHandle());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        
        figures[0]->draw(); // отрисовка фигуры
        
        glfwSwapBuffers(window); 
    }
}

// callbacks
void App::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) 
{   

}

void App::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) 
{

}


App::~App() 
{
    if (sh_program)
        delete sh_program;
    if (camera) // удаление камеры
        delete camera;

    glfwDestroyWindow(window);
    glfwTerminate();
    std::cout << "Application was closed." << std::endl;
}