#pragma once
#include "../Header/Angel.h"
#include "Planet.h"

//class Planet;
class PBoat;
class EnemyManager;

class MainScene
{
private:
	//«Å§iª«¥ó
	
	Planet *_planet;
	EnemyManager *_enemyManager;
	mat4 _mxModelView, _mxProjection;

	void CreateGameObject();
	
public:
	PBoat *_pBoat;
	bool isBoatShoot=false;

	MainScene(mat4 &g_mxModelView, mat4 &g_mxProjection);
	~MainScene();
	void Update(float timeDelta);
	void Draw();
};