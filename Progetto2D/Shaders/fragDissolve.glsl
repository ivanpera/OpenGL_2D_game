#version 400 core
in vec4 ourColor;
out vec4 FragColor;  
uniform int t;
uniform float dt;
  
void main()
{
    FragColor = ourColor - vec4(0,0,0,.3);
}