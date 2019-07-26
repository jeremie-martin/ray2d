R""(
#version 430 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float brightness;
uniform float contrast;
uniform float gamma;

void main()
{
    vec3 diffuseColor = texture(screenTexture, TexCoords).rgb;
    vec3 avgColor = textureLod(screenTexture, TexCoords, 1000.0).rgb;

    float avgL = 0.2126 * avgColor.r + 0.7152 * avgColor.g + 0.0722 * avgColor.b;
    float L = 0.2126 * diffuseColor.r + 0.7152 * diffuseColor.g + 0.0722 * diffuseColor.b;
    float exposure =  L / avgL;

    diffuseColor = diffuseColor / avgL;
    avgColor = avgColor / avgL;

    //diffuseColor = diffuseColor*exposure;

    diffuseColor = diffuseColor * vec3(contrast);
	diffuseColor = diffuseColor + vec3(brightness);
    diffuseColor = pow(diffuseColor, 1/vec3(gamma));

    FragColor = vec4(diffuseColor, 1.0);


}
)""