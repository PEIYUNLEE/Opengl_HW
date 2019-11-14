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
		if (idx == 0) { // �Ĥ@�Ӫ���A�����إ� Shader
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

	_bulletList = new BulletList(_mxModelView, _mxProjection,TOTBULLETCOUNT);
	
	_pBoat = new PBoat;
	_pBoat->SetShader(_mxModelView, _mxProjection);
}

void MainScene::Draw() {
	for (int i = 0; i < 3; i++)
	{
		_planet[i]->Draw();
	}

	_bulletList->BulletDraw();

	_pBoat->Draw();

}
int k = 0;
void MainScene::Update(float delta) {
	_bulletList->Collision();

	_timer += delta;
	if (isBoatShoot == true) {
		if (_timer >= 0.2f) {
			_timer = 0.0f;
			_bulletList->BulletShoot(_pBoat->_transform->_mxTRS); //player�g�X�l�u�A�ǤJplayer�y��
			k++;
			printf("k = %d\n", k);
			printf("%d\n", _bulletList->_shootCount);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		_planet[i]->AutoTranslate(delta);
	}
	_bulletList->AutoTranslate(delta);
}

MainScene::~MainScene() {
	delete [] _planet;
	delete _pBoat;
	delete _bulletList;
}

void MainScene::SetPosition(mat4 mxGT) {
	_pBoat->_transform->SetTRSMatrix(mxGT);
}