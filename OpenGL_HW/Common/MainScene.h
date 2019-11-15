#pragma once
#include "../Header/Angel.h"
#include "Planet.h"
#include "PBoat.h"
#include "Bullet.h"
#include "EnemyManager.h"


class MainScene
{
private:
	//«Å§iª«¥ó
	
	Planet *_planet[3];
	EnemyManager *_enemyManager;
	mat4 _mxModelView, _mxProjection;

	void CreateGameObject();
	
public:
	PBoat *_pBoat;
	bool isBoatShoot=false;

	MainScene(mat4 g_mxModelView, mat4 g_mxProjection);
	~MainScene();
	void Update(float timeDelta);
	void Draw();
};