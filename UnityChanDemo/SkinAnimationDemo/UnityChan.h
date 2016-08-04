#pragma once

#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkAnimation.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/graphics/tkTexture.h"

/*!
 * @brief	���j�e�B�����
 */
class UnityChan : public IGameObject {
	enum AnimationNo {
		AnimationStand,		//�����B
		AnimationWalk,		//�����B
		AnimationRun,		//����B
		AnimationJump,		//�W�����v�B
	};
	static CSkinModelData*	orgSkinModelData;		//�X�L�����f���f�[�^�B
	CSkinModelData			skinModelData;
	CSkinModel				skinModel;			//�X�L�����f���B
	CAnimation				animation;			//�A�j���[�V�����B
	CCamera					camera;				//�J�����B
	CLight					light;				//���C�g�B
	int						currentAnimSetNo;		
	CTexture				normalMap;			//�@���}�b�v�B
	CVector3				position;			//���W�B
public:
	bool					isUpdateAnim;		//

	UnityChan() :
		position(CVector3::Zero),
		isUpdateAnim(false)
	{

	}
	void Start() override ;
	void Update() override ;
	void Render( CRenderContext& renderContext ) override;
	void SetPosition(const CVector3& position)
	{
		this->position = position;
	}
};