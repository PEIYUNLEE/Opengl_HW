#pragma once
#include "../Header/Angel.h"
class EnemyManager;
class Enemy;

class Collision {
public:
	bool OnCircleCollision(mat4 mat_Object, float cObjectRadius, EnemyManager *getEnemyList);	//����P�Ҧ�Enemy���
	bool OnCircleCollision(mat4 mat_Object, float cObjectRadius, mat4 mat_Main, float cPBoatRadius);	//����P����
};