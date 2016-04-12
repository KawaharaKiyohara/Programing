/*!
 * @brief	�v���C���[
 */

#ifndef _CPLAYER_H_
#define _CPLAYER_H_

#include "tkEngine/shape/tkSphereShape.h"

class CPlayer : public tkEngine::IGameObject{
public:
	CPlayer(){}
	~CPlayer(){}
	/*!
	 *@brief	Update�����߂ČĂ΂�钼�O�Ɉ�x�����Ă΂�鏈���B
	 */
	void Start() override final;
	/*!
	 *@brief	�X�V�����B60fps�Ȃ�16�~���b�Ɉ�x�B30fps�Ȃ�32�~���b�Ɉ�x�Ă΂��B
	 */
	void Update() override final;
	/*!
	 *@brief	�`�揈���B60fps�Ȃ�16�~���b�Ɉ�x�B30fps�Ȃ�32�~���b�Ɉ�x�Ă΂��B
	 */
	void Render(tkEngine::CRenderContext& renderContext) override final;
	/*!
	 *@brief	�\�z�B
	 *�K�����CreateShape����x�R�[�����Ă����K�v������B
	 */
	void Build( const CVector3& pos );
	/*!
	*@brief	�ړ������B
	*/
	void Move();
private:
	tkEngine::CSphereShape	m_sphere;
	CMatrix					m_wvpMatrix;			//<���[���h�r���[�v���W�F�N�V�����s��B
	tkEngine::CIDMapModel	m_idMapModel;
	CVector3				m_position;
};

#endif 