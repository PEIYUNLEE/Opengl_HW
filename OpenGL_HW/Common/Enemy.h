#pragma once
#include "../Header/Angel.h"
#include "Transform.h"
#include "Bullet.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

class Enemy
{
private:
protected:
	int _pointNum;
	vec4 *_points;
	vec4 *_colors;
public:
	Transform *_transform;

	Enemy(mat4 &_mxView, mat4 &_mxProjection, int pointNum);
	virtual ~Enemy();

	virtual void SetPoint() = 0;
	virtual void Shoot() = 0;

	void Draw();
	//void Destroy();

	Enemy *_prelink;
	Enemy *_nextlink;

	friend class EnemyManager;
};

class EnemySmall : public Enemy
{
private:
	void SetPoint();
	void Shoot();
public:
	EnemySmall(mat4 &mxView, mat4 &mxProjection,int pointNum = 20) : Enemy(mxView,mxProjection, pointNum) {};
	//~EnemySmall();
};

