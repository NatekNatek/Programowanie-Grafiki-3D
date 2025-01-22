#include "KdMaterial.h"
#include "ObjectReader/sMesh.h"
#include "texture.h"
#include "utils.h"


namespace xe {

	GLint KdMaterial::map_Kd_location_ = -1;

	void KdMaterial::init() {
	
		create_material_uniform_buffer(2 * sizeof(glm::vec4));
		create_program_in_engine({ {GL_VERTEX_SHADER, "Kd_vs.glsl"},
					   {GL_FRAGMENT_SHADER, "Kd_fs.glsl"} });

		map_Kd_location_ = glGetUniformLocation(program(), "map_Kd");
		if (map_Kd_location_ == -1) {
			SPDLOG_WARN("Cannot find map_Kd uniform");
		}

		xe::add_mat_function("KdMaterial", KdMaterial::create_from_mtl);
	};

	void KdMaterial::bind() const{  
		glUseProgram(program());

		OGL_CALL(glBindBufferBase(GL_UNIFORM_BUFFER, 0, material_uniform_buffer_));
		OGL_CALL(glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec4), &Kd_));
		OGL_CALL(glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), sizeof(int), &use_vertex_colors_));

		if (texture_ > 0) {

			bool use_map_Kd;
			OGL_CALL(glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) + sizeof(int), sizeof(bool), &use_map_Kd));

			glActiveTexture(GL_TEXTURE0);

			glBindTexture(GL_TEXTURE_2D, texture_);
		}
		else {
			
			bool use_map_Kd = false;
			OGL_CALL(glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) + sizeof(int), sizeof(bool), &use_map_Kd));
		}
	}

	void KdMaterial::set_texture(GLint texture) {
		texture_ = texture;
	}

	Material* KdMaterial::create_from_mtl(const mtl_material_t& mat, std::string mtl_dir) {
		glm::vec4 color = get_color(mat.diffuse);
		SPDLOG_DEBUG("Adding ColorMaterial {}", glm::to_string(color));
		auto material = new xe::KdMaterial(color);
		if (!mat.diffuse_texname.empty()) {
			auto texture = xe::create_texture(mtl_dir + "/" + mat.diffuse_texname, true);
			SPDLOG_DEBUG("Adding Texture {} {:1d}", mat.diffuse_texname, texture);
			if (texture > 0) {
				material->set_texture(texture);
			}
		}

		return material;
	}
}