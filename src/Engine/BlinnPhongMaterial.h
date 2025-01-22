#pragma once

#include "AbstractMaterial.h"

#include "mesh_loader.h"


namespace xe {
    class BlinnPhongMaterial : public AbstractMaterial<BlinnPhongMaterial> {

    public:

        GLint texture_;

        int use_vertex_colors_ = 0;

        const glm::vec4 Kd_;

        glm::vec4 Ka_;

        static GLint map_Kd_location_;

        BlinnPhongMaterial(const glm::vec4& Kd) : Kd_(Kd), texture_(0), Ka_(Kd) {}

        BlinnPhongMaterial(const glm::vec4& Kd, bool use_vertex_colors, GLuint texture)
            : Kd_(Kd), use_vertex_colors_(use_vertex_colors), texture_(texture), Ka_(Kd) {}

        void bind() const override;

        static void init();

        void set_texture(GLint texture);

        static Material* create_from_mtl(const mtl_material_t& mat, std::string mtl_dir);
    };
};