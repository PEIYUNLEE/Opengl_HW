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
	float _attackDuration;
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
	virtual void Reset() =0;

	friend class EnemyManager;
};

class EnemySmall : public Enemy
{
private:
	void Attack(float delta);
	void AutoTranslate(float ftottime);
public:

	EnemySmall(mat4 &mxView, mat4 &mxProjection, float fspeed = -0.5f, float attackDuration = 3.0f, int pointNum = 18, char type = 's');

	void Draw();
	void Hurt();
	void SetPoint();
	void Reset();
};

class EnemyMiddle : public Enemy
{
private:
	float _iX = 0.0f;
	float _iY = 1.0f;
	float _rotateDuration= 4.5f;
	float _rotateTimer = 0.0f;
	float _translateTimer = 0.0f;
	GLfloat _fZAngle = 0.0f;
	GLfloat _btx = 0.0f;
	GLfloat _bty = 0.0f;
	bool _isStop=false;

	void Attack(float delta);
	void AutoTranslate(float ftottime);
public:
	EnemyMiddle(mat4 &mxView, mat4 &mxProjection, float fspeed = -0.5f, float attackDuration = 3.0f, int pointNum = 30, char type = 'm');

	void Draw();
	void Hurt();
	void SetPoint();
	void Reset();
};

class EnemyBoss : public Enemy
{
	enum AttackState
	{
		Idle,
		Normal,
		Progressive,
		Explosion
	};
private:
	float _iX;
	float _iY;
	int _attackState;
	float _translateTimer;
	GLfloat _btx;
	GLfloat _bty;
	bool _isExploShoot;

	void Attack(float delta);
	void AutoTranslate(float ftottime);
public:
	EnemyBoss(mat4 &mxView, mat4 &mxProjection, float fspeed = 1.0f, float attackDuration = 3.0f, int pointNum = 32, char type = 'b');

	void Draw();
	void Hurt();
	void SetPoint();
	void Reset();
	void AttackNormal();
	void AttackProgressive(int &k);
	void AttackExplosion();
};

