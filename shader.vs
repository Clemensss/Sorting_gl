#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec4 ourColor;

uniform mat4 trans_t;
uniform float y_var;

void main()
{
    float pos_y;

    if(aPos.z > 2.0)
    {
	pos_y = y_var;
    }
    else
    {
	pos_y = aPos.y;
    }

    vec4 new_pos = vec4(aPos.x, pos_y, 0.0, 1.0);

    gl_Position = trans_t*new_pos;
    ourColor = trans_t*vec4(aColor, 1.0);
}
