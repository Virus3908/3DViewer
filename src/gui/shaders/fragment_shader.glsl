#ifdef GL_ES
precision mediump float;
#endif

varying vec4 frag_color;
uniform bool isDashed;
uniform bool isLine;
varying float distance;

void main() {
    if (isDashed && isLine) {
        float dashSize = 0.02;
        float gapSize = 0.008;
        float cycleSize = dashSize + gapSize;
        float currentPos = mod(distance, cycleSize);

        if (currentPos < dashSize) {
            gl_FragColor = frag_color;
        } else {
            discard;
        }
    } else {
        gl_FragColor = frag_color;
    }
}