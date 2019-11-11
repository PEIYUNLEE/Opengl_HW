#include "../Header/Angel.h"
#include "Planet.h"
#include "PBoat.h"

#define TOTBULLETCOUNT 50

class MainScene
{
private:
	//«Å§iª«¥ó
	
	Planet *_planet[3];
	BulletList *_bulletList;
	mat4 _mxModelView, _mxProjection;

	void CreateGameObject();

public:
	PBoat *_pBoat;
	int _currentBullet = 0;

	MainScene(mat4 g_mxModelView, mat4 g_mxProjection);
	~MainScene();
	void Update(float timeDelta);
	void Draw();
};