/*!
 *@brief	�����_�����O�^�[�Q�b�g
 */
#ifndef _TKRENDERTARGET_H_
#define _TKRENDERTARGET_H_

namespace tkEngine{
	/*!
	 *@brief	�����_�����O�^�[�Q�b�g
	 */
	class CRenderTarget{
	public:
		/*!
		 *@brief	�R���X�g���N�^
		 */
		CRenderTarget();
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		~CRenderTarget();
		/*!
		 *@brief	�����_�����O�^�[�Q�b�g�̍쐬�B
		 *@param[in]	w					�����_�����O�^�[�Q�b�g�̕��B
		 *@param[in]	h					�����_�����O�^�[�Q�b�g�̍����B
		 *@param[in]	mipLevel			�~�b�v�}�b�v���x���B0���w�肵���ꍇ�̓~�b�v�}�b�v���T�|�[�g����Ă���GPU�ł�1*1�s�N�Z���܂ł̃~�b�v�}�b�v���쐬�����B
		 *@param[in]	colorFormat			�J���[�o�b�t�@�̃t�H�[�}�b�g�B
		 *@param[in]	depthStencilFormat	�[�x�X�e���V���o�b�t�@�̃t�H�[�}�b�g�B
		 *@param[in]	multiSampleType		�}���`�T���v�����O�̎�ށB
		 *@param[in]	multiSampleQuality	�}���`�T���v�����O�̃N�I���e�B�B
		 */
		void Create(
			u32 w,
			u32 h,
			u32 mipLevel,
			EFormat colorFormat,
			EFormat depthStencilFormat,
			EMultisampleType multiSampleType,
			u32 multiSampleQuality
		);
		/*!
		 *@brief	�����_�����O�^�[�Q�b�g�̔j���B
		 */
		void Release();
	private:
		LPDIRECT3DSURFACE9		m_depthSurface;		//!<�[�x�o�b�t�@�p�̃T�[�t�F�C�X
		LPDIRECT3DTEXTURE9		m_texture;			//!<�������ݐ�̃e�N�X�`���B
		LPDIRECT3DSURFACE9		m_surface;			//!<�T�[�t�F�C�X
	};
}
#endif // _TKRENDERTARGET_H_