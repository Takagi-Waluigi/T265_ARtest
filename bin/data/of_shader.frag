#version 410

uniform vec3 _Ambient;
uniform vec3 _LightColor0;
uniform vec3 _SpecularColor0;
uniform vec3 _CameraPosition;
uniform float _Shiness;
uniform vec3 _LightPos;


in vec4 v_color;
in vec3 v_normal;

out vec4 fragColor;

void main() {
   // fragColor = vec4(v_color.rgb * 1.3, 0.75);
   vec3 normal = normalize(v_normal);
    vec3 light = normalize(_LightPos);

    float diffuse = clamp(1.0, 0.0, dot(normal, light));

    fragColor = vec4(diffuse * v_color.xyz, 1.0);

    fragColor.xyz += v_color.xyz * _Ambient *_LightColor0;
}