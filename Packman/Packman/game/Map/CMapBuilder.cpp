/*!
 * @brief	�}�b�v�\�z�����B
 */

#include "stdafx.h"
#include "Packman/game/Map/CMapBuilder.h"
#include "Packman/game/Map/CWall.h"
#include "Packman/game/Map/CFood.h"
namespace{
	const f32 GRID_SIZE = 0.2f;
	const u32 NUM_GRID = 15;
	//1�͕ǁB
	static u32 sMap[NUM_GRID][NUM_GRID] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1},
		{1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
		{1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
		{1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1},
		{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1},
		{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		
		
	};
}
CMapBuilder::CMapBuilder()
{
}
CMapBuilder::~CMapBuilder()
{
}
void CMapBuilder::Build()
{
	//�n�ʂ��쐬�B
	m_ground.Create( NUM_GRID * GRID_SIZE );
	CGameObjectManager::Instance().AddGameObject(0, &m_ground);
	//�e�X�g��
	/*CWall* wall = CGameObjectManager::Instance().NewGameObject<CWall>(0);
	wall->Build(CVector3(GRID_SIZE, GRID_SIZE, GRID_SIZE), CVector3(0, GRID_SIZE, 0));*/
	for (u32 i = 0; i < NUM_GRID; i++) {
		for (u32 k = 0; k < NUM_GRID; k++) {
			s32 x = k - NUM_GRID / 2;
			s32 z = i - NUM_GRID / 2;
			if (sMap[i][k] == 1) {
				//�ǂ��쐬�B
				CWall* wall = CGameObjectManager::Instance().NewGameObject<CWall>(0);
				wall->Build(CVector3(GRID_SIZE, GRID_SIZE, GRID_SIZE), CVector3(GRID_SIZE*x, GRID_SIZE*0.5f, GRID_SIZE*-z));
			}
			else if (sMap[i][k] == 0) {
				//�p�b�N�}���̃G�T���쐬�B
				CFood* food = CGameObjectManager::Instance().NewGameObject<CFood>(0);
				f32 radius = GRID_SIZE *0.2f;
				food->Build(radius, CVector3(GRID_SIZE*x, radius, GRID_SIZE*-z ) );
			}
		}
	}
}