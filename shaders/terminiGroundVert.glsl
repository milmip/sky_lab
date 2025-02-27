#version 330 core
layout (location = 0) in vec2 aPos;

uniform mat3 upInTheCorner;

void main()
{
	vec3 scaledPos = upInTheCorner * vec3(aPos.x, aPos.y, 1.0);
	gl_Position = vec4(scaledPos.x, scaledPos.y, -0.01, 1.0);
}