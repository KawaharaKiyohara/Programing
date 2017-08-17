/*!
 *@brief	�X�L�����f���f�[�^�B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/tkEngine.h"
#include "tkEngine/graphics/tkAnimationClip.h"

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
		//�{�[���𔭌������Ƃ��̃R�[���o�b�N�B
		std::vector<int> localBoneIDtoGlobalBoneIDTbl; //���b�V���ɃE�F�C�g���ݒ肳��Ă���{�[�������̃{�[���z���ID����A���ׂẴ{�[���z���ID�ɕϊ�����e�[�u���B
		localBoneIDtoGlobalBoneIDTbl.reserve(512);
		auto onFindBone = [&](
			const wchar_t* boneName, 
			const VSD3DStarter::Bone* bone,
			int baseBoneNo
		) {
			int globalBoneID = m_skeleton.FindBoneID(boneName);
			if (globalBoneID == -1) {
				TK_WARNING("BoneID wasn't found!!!!");
				return;
			}
			localBoneIDtoGlobalBoneIDTbl.push_back(globalBoneID);
		};
		//�A�j���[�V�����N���b�v�𔭌������Ƃ��̃R�[���o�b�N�B
		auto onFindAnimationClip = [&](
			const wchar_t* clipName,
			const VSD3DStarter::Clip* clip, 
			const VSD3DStarter::Keyframe* keyFrame,
			int baseBoneNo
		) {
			auto it = std::find_if(
				m_animationClips.begin(),
				m_animationClips.end(),
				[clipName](auto& clip) {return clip->GetName() == clipName;}
			);
			if (it == m_animationClips.end()) {
				//�V�K
				CAnimationClipPtr animClip = std::make_unique<CAnimationClip>(
					clipName, clip, keyFrame, baseBoneNo, localBoneIDtoGlobalBoneIDTbl);
				m_animationClips.push_back(std::move(animClip));
			}
			else {
				//�����̃N���b�v�Ȃ̂ŃL�[�t���[����ǉ�����B
				(*it)->AddKeyFrame(clip->keys, keyFrame, baseBoneNo, localBoneIDtoGlobalBoneIDTbl);
			}
		};
		//�{�[���C���f�b�N�X�����������Ƃ��̃R�[���o�b�N�֐��B
		auto onFindBlendIndex = [&](auto& index){
			index.x = localBoneIDtoGlobalBoneIDTbl[index.x];
			index.y = localBoneIDtoGlobalBoneIDTbl[index.y];
			index.z = localBoneIDtoGlobalBoneIDTbl[index.z];
			index.w = localBoneIDtoGlobalBoneIDTbl[index.w];
		};
		//�X�P���g���̃f�[�^��ǂݍ��݁B
		m_skeleton.Load(filePath);
		//���f���f�[�^�����[�h�B
		m_modelDx = DirectX::Model::CreateFromCMO(
			GraphicsEngine().GetD3DDevice(), 
			filePath, 
			effectFactory, 
			false,
			false,
			onFindBone,
			onFindAnimationClip,
			onFindBlendIndex
		);
		

		return true;
	}
	void CSkinModelData::FindMesh(OnFindMesh findMesh)
	{
		for (const auto& modelMeshs : m_modelDx->meshes) {
			for (const std::unique_ptr<DirectX::ModelMeshPart>& mesh : modelMeshs->meshParts) {
				findMesh(mesh);
			}
		}
	}
}

