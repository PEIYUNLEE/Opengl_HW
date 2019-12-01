#pragma once

#include "../Header/Angel.h"
#include "Transform.h"
#include "ColorDefine.h"

class Defense
{
private:
	vec4 *_points;
	vec4 *_colors;

	int _pointNum;
	float _rotTimer;
public:
	Transform *_transform;
	float *_colliderSize;
	float _rotSpeed;
	
	Defense(mat4 &mxView, mat4 &mxProjection, float circlecollider);
	~Defense();
	void SetPoint();
	void Draw();
	void Reset();
	void AutoRotation(float dt);
};