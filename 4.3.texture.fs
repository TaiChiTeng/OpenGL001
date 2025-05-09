#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
	// linearly interpolate between both textures (62% texture1, 38% texture2)
	// FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.38);
	// 厉害，这样就可以实现左右镜像了
    FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.38);
}