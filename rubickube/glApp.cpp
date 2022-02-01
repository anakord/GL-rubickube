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
        loadController();
        loadFigures();
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
    camera = new glCamera(width, height);
}

void glApp::loadController() {
    controller = new glMouseController(window, camera);
}

void glApp::loadFigures()
{
    if (sh_program) {
        figures.push_back(new Cube(glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)),
            glFigure::Color::RED,
            glFigure::Color::GREEN,
            glFigure::Color::BLUE,
            glFigure::Color::YELLOW,
            glFigure::Color::PURPLE,
            glFigure::Color::WHITE)
        );
        figures.push_back(new Cube(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
            glFigure::Color::RED,
            glFigure::Color::GREEN,
            glFigure::Color::BLUE,
            glFigure::Color::YELLOW,
            glFigure::Color::PURPLE,
            glFigure::Color::WHITE)
        );
        figures.push_back(new Cube(glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
            glFigure::Color::RED,
            glFigure::Color::GREEN,
            glFigure::Color::BLUE,
            glFigure::Color::YELLOW,
            glFigure::Color::PURPLE,
            glFigure::Color::WHITE)
        );
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
        
        figures[0]->draw(sh_program); // отрисовка фигуры
        figures[1]->draw(sh_program); // отрисовка фигуры
        figures[2]->draw(sh_program); // отрисовка фигуры

        glfwSwapBuffers(window); 
    }
}

glApp::~glApp()
{
    if (sh_program)
        delete sh_program;
    if (camera) // удаление камеры
        delete camera;

    glfwDestroyWindow(window);
    glfwTerminate();
    std::cout << "Application was closed." << std::endl;
}