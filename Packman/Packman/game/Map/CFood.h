/*!
 * @brief	�p�b�N�}�����H�ׂ�A�C�e���B
 */

#ifndef _CFOOD_H_
#define _CFOOD_H_

#include "tkEngine/shape/tkSphereShape.h"

class CFood : public tkEngine::IGameObject{
public:
	
	void Start() override final;
	void Update() override final;
	void Render(tkEngine::CRenderContext& renderContext) override final;
	void Build( f32 radius, const CVector3& pos );
private:
	tkEngine::CSphereShape	m_sphere;
	tkEngine::CEffect*		m_pEffect;
	CMatrix					m_wvpMatrix;	//<���[���h�r���[�v���W�F�N�V�����s��B
	tkEngine::CIDMapModel	m_idMapModel;
};

#endif // _CFOOD_H_