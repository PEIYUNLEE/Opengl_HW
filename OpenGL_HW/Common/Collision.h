#pragma once
#include "../Header/Angel.h"
class EnemyManager;
class Enemy;

class Collision {
public:
	bool OnCircleCollision(mat4 mat_Object, float cObjectRadius, EnemyManager *getEnemyList);	//物件與所有Enemy比較
	bool OnCircleCollision(mat4 mat_Object, float cObjectRadius, mat4 mat_Main, float cPBoatRadius);	//物件與物件
};