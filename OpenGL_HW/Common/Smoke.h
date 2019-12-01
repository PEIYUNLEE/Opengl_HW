#pragma once
#include "../Header/Angel.h"
#include "Transform.h"
#include "ColorDefine.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define POINT_NUM 80

class Smoke
{
	enum TYPE
	{
		RED,
		GRAY
	};
	enum STATE
	{
		NONE = 0,
		FIRST,
		SECOND,
		THIRD,
		FOURTH
	};
private:
	vec4 *_points;
	vec4 *_colors;

	Transform *_transform;

	float _timer;
	int _showCount;
	void SetPoint();
public:
	int _smokeState;

	Smoke(mat4 &mxView, mat4 &mxProjection);
	~Smoke();

	void Update(float dt, mat4 mat);
	void Draw();
	void Show(int type);	//red:1 gray:0
};