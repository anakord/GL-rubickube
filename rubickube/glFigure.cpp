#include "glFigure.h"

using namespace OpenGL;


const glm::vec3 glFigure::Color::RED    = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 glFigure::Color::GREEN  = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 glFigure::Color::BLUE   = glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3 glFigure::Color::YELLOW = glm::vec3(1.0f, 1.0f, 0.0f);
const glm::vec3 glFigure::Color::PURPLE = glm::vec3(1.0f, 0.0f, 1.0f);
const glm::vec3 glFigure::Color::WHITE  = glm::vec3(1.0f, 1.0f, 1.0f);
const glm::vec3 glFigure::Color::NONE   = glm::vec3(0.0f, 0.0f, 0.0f);

glFigure::glFigure(glm::mat4 position) {
    model = position;
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
Cube::Cube(glm::mat4 position,
           glm::vec3 back_color, glm::vec3 front_color,
           glm::vec3 left_color, glm::vec3 right_color,
           glm::vec3 bottom_color, glm::vec3 top_color) 
              :glFigure(position) {

    vertex vertices[] = {
                                         // BACK
       glm::vec3(-0.5f, -0.5f, -0.5f),  back_color,  glm::vec2(0.0f, 0.0f),
       glm::vec3( 0.5f, -0.5f, -0.5f),  back_color,  glm::vec2(1.0f, 0.0f),
       glm::vec3( 0.5f,  0.5f, -0.5f),  back_color,  glm::vec2(1.0f, 1.0f),
       glm::vec3( 0.5f,  0.5f, -0.5f),  back_color,  glm::vec2(1.0f, 1.0f),
       glm::vec3(-0.5f,  0.5f, -0.5f),  back_color,  glm::vec2(0.0f, 1.0f),
       glm::vec3(-0.5f, -0.5f, -0.5f),  back_color,  glm::vec2(0.0f, 0.0f),
                                        
                                         // FRONT
       glm::vec3(-0.5f, -0.5f,  0.5f),  front_color,  glm::vec2(0.0f, 0.0f),
       glm::vec3( 0.5f, -0.5f,  0.5f),  front_color,  glm::vec2(1.0f, 0.0f),
       glm::vec3( 0.5f,  0.5f,  0.5f),  front_color,  glm::vec2(1.0f, 1.0f),
       glm::vec3( 0.5f,  0.5f,  0.5f),  front_color,  glm::vec2(1.0f, 1.0f),
       glm::vec3(-0.5f,  0.5f,  0.5f),  front_color,  glm::vec2(0.0f, 1.0f),
       glm::vec3(-0.5f, -0.5f,  0.5f),  front_color,  glm::vec2(0.0f, 0.0f),
                                        
                                         // LEFT
        glm::vec3(-0.5f,  0.5f,  0.5f), left_color,  glm::vec2(1.0f, 0.0f),
        glm::vec3(-0.5f,  0.5f, -0.5f), left_color,  glm::vec2(1.0f, 1.0f),
        glm::vec3(-0.5f, -0.5f, -0.5f), left_color,  glm::vec2(0.0f, 1.0f),
        glm::vec3(-0.5f, -0.5f, -0.5f), left_color,  glm::vec2(0.0f, 1.0f),
        glm::vec3(-0.5f, -0.5f,  0.5f), left_color,  glm::vec2(0.0f, 0.0f),
        glm::vec3(-0.5f,  0.5f,  0.5f), left_color,  glm::vec2(1.0f, 0.0f),
                                         
                                         // RIGHT
        glm::vec3(0.5f,  0.5f,  0.5f),  right_color,  glm::vec2(1.0f, 0.0f),
        glm::vec3(0.5f,  0.5f, -0.5f),  right_color,  glm::vec2(1.0f, 1.0f),
        glm::vec3(0.5f, -0.5f, -0.5f),  right_color,  glm::vec2(0.0f, 1.0f),
        glm::vec3(0.5f, -0.5f, -0.5f),  right_color,  glm::vec2(0.0f, 1.0f),
        glm::vec3(0.5f, -0.5f,  0.5f),  right_color,  glm::vec2(0.0f, 0.0f),
        glm::vec3(0.5f,  0.5f,  0.5f),  right_color,  glm::vec2(1.0f, 0.0f),
                                        
                                         // BOTTOM
        glm::vec3(-0.5f, -0.5f, -0.5f), bottom_color,  glm::vec2(0.0f, 1.0f),
        glm::vec3( 0.5f, -0.5f, -0.5f), bottom_color,  glm::vec2(1.0f, 1.0f),
        glm::vec3( 0.5f, -0.5f,  0.5f), bottom_color,  glm::vec2(1.0f, 0.0f),
        glm::vec3( 0.5f, -0.5f,  0.5f), bottom_color,  glm::vec2(1.0f, 0.0f),
        glm::vec3(-0.5f, -0.5f,  0.5f), bottom_color,  glm::vec2(0.0f, 0.0f),
        glm::vec3(-0.5f, -0.5f, -0.5f), bottom_color,  glm::vec2(0.0f, 1.0f),
                                                 
                                        // TOP
        glm::vec3(-0.5f,  0.5f, -0.5f), top_color,  glm::vec2(0.0f, 1.0f),
        glm::vec3( 0.5f,  0.5f, -0.5f), top_color,  glm::vec2(1.0f, 1.0f),
        glm::vec3( 0.5f,  0.5f,  0.5f), top_color,  glm::vec2(1.0f, 0.0f),
        glm::vec3( 0.5f,  0.5f,  0.5f), top_color,  glm::vec2(1.0f, 0.0f),
        glm::vec3(-0.5f,  0.5f,  0.5f), top_color,  glm::vec2(0.0f, 0.0f),
        glm::vec3(-0.5f,  0.5f, -0.5f), top_color,  glm::vec2(0.0f, 1.0f)
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


glFigures::glFigures(uchar n) {
    n_row = n;
}

glFigures::~glFigures() {
    for(auto it = figures.begin(); it != figures.end(); ++it)
        delete *it;
    figures.clear();
}

glCubes::glCubes(uchar n)
    :glFigures(n) {
    for(uchar z = 0; z < n_row; z++) {
        for(uchar y = 0; y < n_row; y++)
            for(uchar x = 0; x < n_row; x++) {
                figures.push_back(new Cube(glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z)),
                    glFigure::Color::RED, glFigure::Color::RED, 
                    glFigure::Color::RED, glFigure::Color::RED, 
                    glFigure::Color::RED, glFigure::Color::RED));
            }
    }
}

void glCubes::draw(glShaderProgram* sh_program) {
    for(auto it = figures.begin(); it != figures.end(); ++it) {
        sh_program->loadModel((*it)->getModel());
        (*it)->draw();
    }
}

glCubes::~glCubes() {

}
