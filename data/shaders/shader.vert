#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec3 obj_pos;
uniform mat3 obj_trans;

void main() {
	gl_Position = vec4(obj_trans*aPos + obj_pos, 1.0);
}
