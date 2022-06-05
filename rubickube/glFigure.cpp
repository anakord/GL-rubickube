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
    vec3 oc = ray_origin_wor - (vec3(*center)); // смещение точки относительно камеры + разнос
    auto a = dot(ray_direction_wor, ray_direction_wor);
    auto b = 2.0 * dot(oc, ray_direction_wor);
    auto c = dot(oc, oc) - 1.0f * 1.0f;
    auto discriminant = b * b - 4 * a * c;
    if (discriminant < 0) // пересечения нет
        return 0.0;
    discriminant = sqrt(discriminant);
    auto t = (-0.5) * (b + discriminant) / a;
    double distance = sqrt(a) * t;
    return distance;
}

void glFigure::addOrbitRotate(float pitch, float yaw, float roll)
{
    glm::qua <float> q = glm::qua <float>(glm::radians(glm::vec3(pitch, yaw, roll)));
    model = glm::mat4_cast(q) * model;
    d_pitch += pitch; // приращение угла отклонения
    d_yaw += yaw;
    d_roll += roll;
    // TODO: в отдельный класс (поведение градусов)
    if (d_pitch < 0.0f) d_pitch = 360.0f + d_pitch;
    if (d_yaw < 0.0f) d_yaw = 360.0f + d_yaw;
    if (d_roll < 0.0f) d_roll = 360.0f + d_roll;
    d_pitch = d_pitch - (int(d_pitch) / 360) * 360.0f;// закольцовывание
    d_yaw = d_yaw - (int(d_yaw) / 360) * 360.0f;
    d_roll = d_roll - (int(d_roll) / 360) * 360.0f;
}


glFigure::~glFigure() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

// glFigure REALIZATION

