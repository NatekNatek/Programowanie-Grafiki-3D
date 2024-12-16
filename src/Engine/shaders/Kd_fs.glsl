#version 450

in vec3 vertex_color;
layout(location=0) out vec4 vFragColor;

layout(std140, binding=0) uniform KdMaterial {
    vec4 Kd;
    bool use_vertex_color; 
};

void main() {
    if (use_vertex_color) {
        vFragColor = vec4(vertex_color, 0.0)*Kd;
    } else {
        vFragColor = Kd;
    }
}