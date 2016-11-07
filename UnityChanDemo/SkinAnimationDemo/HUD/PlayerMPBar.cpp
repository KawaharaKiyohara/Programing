/*!
 *@brief	�v���C���[��MP�o�[�B
 */

#include "stdafx.h"
#include "HUD/PlayerMPBar.h"
#include "Player/Player.h"

namespace {
	const CVector2 hpGaugeMaxSize = { 245.0f, 31.5f };
	const CVector2 hpBarMaxSize = { 230.5f, 14.2f };
	const CVector2 hpBarPos = { -592.95f, 278.0f };
	const CVector2 hpGaugePos = { -600.0f, 278.0f };
}
PlayerMPBar::PlayerMPBar()
{
}
PlayerMPBar::~PlayerMPBar()
{
}
void PlayerMPBar::Start()
{
	m_mpBarTex.Load("Assets/sprite/mp.png");
	m_mpGaugeTex.Load("Assets/sprite/hpsp_bar.png");

	m_mpBar.Init(&m_mpBarTex);
	m_mpGauge.Init(&m_mpGaugeTex);

	m_mpGauge.SetSize(hpGaugeMaxSize);
	m_mpBar.SetSize(hpBarMaxSize);
	//�s�{�b�g�͍������B
	m_mpBar.SetPivot({ 0.0f, 0.5f });
	m_mpGauge.SetPivot({ 0.0f, 0.5f });

	m_mpBar.SetPosition(hpBarPos);
	m_mpGauge.SetPosition(hpGaugePos);

}
void PlayerMPBar::Update()
{
	//�v���C���[�̎cHP�ɉ�����MP�o�[�̃T�C�Y��ς���B
	
	float hpRate = (float)g_player->GetMP() / (float)g_player->GetMaxMP();
	CVector2 size = hpBarMaxSize;
	size.x *= hpRate;
	m_mpBar.SetSize(size);
}
void PlayerMPBar::PostRender(CRenderContext& renderContext)
{
	m_mpGauge.Draw(renderContext);
	m_mpBar.Draw(renderContext);
}
