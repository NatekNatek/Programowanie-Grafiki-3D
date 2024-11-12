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

#include "glm/gtc/matrix_transform.hpp"

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

            //base
            -0.5f, 0.5f, 0.0f, 0.5, 0.5, 0.5, //0
            -0.5f, -0.5f, 0.0f, 0.5, 0.5, 0.5, //1
            0.5f, -0.5f, 0.0f, 0.5, 0.5, 0.5, //2
            0.5f, 0.5f, 0.0f, 0.5, 0.5, 0.5, //3
            //red wall
            0.5f, -0.5f, 0.0f, 1, 0, 0, //4
            0.0f, 0.0f, 1.0f, 1, 0, 0, //5
            0.5f, 0.5f, 0.0f, 1, 0, 0, //6
            // green wall
            -0.5f, -0.5f, 0.0f, 0, 1, 0, //7
            0.0f, 0.0f, 1.0f, 0, 1, 0, //8
            -0.5f, 0.5f, 0.0f, 0, 1, 0, //9
            //blue wall
            0.5f, 0.5f, 0.0f, 0, 0, 1, //10
            0.0f, 0.0f, 1.0f, 0, 0, 1, //11
            -0.5f, 0.5f, 0.0f, 0, 0, 1, //12
            //yellow wall
            0.5f, -0.5f, 0.0f, 1, 1, 0, //13
            0.0f, 0.0f, 1.0f, 1, 1, 0, //14
            -0.5f, -0.5f, 0.0f, 1, 1, 0, //15

            };

    std::vector<GLubyte> indices = {
        0, 2, 1,
        0, 3, 2,
        4, 6, 5,
        7, 8, 9,
        10, 12, 11,
        13, 14, 15
    }; 


    set_camera(new xe::Camera);
    set_controler(new xe::CameraController(camera()));
    auto [w, h] = frame_buffer_size();
    float fov_ = glm::radians(45.0f);
    float aspect_ = float(w) / float(h);
    float near_ = 0.1;
    float far_ = 20.0;
    glm::mat4 PVM(1.0f);
    M_ = (1.0);
    camera() -> xe::Camera::look_at(glm::vec3 (0,0,2), glm::vec3 (0,0,0), glm::vec3 (0,1,0));
    camera() -> xe::Camera::perspective(fov_, aspect_, near_, far_);
    glm::vec3 translation{ 0, 0, 0 };
    M_ = glm::translate(M_, translation);

    auto pyramid = new xe::Mesh(6 * sizeof(float), vertices.size() * sizeof(float), GL_STATIC_DRAW,
        indices.size() * sizeof(GLubyte), GL_UNSIGNED_BYTE, GL_STATIC_DRAW);

    pyramid -> load_vertices(0, vertices.size() * sizeof(float), vertices.data());

    pyramid-> add_attribute(xe::POSITION, 3, GL_FLOAT, 6 * sizeof(GLfloat));

    pyramid -> load_indices(0, indices.size() * sizeof(GLubyte), indices.data());

    pyramid-> add_attribute(xe::COLOR_0, 3, GL_FLOAT, 6 * sizeof(GLfloat));


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

    OGL_CALL(glCreateBuffers(1, &u_trans_buffer_handle_));
    OGL_CALL(glNamedBufferData(u_trans_buffer_handle_, 16 * sizeof(float), nullptr, GL_STATIC_DRAW));





    // This sets up a Vertex Array Object (VAO) that encapsulates
    // the state of all vertex buffers needed for rendering.
    // The vao_ variable is a member of the SimpleShapeApplication class and is defined in src/Application/app.h.
    /*OGL_CALL(glGenVertexArrays(1, &vao_));
    OGL_CALL(glBindVertexArray(vao_));
    OGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle));
    OGL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer));*/ //(GL_UNIFORM_BUFFER didn't work for me)
    



    /*
     * The following lines bound the vertex attribute 0 to the currently bound vertex buffer (the one we just created).
     * Attribute 0 is specified in the vertex shader with the
     * layout (location = 0) in vec4 a_vertex_position;
     * directive.
     */
     // This specifies that the data for attribute 0 should be read from a vertex buffer
    //OGL_CALL(glEnableVertexAttribArray(0));
    // and this specifies the data layout in the buffer.
    //OGL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
    //    reinterpret_cast<GLvoid*>(0)));

    //OGL_CALL(glEnableVertexAttribArray(5));
    //OGL_CALL(glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
    //    reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat))));

    //OGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    //OGL_CALL(glBindVertexArray(0));
    //end of vao "recording"

    // Setting the background color of the rendering window,
    // I suggest not using white or black for better debugging.
    OGL_CALL(glClearColor(0.81f, 0.81f, 0.8f, 1.0f));

    OGL_CALL(glViewport(0, 0, w, h));

    OGL_CALL(glUseProgram(program));

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

//This functions is called every frame and does the actual rendering.
void SimpleShapeApplication::frame() {

    glm::mat4 P_ = camera() -> xe::Camera::projection();
    glm::mat4 V_ = camera() -> xe::Camera::view();
    glm::mat4 PVM = P_ * V_ * M_;
    OGL_CALL(glNamedBufferSubData(u_trans_buffer_handle_, 0, 16 * sizeof(float), &PVM[0]));

    OGL_CALL(glBindBufferBase(GL_UNIFORM_BUFFER, 1, u_trans_buffer_handle_));

    for (auto m : meshes_)
        m->draw();
}

void SimpleShapeApplication::framebuffer_resize_callback(int w, int h) {
    Application::framebuffer_resize_callback(w, h);
    OGL_CALL(glViewport(0, 0, w, h));
    float new_aspect = float(w) / float(h);
    camera() -> Camera::set_aspect(new_aspect);
}

void SimpleShapeApplication::scroll_callback(double xoffset, double yoffset) {
    Application::scroll_callback(xoffset, yoffset);
    camera()->zoom(yoffset / 20.0f);
}

void SimpleShapeApplication::mouse_button_callback(int button, int action, int mods) {
    Application::mouse_button_callback(button, action, mods);

    if (controller_) {
        double x, y;
        glfwGetCursorPos(window_, &x, &y);

        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
            controller_->LMB_pressed(x, y);

        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
            controller_->LMB_released(x, y);
    }
}

void SimpleShapeApplication::cursor_position_callback(double x, double y) {
    Application::cursor_position_callback(x, y);
    if (controller_) {
        controller_->mouse_moved(x, y);
    }
}

