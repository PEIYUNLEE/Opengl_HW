#include "Collision.h"
#include "EnemyManager.h"
#include "Enemy.h"

bool Collision::OnCircleCollision(mat4 mat_Object, float cObjectRadius, EnemyManager *getEnemyList) {
	//物件與所有Enemy比較 已經確定有Enemy存在

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
			if (dsquare <= radiusPlus*radiusPlus) {
				pGet->Hurt(); //Enemy反應
				return true; //銷毀物件
			}
			else pGet = pGet->_nextlink;
		}
	}
	return false;	//都沒有
}

//bool Collision::OnCircleCollision(mat4 mat_Object, float cObjectRadius, mat4 mat_PBoat, float cPBoatRadius) {
//	//物件與Boat
//	float radiusPlus = 0;
//}