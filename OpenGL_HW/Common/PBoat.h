#include "../Header/Angel.h"

#define BBPOINT_NUM 12
#define BCPOINT_NUM 20
#define BTPOINT_NUM 10
#define BTOTPOINT_NUM BBPOINT_NUM+BCPOINT_NUM+BTPOINT_NUM

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

class PBoat
{
private:
	vec4 _points[BTOTPOINT_NUM];
	vec4 _colors[BTOTPOINT_NUM];
	GLuint _uiVao;
	GLuint _uiBuffer;
	GLuint _uiProgram;
	GLuint _uiModelView, _uiProjection;

	mat4 _mxView, _mxProjection;
	mat4 _mxMVFinal, _mxTRS;

	void CreateBufferObject();
public:
	PBoat();

	void SetShader(mat4 &mxView, mat4 &mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	GLuint GetShaderHandle() { return _uiProgram; }
	void SetViewMatrix(mat4 &mat);
	void SetProjectionMatrix(mat4 &mat);

	void Draw();
};