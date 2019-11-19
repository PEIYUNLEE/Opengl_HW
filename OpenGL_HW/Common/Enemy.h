#pragma once
#include "../Header/Angel.h"
#include "Transform.h"
class BulletList;
class PBoat;


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
	bool _isDead;


	bool _initFlag;

public:
	Transform *_transform;
	BulletList *_bulletList;

	Enemy *_prelink;
	Enemy *_nextlink;

	float _circlecollider;

	Enemy(mat4 &_mxView, mat4 &_mxProjection, float fspeed,float attackDuration, int pointNum, char type);
	virtual ~Enemy();

	virtual void SetPoint() = 0;
	virtual void Attack(float ftottime) = 0;
	virtual void AutoTranslate(float ftottime) = 0;
	virtual void Draw() = 0;
	virtual void Hurt() = 0;

	void Action(float delta, PBoat *getPBoat);
	void Reset();

	friend class EnemyManager;
};

class EnemySmall : public Enemy
{
private:
	void Attack(float delta);
	void AutoTranslate(float ftottime);
public:
	//EnemySmall(mat4 &mxView, mat4 &mxProjection, float fspeed = -0.5f,float attackDuration = 3.0f, int pointNum = 18, char type = 's') :Enemy(mxView, mxProjection, fspeed, attackDuration, pointNum, type) {
	//	_bulletList = new BulletList(mxView, mxProjection, 10, 'e', 1.25f);
	//	SetPoint();
	//	_transform = new Transform(mxView, mxProjection, _pointNum, _points, _colors);
	//};
	//~EnemySmall();

	EnemySmall(mat4 &mxView, mat4 &mxProjection, float fspeed = -0.5f, float attackDuration = 3.0f, int pointNum = 18, char type = 's');

	void Draw();
	void Hurt();
	void SetPoint();
};


class EnemyMiddle : public Enemy
{
private:
	void Attack(float delta);
	void AutoTranslate(float ftottime);
public:
	//EnemyMiddle(mat4 &mxView, mat4 &mxProjection, float fspeed = -0.5f, float attackDuration = 3.0f, int pointNum = 30, char type = 'm') :Enemy(mxView, mxProjection, fspeed, attackDuration, pointNum, type) {

	//	_bulletList = new BulletList(mxView, mxProjection, 50, 'm', 1.25f);
	//	SetPoint();
	//	_transform = new Transform(mxView, mxProjection, _pointNum, _points, _colors);
	//};
	//~EnemyMiddle();
	EnemyMiddle(mat4 &mxView, mat4 &mxProjection, float fspeed = -0.3f, float attackDuration = 3.0f, int pointNum = 30, char type = 'm');

	void Draw();
	void Hurt();
	void SetPoint();
};

