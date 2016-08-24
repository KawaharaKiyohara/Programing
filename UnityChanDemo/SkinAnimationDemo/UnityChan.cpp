#include "stdafx.h"
#include "UnityChan.h"


CSkinModelData*	UnityChan::orgSkinModelData = NULL;	//�I���W�i���X�L�����f���f�[�^�B
CAnimation				*orgAnimation;			//�A�j���[�V�����B

namespace {
	const float MAX_RUN_SPEED = 0.1f;					//���j�e�B�����̑���̍ō����x�B
	const float RUN_THREADHOLD_SQ = 0.07f * 0.07f;		//����A�j���[�V�������Đ����鑬�x��臒l�B
}
/*!
 * @brief	�J�n
 */
void UnityChan::Start()
{
	if (orgSkinModelData == NULL) {
		orgSkinModelData = new CSkinModelData;
		orgAnimation = new CAnimation;
		orgSkinModelData->LoadModelData("Assets/modelData/car.X", orgAnimation);
	}
	//�I���W�i���̃��f���f�[�^����N���[�����f�����쐬�B
	skinModelData.CloneModelData(*orgSkinModelData, &animation);
	normalMap.Load("Assets/modelData/Scout_Normal.png");

	//skinModelData.LoadModelData("Assets/modelData/unity.X", NULL);
	skinModel.Init(&skinModelData);
	skinModel.SetLight(&light);
	skinModel.SetNormalMap(&normalMap);
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
	light.SetAmbinetLight(CVector3(0.2f, 0.2f, 0.2f));
	//animation.SetAnimationEndTime(AnimationRun, 0.8);
	currentAnimSetNo = AnimationInvalid;
	PlayAnimation(currentAnimSetNo);
	rotation = CQuaternion::Identity;

	
	CVector3 lightPos = CVector3(0.0f, 3.5f, 3.5f);
	ShadowMap().SetLightPosition(lightPos);
	ShadowMap().SetLightTarget(position);
	toLightPos.Subtract( lightPos, position );
	ShadowMap().SetCalcLightViewFunc(CShadowMap::enCalcLightViewFunc_PositionTarget);
	state = enStateStand;
}
/*!
 * @brief	�X�V�B
 */
void UnityChan::Update()  
{
	
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

	moveSpeed = moveDir;
	moveSpeed.Scale(0.1f);
	position.Add(moveSpeed);

	if (moveDir.LengthSq() > 0.0001f) {
		rotation.SetRotation(CVector3::Up, atan2f(moveDir.x, moveDir.z));
		//�����ԂɑJ�ځB
		state = enStateRun;
	}
	else {
		//������ԁB%
		state = enStateStand;
	}
	skinModel.Update(position, rotation, CVector3::One);
	ShadowMap().SetLightTarget(position);
	CVector3 lightPos;
	lightPos.Add(position, toLightPos);
	ShadowMap().SetLightPosition(lightPos);

	//�A�j���[�V�����R���g���[���B
	//AnimationControl();
	lastFrameState = state;
}
/*!
* @brief	�A�j���[�V�����Đ��B
*/
void UnityChan::PlayAnimation(AnimationNo animNo)
{
	if (currentAnimSetNo != animNo) {
		//�ʂ̃A�j���[�V����
		//animation.PlayAnimation(animNo, 0.1f);
		currentAnimSetNo = animNo;
	}
}
/*!
* @brief	�A�j���[�V�����R���g���[���B
*/
void UnityChan::AnimationControl()
{
	animation.Update(1.0f / 60.0f);
	if (state == enStateRun) {
		if (moveSpeed.LengthSq() > RUN_THREADHOLD_SQ) {
			//����A�j���[�V�����𗬂��B
			PlayAnimation(AnimationRun);
		}
		else {
			//�����A�j���[�V�����B
			PlayAnimation(AnimationWalk);
		}
	}
	else if(state == enStateStand) {
		//�����A�j���[�V�����𗬂��B
		PlayAnimation(AnimationStand);
	}
}
/*!
 * @brief	�`��B
 */
void UnityChan::Render( CRenderContext& renderContext ) 
{
	skinModel.Draw(renderContext, g_camera->GetCamera().GetViewMatrix(), g_camera->GetCamera().GetProjectionMatrix());
}
