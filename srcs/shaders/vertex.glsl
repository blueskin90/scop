#version 400
in vec3 vp;
uniform mat4 worldToCam;
uniform mat4 objToWorld;
uniform mat4 persp;

out vec3 pos;

void main() {
    pos = vp;
    gl_Position = persp * worldToCam * objToWorld * vec4(vp.x, vp.y, vp.z, 1.0);
}
