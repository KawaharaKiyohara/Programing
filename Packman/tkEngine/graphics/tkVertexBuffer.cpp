/*!
 * @brief	���_�o�b�t�@
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/tkEngine.h"
#include "tkEngine/graphics/tkVertexBuffer.h"

namespace tkEngine{
	CVertexBuffer::CVertexBuffer() :
		m_pVB(nullptr)
	{
	}
	CVertexBuffer::~CVertexBuffer()
	{
		Release();
	}
	void CVertexBuffer::Create( u32 size, u32 format, const void* pSrcVertexBuffer )
	{
		Release();
		LPDIRECT3DDEVICE9 d3dDevice = CEngine::GetInstance().GetD3DDevice();
		HRESULT hr = d3dDevice->CreateVertexBuffer(
			size,
			D3DUSAGE_DYNAMIC,
			format,
			D3DPOOL_DEFAULT,
			&m_pVB,
			NULL
		);
		TK_ASSERT(SUCCEEDED(hr), "Failed CeateVertexBuffer!!" );
		if(pSrcVertexBuffer != nullptr){
			//�\�[�X���w�肳��Ă���B
			//���_�o�b�t�@�����b�N���ăR�s�[�B
			void* pDstVertexBuffer;
			hr = m_pVB->Lock( 0, 0, &pDstVertexBuffer, D3DLOCK_DISCARD );
			TK_ASSERT(SUCCEEDED(hr), "Failed VertexBuffer Lock!!" );
			//�܂���ƃR�s�[�B
			memcpy( pDstVertexBuffer, pSrcVertexBuffer, size );
			m_pVB->Unlock();
		}
	}
	void CVertexBuffer::Release()
	{
		if(m_pVB != nullptr){
			m_pVB->Release();
			m_pVB = nullptr;
		}
	}
}
