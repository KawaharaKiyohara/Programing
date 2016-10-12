/*!
 * @brief	�^�C�v0�̓G�B
 */

#include "stdafx.h"
#include "Enemy/Enemy_00.h"
#include "Player/Player.h"
#include "Enemy/HFSM/EnemyStateSearch.h"
#include "Enemy/HFSM/EnemyStateFind.h"
#include "Enemy/HFSM/EnemyStateDamage.h"
#include "Enemy/HFSM/EnemyStateDeath.h"
#include "DamageCollisionWorld.h"

Enemy_00::Enemy_00()
{
	state = enLocalState_Search;
	initPosition = CVector3::Zero;
	moveSpeed = 0.0f;
	direction = CVector3::AxisZ;
	moveDirection = CVector3::AxisZ;
	radius = 0.0f;
	height = 0.0f;
	hp = 70;
}
Enemy_00::~Enemy_00()
{
	for (auto& state : states) {
		delete state;
	}
}

void Enemy_00::Init(const char* modelPath, CVector3 pos, CQuaternion rotation)
{
	char filePath[1024];
	sprintf(filePath, "Assets/modelData/%s.x", modelPath);
	SkinModelDataResources().Load(
		skinModelData,
		filePath,
		&animation
	);
	//�}�e���A�����擾�B
	const std::vector<CSkinModelMaterial*> materials = skinModelData.GetBody()->GetSkinModelMaterials();
	specMapList.resize(materials.size());
	normalMapList.resize(materials.size());
	int i = 0;
	for (CSkinModelMaterial* mat : materials) {
		char work[256];
		strcpy(work, mat->GetMaterialName());
		strtok(work, ".");
		sprintf(filePath, "Assets/modelData/%s_n.png", work);
		if (normalMapList[i].Load(filePath)) {
			mat->SetTexture("g_normalTexture", &normalMapList[i]);
			skinModel.SetHasNormalMap(true);
		}
		sprintf(filePath, "Assets/modelData/%s_s.png", work);
		if (specMapList[i].Load(filePath)) {
			mat->SetTexture("g_speculerMap", &specMapList[i]);
			skinModel.SetHasSpeculerMap(true);
		}

		i++;
	}

	skinModel.Init(skinModelData.GetBody());
	position = pos;
	this->rotation = rotation;

	skinModel.SetLight(&light);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);
	skinModel.SetFresnelFlag(true);

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
	PlayAnimation(enAnimWalk);
	animation.SetAnimationLoopFlag(enAnimAttack, false);
	animation.SetAnimationLoopFlag(enAnimDamage, false);
	animation.SetAnimationLoopFlag(enAnimDeath, false);
	initPosition = position;
	radius = 0.4f;
	height = 0.3f;

	characterController.Init(radius, height, position);
	InitHFSM();
}
/*!
 * @brief	HFSM���������B
 */
void Enemy_00::InitHFSM()
{
	//�T����Ԃ�ǉ��B
	states.push_back( new EnemyStateSearch(this) );
	//������Ԃ�ǉ��B
	states.push_back( new EnemyStateFind(this) );
	//�_���[�W��Ԃ�ǉ��B
	states.push_back( new EnemyStateDamage(this));
	//���S��Ԃ�ǉ��B
	states.push_back( new EnemyStateDeath(this));
	state = enLocalState_Search;
	states[state]->Enter(IEnemyState::SEnterArg());
}
void Enemy_00::Start()
{
}
void Enemy_00::Update()
{
	states[state]->Update();
	switch (state) {
	case enLocalState_Search:
	{
		CVector3 unityPos = g_player->GetPosition();
		CVector3 diff;
		diff.Subtract(unityPos, position);
		if (diff.LengthSq() < 5.0f * 5.0f) {
			//�������B
			states[state]->Leave();
			state = enLocalState_Find;
			states[state]->Enter(IEnemyState::SEnterArg());
		}
	}break;
	case enLocalState_Find:
	{
	
	}break;
	case enLocalState_Damage:
		if (!animation.IsPlay()) {
			states[state]->Leave();
			state = enLocalState_Find;
			states[state]->Enter(IEnemyState::SEnterArg());
		}
		break;
	}
	//�_���[�W����
	Damage();
	
	if (state != enLocalState_Death) {
		CVector3 speed = characterController.GetMoveSpeed();
		speed.x = moveDirection.x * moveSpeed;
		speed.z = moveDirection.z * moveSpeed;
		characterController.SetMoveSpeed(speed);
		characterController.Execute();
		position = characterController.GetPosition();

		//��]�͓K���ɁB
		float angle = atan2f(direction.x, direction.z);
		rotation.SetRotation(CVector3::AxisY, angle);
	}
	animation.Update(GameTime().GetFrameDeltaTime());
	light.SetPointLightPosition(g_player->GetPointLightPosition());
	light.SetPointLightColor(g_player->GetPointLightColor());
	
	skinModel.Update(position, rotation, CVector3::One);
}
void Enemy_00::Damage()
{
	if (state == enLocalState_Death) {
		//����ł�B
		return;
	}
	float offset = radius + height * 0.5f;
	CVector3 centerPos;
	centerPos = position;
	centerPos.y += offset;

	const DamageCollisionWorld::Collision* dmgColli = g_damageCollisionWorld->FindOverlappedDamageCollision(
		DamageCollisionWorld::enDamageToEnemy,
		centerPos,
		radius
	);
	if (!dmgColli) {
		centerPos.y += offset;
		dmgColli = g_damageCollisionWorld->FindOverlappedDamageCollision(
			DamageCollisionWorld::enDamageToEnemy,
			centerPos,
			radius
			);
	}
	if (dmgColli != NULL && states[state]->IsPossibleApplyDamage(dmgColli) ) {
		//�_���[�W��H����Ă���B
		hp -= dmgColli->damage;
		if (hp < 0) {
			//���S�B
			states[state]->Leave();
			state = enLocalState_Death;
			states[state]->Enter(IEnemyState::SEnterArg());
		}
		else {
			states[state]->Leave();
			state = enLocalState_Damage;
			IEnemyState::SEnterArg enterArg;
			enterArg.arg[0] = dmgColli->groupID;	//�_���[�W���󂯂��R���W�����̃O���[�v�h�c��n���B
			states[state]->Enter(enterArg);
		}
	}
}
void Enemy_00::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, g_camera->GetCamera().GetViewMatrix(), g_camera->GetCamera().GetProjectionMatrix());
}