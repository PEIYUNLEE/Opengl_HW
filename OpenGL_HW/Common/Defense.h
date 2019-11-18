#pragma once

#include "../Header/Angel.h"
#include "Transform.h"
#include "ColorDefine.h"

#define POINT_NUM_CIRCLE 20
#define POINT_NUM_BOX 6


class Defense
{
private:
	vec4 *_points;
	vec4 *_colors;

public:
	Transform *_transform;
	float *_colliderSize;
	
	Defense(mat4 &mxView, mat4 &mxProjection, float circlecollider);
	Defense(mat4 &mxView, mat4 &mxProjection, float boxCollider_X,float boxCollider_Y);
	~Defense();
	void SetPoint(float circlecollider);
	//void SetPoint(float boxCollider_X, float boxCollider_Y);
	void Draw(char type);
};