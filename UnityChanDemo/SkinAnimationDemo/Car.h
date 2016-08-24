/*!
 *@brief	�ԃN���X�B
 */
#pragma once

class Car : public IGameObject{
public:
	Car();
	~Car();
	void Start() override ;
	void Update() override ;
	void Render( CRenderContext& renderContext ) override;
private:
	CSkinModelData			skinModelData;
	CSkinModel				skinModel;			//�X�L�����f���B
	CLight					light;				//���C�g�B
	CTexture				normalMap;			//�@���}�b�v�B
	CVector3				position;			//���W�B
	CQuaternion				rotation;			//��]�B
};