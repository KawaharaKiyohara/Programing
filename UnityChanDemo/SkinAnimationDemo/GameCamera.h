/*!
 *@brief	�Q�[���J����
 */

#pragma once

class Player;
class Car;
/*!
 *@brief	�Q�[���J�����B
 */
class GameCamera : public IGameObject{
public:
	GameCamera();
	~GameCamera();
	void Start() override ;
	void Update() override ;
	void Render( CRenderContext& renderContext ) override;
	void SetPlayer(Player* player)
	{
		this->player = player;
	}
	void SetCar(Car* car)
	{
		this->car = car;
	}
	const CCamera& GetCamera() const
	{
		return camera;
	}
private:
	CCamera camera;
	Car* car;
	Player*	player;
	CVector3	toPosition;		//�����_���王�_�ւ̃x�N�g���B
};


extern GameCamera*			g_camera;				//�J�����B