/*!
 * @brief	�v���~�e�B�u�B
 */

#ifndef _TKPRIMITIVE_H_
#define _TKPRIMITIVE_H_

#include "tkEngine/graphics/tkIndexBuffer.h"
#include "tkEngine/graphics/tkVertexBuffer.h"

namespace tkEngine{
	/*!
	 * @brief	�v���~�e�B�u�B
	 */
	class CPrimitive{
	public:
		/*!
		 * @brief	�v���~�e�B�u�^�C�v�B
		 */
		enum EType{
			eTriangleList,		//!<�g���C�A���O�����X�g�B
			eTriangleStrip,		//!<�g���C�A���O���X�g���b�v�B
			eTypeNum,
		};
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CPrimitive();
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CPrimitive();
		/*!
		 *@brief	�v���~�e�B�u�̍쐬�B
		 *@param[in]	primitiveType		�v���~�e�B�u�^�C�v�B
		 *@param[in]	numVertex			���_��
		 *@param[in]	vertexStride		���_�X�g���C�h
		 *@param[in]	pSrcVertexBuffer	�\�[�X���_�o�b�t�@�B
		 *@param[in]	numIndex			�C���f�b�N�X�̐�
		 *@param[in]	indexFormat			�C���f�b�N�X�o�b�t�@�̃t�H�[�}�b�g�B
		 *@param[in]	pSrcIndexBuffer		�\�[�X�C���f�b�N�X�o�b�t�@�B
		 */
		void Create( 
			EType 			primitiveType,
			u32 			numVertex,
			u32 			vertexStride,
			void*			pSrcVertexBuffer,
			u32 			numIndex,
			EIndexFormat	indexFormat,
			void*			pSrcIndexbuffer,
		);
		/*!
		 * @brief	�����[�X�B
		 */
		void Release();
	private:
		/*!
		 * @brief	�o���f�[�V�����`�F�b�N�B
		 */
		void CheckValidation();
	private:
		u32				m_numVertex;		//!<���_���B
		u32				m_vertexStride;		//!<���_�X�g���C�h�B
		u32				m_numIndex;			//!<�C���f�b�N�X���B
		u32				m_numPolygon;		//!<�|���S���̐��B
		CVertexBuffer	m_vertexBuffer;		//!<���_�o�b�t�@�B
		CIndexBuffer	m_indexBuffer;		//!<�C���f�b�N�X�o�b�t�@�B
	};
}
#endif // _TKPRIMITIVE_H_