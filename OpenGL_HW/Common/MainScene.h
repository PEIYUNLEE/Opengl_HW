#include "../Header/Angel.h"
#include "Planet.h"
#include "PBoat.h"
#include "Bullet.h"

#define TOTBULLETCOUNT 50

class MainScene
{
private:
	//«Å§iª«¥ó
	
	Planet *_planet[3];
	BulletList *_bulletList;
	mat4 _mxModelView, _mxProjection;

	void CreateGameObject();
	float _timer;
	
public:
	PBoat *_pBoat;
	bool isBoatShoot=false;

	MainScene(mat4 g_mxModelView, mat4 g_mxProjection);
	~MainScene();
	void Update(float timeDelta);
	void Draw();

	void SetPosition(mat4 mxGT);
};