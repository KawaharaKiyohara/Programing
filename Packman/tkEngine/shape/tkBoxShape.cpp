/*!
 * @brief	�{�b�N�X
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/shape/tkBoxShape.h"

namespace tkEngine{
	namespace {
	}
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	CBoxShape::CBoxShape() :
		m_isCreatePrimitive(false),
		m_pPrimitive(nullptr),
		m_position(CVector3::Zero),
		m_worldMatrix(CMatrix::Identity)
	{
	}
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	CBoxShape::~CBoxShape()
	{
		Release();
	}
	/*!
	 *@brief	�J���[�{�b�N�X���쐬�B
	 *@param[in]	size	�T�C�Y�B
	 *@param[in]	color	�J���[�B
	 */
	void CBoxShape::Create( CVector3 size, u32 color )
	{
		Release();
		if(!m_isCreatePrimitive){
			m_isCreatePrimitive;
			CVector3 halfSize = size;
			halfSize.Scale(0.5f);
			ShapeVertex_Color vertex[] = {
				//�O��
				{
					-halfSize.x, halfSize.y, -halfSize.z, 1.0f,
					color,
				},
				{
					halfSize.x, halfSize.y, -halfSize.z, 1.0f,
					color,
				},
				{
					halfSize.x, -halfSize.y, -halfSize.z, 1.0f,
					color,
				},
				{
					-halfSize.x, -halfSize.y, -halfSize.z, 1.0f,
					color,
				},
				{
					-halfSize.x, halfSize.y, -halfSize.z, 1.0f,
					color,
				},
				{
					halfSize.x, -halfSize.y, -halfSize.z, 1.0f,
					color,
				},
				//���ʁB
				{
					halfSize.x, halfSize.y, halfSize.z, 1.0f,
					color,
				},
				{
					-halfSize.x, halfSize.y, halfSize.z, 1.0f,
					color,
				},
				{
					-halfSize.x, -halfSize.y, halfSize.z, 1.0f,
					color,
				},
				{
					halfSize.x, -halfSize.y, halfSize.z, 1.0f,
					color,
				},
				{
					halfSize.x, halfSize.y, halfSize.z, 1.0f,
					color,
				},
				{
					-halfSize.x, -halfSize.y, halfSize.z, 1.0f,
					color,
				},
			};
			static u16 index[] = {
				0,1,2,3,4,5,6,7,8,9,10,11,12
			};
			m_pPrimitive = new CPrimitive;
			m_pPrimitive->Create(
				CPrimitive::eTriangleList,
				sizeof(vertex) / sizeof(vertex[0]),
				sizeof(vertex[0]),
				eVertexFormat_diffuse | eVertexFormat_xyzw,
				vertex,
				sizeof(index) / sizeof(index[0]),
				eIndexFormat16,
				index
			);
		}
	}
	/*!
	 * @brief	�����[�X�B
	 */
	void CBoxShape::Release()
	{
		if(!m_isCreatePrimitive){
			delete m_pPrimitive;
			m_pPrimitive = nullptr;
			m_isCreatePrimitive = false;
		}
	}
	/*!
	*@brief	���[���h�s��̍X�V
	*/
	void CBoxShape::UpdateWorldMatrix()
	{
	}
	/*!
	*@brief	�`��B
	*@param[in]	renderContext	�����_�����O�R���e�L�X�g�B
	*/
	void CBoxShape::Render(CRenderContext& renderContext)
	{
		renderContext.SetRenderCommand(CRenderCommand_SetFVF(m_pPrimitive->GetVertexFormat()));
		renderContext.SetRenderCommand(CRenderCommand_SetStreamSource(
			0,
			m_pPrimitive->GetVertexBuffer()
		));
		renderContext.SetRenderCommand(CRenderCommand_SetIndices(
			m_pPrimitive->GetIndexBuffer()
		));
		renderContext.SetRenderCommand(CRenderCommand_DrawIndexedPrimitive(
			m_pPrimitive
		));
	}
}
