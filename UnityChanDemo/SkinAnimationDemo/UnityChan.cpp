#include "stdafx.h"
#include "UnityChan.h"
#include "Car.h"
#include "Ground.h"

namespace {
	const float MAX_RUN_SPEED = 0.1f;					//���j�e�B�����̑���̍ō����x�B
	const float RUN_THREADHOLD_SQ = 0.07f * 0.07f;		//����A�j���[�V�������Đ����鑬�x��臒l�B
	//�n�ʂƂ̓����蔻��B
	struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
	{
		bool isHit;
		CVector3 hitPos;
		CVector3 startPos;
		float dist;
		CVector3 hitNormal;
		SweepResultGround()
		{
			isHit = false;
			dist = FLT_MAX;
			hitPos = CVector3::Zero;
			startPos = CVector3::Zero;
			hitNormal = CVector3::Zero;
		}

		virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			CVector3 hitNormalTmp = *(CVector3*)&convexResult.m_hitNormalLocal;
			float t = fabsf(acosf(hitNormalTmp.Dot(CVector3::Up)));
			if (t < CMath::PI * 0.3f) {
				isHit = true;
				CVector3 hitPosTmp = *(CVector3*)&convexResult.m_hitPointLocal;
				//��_�Ƃ̋����𒲂ׂ�B
				CVector3 vDist;
				vDist.Subtract(hitPosTmp, startPos);
				float distTmp = vDist.Length();
				if (distTmp < dist) {
					hitPos = hitPosTmp;
					dist = distTmp;
					hitNormal = *(CVector3*)&convexResult.m_hitNormalLocal;
				}
			}
			return 0.0f;
		}
	};
	//��
	struct SweepResultWall : public btCollisionWorld::ConvexResultCallback
	{
		bool isHit;
		CVector3 hitPos;
		CVector3 startPos;
		float dist;
		CVector3 hitNormal;
		SweepResultWall()
		{
			isHit = false;
			dist = FLT_MAX;
			hitPos = CVector3::Zero;
			startPos = CVector3::Zero;
			hitNormal = CVector3::Zero;
		}

		virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			CVector3 hitNormalTmp = *(CVector3*)&convexResult.m_hitNormalLocal;
			float t = fabsf(acosf(hitNormalTmp.Dot(CVector3::Up)));
			if (t >= CMath::PI * 0.3f) {
				isHit = true;
				CVector3 hitPosTmp = *(CVector3*)&convexResult.m_hitPointLocal;
				//��_�Ƃ̋����𒲂ׂ�B
				CVector3 vDist;
				vDist.Subtract(hitPosTmp, startPos);
				float distTmp = vDist.Length();
				if (distTmp < dist) {
					hitPos = hitPosTmp;
					dist = distTmp;
					hitNormal = *(CVector3*)&convexResult.m_hitNormalLocal;
				}
			}
			return 0.0f;
		}
	};
}
/*!
* @brief	�J�n
*/
void UnityChan::Start()
{
	SkinModelDataResources().Load(skinModelData, "Assets/modelData/Player.X", &animation);
//	normalMap.Load("Assets/modelData/utc_nomal.tga");
//	specMap.Load("Assets/modelData/utc_spec.tga");
	//skinModelData.LoadModelData("Assets/modelData/unity.X", NULL);
	skinModel.Init(skinModelData.GetBody());
	skinModel.SetLight(&light);
	skinModel.SetNormalMap(&normalMap);
	skinModel.SetSpeculerMap(&specMap);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);
	skinModel.SetFresnelFlag(true);
	skinModel.SetReflectionCasterFlag(true);

	light.SetDiffuseLightDirection(0, CVector3(0.707f, 0.0f, -0.707f));
	light.SetDiffuseLightDirection(1, CVector3(-0.707f, 0.0f, -0.707f));
	light.SetDiffuseLightDirection(2, CVector3(0.0f, 0.707f, -0.707f));
	light.SetDiffuseLightDirection(3, CVector3(0.0f, -0.707f, -0.707f));


	light.SetDiffuseLightColor(0, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(3, CVector4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbinetLight(CVector3(0.4f, 0.4f, 0.4f));

	light.SetLimLightColor(CVector4(0.6f, 0.6f, 0.6f, 1.0f));
	light.SetLimLightDirection(CVector3(0.0f, 0.0f, -1.0f));

	isPointLightOn = false;
	UpdatePointLightPosition();

	animation.SetAnimationEndTime(AnimationRun, 0.8);
	currentAnimSetNo = AnimationInvalid;
	PlayAnimation(currentAnimSetNo);
	rotation = CQuaternion::Identity;

	CVector3 lightPos = CVector3(0.0f, 25.5f, 24.5f);
	ShadowMap().SetLightPosition(lightPos);
	ShadowMap().SetLightTarget(position);
	toLightPos.Subtract(lightPos, position);
	ShadowMap().SetCalcLightViewFunc(CShadowMap::enCalcLightViewFunc_PositionTarget);
	state = enStateStand;

	characterController.Init(0.4f, position);
	toLampLocalPos.Set( 0.0f, 0.5f, 0.2f);
	InitBattleSeats();
	//g_physicsWorld->AddRigidBody(&rigidBody);
}
void UnityChan::Update()
{
	CVector3 nextPosition = position;
	CVector3 moveSpeed = characterController.GetMoveSpeed();
	const float MOVE_SPEED = 5.0f;
	if (state == enStateRun || state == enStateStand) {
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
		position = characterController.GetPosition();
		ShadowMap().SetLightTarget(position);
		CVector3 lightPos;
		lightPos.Add(position, toLightPos);
		ShadowMap().SetLightPosition(lightPos);
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
	
	skinModel.Update(position, rotation, CVector3::One);
	
	//�|�C���g���C�g�̈ʒu���X�V�B
	UpdatePointLightPosition();
	//�A�j���[�V�����R���g���[���B
	AnimationControl();
	//�o�g���p�̃V�[�g�̍X�V�B
	UpdateBattleSeats();
	lastFrameState = state;
}
/*!
* @brief	�|�C���g���C�g�̈ʒu���X�V�B
*/
void UnityChan::UpdatePointLightPosition()
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
void UnityChan::PlayAnimation(AnimationNo animNo)
{
	if (currentAnimSetNo != animNo) {
		//�ʂ̃A�j���[�V����
		animation.PlayAnimation(animNo, 0.1f);
		currentAnimSetNo = animNo;
	}
}
/*!
* @brief	�A�j���[�V�����R���g���[���B
*/
void UnityChan::AnimationControl()
{
	animation.Update(GameTime().GetFrameDeltaTime());
	if (characterController.IsJump()) {
		PlayAnimation(AnimationJump);
	}else{
		if (state == enStateRun) {
			if (characterController.GetMoveSpeed().LengthSq() > RUN_THREADHOLD_SQ) {
				//����A�j���[�V�����𗬂��B
				PlayAnimation(AnimationRun);
			}
			else {
				//�����A�j���[�V�����B
				PlayAnimation(AnimationWalk);
			}
		}
		else if (state == enStateStand) {
			//�����A�j���[�V�����𗬂��B
			PlayAnimation(AnimationStand);
		}
	}
}
/*!
* @brief	�o�g���Ŏg�p����V�[�g���������B
*/
void UnityChan::InitBattleSeats()
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
void UnityChan::UpdateBattleSeats()
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
UnityChan::SBattleSeat* UnityChan::FindUnuseSeat(const CVector3& pos)
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
void UnityChan::Render(CRenderContext& renderContext)
{
#ifdef ENEMY_TEST
	return;
#endif
	if (state != enState_RideOnCar) {
		//�Ԃɏ���Ă���Ƃ��͔�\���ɂ���B
		skinModel.Draw(renderContext, g_camera->GetCamera().GetViewMatrix(), g_camera->GetCamera().GetProjectionMatrix());
	}
}
