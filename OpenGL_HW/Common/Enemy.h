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
	float _bIX; //子彈移動單位向量
	float _bIY; //子彈移動單位向量
	float _rotateDuration; //紀錄旋轉間隔時間
	float _rotateTimer ; //紀錄旋轉時間
	float _translateTimer ; //紀錄移動時間
	GLfloat _fZAngle;
	GLfloat _btx; //儲存移動
	GLfloat _bty; //儲存移動
	bool _isStop=false; //到定位

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
	float _bIX; //子彈移動單位向量
	float _bIY; //子彈移動單位向量
	int _attackState; //攻擊模式
	float _translateTimer; //紀錄移動時間
	GLfloat _btx; //儲存移動
	GLfloat _bty; //儲存移動
	bool _isExploShoot;	//第三種攻擊發射
	int _heart;	//血量

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

