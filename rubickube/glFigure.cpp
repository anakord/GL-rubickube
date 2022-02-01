#include "glFigure.h"
#include "glTexture.h"

using namespace OpenGL;


const glm::vec3 glFigure::Color::RED    = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 glFigure::Color::GREEN  = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 glFigure::Color::BLUE   = glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3 glFigure::Color::YELLOW = glm::vec3(1.0f, 1.0f, 0.0f);
const glm::vec3 glFigure::Color::PURPLE = glm::vec3(1.0f, 0.0f, 1.0f);
const glm::vec3 glFigure::Color::WHITE  = glm::vec3(1.0f, 1.0f, 1.0f);
const glm::vec3 glFigure::Color::NONE   = glm::vec3(0.0f, 0.0f, 0.0f);

glFigure::glFigure() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    texture = new glTexture("side.png");

}

glFigure::~glFigure() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

// glFigure REALIZATION

// CUBE

Cube::Cube(glm::vec3 BACK_COLOR, glm::vec3 FRONT_COLOR, 
           glm::vec3 LEFT_COLOR, glm::vec3 RIGHT_COLOR, 
           glm::vec3 BOTTOM_COLOR, glm::vec3 TOP_COLOR)
    :glFigure() {

    vertex vertices[] = {
                                         // BACK
       glm::vec3(-0.5f, -0.5f, -0.5f),  BACK_COLOR,  glm::vec2(0.0f, 0.0f),
       glm::vec3( 0.5f, -0.5f, -0.5f),  BACK_COLOR,  glm::vec2(1.0f, 0.0f),
       glm::vec3( 0.5f,  0.5f, -0.5f),  BACK_COLOR,  glm::vec2(1.0f, 1.0f),
       glm::vec3( 0.5f,  0.5f, -0.5f),  BACK_COLOR,  glm::vec2(1.0f, 1.0f),
       glm::vec3(-0.5f,  0.5f, -0.5f),  BACK_COLOR,  glm::vec2(0.0f, 1.0f),
       glm::vec3(-0.5f, -0.5f, -0.5f),  BACK_COLOR,  glm::vec2(0.0f, 0.0f),
                                        
                                         // FRONT
       glm::vec3(-0.5f, -0.5f,  0.5f),  FRONT_COLOR,  glm::vec2(0.0f, 0.0f),
       glm::vec3( 0.5f, -0.5f,  0.5f),  FRONT_COLOR,  glm::vec2(1.0f, 0.0f),
       glm::vec3( 0.5f,  0.5f,  0.5f),  FRONT_COLOR,  glm::vec2(1.0f, 1.0f),
       glm::vec3( 0.5f,  0.5f,  0.5f),  FRONT_COLOR,  glm::vec2(1.0f, 1.0f),
       glm::vec3(-0.5f,  0.5f,  0.5f),  FRONT_COLOR,  glm::vec2(0.0f, 1.0f),
       glm::vec3(-0.5f, -0.5f,  0.5f),  FRONT_COLOR,  glm::vec2(0.0f, 0.0f),
                                        
                                         // LEFT
        glm::vec3(-0.5f,  0.5f,  0.5f), LEFT_COLOR,  glm::vec2(1.0f, 0.0f),
        glm::vec3(-0.5f,  0.5f, -0.5f), LEFT_COLOR,  glm::vec2(1.0f, 1.0f),
        glm::vec3(-0.5f, -0.5f, -0.5f), LEFT_COLOR,  glm::vec2(0.0f, 1.0f),
        glm::vec3(-0.5f, -0.5f, -0.5f), LEFT_COLOR,  glm::vec2(0.0f, 1.0f),
        glm::vec3(-0.5f, -0.5f,  0.5f), LEFT_COLOR,  glm::vec2(0.0f, 0.0f),
        glm::vec3(-0.5f,  0.5f,  0.5f), LEFT_COLOR,  glm::vec2(1.0f, 0.0f),
                                         
                                         // RIGHT
        glm::vec3(0.5f,  0.5f,  0.5f),  RIGHT_COLOR,  glm::vec2(1.0f, 0.0f),
        glm::vec3(0.5f,  0.5f, -0.5f),  RIGHT_COLOR,  glm::vec2(1.0f, 1.0f),
        glm::vec3(0.5f, -0.5f, -0.5f),  RIGHT_COLOR,  glm::vec2(0.0f, 1.0f),
        glm::vec3(0.5f, -0.5f, -0.5f),  RIGHT_COLOR,  glm::vec2(0.0f, 1.0f),
        glm::vec3(0.5f, -0.5f,  0.5f),  RIGHT_COLOR,  glm::vec2(0.0f, 0.0f),
        glm::vec3(0.5f,  0.5f,  0.5f),  RIGHT_COLOR,  glm::vec2(1.0f, 0.0f),
                                        
                                         // BOTTOM
        glm::vec3(-0.5f, -0.5f, -0.5f), BOTTOM_COLOR,  glm::vec2(0.0f, 1.0f),
        glm::vec3( 0.5f, -0.5f, -0.5f), BOTTOM_COLOR,  glm::vec2(1.0f, 1.0f),
        glm::vec3( 0.5f, -0.5f,  0.5f), BOTTOM_COLOR,  glm::vec2(1.0f, 0.0f),
        glm::vec3( 0.5f, -0.5f,  0.5f), BOTTOM_COLOR,  glm::vec2(1.0f, 0.0f),
        glm::vec3(-0.5f, -0.5f,  0.5f), BOTTOM_COLOR,  glm::vec2(0.0f, 0.0f),
        glm::vec3(-0.5f, -0.5f, -0.5f), BOTTOM_COLOR,  glm::vec2(0.0f, 1.0f),
                                                 
                                        // TOP
        glm::vec3(-0.5f,  0.5f, -0.5f), TOP_COLOR,  glm::vec2(0.0f, 1.0f),
        glm::vec3( 0.5f,  0.5f, -0.5f), TOP_COLOR,  glm::vec2(1.0f, 1.0f),
        glm::vec3( 0.5f,  0.5f,  0.5f), TOP_COLOR,  glm::vec2(1.0f, 0.0f),
        glm::vec3( 0.5f,  0.5f,  0.5f), TOP_COLOR,  glm::vec2(1.0f, 0.0f),
        glm::vec3(-0.5f,  0.5f,  0.5f), TOP_COLOR,  glm::vec2(0.0f, 0.0f),
        glm::vec3(-0.5f,  0.5f, -0.5f), TOP_COLOR,  glm::vec2(0.0f, 1.0f)
    };
 
    glBindVertexArray(VAO); // set arrays' obj
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // load vertex data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
   
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
        
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
}

void Cube::draw() {
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->getTexture());
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

Cube::~Cube() {

}
