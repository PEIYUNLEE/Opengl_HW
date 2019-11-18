#pragma once

#include <cstdlib> /* 亂數相關函數 */
#include <ctime>   /* 時間相關函數 */
#include "../Header/Angel.h"
#include "Transform.h"
#include "ColorDefine.h"
#include "Defense.h"
class BulletList;
class EnemyManager;

#define BSPOINT_NUM 3 //side
#define BBPOINT_NUM 4 //body
#define BCPOINT_NUM 20 //center circle
#define BTPOINT_NUM 11 //top circle
#define BPPOINT_NUM 21 //拋物線
#define BTOTPOINT_NUM BSPOINT_NUM*2+BBPOINT_NUM+BCPOINT_NUM+BTPOINT_NUM+BPPOINT_NUM*2+1

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

class PBoat
{
private:
	vec4 *_points;
	vec4 *_colors;

	float _timer;
	EnemyManager *_getEnemyManager;
public:
	Transform *_transform;
	BulletList *_bulletList;
	Defense *_defense;
	bool _isDefense;
	bool _isDead;
	float *_colliderSize;

	PBoat(mat4 &mxView, mat4 &mxProjection);
	~PBoat();
	void GetComponent(EnemyManager *getEnemyManager);
	void SetPoint();
	void Draw();
	void Update(float delta, bool isBoatShoot);
	void Hurt();

	void Revival();
};