//
// Created by pbialas on 25.09.2020.
//


#include "app.h"

#include <vector>

#include "spdlog/spdlog.h"

#include "glad/gl.h"

#include "Application/utils.h"

#include "glm/glm.hpp"

#include "glm/gtc/constants.hpp"

void SimpleShapeApplication::init() {
    /*
     * A utility function that reads the shaders' source files, compiles them and creates the program object,
     * as everything in OpenGL we reference the program by an integer "handle".
     * The input to this function is a map that associates a shader type (GL_VERTEX_SHADER and GL_FRAGMENT_SHADER) with
     * its source file. The source files are located in the PROJECT_DIR/shaders directory, where  PROJECT_DIR is the
     * current assignment directory (e.g., src/Assignments/Triangle).
     */
    auto program = xe::utils::create_program(
        {
                {GL_VERTEX_SHADER,   std::string(PROJECT_DIR) + "/shaders/base_vs.glsl"},
                {GL_FRAGMENT_SHADER, std::string(PROJECT_DIR) + "/shaders/base_fs.glsl"}
        });


    if (!program) {
        SPDLOG_CRITICAL("Invalid program");
        exit(-1);
    }

     
    std::vector<GLfloat> vertices = {
            -0.5f, 0.0f, 0.0f,  1, 0, 0, //0
            0.5f, 0.0f, 0.0f,   1, 0, 0, //1
            0.0f, 0.5f, 0.0f,   1, 0, 0, //2
            -0.5f, -0.5f, 0.0f, 0, 1, 0, //3
            -0.5f, 0.0f, 0.0f,  0, 1, 0, //4
            0.5F, -0.5F, 0.0f,  0, 1, 0, //5
            0.5f, 0.0f, 0.0f,   0, 1, 0, //6
            };

    std::vector<GLubyte> indices = {
        0, 1, 2,
        3, 4, 5,
        4, 5, 6        
    }; 

    float strength = 0.5;
    float mix_color[3] = { 0.0, 0.0, 1.0 };

    float theta = 1.0 * glm::pi<float>() / 6.0f;//30 degrees
    auto cs = std::cos(theta);
    auto ss = std::sin(theta);
    glm::mat2 rot{ cs,ss,-ss,cs };
    glm::vec2 trans{ 0.0,  -0.25 };
    glm::vec2 scale{ 0.5, 0.5 };

    /*
     * All the calls to the OpenGL API are "encapsulated" in the OGL_CALL macro for debugging purposes as explained in
     * Assignments/DEBUGGING.md. The macro is defined in src/Application/utils.h. If the call to the OpenGL API returns an
     * error code, the macro will print the name of the function that failed, the file and line number where the error
     * occurred.
     */

     // Generating the buffer and loading the vertex data into it.
    GLuint v_buffer_handle;
    OGL_CALL(glCreateBuffers(1, &v_buffer_handle));
    OGL_CALL(glNamedBufferData(v_buffer_handle, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW));

    GLuint index_buffer;
    OGL_CALL(glCreateBuffers(1, &index_buffer));
    OGL_CALL(glNamedBufferData(index_buffer, indices.size() * sizeof(GLubyte), indices.data(), GL_STATIC_DRAW));

    GLuint mixer_buffer;
    OGL_CALL(glCreateBuffers(1, &mixer_buffer));
    OGL_CALL(glNamedBufferData(mixer_buffer, 8 * sizeof(float),nullptr ,GL_STATIC_DRAW));

    OGL_CALL(glNamedBufferSubData(mixer_buffer, 0, sizeof(float), &strength));
    OGL_CALL(glNamedBufferSubData(mixer_buffer, 4 * sizeof(float), 3 * sizeof(float), mix_color));

    GLuint transform_buffer;
    OGL_CALL(glCreateBuffers(1, &transform_buffer));
    OGL_CALL(glNamedBufferData(transform_buffer, 12 * sizeof(float), nullptr, GL_STATIC_DRAW));

    OGL_CALL(glNamedBufferSubData(transform_buffer, 0, 2 * sizeof(float), &scale));
    OGL_CALL(glNamedBufferSubData(transform_buffer, 2 * sizeof(float), 2 * sizeof(float), &trans));
    OGL_CALL(glNamedBufferSubData(transform_buffer, 4 * sizeof(float), 2 * sizeof(float), &rot[0]));
    OGL_CALL(glNamedBufferSubData(transform_buffer, 8 * sizeof(float), 2 * sizeof(float), &rot[1]));


    // This sets up a Vertex Array Object (VAO) that encapsulates
    // the state of all vertex buffers needed for rendering.
    // The vao_ variable is a member of the SimpleShapeApplication class and is defined in src/Application/app.h.
    OGL_CALL(glGenVertexArrays(1, &vao_));
    OGL_CALL(glBindVertexArray(vao_));
    OGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle));
    OGL_CALL(glBindBufferBase(GL_UNIFORM_BUFFER, 0, mixer_buffer));
    OGL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer));
    OGL_CALL(glBindBufferBase(GL_UNIFORM_BUFFER, 1,transform_buffer));



    /*
     * The following lines bound the vertex attribute 0 to the currently bound vertex buffer (the one we just created).
     * Attribute 0 is specified in the vertex shader with the
     * layout (location = 0) in vec4 a_vertex_position;
     * directive.
     */
     // This specifies that the data for attribute 0 should be read from a vertex buffer
    OGL_CALL(glEnableVertexAttribArray(0));
    // and this specifies the data layout in the buffer.
    OGL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
        reinterpret_cast<GLvoid*>(0)));

    OGL_CALL(glEnableVertexAttribArray(1));
    OGL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
        reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat))));

    OGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    OGL_CALL(glBindVertexArray(0));
    //end of vao "recording"

    // Setting the background color of the rendering window,
    // I suggest not using white or black for better debugging.
    OGL_CALL(glClearColor(0.81f, 0.81f, 0.8f, 1.0f));

    // This set up an OpenGL viewport of the size of the whole rendering window.
    auto [w, h] = frame_buffer_size();
    OGL_CALL(glViewport(0, 0, w, h));

    OGL_CALL(glUseProgram(program));
}

//This functions is called every frame and does the actual rendering.
void SimpleShapeApplication::frame() {
    // Binding the VAO will set up all the required vertex attribute arrays.
    OGL_CALL(glBindVertexArray(vao_));
    OGL_CALL(glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_BYTE, nullptr));
    OGL_CALL(glBindVertexArray(0));
}

