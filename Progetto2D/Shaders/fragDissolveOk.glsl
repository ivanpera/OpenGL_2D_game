#version 400 core
in vec4 ourColor;
out vec4 FragColor;  
uniform int t;
uniform float dt;
  
void main()
{
    FragColor = vec4(0.224,0.639,0.223,.7);
}