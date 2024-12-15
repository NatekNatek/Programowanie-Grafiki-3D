#version 450

in vec3 vertex_color;
layout(location=0) out vec4 vFragColor;

layout(std140, binding=0) uniform KdMaterial {
    vec4 Kd;
    bool use_vertex_color; 
};

void main() {
    vFragColor = vertex_color*Kd;
}