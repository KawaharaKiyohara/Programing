/*!
 *@brief	�X�L�����f���f�[�^�B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/tkEngine.h"

namespace tkEngine{
	
	/*!
	 *@brief
	 *  �G�t�F�N�g�t�@�N�g���B
	 */
	class CSkinModelEffectFactory : public DirectX::EffectFactory {
	public:
		CSkinModelEffectFactory(ID3D11Device* device) :
			EffectFactory(device) {}
		std::shared_ptr<DirectX::IEffect> __cdecl CreateEffect(const EffectInfo& info,  ID3D11DeviceContext* deviceContext)override
		{
			std::shared_ptr<CModelEffect> effect = std::make_shared<CSkinModelEffect>();
			if (info.enableSkinning) {
				//�X�L�j���O����B
				effect = std::make_shared<CSkinModelEffect>();
			}
			else {
				//�X�L�j���O�Ȃ��B
				effect = std::make_shared<CNonSkinModelEffect>();
			}
			
			if (info.diffuseTexture && *info.diffuseTexture)
			{
				ID3D11ShaderResourceView* texSRV;
				DirectX::EffectFactory::CreateTexture(info.diffuseTexture, deviceContext, &texSRV);
				effect->SetDiffuseTexture(texSRV);
			}
			return effect;
		}

		void __cdecl CreateTexture( const wchar_t* name,  ID3D11DeviceContext* deviceContext,  ID3D11ShaderResourceView** textureView) override
		{
			return DirectX::EffectFactory::CreateTexture(name, deviceContext, textureView);
		}
	};
	CSkinModelData::CSkinModelData()
	{
	}
	CSkinModelData::~CSkinModelData()
	{
	}
	
	bool CSkinModelData::Load(const wchar_t* filePath)
	{
		CSkinModelEffectFactory effectFactory(GraphicsEngine().GetD3DDevice());
		m_modelDx = DirectX::Model::CreateFromCMO(GraphicsEngine().GetD3DDevice(), filePath, effectFactory, false);
		return true;
	}
}

