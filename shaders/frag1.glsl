#version 330 core
in vec3 frag_pos;
in vec2 TextCoord;
in vec3 normal;

out vec4 FragColor;

uniform vec3 viewPos;

uniform vec3 light_pos;
uniform vec3 light_color;
uniform float ambiant;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	vec3 lightDir = normalize(light_pos - frag_pos);
	float diff = max(dot(normal, lightDir), 0.0);

	float specularStrength = 1;
	vec3 viewDir = normalize(viewPos - frag_pos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	float specular = specularStrength * spec;

	vec4 text_col = texture(texture1, TextCoord)/* + texture(texture2, TextCoord)*/;
	//vec3 obj_col = vec3(1.0, 0.0, 0.0);

	FragColor = vec4(text_col.xyz * light_color * (diff + ambiant + specular), text_col.w)/* + texture(texture2, TextCoord)*/;
	//FragColor = vec4(obj_col * light_color * (diff + ambiant), 1);
}