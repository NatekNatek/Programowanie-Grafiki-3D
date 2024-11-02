//
// Created by pbialas on 05.08.2020.
//

#pragma once

#include <vector>

#include "glad/gl.h"

#include "Application/application.h"

#include "glm/glm.hpp"

#include "camera.h"


class SimpleShapeApplication : public xe::Application {
public:
    SimpleShapeApplication(int width, int height, std::string title, bool debug, int swap_interval = 1) : Application(
            width, height, title,
            debug, swap_interval), camera_(nullptr) {}

    Camera* camera_;

    glm::mat4 M_;

    GLuint u_trans_buffer_handle_;

    void init() override;

    void frame() override;

    void framebuffer_resize_callback(int w, int h) override;

    void SimpleShapeApplication::scroll_callback(double xoffset, double yoffset) override;

    void set_camera(Camera* camera) { camera_ = camera; }

    Camera* camera() const {
        assert(camera_);
        return camera_;
    }

private:
    GLuint vao_;
};