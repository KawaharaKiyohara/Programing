#include "stdafx.h"
#include "Player.h"
#include "Car.h"
#include "Map/Ground.h"
#include "tkEngine/graphics/tkSkinModelMaterial.h"

namespace {
	const float MAX_RUN_SPEED = 0.1f;					//���j�e�B�����̑���̍ō����x�B
	const float RUN_THREADHOLD_SQ = 4.0f * 4.0f;		//����A�j���[�V�������Đ����鑬�x��臒l�B
	//�A�j���[�V�����̃C�x���g�e�[�u���B
	AnimationEventGroup animationEventGroupTbl[Player::NumAnimation] = {
		//AnimationStand
		{
			END_ANIMATION_EVENT(),
		},
		//AnimationWalk
		{
			END_ANIMATION_EVENT(),
		},
		//AnimationRun
		{
			END_ANIMATION_EVENT(),
		},
		//AnimationJump
		{
			END_ANIMATION_EVENT(),
		},
		//AnimationAttack_00
		{
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(0.4f, 0.3f, 0.7f, 10, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 0),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(0.48f, 0.3f, 0.7f, 10, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 0),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(0.56f, 0.3f, 0.7f, 10, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 0),
			END_ANIMATION_EVENT(),
		},
		//AnimationAttack_01
		{
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(0.4f, 0.3f, 0.7f, 10, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 1),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(0.48f, 0.3f, 0.7f, 10, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 1),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(0.56f, 0.3f, 0.7f, 10, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 1),
			END_ANIMATION_EVENT(),
		},
		//AnimationAttack_02
		{
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.3f, 0.3f, 0.7f, 20, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.31f, 0.3f, 0.7f, 20, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.32f, 0.3f, 0.7f, 20, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.33f, 0.3f, 0.7f, 20, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.34f, 0.3f, 0.7f, 20, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.35f, 0.3f, 0.7f, 20, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.36f, 0.3f, 0.7f, 20, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.37f, 0.3f, 0.7f, 20, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.38f, 0.3f, 0.7f, 20, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.39f, 0.35f, 0.7f, 20, "thief_Bip01_R_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),

			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.3f, 0.3f, 0.7f, 20, "thief_Bip01_L_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.31f, 0.3f, 0.7f, 20, "thief_Bip01_L_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.32f, 0.3f, 0.7f, 20, "thief_Bip01_L_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.33f, 0.3f, 0.7f, 20, "thief_Bip01_L_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.34f, 0.3f, 0.7f, 20, "thief_Bip01_L_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.35f, 0.3f, 0.7f, 20, "thief_Bip01_L_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.36f, 0.3f, 0.7f, 20, "thief_Bip01_L_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.37f, 0.3f, 0.7f, 20, "thief_Bip01_L_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.38f, 0.3f, 0.7f, 20, "thief_Bip01_L_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),
			EMIT_DAMAGE_TO_ENEMY_COLLISION_EVENT(1.39f, 0.35f, 0.7f, 20, "thief_Bip01_L_Hand", CVector3(0.0f, 0.0f, 0.0f), 2),

			END_ANIMATION_EVENT(),
		},
		//AnimationDamage
		{
			END_ANIMATION_EVENT(),
		},
		//AnimationDeath
		{
			END_ANIMATION_EVENT(),
		},
	};
}
AnimationEvent hoge[] = {
	END_ANIMATION_EVENT(),
	END_ANIMATION_EVENT(),
};
/*!
* @brief	�J�n
*/
void Player::Start()
{
	SkinModelDataResources().Load(skinModelData, "Assets/modelData/Player.X", &animation);
	normalMap.Load("Assets/modelData/Thethief_N.tga");
	specMap.Load("Assets/modelData/Thethief_S.tga");
	weaponNormalMap.Load("Assets/modelData/Thethief_wuqi_N.tga");
	weaponSpecMap.Load("Assets/modelData/Thethief_wuqi_S.tga");
	//�̂̃}�e���A�����擾�B
	CSkinModelMaterial* mat = skinModelData.GetBody()->FindMaterial("Thethief_D.tga");
	mat->SetTexture("g_normalTexture", &normalMap );
	mat->SetTexture("g_speculerMap", &specMap);
	//����̃}�e���A�����擾�B
	mat = skinModelData.GetBody()->FindMaterial("Thethief_wuqi_D.tga");
	mat->SetTexture("g_normalTexture", &weaponNormalMap);
	mat->SetTexture("g_speculerMap", &weaponSpecMap);

	skinModel.Init(skinModelData.GetBody());
	skinModel.SetLight(&light);
	skinModel.SetHasNormalMap(true);
	skinModel.SetHasSpeculerMap(true);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);
	skinModel.SetFresnelFlag(true);
	skinModel.SetReflectionCasterFlag(true);

	light.SetDiffuseLightDirection(0, CVector3(0.707f, 0.0f, -0.707f));
	light.SetDiffuseLightDirection(1, CVector3(-0.707f, 0.0f, -0.707f));
	light.SetDiffuseLightDirection(2, CVector3(0.0f, 0.707f, -0.707f));
	light.SetDiffuseLightDirection(3, CVector3(0.0f, -0.707f, -0.707f));


	light.SetDiffuseLightColor(0, CVector4(0.2f, 0.2f, 0.2f, 10.0f));
	light.SetDiffuseLightColor(1, CVector4(0.2f, 0.2f, 0.2f, 10.0f));
	light.SetDiffuseLightColor(2, CVector4(0.2f, 0.2f, 0.2f, 10.0f));
	light.SetDiffuseLightColor(3, CVector4(0.2f, 0.2f, 0.2f, 10.0f));
	light.SetAmbinetLight(CVector3(0.4f, 0.4f, 0.4f));

	light.SetLimLightColor(CVector4(0.6f, 0.6f, 0.6f, 1.0f));
	light.SetLimLightDirection(CVector3(0.0f, 0.0f, -1.0f));

	isPointLightOn = false;
	UpdatePointLightPosition();

	PlayAnimation(AnimationInvalid, 0.0f);
	rotation = CQuaternion::Identity;
	
	CVector3 lightPos = CVector3(0.0f, 25.5f, 24.5f);
	ShadowMap().SetLightPosition(lightPos);
	ShadowMap().SetLightTarget(position);
	toLightPos.Subtract(lightPos, position);
	ShadowMap().SetCalcLightViewFunc(CShadowMap::enCalcLightViewFunc_PositionTarget);
	state = enStateStand;

	characterController.Init(0.4f, 0.3f, position);
	toLampLocalPos.Set( 0.0f, 0.5f, 0.2f);
	InitBattleSeats();
	//g_physicsWorld->AddRigidBody(&rigidBody);
	animation.SetAnimationEndTime(AnimationAttack_00, 0.63333f);
	animation.SetAnimationEndTime(AnimationAttack_01, 0.76666f);
	animation.SetAnimationLoopFlag(AnimationJump, false);
	animation.SetAnimationLoopFlag(AnimationAttack_00, false);
	animation.SetAnimationLoopFlag(AnimationAttack_01, false);
	animation.SetAnimationLoopFlag(AnimationAttack_02, false);
	animation.SetAnimationLoopFlag(AnimationDamage, false);
	nextAttackAnimNo = AnimationInvalid;
	reqAttackAnimNo = AnimationInvalid;

	//�A�j���[�V�����C�x���g�R���g���[���̏������B
	animationEventController.Init(
		&skinModel, 
		&animation, 
		animationEventGroupTbl, 
		sizeof(animationEventGroupTbl)/sizeof(animationEventGroupTbl[0])
	);
}
void Player::Update()
{
	CVector3 nextPosition = position;
	
	const float MOVE_SPEED = 7.0f;
	if (state == enStateRun || state == enStateStand) {
		CVector3 moveSpeed = characterController.GetMoveSpeed();
		if (Pad(0).IsTrigger(enButtonRB3)) {
			isPointLightOn = !isPointLightOn;
		}
		if (Pad(0).IsPress(enButtonA)) {
			//A�{�^���������ꂽ�B
			//�ԂƂ̋����𒲂ׂ�B
			CVector3 diff = g_car->GetPosition();
			diff.Subtract(position);
			if (diff.Length() < 2.0f) {
				//�ԂƂ̋�����2m�ȓ��B
				state = enState_RideOnCar;
				skinModel.SetShadowReceiverFlag(false);
				skinModel.SetShadowCasterFlag(false);
				g_car->SetRideOnFlag(true);
				g_camera->SetCar(g_car);
				return;
			}
			else if(!characterController.IsJump()){
				//�ԂƂ̋���������Ă�����W�����v�B
				moveSpeed.y = 8.0f;
				characterController.Jump();
			}
		}
		//���肩������Ԃ̎��B
		CVector3 moveDirLocal;
		moveDirLocal.y = 0.0f;
		moveDirLocal.x = Pad(0).GetLStickXF();
		moveDirLocal.z = Pad(0).GetLStickYF();
		const CMatrix& mViewInv = g_camera->GetCamera().GetViewMatrixInv();
		//�J������Ԃ��猩���������̃x�N�g�����擾�B
		CVector3 cameraZ;
		cameraZ.x = mViewInv.m[2][0];
		cameraZ.y = 0.0f;		//Y������Ȃ��B
		cameraZ.z = mViewInv.m[2][2];
		cameraZ.Normalize();	//Y����ł������Ă���̂Ő��K������B
								//�J�������猩���������̃x�N�g�����擾�B
		CVector3 cameraX;
		cameraX.x = mViewInv.m[0][0];
		cameraX.y = 0.0f;		//Y���͂���Ȃ��B
		cameraX.z = mViewInv.m[0][2];
		cameraX.Normalize();	//Y����ł������Ă���̂Ő��K������B

		CVector3 moveDir;
		moveDir.x = cameraX.x * moveDirLocal.x + cameraZ.x * moveDirLocal.z;
		moveDir.y = 0.0f;	//Y���͂���Ȃ��B
		moveDir.z = cameraX.z * moveDirLocal.x + cameraZ.z * moveDirLocal.z;

		moveSpeed.x = moveDir.x * MOVE_SPEED;
		moveSpeed.z = moveDir.z * MOVE_SPEED;
		
		if (moveDir.LengthSq() > 0.0001f) {
			rotation.SetRotation(CVector3::Up, atan2f(moveDir.x, moveDir.z));
			//�����ԂɑJ�ځB
			state = enStateRun;
		}
		else {
			//������ԁB
			state = enStateStand;
		}
		characterController.SetMoveSpeed(moveSpeed);
		characterController.Execute();
		
		if (Pad(0).IsTrigger(enButtonX) && !characterController.IsJump()) {
			nextAttackAnimNo = AnimationAttack_00;
			state = enState_Attack;
		}
	}
	else if (state == enState_RideOnCar) {
		ShadowMap().SetLightTarget(g_car->GetPosition());
		CVector3 lightPos;
		lightPos.Add(g_car->GetPosition(), toLightPos);
		ShadowMap().SetLightPosition(lightPos);
		if (g_car->GetMoveSpeed().Length() < 0.1f) {
			//�Ԃ���~��ԁB
			if (Pad(0).IsPress(enButtonB)) {
				//�~�ԁB
				g_camera->SetCar(NULL);
				g_car->SetRideOnFlag(false);
				skinModel.SetShadowReceiverFlag(true);
				skinModel.SetShadowCasterFlag(true);
				position = g_car->GetPosition();
				state = enStateStand;
			}
		}
	}
	else if (state == enState_Attack) {
		//�ړ����s�^���Ď~�܂�ƋC������邢�̂�
		CVector3 moveSpeed = characterController.GetMoveSpeed();
		moveSpeed.Scale(0.8f);
		characterController.SetMoveSpeed(moveSpeed);
		characterController.Execute();
		int currentAnimNo = animation.GetPlayAnimNo();
		if (!animation.IsPlay() && nextAttackAnimNo == AnimationInvalid) {
			state = enStateStand;
		}
		else if (
				Pad(0).IsTrigger(enButtonX) 
				&& currentAnimNo >= AnimationAttack_Start
				&& currentAnimNo < AnimationAttack_End
				&& currentAnimNo == reqAttackAnimNo
			) {
			//�R���{�����B
			nextAttackAnimNo = (AnimationNo)(animation.GetPlayAnimNo() + 1);
		}
	}
	position = characterController.GetPosition();

	//�|�C���g���C�g�̈ʒu���X�V�B
	UpdatePointLightPosition();
	//�A�j���[�V�����R���g���[���B
	AnimationControl();
	//�o�g���p�̃V�[�g�̍X�V�B
	UpdateBattleSeats();
	//�A�j���[�V�����C�x���g�R���g���[���̎��s�B
	animationEventController.Update();

	ShadowMap().SetLightTarget(position);
	CVector3 lightPos;
	lightPos.Add(position, toLightPos);
	ShadowMap().SetLightPosition(lightPos);

	skinModel.Update(position, rotation, CVector3::One);
	
	
	lastFrameState = state;
}
/*!
* @brief	�|�C���g���C�g�̈ʒu���X�V�B
*/
void Player::UpdatePointLightPosition()
{
	if (isPointLightOn) {
		pointLightColor.Set(0.9f, 0.75f, 0.6f, 1.0f);
	}
	else {
		pointLightColor = CVector4(0.0f, 0.0f, 0.0f, 0.0f);
	}
	light.SetPointLightColor(pointLightColor);
	pointLightPosition = toLampLocalPos;
	CMatrix mWorld = skinModel.GetWorldMatrix();
	mWorld.Mul(pointLightPosition);
	light.SetPointLightPosition(pointLightPosition);
}
/*!
* @brief	�A�j���[�V�����Đ��B
*/
void Player::PlayAnimation(AnimationNo animNo, float interpolateTime)
{
	if (animation.GetPlayAnimNo() != animNo && animNo != AnimationInvalid) {
		//�ʂ̃A�j���[�V����
		animation.PlayAnimation(animNo, interpolateTime);
	}
}
/*!
* @brief	�A�j���[�V�����R���g���[���B
*/
void Player::AnimationControl()
{
	if (characterController.IsJump()) {
		PlayAnimation(AnimationJump, 0.05f);
	}else{
		if (state == enStateRun) {
			if (characterController.GetMoveSpeed().LengthSq() > RUN_THREADHOLD_SQ) {
				//����A�j���[�V�����𗬂��B
				PlayAnimation(AnimationRun, 0.1f);
			}
			else {
				//�����A�j���[�V�����B
				PlayAnimation(AnimationWalk, 0.1f);
			}
		}
		else if (state == enStateStand) {
			//�����A�j���[�V�����𗬂��B
			PlayAnimation(AnimationStand, 0.3f);
		}
		else if (state == enState_Attack) {
			if (nextAttackAnimNo == AnimationAttack_Start) {
				//�U���J�n�B
				PlayAnimation(nextAttackAnimNo, 0.1f);
				reqAttackAnimNo = nextAttackAnimNo;
				nextAttackAnimNo = AnimationInvalid;
			}else if( nextAttackAnimNo != AnimationInvalid ){
				//�A���̃A�j���[�V���������N�G�X�g�L���[�ɐςށB
				animation.PlayAnimationQueue(nextAttackAnimNo, 0.05f);
				reqAttackAnimNo = nextAttackAnimNo;
				nextAttackAnimNo = AnimationInvalid;
			}
		}
	}
	animation.Update(GameTime().GetFrameDeltaTime());
}
/*!
* @brief	�o�g���Ŏg�p����V�[�g���������B
*/
void Player::InitBattleSeats()
{
	float angleBase = 2.0f * CMath::PI / NUM_BATTLE_SEAT;
	for (int i = 0; i < NUM_BATTLE_SEAT; i++) {
		battleSeats[i].seatNo = i;
		battleSeats[i].isUse = false;
		battleSeats[i].localPosition.x = sinf(angleBase * i) * 1.5f;
		battleSeats[i].localPosition.y = 0.0f;
		battleSeats[i].localPosition.z = cosf(angleBase * i) * 1.5f;
		battleSeats[i].position.Add(battleSeats[i].localPosition, position);
	}
}
/*!
* @brief	�o�g���Ŏg�p����V�[�g���X�V�B
*/
void Player::UpdateBattleSeats()
{
	for (auto& seat : battleSeats) {
		seat.position.Add(seat.localPosition, position);
	}
}
/*!
* @brief	���g�p�̃V�[�g�������B
*@param[in]	pos		���g�p�̃V�[�g�̒����炱�̍��W�Ɉ�ԋ߂��V�[�g��Ԃ��܂��B
*@return		���g�p�̃V�[�g���Ȃ��ꍇ��NULL���Ԃ��Ă���B
*/
Player::SBattleSeat* Player::FindUnuseSeat(const CVector3& pos)
{
	float dist = FLT_MAX;
	float distTmp;
	SBattleSeat* result = NULL;
	for (auto& seat : battleSeats) {
		if (!seat.isUse) {
			//���g�p�B
			CVector3 diff;
			diff.Subtract(seat.position, pos);
			distTmp = diff.LengthSq();
			if (distTmp < dist) {
				dist = distTmp;
				result = &seat;
			}
		}
	}
	return result;
}
/*!
* @brief	�`��B
*/
void Player::Render(CRenderContext& renderContext)
{
#ifdef ENEMY_TEST
	return;
#endif
	if (state != enState_RideOnCar) {
		//�Ԃɏ���Ă���Ƃ��͔�\���ɂ���B
		skinModel.Draw(renderContext, g_camera->GetCamera().GetViewMatrix(), g_camera->GetCamera().GetProjectionMatrix());
	}
}