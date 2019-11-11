#include "MainScene.h"

MainScene::MainScene(mat4 g_mxModelView, mat4 g_mxProjection) {
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

	_pBoat = new PBoat;
	_pBoat->SetShader(_mxModelView, _mxProjection);

	_bulletList = new BulletList(_mxModelView, _mxProjection,TOTBULLETCOUNT);
}

void MainScene::Draw() {
	for (int i = 0; i < 3; i++)
	{
		_planet[i]->Draw();
	}

	_pBoat->Draw();

	if (_currentBullet > 0) {
		_bulletList->BulletDraw(_currentBullet);
	}
}

void MainScene::Update(float delta) {
	for (int i = 0; i < 3; i++)
	{
		_planet[i]->AutoTranslate(delta);
	}
	if (_currentBullet>0)
	{
		_bulletList->AutoTranslate(delta, _currentBullet);
	}
}

MainScene::~MainScene() {
	delete [] _planet;
	delete _pBoat;
	delete _bulletList;
}