/*!
 * @brief	���_�o�b�t�@
 */

#ifndef _TKRENDERBUFFER_H_
#define _TKRENDERBUFFER_H_

namespace tkEngine{
	enum EVertexFormat {
		eVertexFormat_xyz		= D3DFVF_XYZ,
		eVertexFormat_wyzrhw	= D3DFVF_XYZRHW,
		eVertexFormat_xyzw		= D3DFVF_XYZW,
		eVertexFormat_normal	= D3DFVF_NORMAL,
		eVertexFormat_diffuse	= D3DFVF_DIFFUSE,
		eVertexFormat_tex0		= D3DFVF_TEX0,
		eVertexFormat_tex1		= D3DFVF_TEX1,
		eVertexFormat_tex2		= D3DFVF_TEX2,
		eVertexFormat_tex3		= D3DFVF_TEX3,
		eVertexFormat_tex4		= D3DFVF_TEX4,
		eVertexFormat_tex5		= D3DFVF_TEX5,
		eVertexFormat_tex6		= D3DFVF_TEX6,
		eVertexFormat_tex7		= D3DFVF_TEX7,
		eVertexFormat_tex8		= D3DFVF_TEX8,
		eVertexFormat_invalid	= 0xffffffff,

	};
	/*!
	 * @brief	���_�o�b�t�@
	 */
	class CVertexBuffer{
	public:
		CVertexBuffer();
		~CVertexBuffer();
		/*!
		 *@brief	���_�o�b�t�@�̍쐬�B
		 *@param[in]	numVertex		���_���B
		 *@param[in]	stride			���_�X�g���C�h�B
		 *@param[in]	vertexFormat	���_�t�H�[�}�b�g�BEVertexFormat�̘_���a��n���B
		 *@param[in]	srcVertexBuffer	�\�[�X���_�o�b�t�@�B�쐬���ꂽ���_�o�b�t�@�ɃR�s�[����܂��BNULL���w��\�B
		 */
		void Create( u32 numVertex, u32 stride, u32 vertexFormat, const void* pSrcVertexBuffer );
		/*!
		 * @brief	���_�o�b�t�@�̊J���B
		 */
		void Release();
		/*!
		* @brief	LPDIRECT3DVERTEXBUFFER9���擾�B
		*/
		LPDIRECT3DVERTEXBUFFER9 GetBody()
		{
			return m_pVB;
		}
		/*!
		* @brief	���_�X�g���C�h���擾�B
		*/
		u32 GetStride() const
		{
			return m_stride;
		}
		/*!
		* @brief	���_�t�H�[�}�b�g���擾
		*/
		u32 GetVertexFormat() const
		{
			return m_vertexFormat;
		}
	private:
		LPDIRECT3DVERTEXBUFFER9	m_pVB;	//!<���_�o�b�t�@�B
		u32 m_stride;					//!<���_�X�g���C�h�B
		u32 m_numVertex;				//!<���_���B
		u32 m_size;						//!<�o�b�t�@�T�C�Y�B
		u32	m_vertexFormat;	//!<���_�t�H�[�}�b�g�B
	};
}
#endif // #define _TKRENDERBUFFER_H_