#include "glFigure.h"
#include <limits.h>
#include <array>
#include <cmath>
#include <iostream>

using namespace OpenGL;

const float glFigure::SIZE = 0.5f;
const glm::vec3 glFigure::Color::RED    = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 glFigure::Color::GREEN  = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 glFigure::Color::BLUE   = glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3 glFigure::Color::YELLOW = glm::vec3(1.0f, 1.0f, 0.0f);
const glm::vec3 glFigure::Color::PURPLE = glm::vec3(1.0f, 0.0f, 1.0f);
const glm::vec3 glFigure::Color::WHITE  = glm::vec3(1.0f, 1.0f, 1.0f);
const glm::vec3 glFigure::Color::NONE   = glm::vec3(0.0f, 0.0f, 0.0f);

glFigure::glFigure(glm::vec3 center) {
    model = glm::translate(glm::mat4(1.0f), center);
    this->center = &model[3];
    LOGICAL_POSITION = center;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    texture = new glTexture("side.png");
}

double glFigure::is_hit(glm::vec3 ray_origin_wor, glm::vec3 ray_direction_wor)
{
    using namespace glm;
    vec3 oc = ray_origin_wor - (vec3(*center * 3.5f)); // смещение точки относительно камеры + разнос
    auto a = dot(ray_direction_wor, ray_direction_wor);
    auto b = 2.0 * dot(oc, ray_direction_wor);
    auto c = dot(oc, oc) - 1.8 * 1.8;
    auto discriminant = b * b - 4 * a * c;
    if (discriminant < 0) // пересечения нет
        return 0.0;
    discriminant = sqrt(discriminant);
    auto t = (-0.5) * (b + discriminant) / a;
    double distance = sqrt(a) * t;
    return distance;
}

void glFigure::addOrbitRotate(double pitch, double yaw)
{
    glm::qua <float> q = glm::qua <float>(glm::radians(glm::vec3(pitch, yaw, 0.0f)));
    model = glm::mat4_cast(q) * model;
    d_pitch += pitch; // приращение угла отклонения
    d_yaw += yaw;
    // TODO: в отдельный класс (поведение градусов)
    if (d_pitch < 0.0) d_pitch = 360.0 + d_pitch;
    if (d_yaw < 0.0) d_yaw = 360.0 + d_yaw;
    d_pitch = d_pitch - (int(d_pitch) / 360) * 360.0;// закольцовывание
    d_yaw = d_yaw - (int(d_yaw) / 360) * 360.0;
}


glFigure::~glFigure() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

// glFigure REALIZATION

