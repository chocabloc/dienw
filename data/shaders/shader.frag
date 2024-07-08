#version 330 core
out vec4 FragColor;

void main() {
    float normx = gl_FragCoord.x/10.0,
          normy = gl_FragCoord.y/10.0;
    FragColor = vec4(sin(normx), cos(normy), sin(sqrt(normx*normy)), 1.0);
}