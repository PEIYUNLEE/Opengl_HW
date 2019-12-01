#version 130
in  vec4 vPosition;
in  vec4 vColor;
out vec4 color;

uniform mat4 ModelView;
uniform mat4 Projection;
uniform mat4 mxOri;
uniform mat4 mxTRS;
uniform float tx;
uniform float ty;

void main()
{
	//¦ì²¾¯x°}
	mat4 mxTra = mat4( 
	1, 0, 0 ,0,
	0, 1, 0 ,0,
	0, 0, 1 ,0,
	0, 0, 0 ,1);

	mxTra[3][0]=ty;
	mxTra[3][1]=tx;

    gl_Position = Projection * ModelView * mxTra * mxOri * vPosition;
	color = vColor;
}