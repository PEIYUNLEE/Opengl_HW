#include "MainScene.h"
#include "PBoat.h"
#include "EnemyManager.h"

MainScene::MainScene(mat4 &g_mxModelView, mat4 &g_mxProjection) {
	_mxModelView = g_mxModelView;
	_mxProjection = g_mxProjection;
	CreateGameObject();
}

void MainScene::CreateGameObject() {

	/*_planet = new Planet[3];

	_planet[0] = Planet(0.75f, 1, -0.7f, 8.0f);
	(_planet + 0)->SetVShaderName("vsPlanet1.glsl");
	(_planet + 0)->SetShader(_mxModelView, _mxProjection);

	_planet[1] = Planet(0.5f, 2, -0.8f, 10.0f);
	(_planet + 1)->SetVShaderName("vsPlanet2.glsl");

	_planet[2] = Planet(0.35f, 3, -0.6f, 12.0f);
	(_planet + 2)->SetVShaderName("vsPlanet3.glsl");
	(_planet + 2)->SetShader(_mxModelView, _mxProjection);*/

	_enemyManager = new EnemyManager(_mxModelView, _mxProjection);
	_pBoat = new PBoat(_mxModelView, _mxProjection);

	_enemyManager->GetComponent(_pBoat);
	_pBoat->GetComponent(_enemyManager);
}

void MainScene::Draw() {
	/*for (int i = 0; i < 3; i++)
	{
		(_planet+i)->Draw();
	}*/

	_pBoat->Draw();
	_enemyManager->EnemyDraw();
}


void MainScene::Update(float delta) {

	/*for (int i = 0; i < 3; i++)
	{
		(_planet + i)->AutoTranslate(delta);
	}
*/
	_pBoat->Update(delta, isBoatShoot);
	_enemyManager->Update(delta);
}

MainScene::~MainScene() {
	/*if (_planet != NULL) delete [] _planet;*/
	if (_pBoat != NULL) delete _pBoat;
	if (_enemyManager != NULL) delete _enemyManager;
}