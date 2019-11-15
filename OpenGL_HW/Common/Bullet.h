#pragma once
#include "../Header/Angel.h"
#include "Transform.h"
#include "Enemy.h"
#include "PBoat.h"

#define POINT_NUM 10

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

//class BulletList;

class Bullet
{
private:
	//data
	vec4 _points[POINT_NUM];
	vec4 _colors[POINT_NUM];

	void CreateBufferObject();

	float _fspeed =0.7f;
	float _ftottime;

	//node
	Bullet *_prelink;
	Bullet *_nextlink;
public:
	Transform *_transform;
	mat4 _mxOri;

	Bullet();
	~Bullet();

	void SetPoint();
	void AutoTranslate(float dt);
	void SetShader(mat4 &mxView, mat4 &mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);

	void Draw();

	//list
	friend class BulletList;
};




class BulletList{
private:
	Bullet *pUseTail, *pUseHead;
	Bullet *pHead, *pTail, *pNewGet;
	Bullet *pColliGet;

	int _totCount;

	float _timer;
	Enemy *_enemy;
	PBoat *_player;

public:
	int _shootCount = 0;
	int _storeCount = 0;

	BulletList(mat4 g_mxModelView, mat4 g_mxProjection,int count,Enemy *enemy);
	~BulletList();
	void PrintList();			// 印出list的所有資料
	void PushHead();		// 在list的尾巴新增node
	void PushTail();		// 在list的尾巴新增node
	void Delete(int index);			// 刪除list中的index
	void Clear();					// 把整串list刪除
	void BulletShoot(mat4 &mat);
	void BulletDraw();
	void AutoTranslate(float timeDelta);
	void Update(float delta, bool isBoatShoot,mat4 matBoat);
	void Collision();	//判定有沒有碰到敵人或超出範圍
	void DestoryBullet();	//將子彈丟回子彈池
};