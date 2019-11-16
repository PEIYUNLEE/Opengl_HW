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
	char _type;
	float _ftottime;
	float _fspeed;
	float _attackTimer;
	float _attakDuration;
public:
	Transform *_transform;
	BulletList *_bulletList;

	Enemy *_prelink;
	Enemy *_nextlink;

	Enemy(mat4 &_mxView, mat4 &_mxProjection, float fspeed,float attackDuration, int pointNum, char type);
	virtual ~Enemy();

	virtual void SetPoint() = 0;
	virtual void Attack(float ftottime) = 0;
	virtual void AutoTranslate(float ftottime) = 0;
	virtual void Draw() = 0;

	void Action(float delta);
	void Reset();

	friend class EnemyManager;
};

class EnemySmall : public Enemy
{
private:
	void Action(float delta);
	void Attack(float delta);
	void AutoTranslate(float ftottime);
public:
	EnemySmall(mat4 &mxView, mat4 &mxProjection, float fspeed = -0.5f,float attackDuration = 1.0f, int pointNum = 20, char type = 's') :Enemy(mxView, mxProjection, fspeed, attackDuration, pointNum, type) {

		SetPoint();
		_transform = new Transform(mxView, mxProjection, _pointNum, _points, _colors);
	};
	//~EnemySmall();

	void Draw();
	void SetPoint();
};

