/*!
 * @brief	�G�t�F�N�g�}�l�[�W��
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkEffectManager.h"
#include "tkEngine/graphics/tkEffect.h"
#include "tkEngine/tkEngine.h"
#include "tkEngine/util/tkUtil.h"

namespace tkEngine{
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	CEffectManager::CEffectManager()
	{
	}
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	CEffectManager::~CEffectManager()
	{
		Release();
	}
	/*!
	 *@brief	�G�t�F�N�g�̃��[�h�B
	 *@details
	 * �ǂݍ��ݍς݂̃G�t�F�N�g�̏ꍇ�̓��[�h�͍s��ꂸ�A</br>
	 * �����̃G�t�F�N�g���Ԃ��Ă��܂��B
	 *@param[in]	filePath	���[�h����G�t�F�N�g�̃t�@�C���p�X�B
	 *@return	���[�h�����G�t�F�N�g�t�@�C���B
	 */
	CEffect* CEffectManager::LoadEffect( const c8* filePath )
	{
		
		CEffect* pEffect = nullptr;
		u32 hash = CUtil::MakeHash(filePath);
		
		auto it = m_effectDictinary.find(hash);
		if (it == m_effectDictinary.end()) {
			//�V�K�B
			LPD3DXEFFECT effect;
			HRESULT hr = D3DXCreateEffectFromFile(
				CEngine::Instance().GetD3DDevice(),
				filePath,
				NULL,
				NULL,
#ifdef _DEBUG
				D3DXSHADER_DEBUG,
#else
				D3DXSHADER_SKIPVALIDATION,
#endif
				NULL,
				&effect,
				NULL
				);
			TK_ASSERT(SUCCEEDED(hr), "Failed D3DXCreateEffectFromFile");
			pEffect = new CEffect(effect);
			std::pair<u32, CEffect*> node(hash, pEffect);
			m_effectDictinary.insert(node);
		}
		else {
			//�o�^�ς݁B
			pEffect = it->second;
		}
		return pEffect;
	}
	/*!
	 * @brief	�����[�X�B
	 */
	void CEffectManager::Release()
	{
		for (auto p : m_effectDictinary) {
			delete p.second;
		}
		m_effectDictinary.clear();
	}
}