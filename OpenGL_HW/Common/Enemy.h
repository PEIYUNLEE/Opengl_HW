#pragma once
#include "../Header/Angel.h"
#include "Transform.h"

#define POINT_NUM 20 //center circle

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

class Enemy
{
private:
	vec4 _points[POINT_NUM];
	vec4 _colors[POINT_NUM];

	void CreateBufferObject();
public:
	Transform *_transform;

	Enemy();
	~Enemy();
	void SetPoint();
	void Draw();
	void SetShader(mat4 &mxView, mat4 &mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	
	friend class EnemyManager;
};