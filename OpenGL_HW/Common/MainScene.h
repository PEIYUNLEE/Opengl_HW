#pragma once
#include "../Header/Angel.h"
#include "Planet.h"

class PBoat;
class EnemyManager;

class MainScene
{
private:
	//�ŧi����
	
	PlanetManager *_planetManager;
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