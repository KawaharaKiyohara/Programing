/*!
 * @brief	�u���[�B
 */

#pragma once

namespace tkEngine{
	/*!
	 * @brief	�u���[�B
	 */
	class CBlur{
	public:
		CBlur();
		~CBlur();
		void Init( int w, int h, const CTexture& srcTexture );
		void Draw(CRenderContext& renderContext);
		const CTexture* GetTexture() const
		{
			return m_rt[1].GetTexture();
		}

	private:
		CRenderTarget		m_rt[2];			//!<�K�E�V�A���u���[�̌��ʂ�`�����ރ����_�����O�^�[�Q�b�g�B
		const CTexture*		m_srcTexture;		//!<�\�[�X�ƂȂ�e�N�X�`���B
		CPrimitive			m_prim;				//!<�v���~�e�B�u�B
		CEffect*			m_effect;			//!<�G�t�F�N�g�B
		int					m_srcTexWH[2];
	};
}