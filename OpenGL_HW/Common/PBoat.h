#pragma once
#include "../Header/Angel.h"
#include "Transform.h"

#define BSPOINT_NUM 3 //side
#define BBPOINT_NUM 4 //body
#define BCPOINT_NUM 20 //center circle
#define BTPOINT_NUM 11 //top circle
#define BPPOINT_NUM 21 //©ßª«½u
#define BTOTPOINT_NUM BSPOINT_NUM*2+BBPOINT_NUM+BCPOINT_NUM+BTPOINT_NUM+BPPOINT_NUM*2+1

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

class PBoat
{
private:
	vec4 _points[BTOTPOINT_NUM];
	vec4 _colors[BTOTPOINT_NUM];

	void CreateBufferObject();
public:
	Transform *_transform;

	PBoat();
	~PBoat();
	void SetPoint();
	void Draw();
	void SetShader(mat4 &mxView, mat4 &mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
};