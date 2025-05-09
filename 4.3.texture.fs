#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform bool flipTexture;

void main()
{
	// linearly interpolate between both textures (62% texture1, 38% texture2)
	if(flipTexture)
	{
		FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.38);
	}else
	{
		FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.38);
	}
}