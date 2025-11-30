#version 330 core

out vec4 FragColor;
out vec2 TexCoord2;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixRatio;

void main()
{
    FragColor = mix( texture( texture1, TexCoord ), texture( texture2, TexCoord ), mixRatio );
}