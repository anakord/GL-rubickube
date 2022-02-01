#include "glShader.h"

#include <fstream>
#include <iostream>

using namespace OpenGL;

// ___ glShader ___

glShader::glShader(const std::string& shader_name, GLint shader_type) {
    this->name = shader_name;
    if(read_from_file(name)) {
        this->type = shader_type;
    }
}

bool glShader::read_from_file(const std::string& shader_name) {
    std::ifstream reader(SHADERS_DIR + shader_name);
    if (!reader.is_open()) {
        std::cout << "ERROR (" << name << "): UNABLE TO READ" << std::endl;
        return false;
    }

    source = std::string(
        std::istreambuf_iterator<char>(reader),
        std::istreambuf_iterator<char>()
    );

    reader.close();
    return true;
}

void glShader::compile() {
    const GLchar* adapter = source.c_str();
    handle = glCreateShader(type);
    glShaderSource(handle, 1, &adapter, NULL);
    glCompileShader(handle);
}

bool glShader::status() {
    GLint success; // проверка сборки
    GLchar infoLog[512];
    glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
    if (success) 
        std::cout << "INFO (" << name << "): COMPILATION_SUCCESS" << std::endl;
    else {
        glGetShaderInfoLog(handle, 512, NULL, infoLog);
        std::cout << "ERROR (" << name << "): COMPILATION_FAILED" << std::endl;
        std::cout << infoLog << std::endl;
        return false;
    }
     
    return true;
}

glShader::~glShader() {
}


// ___ glShaderProgram ___

glShaderProgram::glShaderProgram()
{
    shaders.push_back(glShader("vertex.glsl", GL_VERTEX_SHADER));
    shaders.push_back(glShader("fragment.glsl", GL_FRAGMENT_SHADER));
}

void glShaderProgram::link() {
    handle = glCreateProgram();
    for (auto i = shaders.begin(); i != shaders.end(); ++i) {
        i->compile();
        if (i->status()) {
            glAttachShader(handle, i->getHandlde());
            glDeleteShader(i->getHandlde());
        }
    }
    glLinkProgram(handle);
}

bool glShaderProgram::status()
{
    GLint success; // проверка линковки
    GLchar infoLog[512];
    glGetProgramiv(handle, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(handle, 512, NULL, infoLog);
        std::cout << infoLog << std::endl;
        return false;
    }
    return true;
}

void glShaderProgram::loadModel(glm::mat4 model)
{
    GLint loc; // указатель на uniform шейдера
    loc = glGetUniformLocation(handle, "model");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(model));
}

void glShaderProgram::Use(glm::mat4 view, glm::mat4 projection) {
    
    glUseProgram(handle);
    
    GLint loc; // указатель на uniform шейдера

    loc = glGetUniformLocation(handle, "view");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(view));

    loc = glGetUniformLocation(handle, "projection");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(projection));

}

glShaderProgram::~glShaderProgram()
{
    
}
