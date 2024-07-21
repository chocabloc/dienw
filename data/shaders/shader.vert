#version 330 core
layout (location = 0) in vec3 aPos;

//uniform vec3 obj_pos;
//uniform mat3 obj_trans;

uniform mat4 mat_vm;
uniform mat4 mat_p;

out vec4 world_pos;

void main() {
	world_pos = mat_vm*vec4(aPos, 1.0);
	gl_Position = mat_p*world_pos;
}
