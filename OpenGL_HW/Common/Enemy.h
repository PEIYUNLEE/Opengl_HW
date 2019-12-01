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
	float _fspeed;
	float _attackTimer;
	float _attackDuration;
	int _state;

	bool _initFlag;

	//Smoke *_smokeHurt;
	//Smoke *_smokeDead;
public:
	Transform *_transform;
	BulletList *_bulletList;

	Enemy *_prelink;
	Enemy *_nextlink;

	bool _isDead;
	char _type;
	bool _isDefaultEnemy;

	float _ftottime;
	float *_colliderSize;

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
	float _bIX; //�l�u���ʳ��V�q
	float _bIY; //�l�u���ʳ��V�q
	float _rotateDuration; //�������ඡ�j�ɶ�
	float _rotateTimer ; //��������ɶ�
	float _translateTimer ; //�������ʮɶ�
	GLfloat _fZAngle;
	GLfloat _btx; //�x�s����
	GLfloat _bty; //�x�s����
	bool _isStop=false; //��w��

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
	float _bIX; //�l�u���ʳ��V�q
	float _bIY; //�l�u���ʳ��V�q
	int _attackState; //�����Ҧ�
	float _translateTimer; //�������ʮɶ�
	GLfloat _btx; //�x�s����
	GLfloat _bty; //�x�s����
	bool _isExploShoot;	//�ĤT�ا����o�g
	int _heart;	//��q

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

