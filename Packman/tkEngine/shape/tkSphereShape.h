/*!
 *@brief	��
 */

#ifndef _TKSPHERESHAPE_H_
#define _TKSPHERESHAPE_H_

#include "tkEngine/shape/tkShapeVertex.h"
#include "tkEngine/shape/tkShapeBase.h"

namespace tkEngine{
	/*!
	 *@brief	���B
	 */
	class CSphereShape : public CShapeBase{
	public:
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		CSphereShape();
		/*!
		 *@brief	�f�X�g���N�^
		 */
		~CSphereShape();
		/*!
		 *@brief	�J���[�X�t�B�A���쐬�B
		 *@param[in]	radius		���a�B
		 *@param[in]	grid		�O���b�h�B
		 *@param[in]	color		�J���[�B
		 *@param[in]	hasNormal	�@����ێ����Ă���H
		 */
		void Create(f32 radius, u32 grid, u32 color, bool hasNormal );
	private:
		/*!
		*@brief	�C���f�b�N�X�o�b�t�@�̒��_���쐬�B
		*@param[out]	indexBuffer		�C���f�b�N�X�o�b�t�@�B
		*@param[in]		grid			�O���b�h�B
		*/
		void CreateIndexBuffer(std::vector<u32>& indexBuffer, u32 grid);
		/*!
		*@brief	���_�o�b�t�@�̒��_���쐬�B
		*@param[out]	vertexBuffer	���_�o�b�t�@�B
		*@param[in]		radius			���a�B
		*@param[in]		grid			�O���b�h�B
		*@param[in]		color			�J���[
		*/
		template<class TVertex>
		void CreateVertexPosition(std::vector<TVertex>& vertexBuffer, f32 radius, u32 grid, u32 color);
	};
}
#endif // _TKSPHERESHAPE_H_
