#version 420

layout(location=0) in  vec4 a_vertex_position;
layout(location=5) in  vec3 a_vertex_color;
layout(location=3) in  vec2 a_texture_coordinates;
layout(location=1) in  vec3 a_vertex_normal;

layout(std140, binding=1) uniform Transformations {
    mat4 PVM;
    mat4 VM;
    mat3 VM_Normal; 
};

out vec3 vertex_color;
out vec2 texture_coordinates;
out vec3 vertex_normal_vs;
out vec3 vertex_position_vs;

void main() {  
    gl_Position =  PVM * a_vertex_position;
    vertex_color = a_vertex_color;  
    texture_coordinates = a_texture_coordinates;
    vertex_position_vs = (ModelView * a_vertex_position).xyz;
    vec4 a_vertex_position_vs = VM * a_vertex_position;
    vertex_position_vs = a_vertex_position_vs.xyz/a_vertex_position_vs.w;
    vertex_normal_vs = normalize(VM_normal * a_vertex_normal);
}
