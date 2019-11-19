#include "MainScene.h"
#include "PBoat.h"
#include "EnemyManager.h"

MainScene::MainScene(mat4 &g_mxModelView, mat4 &g_mxProjection) {
	_mxModelView = g_mxModelView;
	_mxProjection = g_mxProjection;
	CreateGameObject();
}

void MainScene::CreateGameObject() {

	int idx = 0;
	for (int i = 0; i < 3; i++)
	{
		if (idx == 0) { // 第一個物件，必須建立 Shader
			_planet[idx] = new Planet(0.75f, 1, -0.7f, 8.0f);
			_planet[idx]->SetVShaderName("vsPlanet1.glsl");
			_planet[idx]->SetShader(_mxModelView, _mxProjection);
		}
		else {
			if (idx == 2) {
				_planet[idx] = new Planet(0.5f, 2, -0.8f, 10.0f);
				_planet[idx]->SetVShaderName("vsPlanet2.glsl");
			}
			else {
				_planet[idx] = new Planet(0.35f, 3, -0.6f, 12.0f);
				_planet[idx]->SetVShaderName("vsPlanet3.glsl");
			}
			_planet[idx]->SetShader(_mxModelView, _mxProjection);
		}
		idx++;
	}

	_enemyManager = new EnemyManager(_mxModelView, _mxProjection);
	_pBoat = new PBoat(_mxModelView, _mxProjection);

	_enemyManager->GetComponent(_pBoat);
	_pBoat->GetComponent(_enemyManager);
}

void MainScene::Draw() {
	for (int i = 0; i < 3; i++)
	{
		_planet[i]->Draw();
	}

	_pBoat->Draw();
	_enemyManager->EnemyDraw();
}


void MainScene::Update(float delta) {

	for (int i = 0; i < 3; i++)
	{
		_planet[i]->AutoTranslate(delta);
	}

	_pBoat->Update(delta, isBoatShoot);
	_enemyManager->Update(delta);
}

MainScene::~MainScene() {
	if (_planet != NULL) delete [] _planet;
	if (_pBoat != NULL) delete _pBoat;
	if (_enemyManager != NULL) delete _enemyManager;
}