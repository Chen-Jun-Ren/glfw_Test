#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform float mixValue;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec4 color;

void main()
{
	//FragColor = texture(texture1, TexCoord) * vec4(ourColor,1.0);
	FragColor = mix(texture(texture1, TexCoord),texture(texture2,TexCoord),mixValue);
}

//* vec4(color, 1.0)