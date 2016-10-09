#pragma once

#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/graphics/tkAnimation.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/graphics/tkTexture.h"
#include "Physics/SphereCollider.h"
#include "Physics/RigidBody.h"
#include "CharacterController.h"

/*!
 * @brief	���j�e�B�����
 */
class UnityChan : public IGameObject {
private:
	
	static const int NUM_BATTLE_SEAT = 8;		//�V�[�g�̐��B
	enum AnimationNo {
		AnimationInvalid = -1,
		AnimationStand,		//�����B
		AnimationWalk,		//�����B
		AnimationRun,		//����B
		AnimationJump,		//�W�����v�B
		AnimationAttack_Start,
		AnimationAttack_00 = AnimationAttack_Start,	//�U��00�B
		AnimationAttack_01,	//�U��01�B
		AnimationAttack_02,	//�U��02�B
		AnimationAttack_End = AnimationAttack_02,
		AnimationDamage,	//�_���[�W�B
		AnimationDeath,		//���S�B
	};
public:
	//�퓬�Ŏg�p����V�[�g
	struct SBattleSeat {
		bool		isUse;			//�g�p���t���O�B
		int			seatNo;			//�V�[�g�ԍ��B
		CVector3	localPosition;	//���[�J�����W�B
		CVector3	position;		//���[���h���W�B
	};
	enum EnState {
		enStateRun,			//�����Ă���B
		enStateStand,		//�����~�܂��Ă���B
		enState_RideOnCar,	//�Ԃɏ���Ă���B
		enState_Attack,		//�U���B
	};
	bool					isUpdateAnim;		//

	UnityChan() :
		position(CVector3::Zero),
		isUpdateAnim(false)
	{
		memset(battleSeats, 0, sizeof(battleSeats));
	}
	void Start() override ;
	void Update() override ;
	void Render( CRenderContext& renderContext ) override;
	void SetPosition(const CVector3& position)
	{
		this->position = position;
	}
	const CVector3& GetPosition() const
	{
		return position;
	}
	/*!
	* @brief	��Ԃ��擾�B
	*/
	EnState GetState() const
	{
		return state;
	}
	/*!
	* @brief	�|�C���g���C�g�̈ʒu���擾�B
	*/
	const CVector3& GetPointLightPosition() const
	{
		return pointLightPosition;
	}
	/*!
	* @brief	�|�C���g���C�g�̐F���擾�B
	*/
	const CVector4& GetPointLightColor() const
	{
		return pointLightColor;
	}
	/*!
	* @brief	���g�p�̃V�[�g�������B
	*@param[in]	pos		���g�p�̃V�[�g�̒����炱�̍��W�Ɉ�ԋ߂��V�[�g��Ԃ��܂��B
	*@return		���g�p�̃V�[�g���Ȃ��ꍇ��NULL���Ԃ��Ă���B
	*/
	SBattleSeat* FindUnuseSeat(const CVector3& pos) ;
private:
	/*!
	* @brief	�|�C���g���C�g�̈ʒu���X�V�B
	*/
	void UpdatePointLightPosition();
	/*!
	* @brief	�A�j���[�V�����R���g���[���B
	*/
	void AnimationControl();
	/*!
	* @brief	�A�j���[�V�����Đ��B
	*/
	void PlayAnimation(AnimationNo animNo, float interpolateTime);
	/*!
	* @brief	�o�g���Ŏg�p����V�[�g���������B
	*/
	void InitBattleSeats();
	/*!
	* @brief	�o�g���Ŏg�p����V�[�g���X�V�B
	*/
	void UpdateBattleSeats();
private:
	CSkinModelDataHandle	skinModelData;
	CSkinModel				skinModel;			//�X�L�����f���B
	CAnimation				animation;			//�A�j���[�V�����B
	CLight					light;				//���C�g�B
	CTexture				normalMap;			//�@���}�b�v�B
	CTexture				specMap;			//�X�y�L�����}�b�v�B
	CTexture				weaponNormalMap;	//����̖@���}�b�v�B
	CTexture				weaponSpecMap;		//����̃X�y�L�����}�b�v�B
	CVector3				position;			//���W�B
	CQuaternion				rotation;			//��]
	CVector3				toLightPos;			//
	CVector3				pointLightPosition;	//�|�C���g���C�g�̈ʒu�B
	CVector4				pointLightColor;	//�|�C���g���C�g�̃J���[�B
	CVector3				toLampLocalPos;		//�����v�̃��[�J�����W�B
	EnState					state;				//��ԁB
	EnState					lastFrameState;		//�O�̃t���[���̏�ԁB
	bool					isPointLightOn;		//�|�C���g���C�g�̃X�C�b�`�B
	RigidBody				rigidBody;			//���́B
	CharacterController		characterController;	//�L�����N�^�R���g���[���B
	SBattleSeat				battleSeats[NUM_BATTLE_SEAT];	//�V�[�g�B
	AnimationNo				reqAttackAnimNo;		//�Đ��̃��N�G�X�g���o���Ă���U�����[�V�����ԍ��B
	AnimationNo				nextAttackAnimNo;		//���̍U�����[�V�����ԍ��B

};