// glCube
glCube::glCube(glm::vec3 center,
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

void glCube::draw() {
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->getTexture());
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

glCube::~glCube() {
    
}

Face::Face(glm::vec3 point, glm::vec3 normal)
{
    this->point = point;
    this->normal = normal;
}



void Face::addFigure(glFigure* figure)
{
    figures.push_back(figure);
}

double Face::is_hit(glm::vec3 ray_origin_wor, glm::vec3 ray_direction_wor)
{
    using namespace glm;
    float denom = dot(normal, ray_direction_wor);
    if (fabs(denom) >= 0.0001f) {
        float t = dot(point - ray_origin_wor, normal) / denom;
        if (denom < 0 && t >= 0.0001f) {
            vec3 O = point + (ray_direction_wor * t);
            return distance(ray_origin_wor, O);
        }
    }
}

Face::~Face() {

}

glFigures::glFigures(uchar n) {
    n_row = n;
}

void OpenGL::glFigures::draw(glShaderProgram* sh_program)
{

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

    using namespace glm;

    if (n_row % 2 != 0) {
        min = trunc(-n_row / 2.0f);
        max = trunc(n_row / 2.0f);
    }
    else {
        min = (-n_row / 2.0f) + 0.5f;
        max = (n_row / 2.0f) - 0.5f;
    }

    faces.resize(N_FACES);
    faces[FRONT] = new Face(vec3(0.0f, 0.0f, max), vec3(0.0f, 0.0f, 1.0f)); //FRONT
    faces[BACK] = new Face(vec3(0.0f, 0.0f, min), vec3(0.0f, 0.0f, -1.0f)); // BACK
    faces[TOP] = new Face(vec3(0.0f, max, 0.0f), vec3(0.0f, 1.0f, 0.0f)); // TOP
    faces[BOTTOM] = new Face(vec3(0.0f, min, 0.0f), vec3(0.0f, -1.0f, 0.0f)); // BOTTOM
    faces[RIGHT] = new Face(vec3(max, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f)); // RIGHT
    faces[LEFT] = new Face(vec3(min, 0.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f)); // LEFT


    for(float z = min; z <= max; z++) {
        for(float y = min; y <= max; y++)
            for(float x = min; x <= max; x++) {
                
                glm::vec3 back =   glFigure::Color::NONE;
                glm::vec3 front =  glFigure::Color::NONE;
                glm::vec3 left =   glFigure::Color::NONE;
                glm::vec3 right =  glFigure::Color::NONE;
                glm::vec3 bottom = glFigure::Color::NONE;
                glm::vec3 top =    glFigure::Color::NONE;
                
                glCube* configured;

                if (x == min) 
                    left = *glCubes::Color::LEFT;
                if (x == max) 
                    right = *glCubes::Color::RIGHT;
                if (y == min) 
                    bottom = *glCubes::Color::BOTTOM;
                if (y == max)
                    top = *glCubes::Color::TOP;
                if (z == min) 
                    back = *glCubes::Color::BACK;
                if (z == max)
                    front = *glCubes::Color::FRONT;
                
                configured = new glCube(glm::vec3(x, y, z),
                    back, front,
                    left, right,
                    bottom, top);
               
                // назначение фигурам граней
                if (x == min)
                    faces[LEFT]->addFigure(configured);
                if (x == max)
                    faces[RIGHT]->addFigure(configured);
                if (y == min)
                    faces[BOTTOM]->addFigure(configured);
                if (y == max)
                    faces[TOP]->addFigure(configured);
                if (z == min)
                    faces[BACK]->addFigure(configured);
                if (z == max)
                    faces[FRONT]->addFigure(configured);
              
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
    
    double cur_distance = 0.0, min_distance = DBL_MAX, max_distance = DBL_MIN;
    Face* selected_face = nullptr;

    // определение выбранной грани
    for (auto it = faces.begin(); it != faces.end(); ++it) {
        float denom = glm::dot((*it)->normal, ray_direction_wor);
        if (fabs(denom) >= 0.0001f) {
            float t = glm::dot((*it)->point - ray_origin_wor, (*it)->normal) / denom;
            if (t >= 0.0001f) {
                glm::vec3 O = (*it)->point + (ray_direction_wor * t);
                cur_distance = glm::distance(ray_origin_wor, O);
                if (denom < 0) {
                    if (max_distance < cur_distance) {
                        max_distance = cur_distance;
                        selected_face = *it;
                    }
                } 
            }
        }   
    }

    cur_distance = 0.0;
    min_distance = DBL_MAX;
    
    glFigure *selected_figure = nullptr;
    for (auto it = figures.begin(); it != figures.end(); ++it) {
        cur_distance = (*it)->is_hit(ray_origin_wor, ray_direction_wor);
        if (cur_distance > 0.0 && cur_distance < min_distance) {
            selected_figure = *it;
            min_distance = cur_distance;
        } 
    }

    return selected_figure;
}

void glFigures::stable(glFigure* selected_figure) {
    for (auto it = figures.begin(); it != figures.end(); ++it) {
        for (float fixed_positions = 360.0f; fixed_positions >= 0.0f; fixed_positions -= 90.0f) {
            float previous = fixed_positions - 90.0f;
            if (fixed_positions == 0.0f)
                previous = 360.0f;
            if (((*it)->LOGICAL_POSITION.x) == (selected_figure->LOGICAL_POSITION.x)) {
                if ((*it)->d_pitch >= fixed_positions - 45.0f && (*it)->d_pitch <= fixed_positions)
                    (*it)->addOrbitRotate(fixed_positions - (*it)->d_pitch, 0.0f, 0.0f);
                else  if ((*it)->d_pitch <= fixed_positions - 45.0f && (*it)->d_pitch >= previous)
                    (*it)->addOrbitRotate(previous - (*it)->d_pitch, 0.0f, 0.0f);
            }
            if (((*it)->LOGICAL_POSITION.y) == (selected_figure->LOGICAL_POSITION.y)) {
                if ((*it)->d_yaw >= fixed_positions - 45.0f && (*it)->d_yaw <= fixed_positions)
                    (*it)->addOrbitRotate(0.0, fixed_positions - (*it)->d_yaw, 0.0f);
                else  if ((*it)->d_yaw <= fixed_positions - 45.0f && (*it)->d_yaw >= previous)
                    (*it)->addOrbitRotate(0.0, previous - (*it)->d_yaw, 0.0f);
            }
            if (((*it)->LOGICAL_POSITION.z) == (selected_figure->LOGICAL_POSITION.z)) {
                if ((*it)->d_roll >= fixed_positions - 45.0f && (*it)->d_roll <= fixed_positions)
                    (*it)->addOrbitRotate(0.0f, 0.0f, fixed_positions - (*it)->d_roll);
                else  if ((*it)->d_roll <= fixed_positions - 45.0f && (*it)->d_roll >= previous)
                    (*it)->addOrbitRotate(0.0, 0.0f, previous - (*it)->d_roll);
            }
        }
        (*it)->LOGICAL_POSITION.x = round((*it)->center->x);
        (*it)->LOGICAL_POSITION.y = round((*it)->center->y);
        (*it)->LOGICAL_POSITION.z = round((*it)->center->z);
    }
}


void glFigures::rotateLine(glFigure* selected_figure, float yaw, float pitch, float roll)
{
    for (auto it = figures.begin(); it != figures.end(); ++it) {      
        if ((*it)->LOGICAL_POSITION.x == selected_figure->LOGICAL_POSITION.x)
            (*it)->addOrbitRotate(yaw, 0.0f, 0.0f);
        if ((*it)->LOGICAL_POSITION.y == selected_figure->LOGICAL_POSITION.y)
            (*it)->addOrbitRotate(0.0f, pitch, 0.0f);
        if ((*it)->LOGICAL_POSITION.z == selected_figure->LOGICAL_POSITION.z)
            (*it)->addOrbitRotate(0.0f, 0.0f, roll);
    }
}

glCubes::~glCubes() {

}

