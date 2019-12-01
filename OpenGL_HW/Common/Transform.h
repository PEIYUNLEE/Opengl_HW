#pragma once
#include "../Header/Angel.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

class Transform {
private:
	//data
	int _pointNum;
	vec4 *_points, *_colors;
	GLuint _uiVao;
	GLuint _uiBuffer;
	GLuint _uiProgram;
	GLuint _uiModelView, _uiProjection;

	mat4 _mxView, _mxProjection;

	bool  _bUpdateMV;
	bool  _bUpdateProj;

	void CreateBufferObject();

	void SetShader(mat4 &mxView, mat4 &mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	GLuint GetShaderHandle() { return _uiProgram; }

public:
	mat4 _mxOri;
	mat4  _mxTRS;
	mat4 _mxMVFinal;

	Transform(mat4 &mxView, mat4 &mxProjection, int pointNum,vec4 *points,vec4 *colors);
	//~Transform();

	void SetTRSMatrix(mat4 &mat);
	void Draw();
	void Reset();
	void SetColorA(float a, int startIndex, int endIndex);
};