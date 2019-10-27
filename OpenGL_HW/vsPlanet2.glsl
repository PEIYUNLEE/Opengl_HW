#version 130
in  vec4 vPosition;
in  vec4 vColor;
out vec4 color;

uniform mat4 ModelView;
uniform mat4 Projection;

void main()
{
	float tx=0.0f;
	float ty=0.0f;

	mat4 tm = mat4(   1.0, 0.0, 0.0, 0.0,
					  0.0, 1.0, 0.0, 0.0,
		              0.0, 0.0, 1.0, 0.0,
		               tx,  ty, 0.0, 1.0 );
    gl_Position = Projection * ModelView * vPosition;
	color = vColor;
}