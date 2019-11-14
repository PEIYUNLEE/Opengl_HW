#pragma once
#include "../Header/Angel.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

class Planet
{
private:
	int _pointsNum;
	vec4 *_points;
	vec4 *_colors;
	GLuint _uiVao;
	GLuint _uiBuffer;
	GLuint _uiProgram;
	GLuint _uiModelView, _uiProjection;

	char *_vsh;

	mat4 _mxView, _mxProjection;
	mat4 _mxMVFinal, _mxTRS;

	bool  _bUpdateMV;
	bool  _bUpdateProj;

	float _fduration;
	float _fspeed;
	float _ftottime;

	void CreateBufferObject();
public:
	Planet(float radius = 0.8f, int colorType = 1,float fspeed=-0.5f,float fduration=10.0f, int pointsNum = 500);
	~Planet();

	void SetShader(mat4 &mxView, mat4 &mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	GLuint GetShaderHandle() { return _uiProgram; }
	void SetViewMatrix(mat4 &mat);
	void SetProjectionMatrix(mat4 &mat);
	void SetTRSMatrix(mat4 &mat);
	void AutoTranslate(float dt);
	vec4 SetColor(int colorType);
	void SetVShaderName(char* vsh);

	void Draw();
};