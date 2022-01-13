#version 400
in vec3 pos;
out vec4 frag_colour;

void main() {
    frag_colour = vec4(pos.x, pos.y, pos.z, 1.0);
}
