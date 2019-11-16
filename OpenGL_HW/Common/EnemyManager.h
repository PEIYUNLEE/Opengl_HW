#pragma once
#include "../Header/Angel.h"
#include "Enemy.h"
//class Enemy;

class EnemyManager {
private:
	Enemy *pEUseTail, *pEUseHead;
	Enemy *pEHead_s, *pETail_s;
	Enemy *pEHead_m, *pETail_m;
	Enemy *pENewGet , *pEUpdateGet;

	int _totCount_s, _totCount_m;
	int _usetotCount, _storetotCount;
	int _useCount_s, _storeCount_s;
	int _useCount_m, _storeCount_m;

	float _timer;
	float _genDuration;
	mat4 _genMat;

	float RandomTime(float min = 5.0f, float max = 10.0f);
	mat4 RandomPosition(float minX = -1.5f, float maxX = 1.5f , float Y = 2.55f);
public:

	EnemyManager(mat4 &mxView, mat4 &mxProjection, int totCount_s=5, int totCount_m=5);
	~EnemyManager();
	void Clear();	// §â¾ã¦êlist§R°£
	void EnemyDraw();
	void Update(float delta);
	void DestroyEnemy();
	void PushTail();
	void EnemyGenerater(char type, mat4 &mat);
};