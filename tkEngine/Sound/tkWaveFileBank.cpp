/*!
 *@brief	�g�`�f�[�^�o���N�B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/Sound/tkWaveFile.h"
#include "tkEngine/Sound/tkWaveFileBank.h"

namespace tkEngine{
	CWaveFileBank::CWaveFileBank()
	{
	}
	CWaveFileBank::~CWaveFileBank()
	{
	}
	void CWaveFileBank::RegistWaveFile(int groupID, CWaveFilePtr waveFile)
	{
		TK_ASSERT(groupID < MAX_GROUP, "groupID is invalid");
		m_waveFileMap[groupID].insert({ waveFile->GetFilePathHash(), waveFile });
	}
	/*!
	*@brief	�����Ŏw�肵���t�@�C���p�X�̔g�`�f�[�^���o���N�ɓo�^����Ă��邩��������B
	*@param[in]	groupID		�O���[�v�h�c�B�w��ł���h�c�̍ő�l��MAX_GROUP-1�B
	*@param[in]	filePath	�t�@�C���p�X�B
	*@return �g�`�f�[�^�B�o�^����Ă��Ȃ��ꍇ��NULL���Ԃ�B
	*/
	CWaveFilePtr CWaveFileBank::FindWaveFile(int groupID, const char* filePath)
	{
		TK_ASSERT(groupID < MAX_GROUP, "groupID is invalid");
		auto value = m_waveFileMap[groupID].find(CUtil::MakeHash(filePath));
		if (value != m_waveFileMap[groupID].end()) {
			return value->second;
		}
		return CWaveFilePtr();
	}
}
