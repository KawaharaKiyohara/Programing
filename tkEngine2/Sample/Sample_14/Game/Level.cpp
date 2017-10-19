#include "stdafx.h"
#include "Level.h"
#include "MapChip.h"

Level::Level()
{
}


Level::~Level()
{
	for (auto& mapChip : m_mapChipList) {
		DeleteGO(mapChip);
	}
}
/*!
*@brief	���x���̍쐬�B
*@param[in]	levelDataFilePath	�ǂݍ��ރ��x���f�[�^�̃t�@�C���p�X�B
*/
void Level::Build(const wchar_t* levelDataFilePath)
{
	//����͔z�u�f�[�^�Ƃ��ăX�P���g���𗘗p����B
	CSkeleton skeleton;
	skeleton.Load(levelDataFilePath);
	int numMapChip = skeleton.GetNumBones();
	for (int i = 1; i < numMapChip; i++) {	//0�Ԗڂ̓_�~�[�f�[�^�Ȃ̂Ŗ����B
		CBone* bone = skeleton.GetBone(i);
		//�{�[������g�嗦�A���s�ړ��A��]���擾����B
		CVector3 position, scale;
		CQuaternion rotation;
		bone->CalcWorldTRS(position, rotation, scale);
		//3dsMax�Ƃ͎����Ⴄ�̂ŁA�␳������B
		float t = position.y;
		position.y = position.z;
		position.z = -t;
		t = rotation.y;
		rotation.y = rotation.z;
		rotation.z = -t;
		//�g��ǂ����悤���˂��E�E�E

		//�{�[�������烂�f���f�[�^�̃t�@�C���p�X���쐬����B
		const wchar_t* boneName = bone->GetName();
		wchar_t modelDataFilePath[256];
		swprintf(modelDataFilePath, L"modelData/%s.cmo", boneName);
		MapChip* mapChip = NewGO<MapChip>(0);
		mapChip->Init(modelDataFilePath, position, CVector3::One, rotation);
		m_mapChipList.push_back(mapChip);
	}

}