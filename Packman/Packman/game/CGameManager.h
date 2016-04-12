/*!
 * @brief	�Q�[���}�l�[�W���B
 */

#ifndef _CGAMEMANAGER_H_
#define _CGAMEMANAGER_H_

#include "Packman/game/CCamera.h"
#include "tkEngine/graphics/tkLight.h"
#include "Packman/game/map/CMapBuilder.h"

class CGameManager : public tkEngine::IGameObject{
public:
	CGameManager();
	~CGameManager();
	void Start() override final;
	void Update() override final;
	void Render(tkEngine::CRenderContext& renderContext) override final;
	static CGameManager& GetInstance()
	{
		return *m_instance;
	}
	CGameCamera&  GetGameCamera()
	{
		return m_camera;
	}
	CLight& GetGroundLight()
	{
		return m_groundLight;
	}
	CLight& GetWallLight()
	{
		return m_wallLight;
	}
	CLight& GetFoodLight()
	{
		return m_foodLight;
	}
private:
	CGameCamera		m_camera;
	CLight			m_groundLight;		//�n�ʂ̃��C�g
	CLight			m_wallLight;		//�ǂ̃��C�g�B
	CLight			m_foodLight;		//�H�ו��̃��C�g�B
	static CGameManager*	m_instance;	//�B��̃C���X�^���X�B
	CMapBuilder		m_mapBuilder;
};

#endif //_CGAMEMANAGER_H_