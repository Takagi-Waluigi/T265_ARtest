#version 410

uniform mat4 modelViewProjectionMatrix;
uniform float _Time;
uniform int _ObjectNum;

layout(location = 0) in vec3 particle_vert;
layout(location = 1) in vec4 color;
layout(location = 2) in vec3 normal;
layout(location = 4) in vec3 pos;

out vec4 v_color;
out vec3 v_normal;

void main()
{
    
     v_color = color;
     v_normal = normal;

    mat4 matrix = mat4(0.20, 0.0, 0.0, 0.0,
                       0.0, 0.20, 0.0, 0.0,
                       0.0, 0.0, 0.20, 0.0,
                       pos.x + (1000.0 * sin(_Time * 0.005)  + 5000.0 ) * cos(float(gl_InstanceID) * 0.01 - _Time * 0.0075),
                       pos.y + (800.0 * cos(_Time * 0.01)  + 5000.0 ) * sin(float(gl_InstanceID) * 0.005 - _Time * 0.0075), 
                       pos.z + (1500.0 * sin(_Time * 0.005)  + 7500.0 ) * sin(float(gl_InstanceID) * 0.01 - _Time * 0.0075), 1.0);

    float Theta = _Time * 0.05;

    vec3 s = vec3(10.0, 10.0, 6.0);

    mat4 scale = mat4(s.x, 0.0, 0.0, 0.0,
                      0.0, s.y, 0.0, 0.0,
                      0.0, 0.0, s.z, 0.0,
                      0.0, 0.0, 0.0, 1.0);    

    float xTheta = gl_InstanceID * 0.02 - _Time * 0.05;
    float yTheta = gl_InstanceID * 0.02  - _Time * 0.05;

    mat4 rotX =    mat4(1.0, 0.0, 0.0, 0.0,
                        0.0, cos(xTheta), -sin(xTheta), 0.0,
                        0.0, sin(xTheta), cos(xTheta), 0.0,
                        0.0, 0.0, 0.0, 1.0);

    mat4 rotY =    mat4(cos(yTheta), 0.0, -sin(yTheta), 0.0,
                               0.0, 1.0,         0.0, 0.0,
                        sin(yTheta), 0.0,  cos(yTheta), 0.0,
                        0.0, 0.0, 0.0, 1.0);


    v_normal = normalize(((rotX * rotY) * vec4(v_normal, 1.0)).xyz);

    gl_Position = modelViewProjectionMatrix * matrix * scale * rotX * rotY * vec4(particle_vert, 1.0);
}