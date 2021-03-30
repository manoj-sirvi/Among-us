#version 330 core

// Interpolated values from the vertex shaders
// in vec3 fragColor;

// // output data
// out vec3 color;

// void main()
// {
//     // Output color = color specified in the vertex shader,
//     // interpolated between all 3 surrounding vertices of the triangle
//     color = fragColor;
// }

// #version 120
varying vec2 texcoord;
uniform sampler2D tex;
uniform vec4 color;

void main(void) {
  gl_FragColor = vec4(1, 1, 1, texture2D(tex, texcoord).r) * color;
}