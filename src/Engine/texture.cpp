#include "texture.h"
#include <stdexcept>
#include <iostream>
#include "stb/stb_image.h"
#include <glad/gl.h>
#include <glm/glm.hpp>
#include "spdlog/spdlog.h"
#include "stb/stb_image.h"

namespace xe {

    GLuint create_texture(const std::string& name, bool is_sRGB) {

        GLuint textureID;   
        stbi_set_flip_vertically_on_load(true);
        GLint width, height, channels;
        auto texture_file = std::string(ROOT_DIR) + name;
        auto img = stbi_load(texture_file.c_str(), &width, &height, &channels, 0);
        if (!img) {
            std::cerr << "Could not read image from file `" << texture_file << "'\n";
        }
        else {
            std::cout << "Loaded a " << width << "x" << height << " texture with " << channels << " channels\n";
        }

        glGenTextures(1, &textureID);

        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


        GLenum internalFormat = is_sRGB ? GL_SRGB : GL_RGB;
        GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, img);

        stbi_image_free(img);



        glBindTexture(GL_TEXTURE_2D, 0);

        return textureID;
    }

}