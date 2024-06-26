
--VERT--

#version 330 core

layout(location = 0) in vec3 position;
layout (location = 1) in vec2 scale_v;
layout (location = 2) in float rotation_v;
uniform float cx;
uniform float cz;

out vec2 scale;
out float rotation;
void main()
{
    vec3 transform =  vec3(position.x, position.y, position.z)+vec3(-cx,0,-cz);
    gl_Position = vec4(transform.xy,transform.z/1000, transform.z);
    scale = scale_v;
    rotation = rotation_v;
    
}

--GMTR--

#version 330 core 

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;
in vec2 scale[];
in float rotation[];

uniform float cd;

out vec2 texture_position;
void main(){

    mat3 rot = mat3(
    cos(rotation[0]), sin(rotation[0]), 0,
    -sin(rotation[0]), cos(rotation[0]),     0,
    0, 0, 1
    );
    mat3 rot2 = mat3(
    cos(cd), 0, sin(cd),
    0,       1,     0,
    -sin(cd), 0, cos(cd)
    );

    vec3 position;
    texture_position = vec2(0, 1);
    position = vec3(rot2*(gl_in[0].gl_Position.xyw + rot*vec3(-scale[0].x, -scale[0].y, 0)));
    gl_Position = vec4(position.xy, 0, position.z);
    EmitVertex();
    texture_position = vec2(1, 1);
    position = vec3(rot2*(gl_in[0].gl_Position.xyw + rot*vec3(scale[0].x, -scale[0].y,0)));
    gl_Position = vec4(position.xy, 0, position.z);
    EmitVertex();
    texture_position = vec2(0, 0);
    position = vec3(rot2*(gl_in[0].gl_Position.xyw + rot*vec3(-scale[0].x, scale[0].y,0)));
    gl_Position = vec4(position.xy, 0, position.z);
    EmitVertex();
    texture_position = vec2(1, 0);
    position = vec3(rot2*(gl_in[0].gl_Position.xyw + rot*vec3(scale[0].x, scale[0].y,0)));
    gl_Position = vec4(position.xy, 0, position.z);
    EmitVertex();
    EndPrimitive();
 
}


--FRAG--

#version 330 core

layout(location = 0) out vec4 color;
uniform sampler2D tex; 
in vec2 texture_position;

void main()
{
    color = texture(tex, texture_position);

}

