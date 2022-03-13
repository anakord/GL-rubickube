#include "glApp.h"

using namespace OpenGL;

glApp::glApp(int width, int height)
{
    this->width = width;
    this->height = height;

    if (initWindow()) {
        std::cout << "Application sucessfully run." << std::endl;
        linkGLEW();
        loadShaders();
        loadCamera();
        loadFigures();
        loadController();
        
    }
    else 
        std::cout << "Application doesn't run." << std::endl;
}

bool glApp::initWindow()
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

    return true;
}

bool glApp::linkGLEW()
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return false;
    } else
        std::cout << "GLEW is initialized" << std::endl;
    return true;
}

void glApp::loadShaders()
{
    sh_program = new glShaderProgram();
    sh_program->link();
    if(sh_program->status())
        std::cout << "INFO (PROGRAM): LINK_SUCCESS" << std::endl;
    else 
        std::cout << "ERROR (PROGRAM): LINK_FAILED" << std::endl;
}

void glApp::loadCamera()
{
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);
    camera = new glCamera(width, height, DEFAULT_SIZE);
}

void glApp::loadController() {
    controller = new glMouseController(window, camera, cubes);
}

void glApp::loadFigures()
{
    if(sh_program) {
        cubes = new glCubes(DEFAULT_SIZE);
    }
}


void glApp::run()
{
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents(); // запрос на ввод
        
        camera->setPosition();
        sh_program->Use(camera->getView(), camera->getProjection()); // наложить шейдеры

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        
        //cubes->is_hit(camera->getPos(), camera->castRay(width, height));
        cubes->draw(sh_program);
        
        glfwSwapBuffers(window); 
    }
}

glApp::~glApp()
{
    if (sh_program)
        delete sh_program;
    if (camera) // удаление камеры
        delete camera;
    if (controller)
        delete controller;
    glfwDestroyWindow(window);
    glfwTerminate();
    std::cout << "Application was closed." << std::endl;
}