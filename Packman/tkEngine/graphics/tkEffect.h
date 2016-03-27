/*!
 * @brief	�V�F�[�_�[�G�t�F�N�g�B
 */
 
#ifndef _TKEFFECT_H_
#define _TKEFFECT_H_

namespace tkEngine{
	/*!
	 * @brief	�V�F�[�_�[�G�t�F�N�g�B
	 */
	class CEffect{
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CEffect(ID3DXEffect* effect);
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CEffect();
		/*!
		*@brief	�e�N�j�b�N��ݒ�B
		*@param[in]	parameterName	�p�����[�^�̖��O�B
		*@param[in]	pData			�ݒ肷��l�B
		*@param[in]	sizeInByte		�T�C�Y(�P�ʁF�o�C�g)
		*/
		void SetTechnique(tkEngine::CRenderContext& renderContext, const c8* tecName)
		{
			TK_ASSERT(tecName != nullptr, "tecName is null");
			renderContext.SetRenderCommand(CRenderCommand_EffectSetTechnique(renderContext, m_pEffect,tecName));
		}
		/*!
		 * @brief	�l��ݒ�B
		 *@param[in]	parameterName	�p�����[�^�̖��O�B
		 *@param[in]	pData			�ݒ肷��l�B
		 *@param[in]	sizeInByte		�T�C�Y(�P�ʁF�o�C�g)
		 */
		void SetValue(tkEngine::CRenderContext& renderContext, const c8* parameterName, const void* pData, u32 sizeInByte )
		{
			TK_ASSERT( m_pEffect != nullptr, "effect is null" );
			renderContext.SetRenderCommand( CRenderCommand_EffectSetValue(renderContext, m_pEffect, parameterName, pData, sizeInByte ) );
		}
		/*!
		 * @brief	�e�N�j�b�N�̓K�p���J�n�B
		 */
		void Begin(tkEngine::CRenderContext& renderContext)
		{
			TK_ASSERT(m_pEffect != nullptr, "effect is null");
			renderContext.SetRenderCommand(CRenderCommand_EffectBegin(m_pEffect));
		}
		/*!
		 * @brief	�e�N�j�b�N�̓K�p���I���B
		 */
		void End(tkEngine::CRenderContext& renderContext)
		{
			TK_ASSERT(m_pEffect != nullptr, "effect is null");
			renderContext.SetRenderCommand(CRenderCommand_EffectEnd(m_pEffect));
		}
		/*!
		 * @brief	�g�p����e�N�j�b�N�̃p�X��ݒ肵�ĕ`��J�n�B
		 */
		void BeginPass(tkEngine::CRenderContext& renderContext, s32 pass )
		{
			TK_ASSERT(m_pEffect != nullptr, "effect is null");
			renderContext.SetRenderCommand(CRenderCommand_EffectBeginPass(m_pEffect, pass));
		}
		/*!
		 * @brief	�`��I���B
		 */
		void EndPass(tkEngine::CRenderContext& renderContext)
		{
			renderContext.SetRenderCommand(CRenderCommand_EffectEndPass(m_pEffect));
		}
	private:
		ID3DXEffect*	m_pEffect;		//!<D3D�G�t�F�N�g
	};
}

#endif 
