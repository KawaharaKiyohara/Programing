/*!
 * @brief	�n�ʁB
 */

#ifndef _CGROUND_H_
#define _CGROUND_H_

#include "tkEngine/shape/tkBoxShape.h"

class CGround : public tkEngine::IGameObject{
public:
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
	 *@brief	�n�ʍ쐬�B
	 */
	void Create( float xz_size );
private:
	tkEngine::CBoxShape		m_box;	
};
#endif 