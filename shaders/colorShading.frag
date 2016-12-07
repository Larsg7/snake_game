#version 130

in vec4 fragmentColor;

out vec4 color;

uniform float time;

void main ()
{
	color = fragmentColor;
	color.x = (1 + sin( time )) / 2;
}
