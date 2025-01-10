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

#include "../../Engine/KdMaterial.h"

#include "stb/stb_image.h"

#include "../../Engine/texture.h"

#include "../../Engine/texture.cpp"

#include "stb/stb_image.h"

#include "../../Engine/texture.h"

#include "../../Engine/texture.cpp"

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
                {GL_VERTEX_SHADER,   std::string(PROJECT_DIR) + "/../../Engine/shaders/Kd_vs.glsl"},
                {GL_FRAGMENT_SHADER, std::string(PROJECT_DIR) + "/../../Engine/shaders/Kd_fs.glsl"}
        });


    if (!program) {
        SPDLOG_CRITICAL("Invalid program");
        exit(-1);
    }

     
    std::vector<GLfloat> vertices = {

             -0.5f,  0.5f,  0.0f,  0.1910f, 0.5000f, // 0
             -0.5f, -0.5f,  0.0f,  0.5000f, 0.1910f, // 1
             0.5f, -0.5f,  0.0f,  0.8090f, 0.5000f, // 2
             0.5f,  0.5f,  0.0f,  0.5000f, 0.8090f, // 3
             0.0f,  0.0f,  1.0f,  0.0000f, 1.0000f, // 4 (Red wall tip)
             0.0f,  0.0f,  1.0f,  0.0000f, 0.0000f, // 5 (Green wall tip)
             0.0f,  0.0f,  1.0f,  1.0000f, 1.0000f, // 6 (Blue wall tip)
             0.0f,  0.0f,  1.0f,  1.0000f, 0.0000f, // 7 (Yellow wall tip)
    };


    std::vector<GLubyte> indices = {
        0, 2, 1, // Base
        3, 2, 0, // Base
        0, 4, 3, // Red wall
        1, 5, 0, // Green wall
        3, 6, 2, // Blue wall
        2, 7, 1  // Yellow wall
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
    GLuint textureID;
    camera() -> xe::Camera::look_at(glm::vec3 (0,0,2), glm::vec3 (0,0,0), glm::vec3 (0,1,0));
    camera() -> xe::Camera::perspective(fov_, aspect_, near_, far_);
    glm::vec3 translation{ 0, 0, 0 };
    M_ = glm::translate(M_, translation);

    auto pyramid = new xe::Mesh(5 * sizeof(float), vertices.size() * sizeof(float), GL_STATIC_DRAW,
        indices.size() * sizeof(GLubyte), GL_UNSIGNED_BYTE, GL_STATIC_DRAW);

    add_mesh(pyramid);

    pyramid -> load_vertices(0, vertices.size() * sizeof(float), vertices.data());

    pyramid-> add_attribute(xe::POSITION, 3, GL_FLOAT, 0);

    pyramid -> load_indices(0, indices.size() * sizeof(GLubyte), indices.data());

    pyramid->add_attribute(xe::TEXCOORD_0, 2, GL_FLOAT, 3 * sizeof(GL_FLOAT));

     
    xe::KdMaterial::init();


   
    auto kd_gray_material = new xe::KdMaterial(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
    auto kd_red_material = new xe::KdMaterial(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    auto kd_green_material = new xe::KdMaterial(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    auto kd_blue_material = new xe::KdMaterial(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
    auto kd_yellow_material = new xe::KdMaterial(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));

 

 

    xe::create_texture(std::string(ROOT_DIR) + "/Models/multicolor.png");
 

    pyramid->add_primitive(0, 18, new xe::KdMaterial({ 1.f, 1.f, 1.0f, 1.0f }, false, textureID));

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




    OGL_CALL(glClearColor(0.81f, 0.81f, 0.8f, 1.0f));

    OGL_CALL(glViewport(0, 0, w, h));

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

