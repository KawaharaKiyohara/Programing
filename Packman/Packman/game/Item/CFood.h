/*!
 * @brief	�p�b�N�}�����H�ׂ�A�C�e���B
 */

#ifndef _CFOOD_H_
#define _CFOOD_H_

#include "tkEngine/shape/tkSphereShape.h"

class CFood : public tkEngine::IGameObject{
public:
	void Awake() override final;
	void Start() override final;
	void Update() override final;
	void Render(tkEngine::CRenderContext& renderContext) override final;
	void Build( const CVector3& pos );
	static void CreateShape(float radius);
	static void ReleaseShape();
private:
	static tkEngine::CSphereShape*	m_sphere;
	CMatrix							m_wvpMatrix;			//<���[���h�r���[�v���W�F�N�V�����s��B
	tkEngine::CIDMapModel			m_idMapModel;
	CVector3						m_position;
};

#endif // _CFOOD_H_