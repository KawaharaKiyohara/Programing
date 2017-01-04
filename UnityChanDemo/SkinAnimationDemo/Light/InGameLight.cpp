/*!
 * @brief	�C���Q�[�����̃��C�g�B
 */

#include "stdafx.h"
#include "Light/InGameLight.h"
#include "Scene/GameScene.h"
#include "Map/Sky.h"

InGameLight::InGameLight()
{
}
InGameLight::~InGameLight()
{
}
bool InGameLight::Start()
{
	defaultLight.SetDiffuseLightDirection(0, CVector3(0.707f, 0.0f, -0.707f));
	defaultLight.SetDiffuseLightDirection(1, CVector3(-0.707f, 0.0f, -0.707f));
	defaultLight.SetDiffuseLightDirection(2, CVector3(0.0f, 0.707f, -0.707f));
	defaultLight.SetDiffuseLightDirection(3, CVector3(0.0f, -0.707f, -0.707f));


	defaultLight.SetDiffuseLightColor(0, CVector4(0.4f, 0.4f, 0.4f, 10.0f));
	defaultLight.SetDiffuseLightColor(1, CVector4(0.4f, 0.4f, 0.4f, 10.0f));
	defaultLight.SetDiffuseLightColor(2, CVector4(0.4f, 0.4f, 0.4f, 10.0f));
	defaultLight.SetDiffuseLightColor(3, CVector4(0.4f, 0.4f, 0.4f, 10.0f));
	
	defaultLight.SetAmbinetLight(CVector3(0.2f, 0.2f, 0.2f));

	defaultLight.SetLimLightColor(CVector4(0.6f, 0.6f, 0.6f, 1.0f));
	defaultLight.SetLimLightDirection(CVector3(0.0f, 0.0f, -1.0f));
	return true;
}
void InGameLight::Update() 
{
	const CVector3& sunDir = gameScene->GetSky()->GetSunDir();

	//�������C�g���X�V�B
	CVector3 limLightDir = sunDir;
	limLightDir.Scale(-1.0f);
	defaultLight.SetLimLightDirection(limLightDir);
	//�A���r�G���g���C�g�X�V�B
	float t = max(0.0f, sunDir.Dot(CVector3::Up));

	//���z�̈ʒu����A���r�G���g���C�g���v�Z�B
	const CVector3 dayLight = CVector3(0.3f, 0.3f, 0.3f);//�����̃A���r�G���g���C�g�B
	const CVector3 nightLight = CVector3(0.07f, 0.07f, 0.07f);	//��Ԃ̃A���r�G���g���C�g�B
	CVector3 ambientLight;
	ambientLight.Lerp(t, nightLight, dayLight);
	defaultLight.SetAmbinetLight(ambientLight);
}