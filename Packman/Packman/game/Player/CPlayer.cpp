/*!
 * @brief	�v���C���[
 */

#include "stdafx.h"
#include "Packman/game/Player/CPlayer.h"
#include "Packman/game/CGameManager.h"

/*!
 *@brief	Update�����߂ČĂ΂�钼�O�Ɉ�x�����Ă΂�鏈���B
 */
void CPlayer::Start() 
{
	m_position = CVector3::Zero;
}
/*!
 *@brief	�X�V�����B60fps�Ȃ�16�~���b�Ɉ�x�B30fps�Ȃ�32�~���b�Ɉ�x�Ă΂��B
 */
void CPlayer::Update() 
{
	Move();
	m_sphere.SetPosition(m_position);
	m_sphere.UpdateWorldMatrix();
	CGameManager& gm = CGameManager::GetInstance();
	CMatrix mMVP = gm.GetGameCamera().GetViewProjectionMatrix();
	const CMatrix& mWorld = m_sphere.GetWorldMatrix();
	m_wvpMatrix.Mul(mWorld, mMVP);

}
/*!
*@brief	�ړ������B
*/
void CPlayer::Move()
{
}
/*!
 *@brief	�`�揈���B60fps�Ȃ�16�~���b�Ɉ�x�B30fps�Ȃ�32�~���b�Ɉ�x�Ă΂��B
 */
void CPlayer::Render(tkEngine::CRenderContext& renderContext) 
{
	CGameManager& gm = CGameManager::GetInstance();
	m_sphere.RenderLightWVP(
		renderContext,
		m_wvpMatrix,
		gm.GetFoodLight(),
		true,
		true
	);
}
/*!
 *@brief	�\�z�B
 *�K�����CreateShape����x�R�[�����Ă����K�v������B
 */
void CPlayer::Build( const CVector3& pos )
{
	m_sphere.Create(0.1f, 10, 0xffff0000, true );
}