/*!
 *@brief	�Q�[���J����
 */

#pragma once

class UnityChan;
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
	void SetUnityChan(UnityChan* unityChan)
	{
		this->unityChan = unityChan;
	}
	const CCamera& GetCamera() const
	{
		return camera;
	}
private:
	CCamera camera;
	UnityChan* unityChan;
	CVector3 toPosition;		//�����_���王�_�ւ̃x�N�g���B
};


extern GameCamera*			g_camera;				//�J�����B