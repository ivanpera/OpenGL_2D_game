#version 400 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec4 aColor; // the color variable has attribute position 1

out vec4 ourColor; // output a color to the fragment shader
uniform mat4 Projection;  //vARIABILE DI TIPO uniform, rimane la stessa per ogni vertice della primitiva e viene passata dall'esterno
uniform mat4 Model;
uniform int t;
uniform float dt;

mat4 rotateZ(float _angle){
    return mat4(cos(_angle),-sin(_angle), 0, 0,
                sin(_angle), cos(_angle), 0, 0,
                          0,           0, 1, 0,
                          0,           0, 0, 1);
}

mat4 identity() {
    return mat4(1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1);
}

mat4 translateBy(vec3 point) {
    return mat4(1, 0, 0, point.x,
                0, 1, 0, point.y,
                0, 0, 1, point.z,
                0, 0, 0,       1);
}

void main()
{
    float T = (t * 1.0) / 1000;
    gl_Position = Projection*Model*vec4(aPos.x, aPos.y, aPos.z, 1.0);
    ourColor = aColor;
} 