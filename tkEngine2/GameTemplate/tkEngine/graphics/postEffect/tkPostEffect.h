/*!
 *@brief	ポストエフェクト。
 */

#pragma once

#include "tkEngine/graphics/postEffect/tkFxaa.h"
#include "tkEngine/graphics/postEffect/tkBloom.h"
#include "tkEngine/graphics/postEffect/tkTonemap.h"
#include "tkEngine/graphics/postEffect/tkDithering.h"
#include "tkEngine/graphics/tkPrimitive.h"


namespace tkEngine{
	/*!
	 *@brief	ポストエフェクト。
	 */
	class CPostEffect : Noncopyable{
	public:
		/*!
		 *@brief	コンストラクタ。
		 */
		CPostEffect();
		/*!
		 *@brief	デストラクタ。
		 */
		~CPostEffect();
		/*!
		 *@brief	開放。
		 */
		void Release();
		/*!
		 *@brief	作成。
		 *@param[in]	config		コンフィグ。
		 */
		void Create( const SGraphicsConfig& config );
		/*!
		*@brief	描画。
		*@param[in]		rc		レンダリングコンテキスト。
		*/
		void Render(CRenderContext& rc);
		/*!
		*@brief	フルスクリーン描画。
		*@param[in]		rc		レンダリングコンテキスト。
		*/
		void DrawFullScreenQuad(CRenderContext& rc);
		/*!
		*@brief	トーンマップの取得。。
		*/
		CTonemap& GetTonemap() 
		{
			return m_tonemap;
		}
	private:
		/*!
		*@brief	フルスクリーン描画用の矩形プリミティブの初期化。。
		*/
		void InitFullScreenQuadPrimitive();
	private:
		CFxaa		m_fxaa;				//!<FXAA。
		CBloom		m_bloom;			//!<BLOOM。
		CTonemap	m_tonemap;			//!<トーンマップ。
		CDithering	m_dithering;		//!<ディザリング。
		CPrimitive	m_fullscreenQuad;	//!<フルスクリーン描画用の矩形プリミティブ。
	};
}