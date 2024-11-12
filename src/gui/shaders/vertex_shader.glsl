#ifdef GL_ES
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp_matrix;
attribute vec3 vertex_pos;
uniform vec4 color;
varying vec4 frag_color;
varying float distance;

void main() {
    gl_Position = mvp_matrix * vec4(vertex_pos, 1.0);
    frag_color = color;
    distance = length(vertex_pos);
}