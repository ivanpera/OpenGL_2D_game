#version 400 core
in vec4 ourColor;
out vec4 FragColor;  
uniform int t;
uniform float dt;
  
void main()
{
    FragColor = vec4(.8,.2,0,1);
}