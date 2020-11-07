//
// Created by pbialas on 25.09.2020.
//

#include "app.h"

#include <iostream>
#include <vector>
#include <tuple>


#include "Application/utils.h"




void SimpleShapeApplication::init() {



    auto program = xe::create_program(std::string(PROJECT_DIR) + "/shaders/base_vs.glsl",
                                      std::string(PROJECT_DIR) + "/shaders/base_fs.glsl");

    auto u_modifiers_index = glGetUniformBlockIndex(program, "Modifiers");


    if (!program) {
        std::cerr << "Cannot create program from " << std::string(PROJECT_DIR) + "/shaders/base_vs.glsl" << " and ";
        std::cerr << std::string(PROJECT_DIR) + "/shaders/base_fs.glsl" << " shader files" << std::endl;

    }

    std::vector<GLfloat> vertices = {
            -0.5f, 0.0f, 0.0, 1.0f, 0.0f, 0.0f, // 0
            0.5f, 0.0f, 0.0, 1.0f, 0.0f, 0.0f, // 1
            0.0f, 1.0f, 0.0, 1.0f, 0.0f, 0.0f, // 2

            -0.5f, 0.0f, 0.0, 0.0f, 1.0f, 0.0f, // 0
            -0.35f, 0.5f, -0.3, 0.0f, 1.0f, 0.0f, // 3
            0.0f, 1.0f, 0.1, 0.0f, 1.0f, 0.0f, // 2

            -0.5f, 0.5f, 0.3, 0.0f, 0.0f, 1.0f, // 3
            0.5f, 0.0f, 0.3, 0.0f, 0.0f, 1.0f, // 4
            0.0f, 1.0f, 0.1, 0.0f, 0.0f, 1.0f, // 2

            0.5f, 0.0f, 0.0, 1.0f, 1.0f, 0.0f, // 1
            0.35f, 0.5f, 0.3, 1.0f, 1.0f, 0.0f, // 4
            0.0f, 1.0f, 0.1f, 1.0f, 1.0f, 0.0f // 2
    };



    GLuint v_buffer_handle;
    glGenBuffers(1, &v_buffer_handle);
    glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);



    GLuint idx_buffer_handle;
    glGenBuffers(1, &idx_buffer_handle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idx_buffer_handle);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(),
//                 GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idx_buffer_handle);
    glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(3 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    float strength = 1.0f;
    float light [] = {0.5f, 0.9f, 1.f};



    GLuint ubo_handle(0u);
    glGenBuffers(1,&ubo_handle);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_handle);
    glBufferData(GL_UNIFORM_BUFFER, 8 * sizeof(float), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_UNIFORM_BUFFER,0, sizeof(GLfloat) , &strength);
    glBufferSubData(GL_UNIFORM_BUFFER, 4 * sizeof(float), 3 * sizeof(float), light);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo_handle);



    glClearColor(0.81f, 0.81f, 0.8f, 1.0f);
    int w, h;
    std::tie(w, h) = frame_buffer_size();
    glViewport(0, 0, w, h);

    glEnable(GL_DEPTH_TEST);
    glUseProgram(program);
}

void SimpleShapeApplication::frame() {
    glBindVertexArray(vao_);
    glEnable(GL_DEPTH_TEST);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0);




}

