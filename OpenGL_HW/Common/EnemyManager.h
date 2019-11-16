#pragma once
#include "../Header/Angel.h"
class Enemy;
class PBoat;

class EnemyManager {
private:
	Enemy *pEHead_s, *pETail_s;
	Enemy *pEHead_m, *pETail_m;
	Enemy *pENewGet , *pEUpdateGet;

	int _totCount_s, _totCount_m;
	int  _storetotCount;
	int _useCount_s, _storeCount_s;
	int _useCount_m, _storeCount_m;

	float _timer;
	float _genDuration;
	mat4 _genMat;

	float RandomTime(float min = 5.0f, float max = 10.0f);
	mat4 RandomPosition(float minX = -1.5f, float maxX = 1.5f , float Y = 2.55f);

	PBoat *_getPBoat;
public:
	Enemy *pEUseTail, *pEUseHead;
	int _usetotCount;

	EnemyManager(mat4 &mxView, mat4 &mxProjection,int totCount_s=5, int totCount_m=5);
	~EnemyManager();
	void GetComponent(PBoat *getPBoat);
	void Clear();	// ����list�R��
	void EnemyDraw();
	void Update(float delta);
	void DestroyEnemy();
	void PushTail();
	void EnemyGenerater(char type, mat4 &mat);
};