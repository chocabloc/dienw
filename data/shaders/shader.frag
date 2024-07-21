#version 330 core
in vec4 world_pos;

out vec4 FragColor;

void main() {
	FragColor = vec4(1.0, 0.2, 0.2, 1.0)/(world_pos.z*world_pos.z);
}