// CUBE
Cube::Cube(glm::vec3 center,
           glm::vec3 back_color, glm::vec3 front_color,
           glm::vec3 left_color, glm::vec3 right_color,
           glm::vec3 bottom_color, glm::vec3 top_color)
              :glFigure(center) {

    vertex vertices[] = {
                                         // BACK
       glm::vec3(-SIZE, -SIZE, -SIZE),  back_color,  glm::vec2(0.0f, 0.0f),
       glm::vec3( SIZE, -SIZE, -SIZE),  back_color,  glm::vec2(1.0f, 0.0f),
       glm::vec3( SIZE,  SIZE, -SIZE),  back_color,  glm::vec2(1.0f, 1.0f),
       glm::vec3( SIZE,  SIZE, -SIZE),  back_color,  glm::vec2(1.0f, 1.0f),
       glm::vec3(-SIZE,  SIZE, -SIZE),  back_color,  glm::vec2(0.0f, 1.0f),
       glm::vec3(-SIZE, -SIZE, -SIZE),  back_color,  glm::vec2(0.0f, 0.0f),
                                        
                                         // FRONT
       glm::vec3(-SIZE, -SIZE,  SIZE),  front_color,  glm::vec2(0.0f, 0.0f),
       glm::vec3( SIZE, -SIZE,  SIZE),  front_color,  glm::vec2(1.0f, 0.0f),
       glm::vec3( SIZE,  SIZE,  SIZE),  front_color,  glm::vec2(1.0f, 1.0f),
       glm::vec3( SIZE,  SIZE,  SIZE),  front_color,  glm::vec2(1.0f, 1.0f),
       glm::vec3(-SIZE,  SIZE,  SIZE),  front_color,  glm::vec2(0.0f, 1.0f),
       glm::vec3(-SIZE, -SIZE,  SIZE),  front_color,  glm::vec2(0.0f, 0.0f),
                                        
                                         // LEFT
        glm::vec3(-SIZE,  SIZE,  SIZE), left_color,  glm::vec2(1.0f, 0.0f),
        glm::vec3(-SIZE,  SIZE, -SIZE), left_color,  glm::vec2(1.0f, 1.0f),
        glm::vec3(-SIZE, -SIZE, -SIZE), left_color,  glm::vec2(0.0f, 1.0f),
        glm::vec3(-SIZE, -SIZE, -SIZE), left_color,  glm::vec2(0.0f, 1.0f),
        glm::vec3(-SIZE, -SIZE,  SIZE), left_color,  glm::vec2(0.0f, 0.0f),
        glm::vec3(-SIZE,  SIZE,  SIZE), left_color,  glm::vec2(1.0f, 0.0f),
                                         
                                         // RIGHT
        glm::vec3(SIZE,  SIZE,  SIZE),  right_color,  glm::vec2(1.0f, 0.0f),
        glm::vec3(SIZE,  SIZE, -SIZE),  right_color,  glm::vec2(1.0f, 1.0f),
        glm::vec3(SIZE, -SIZE, -SIZE),  right_color,  glm::vec2(0.0f, 1.0f),
        glm::vec3(SIZE, -SIZE, -SIZE),  right_color,  glm::vec2(0.0f, 1.0f),
        glm::vec3(SIZE, -SIZE,  SIZE),  right_color,  glm::vec2(0.0f, 0.0f),
        glm::vec3(SIZE,  SIZE,  SIZE),  right_color,  glm::vec2(1.0f, 0.0f),
                                        
                                         // BOTTOM
        glm::vec3(-SIZE, -SIZE, -SIZE), bottom_color,  glm::vec2(0.0f, 1.0f),
        glm::vec3( SIZE, -SIZE, -SIZE), bottom_color,  glm::vec2(1.0f, 1.0f),
        glm::vec3( SIZE, -SIZE,  SIZE), bottom_color,  glm::vec2(1.0f, 0.0f),
        glm::vec3( SIZE, -SIZE,  SIZE), bottom_color,  glm::vec2(1.0f, 0.0f),
        glm::vec3(-SIZE, -SIZE,  SIZE), bottom_color,  glm::vec2(0.0f, 0.0f),
        glm::vec3(-SIZE, -SIZE, -SIZE), bottom_color,  glm::vec2(0.0f, 1.0f),
                                                 
                                        // TOP
        glm::vec3(-SIZE,  SIZE, -SIZE), top_color,  glm::vec2(0.0f, 1.0f),
        glm::vec3( SIZE,  SIZE, -SIZE), top_color,  glm::vec2(1.0f, 1.0f),
        glm::vec3( SIZE,  SIZE,  SIZE), top_color,  glm::vec2(1.0f, 0.0f),
        glm::vec3( SIZE,  SIZE,  SIZE), top_color,  glm::vec2(1.0f, 0.0f),
        glm::vec3(-SIZE,  SIZE,  SIZE), top_color,  glm::vec2(0.0f, 0.0f),
        glm::vec3(-SIZE,  SIZE, -SIZE), top_color,  glm::vec2(0.0f, 1.0f)
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

const glm::vec3* glCubes::Color::BACK =   &glFigure::Color::RED;
const glm::vec3* glCubes::Color::FRONT =  &glFigure::Color::BLUE;
const glm::vec3* glCubes::Color::LEFT =   &glFigure::Color::PURPLE;
const glm::vec3* glCubes::Color::RIGHT =  &glFigure::Color::WHITE;
const glm::vec3* glCubes::Color::BOTTOM = &glFigure::Color::GREEN;
const glm::vec3* glCubes::Color::TOP =    &glFigure::Color::YELLOW;

glCubes::glCubes(uchar n)
    :glFigures(n) {
    char min = - n_row / 2.0f, max = n_row / 2.0f;
    //if (n_row % 2 == 0) {
    //    min += 0.5f;
    //    max -= 0.5f;
    //}
    for(char z = min; z <= max; z++) {
        for(char y = min; y <= max; y++)
            for(char x = min; x <= max; x++) {
                
                glm::vec3 back =   glFigure::Color::NONE;
                glm::vec3 front =  glFigure::Color::NONE;
                glm::vec3 left =   glFigure::Color::NONE;
                glm::vec3 right =  glFigure::Color::NONE;
                glm::vec3 bottom = glFigure::Color::NONE;
                glm::vec3 top =    glFigure::Color::NONE;
                
                if(x == min) left = *glCubes::Color::LEFT;
                if (x == max) right = *glCubes::Color::RIGHT;
         
                if (y == min) bottom = *glCubes::Color::BOTTOM;
                if (y == max) top = *glCubes::Color::TOP;
                
                if (z == min) back = *glCubes::Color::BACK;
                if (z == max) front = *glCubes::Color::FRONT;

                Cube* configured = new Cube(glm::vec3(x, y, z),
                    back, front,
                    left, right,
                    bottom, top);
                      
                figures.push_back(configured);
            }
    }
}

void glCubes::draw(glShaderProgram* sh_program) {
    for(auto it = figures.begin(); it != figures.end(); ++it) {
        sh_program->loadModel((*it)->getModel());
        (*it)->draw();
    }
}

glFigure* glFigures::is_hit(glm::vec3 ray_origin_wor, glm::vec3 ray_direction_wor) {
    double cur_distance = 0.0, min_distance = DBL_MAX;
    glFigure *selected_figure = nullptr;
    for (auto it = figures.begin(); it != figures.end(); ++it) {
        cur_distance = (*it)->is_hit(ray_origin_wor, ray_direction_wor);
        if (cur_distance > 0.0 && cur_distance < min_distance) {
            selected_figure = *it;
            min_distance = cur_distance;
        } 
    }
    if (selected_figure) {
        std::cout << selected_figure->center->x << " | " << selected_figure->center->y << " | " << selected_figure->center->z << " | " << std::endl;
        std::cout << std::endl;
    }
    return selected_figure;
}

void glFigures::stable(glFigure* selected_figure) {
    double previous = 0.0;
    for (auto it = figures.begin(); it != figures.end(); ++it) {
        if ((*it)->LOGICAL_POSITION.y == selected_figure->LOGICAL_POSITION.y) {
            for (double fixed_positions = 360.0; fixed_positions >= 0.0; fixed_positions -= 90.0) {
                previous = fixed_positions - 90.0;
                if (fixed_positions == 0.0)
                    previous = 360.0; // TODO: в отдельный класс (поведение градусов)
                
                if ((*it)->d_yaw >= fixed_positions - 45.0 && (*it)->d_yaw <= fixed_positions)
                    (*it)->addOrbitRotate(0.0, fixed_positions - (*it)->d_yaw);
                else  if((*it)->d_yaw <= fixed_positions - 45.0 && (*it)->d_yaw >= previous)
                    (*it)->addOrbitRotate(0.0, previous - (*it)->d_yaw);
            
            }
                (*it)->d_yaw = 0.0;
        }
        // TODO: общий обработчик
        if ((*it)->LOGICAL_POSITION.x == selected_figure->LOGICAL_POSITION.x) {
            for (double fixed_positions = 360.0; fixed_positions >= 0.0; fixed_positions -= 90.0) {
                previous = fixed_positions - 90.0;
                if (fixed_positions == 0.0)
                    previous = 360.0; // TODO: в отдельный класс (поведение градусов)

                if ((*it)->d_pitch >= fixed_positions - 45.0 && (*it)->d_pitch <= fixed_positions)
                    (*it)->addOrbitRotate(fixed_positions - (*it)->d_pitch, 0.0);
                else  if ((*it)->d_pitch <= fixed_positions - 45.0 && (*it)->d_pitch >= previous)
                    (*it)->addOrbitRotate(previous - (*it)->d_pitch, 0.0);
            }
            (*it)->d_pitch = 0.0;
        }
        (*it)->LOGICAL_POSITION.x = round((*it)->center->x);
        (*it)->LOGICAL_POSITION.y = round((*it)->center->y);
        (*it)->LOGICAL_POSITION.z = round((*it)->center->z);
    }
}

void glFigures::rotate_lineH(glFigure* selected_figure, double degree)
{
    for (auto it = figures.begin(); it != figures.end(); ++it) {    
        if ((*it)->LOGICAL_POSITION.y == selected_figure->LOGICAL_POSITION.y)
            (*it)->addOrbitRotate(0.0, degree);
    }
}

void glFigures::rotate_lineV(glFigure* selected_figure, double degree)
{
    for (auto it = figures.begin(); it != figures.end(); ++it) {
        if ((*it)->LOGICAL_POSITION.x == selected_figure->LOGICAL_POSITION.x)
            (*it)->addOrbitRotate(degree, 0.0);       
    }
}



glCubes::~glCubes() {

}
