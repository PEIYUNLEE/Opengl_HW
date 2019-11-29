#pragma once
#include "../Header/Angel.h"
#include "Collision.h"
class Enemy;
class PBoat;
class BulletList;

enum LEVEL_STATE
{
	LEVEL1,
	LEVEL2,
	LEVEL3
};

class EnemyManager {
private:
	Enemy *pEHead_s, *pETail_s;
	Enemy *pEHead_m, *pETail_m;
	Enemy *pENewGet , *pEUpdateGet;
	Enemy *pEBoss,*pEHead_b;

	int _totCount_s, _totCount_m, _totCount_b;
	int  _storetotCount;
	int _useCount_s, _storeCount_s;
	int _useCount_m, _storeCount_m;
	int _useCount_b, _storeCount_b;

	float _timer;
	float _genDuration;
	mat4 _genMat;

	float RandomTime(float min = 1.5f, float max = 3.5f);
	mat4 RandomPosition(float minX = -1.5f, float maxX = 1.5f , float Y = 2.55f);

	PBoat *_getPBoat;
	int _state;
	Collision _colliSystem;
public:
	Enemy *pEUseTail, *pEUseHead;
	int _usetotCount;

	EnemyManager(mat4 &mxView, mat4 &mxProjection,int totCount_s=5, int totCount_m=5);
	~EnemyManager();
	void GetComponent(PBoat *getPBoat);
	void Clear();	// §â¾ã¦êlist§R°£
	void EnemyDraw();
	void Update(float delta);
	void DestroyEnemy();
	void PushTail();
	void EnemyGenerater(char type, mat4 &mat);
	void EGeneratorController();
};