#pragma once
#include "../Header/Angel.h"
#include "Transform.h"
#include "ColorDefine.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define CPOINT_NUM 10

class Planet
{
private:
	vec4 *_points;
	vec4 *_colors;

	float _fduration;
	float _fspeed;
	float _radius;
	float _ftottime;

	Transform *_transform;
	void SetPoint();

	Planet *_nextlink;
public:
	Planet(mat4 &mxView, mat4 &mxProjection);
	~Planet();

	void AutoTranslate(float dt);
	void Draw();

	friend class  PlanetManager;
};


class PlanetManager
{
private:
	int _planetCount;
	Planet *_pGet,*_pHead,*_pTail;

	void SetPosition(float X,float Y);
	void Clear();
	void PlanetGenerator(mat4 &mxView, mat4 &mxProjection);
	mat4 RandomPosition(float minX, float maxX, float minY, float maxY);
public:
	PlanetManager(mat4 &mxView, mat4 &mxProjection);
	~PlanetManager();

	void Update(float dt);
	void PlanetDraw();
};