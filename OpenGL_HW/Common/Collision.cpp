#include "Collision.h"
#include "EnemyManager.h"
#include "Enemy.h"

bool Collision::OnCircleCollision(mat4 mat_Object, float cObjectRadius, EnemyManager *getEnemyList) {
	//����P�Ҧ�Enemy��� �w�g�T�w��Enemy�s�b

	float radiusPlus = 0;
	float dx, dy, dsquare;
	Enemy *pGet;

	pGet = getEnemyList->pEUseHead;
	for (int i = 0; i < (getEnemyList->_usetotCount); i++)
	{
		dx = dy = dsquare = radiusPlus = 0;
		if (pGet != NULL) {
			radiusPlus = pGet->_colliderSize[0] + cObjectRadius;
			dx = (mat_Object._m[0].w - pGet->_transform->_mxTRS._m[0].w);
			dy = (mat_Object._m[1].w - pGet->_transform->_mxTRS._m[1].w);
			dsquare = dx*dx + dy*dy;
			if (dsquare <= radiusPlus*radiusPlus && dsquare!=0) {
				pGet->Hurt(); //Enemy����
				return true; //�P������
			}
			else pGet = pGet->_nextlink;
		}
	}
	return false;	//���S��
}

bool Collision::OnBoxCollision(mat4 mat_Object, float *cObjectRadius, EnemyManager *getEnemyList) {
	//����P�Ҧ�Enemy��� �w�g�T�w��Enemy�s�b

	float radiusPlus_X, radiusPlus_Y;
	float dx, dy;
	Enemy *pGet;

	pGet = getEnemyList->pEUseHead;
	for (int i = 0; i < (getEnemyList->_usetotCount); i++)
	{
		dx = dy = radiusPlus_X = radiusPlus_Y = 0;
		if (pGet != NULL) {
			radiusPlus_X = pGet->_colliderSize[0] + cObjectRadius[0];
			radiusPlus_Y = pGet->_colliderSize[1] + cObjectRadius[1];

			dx = (mat_Object._m[0].w - pGet->_transform->_mxTRS._m[0].w);
			dy = (mat_Object._m[1].w - pGet->_transform->_mxTRS._m[1].w);
			if (dx < 0)dx = -dx;
			if (dy < 0)dy = -dy;

			if (dx <= radiusPlus_X && dy <= radiusPlus_Y) {
				pGet->Hurt(); //Enemy����
				return true; //�P������
			}
			else pGet = pGet->_nextlink;
		}
	}
	return false;	//���S��
}

bool Collision::OnCircleCollision(mat4 mat_Object,float cObjectRadius, mat4 mat_Main, float cPBoatRadius) {
	//����P����

	float radiusPlus = 0;
	float dx, dy, dsquare;

	dx = dy = dsquare = radiusPlus = 0;
	radiusPlus = cPBoatRadius + cObjectRadius;

	dx = (mat_Object._m[0].w - mat_Main._m[0].w);
	dy = (mat_Object._m[1].w - mat_Main._m[1].w);
	dsquare = dx*dx + dy*dy;

	if (dsquare <= radiusPlus*radiusPlus && dsquare != 0) {
		return true; //�P������
	}
	return false;	//���S��
}

bool Collision::OnBoxCollision(mat4 mat_Object, float *cObjectRadius, mat4 mat_Main, float *cPBoatRadius) {
	//����P����

	float radiusPlus_X , radiusPlus_Y;
	float dx, dy;

	dx = dy = radiusPlus_X = radiusPlus_Y = 0;
	radiusPlus_X = cObjectRadius[0]+ cPBoatRadius[0];
	radiusPlus_Y = cObjectRadius[1] + cPBoatRadius[1];

	dx = (mat_Object._m[0].w - mat_Main._m[0].w);
	dy = (mat_Object._m[1].w - mat_Main._m[1].w);
	if (dx < 0)dx = -dx;
	if (dy < 0)dy = -dy;

	if (dx<= radiusPlus_X && dy <= radiusPlus_Y) {
		return true; //�P������
	}
	return false;	//���S��
}