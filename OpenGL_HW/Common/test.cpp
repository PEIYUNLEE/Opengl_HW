#include "./Header/Angel.h"

const int NumPoints = 6;

void init(void)
{
	vec3 points[NumPoints] = {
		vec3(-0.1f, -0.1f, 0.0),
		vec3(0.1f, -0.1f, 0.0),
		vec3(0.1f,  0.1f, 0.0),
		vec3(-0.1f, -0.1f, 0.0),
		vec3(0.1f,  0.1f, 0.0),
		vec3(-0.1f,  0.1f, 0.0)
	};

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	// Load shaders and use the resulting shader program
	GLuint program = InitShader("vsVtxColor.glsl", "fsVtxColor.glsl");
	glUseProgram(program);

	GLuint loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glClearColor(0.0, 0.0, 0.0, 1.0); // black background
}

//----------------------------------------------------------------------------

void GL_Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);		
	glDrawArrays(GL_TRIANGLES, 0, 6); 
	glFlush();
}

//----------------------------------------------------------------------------

void Win_Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 033:
		exit(EXIT_SUCCESS);
		break;
	}
}

//----------------------------------------------------------------------------
void GL_Reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
}

//----------------------------------------------------------------------------

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);

	glutInitContextVersion(3, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("Draw two triangles");

	glewExperimental = GL_TRUE;
	glewInit();

	init();

	glutDisplayFunc(GL_Display);
	glutKeyboardFunc(Win_Keyboard);
	glutReshapeFunc(GL_Reshape);
	glutMainLoop();
	return 0;
}
