/*!
 * @brief	�p�b�N�}�����H�ׂ�A�C�e���B
 */

#include "stdafx.h"
#include "Packman/game/item/CFood.h"
#include "tkEngine/graphics/tkEffect.h"
#include "Packman/game/CGameManager.h"

CSphereShape*	CFood::m_sphere = nullptr;
void CFood::Awake()
{
	m_position = CVector3::Zero;
}
void CFood::Start()
{
}
void CFood::Update()
{
	m_sphere->SetPosition(m_position);
	m_sphere->UpdateWorldMatrix();
	CGameManager& gm = CGameManager::GetInstance();
	CMatrix mMVP = gm.GetGameCamera().GetViewProjectionMatrix();
	m_worldMatrix = m_sphere->GetWorldMatrix();
	m_wvpMatrix.Mul(m_worldMatrix, mMVP);
	m_idMapModel.SetWVPMatrix(m_wvpMatrix);
	IDMap().Entry(&m_idMapModel);
	//�v���C���[����G�܂ł̃x�N�g�����v�Z����B
	CVector3 diff;
	CVector3 playerPos = Player().GetPosition();
	diff.x = playerPos.x - m_position.x;
	diff.y = playerPos.y - m_position.y;
	diff.z = playerPos.z - m_position.z;
	//�v���C���[����G�܂ł̃x�N�g����傫���P�̃x�N�g���ɕϊ�����B
	//���̂悤�ȃx�N�g���������x�N�g���Ƃ����B�傫���������Ȃ��x�N�g���B
	//�傫���������Ȃ��x�N�g���̓x�N�g���̒����Ŋe�v�f�����Z����Ƌ��܂�B
	float L = diff.Length();
	diff.x /= L;
	diff.y /= L;
	diff.z /= L;
	//��͈ړ����x��ݒ肵�āA���̌����x�N�g���̕����ɓG�𓮂����B
	//�ړ����x��0.05���炢�ɂ��Ă݂�B
	m_position.x += diff.x * 0.05f;
	m_position.y += diff.y * 0.05f;
	m_position.z += diff.z * 0.05f;
}
void CFood::Render(tkEngine::CRenderContext& renderContext)
{
	CGameManager& gm = CGameManager::GetInstance();
	m_sphere->RenderLightWVP(
		renderContext,
		m_wvpMatrix,
		gm.GetFoodLight(),
		true,
		true,
		&m_worldMatrix
	);
}
void CFood::Build( const CVector3& pos )
{
	m_idMapModel.Create(m_sphere->GetPrimitive());
	m_position = pos;
}
void CFood::CreateShape(float radius)
{
	if (m_sphere == nullptr) {
		m_sphere = new tkEngine::CSphereShape();
		m_sphere->Create(radius * 1.5f, 10, 0xffffffff, true);
	}
}
void CFood::ReleaseShape()
{
	delete m_sphere;
	m_sphere = nullptr;
}