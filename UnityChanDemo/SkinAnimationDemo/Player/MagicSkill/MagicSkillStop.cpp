/*!
 * @brief	時間操作系(時間停止)
 */

#include "stdafx.h"
#include "Player/MagicSkill/MagicSkillStop.h"
#include "Player/Player.h"
#include "Enemy/EnemyManager.h"
#include "Enemy/Enemy.h"
#include "tkEngine/Sound/tkSoundSource.h"
#include "Scene/gameScene.h"
#include "Map/Sky.h"

void MagicSkillStop::MagicSkillStopFinish::Update()
{
	float blendRate = MonochromeFilter().GetBlendRate();
	blendRate = blendRate - 4.0f * GameTime().GetFrameDeltaTime();
	

	if (blendRate < 0.0f) {
		//終わり。
		DeleteGO(this);
		MonochromeFilter().SetEnalbe(false);
	}
	else {
		MonochromeFilter().RegistMaskSkinModel([](CRenderContext& renderContext) {
			//プレイヤーをレンダリングしてマスクを作成する。
			g_player->Render(renderContext);
			for (auto& e : g_enemyManager->GetEnemyList()) {
				e->Render(renderContext);
			}
		});
		MonochromeFilter().SetBlendRate(blendRate);
	}
}
MagicSkillStop::MagicSkillStop(Player* pl) :
	IMagicSkill(pl)
{
}
MagicSkillStop::~MagicSkillStop()
{
}
void MagicSkillStop::OnChangeMagic()
{
}
void MagicSkillStop::OnStartMagic()
{
	//鼓動音を再生
	CSoundSource* s = NewGO<CSoundSource>(0);
	s->Init("Assets/Sound/heartbeat.wav");
	s->Play(false);
	g_enemyManager->SetFrameDeltaTimeMul(0.0f);
	gameScene->GetSky()->SetFrameDeltaTimeMul(0.0f);
	MonochromeFilter().SetEnalbe(true);

	auto pauseSound = [](IGameObject* go) {
		CSoundSource* s = (CSoundSource*)go;
		s->Pause();
	};
	FindGameObjectsWithTag(
		GameScene::enGameObjectTags_BGM | GameScene::enGameObjectTags_EnemySound,
		pauseSound
	);

	//終了処理が走っているかもしれないので削除。
	DeleteGO(&m_finish);
}
void MagicSkillStop::OnEndMagic()
{
	g_enemyManager->SetFrameDeltaTimeMul(1.0f);
	gameScene->GetSky()->SetFrameDeltaTimeMul(1.0f);
	//終了処理をゲームオブジェクトマネージャーに登録。
	AddGO(0, &m_finish);
	//ここでもマスクを描画しないと１フレームだけマスクがない状態で描画されてしまう。
	MonochromeFilter().RegistMaskSkinModel([](CRenderContext& renderContext) {
		//プレイヤーをレンダリングしてマスクを作成する。
		g_player->Render(renderContext);
		for (auto& e : g_enemyManager->GetEnemyList()) {
			e->Render(renderContext);
		}
	});
	auto resumeSound = [](IGameObject* go) {
		CSoundSource* s = (CSoundSource*)go;
		s->Play(s->GetLoopFlag());
	};
	FindGameObjectsWithTag(
		GameScene::enGameObjectTags_BGM | GameScene::enGameObjectTags_EnemySound,
		resumeSound
		);
}
void MagicSkillStop::OnUsingMagicSkill()
{
	float blendRate = MonochromeFilter().GetBlendRate();
	blendRate = min(1.0f, blendRate + 4.0f * GameTime().GetFrameDeltaTime());
	MonochromeFilter().SetBlendRate(blendRate);
	MonochromeFilter().RegistMaskSkinModel([](CRenderContext& renderContext){
		//プレイヤーをレンダリングしてマスクを作成する。
		g_player->Render(renderContext);
		for (auto& e : g_enemyManager->GetEnemyList()) {
			e->Render(renderContext);
		}
	});
}

