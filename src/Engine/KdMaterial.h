#pragma once

#include "AbstractMaterial.h"



namespace xe {
    class KdMaterial : public AbstractMaterial<KdMaterial> {

    public:
        int use_vertex_colors_;

        const glm::vec4 Kd_;

        KdMaterial(const glm::vec4& Kd) : Kd_(Kd) {}

        void bind() const override;
          
        static void init();
    };
};