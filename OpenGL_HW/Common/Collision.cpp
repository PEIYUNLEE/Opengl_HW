#include "Collision.h"
#include "EnemyManager.h"
#include "Enemy.h"

bool Collision::OnCircleCollision(mat4 mat_Object, float cObjectRadius, EnemyManager *getEnemyList) {
	//ン籔┮ΤEnemyゑ耕 竒絋﹚ΤEnemy

	float radiusPlus = 0;
	float dx, dy, dsquare;
	Enemy *pGet;

	pGet = getEnemyList->pEUseHead;
	for (int i = 0; i < (getEnemyList->_usetotCount); i++)
	{
		dx = dy = dsquare = radiusPlus = 0;
		if (pGet != NULL) {
			radiusPlus = pGet->_circlecollider + cObjectRadius;
			dx = (mat_Object._m[0].w - pGet->_transform->_mxTRS._m[0].w);
			dy = (mat_Object._m[1].w - pGet->_transform->_mxTRS._m[1].w);
			dsquare = dx*dx + dy*dy;
			if (dsquare <= radiusPlus*radiusPlus && dsquare!=0) {
				pGet->Hurt(); //Enemyは莱
				return true; //綪反ン
			}
			else pGet = pGet->_nextlink;
		}
	}
	return false;	//常⊿Τ
}

bool Collision::OnCircleCollision(mat4 mat_Object,float cObjectRadius, mat4 mat_Main, float cPBoatRadius) {
	//ン籔ン

	float radiusPlus = 0;
	float dx, dy, dsquare;

	dx = dy = dsquare = radiusPlus = 0;
	radiusPlus = cPBoatRadius + cObjectRadius;

	dx = (mat_Object._m[0].w - mat_Main._m[0].w);
	dy = (mat_Object._m[1].w - mat_Main._m[1].w);
	dsquare = dx*dx + dy*dy;

	if (dsquare <= radiusPlus*radiusPlus && dsquare != 0) {
		return true; //綪反ン
	}
	return false;	//常⊿Τ
}