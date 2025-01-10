
#include <glad/gl.h>
#include <glm/glm.hpp>
#include "spdlog/spdlog.h"


namespace xe {
	GLuint create_texture(const std::string &name, bool is_sRGB = true);
}