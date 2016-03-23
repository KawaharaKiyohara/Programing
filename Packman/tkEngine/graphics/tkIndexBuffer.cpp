/*!
 *@brief	�C���f�b�N�X�o�b�t�@
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkIndexBuffer.h"
#include "tkEngine/tkEngine.h"

namespace tkEngine {
	CIndexBuffer::CIndexBuffer() :
		m_pIB(nullptr)
	{

	}
	CIndexBuffer::~CIndexBuffer()
	{
		Release();
	}
	void CIndexBuffer::Create(u32 size, EIndexFormat format, const void* pSrcIndexBuffer)
	{
		Release();
		LPDIRECT3DDEVICE9 d3dDevice = CEngine::GetInstance().GetD3DDevice();
		HRESULT hr = d3dDevice->CreateIndexBuffer(
			size,
			D3DUSAGE_DYNAMIC,
			(D3DFORMAT)format,
			D3DPOOL_DEFAULT,
			&m_pIB,
			nullptr
			);
		TK_ASSERT(SUCCEEDED(hr), "Failed CreateIndexBuffer!!");
		if (pSrcIndexBuffer != nullptr) {
			//�\�[�X���w�肳��Ă���B
			//�C���f�b�N�X�o�b�t�@�����b�N���ăR�s�[�B
			void* pDstIndexBuffer;
			hr = m_pIB->Lock(0, 0, &pDstIndexBuffer, D3DLOCK_DISCARD);
			TK_ASSERT(SUCCEEDED(hr), "Failed IndexBuffer Lock!!");
			//�܂���ƃR�s�[�B
			memcpy(pDstIndexBuffer, pSrcIndexBuffer, size);
			m_pIB->Unlock();
		}
	}
	void CIndexBuffer::Release()
	{
		if (m_pIB != nullptr) {
			m_pIB->Release();
			m_pIB = nullptr;
		}
	}
}