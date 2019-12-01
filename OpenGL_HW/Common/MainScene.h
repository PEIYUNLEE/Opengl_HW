#pragma once
#include "../Header/Angel.h"
#include "Planet.h"

class PBoat;
class EnemyManager;

class MainScene
{
private:
	//«Å§iª«¥ó
	
	PlanetManager *_planetManager;
	mat4 _mxModelView, _mxProjection;

	void CreateGameObject();
	
public:
	EnemyManager *_enemyManager;
	PBoat *_pBoat;
	bool isBoatShoot=false;

	MainScene(mat4 &g_mxModelView, mat4 &g_mxProjection);
	~MainScene();
	void Update(float timeDelta);
	void Draw();
};