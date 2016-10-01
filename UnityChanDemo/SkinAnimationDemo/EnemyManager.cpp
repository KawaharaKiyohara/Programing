#include "stdafx.h"
#include "EnemyManager.h"

using namespace std;
namespace {
	struct SEnemyLocInfo {
		const char* modelName;		//���f���B
		CVector3	pos;			//���W�B
		CQuaternion	rotation;		//��]�B
	};
	SEnemyLocInfo enemyLocInfoTable[] = {
		#include "EnemyInfo.h"
	};
}
EnemyManager::EnemyManager()
{
}
EnemyManager::~EnemyManager()
{
}
void EnemyManager::Start()
{
	//�z�u��񂩂�G���\�z�B
	map<const char*, vector<SEnemyLocInfo*>*> m;
	//�������O�̃��f�����W�߂�B
	for (SEnemyLocInfo& info : enemyLocInfoTable) {
		auto& it = m.find(info.modelName);
		if (it != m.end()) {
			//���̖��O�̃��f���͓o�^�ς݁B
			it->second->push_back(&info);
		}
		else {
			//�V�K���f���B
			vector<SEnemyLocInfo*>* newList = new vector<SEnemyLocInfo*>();
			newList->push_back(&info);
			m.insert(std::pair< const char*, vector<SEnemyLocInfo*>*>(
				info.modelName,
				newList
				));
		}
	}
	
	for (auto& enemyList : m) {
		//�܂����f�������[�h����B
		
	}

}
void EnemyManager::Update()
{
}
void EnemyManager::Render(CRenderContext& renderContext) 
{
}
