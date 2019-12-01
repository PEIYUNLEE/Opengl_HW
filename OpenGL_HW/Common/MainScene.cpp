#include "MainScene.h"
#include "PBoat.h"
#include "EnemyManager.h"

MainScene::MainScene(mat4 &g_mxModelView, mat4 &g_mxProjection) {
	_mxModelView = g_mxModelView;
	_mxProjection = g_mxProjection;
	CreateGameObject();
}

void MainScene::CreateGameObject() {

	_planetManager = new PlanetManager(_mxModelView, _mxProjection);
	_enemyManager = new EnemyManager(_mxModelView, _mxProjection);
	_pBoat = new PBoat(_mxModelView, _mxProjection);

	_enemyManager->GetComponent(_pBoat);
	_pBoat->GetComponent(_enemyManager);
}

void MainScene::Draw() {
	
	_planetManager->PlanetDraw();
	_enemyManager->EnemyDraw();
	_pBoat->Draw();
}


void MainScene::Update(float delta) {

	_planetManager->Update(delta);
	_pBoat->Update(delta, isBoatShoot);
	_enemyManager->Update(delta);

	if (_enemyManager->_state == LEVEL3) {
		_planetManager->SetSpeed(-1.5f);
	}
}

MainScene::~MainScene() {
	if (_planetManager != NULL) delete _planetManager;
	if (_pBoat != NULL) delete _pBoat;
	if (_enemyManager != NULL) delete _enemyManager;
}