/*!
 * @brief	ライトの管理者。
 */

#pragma once
#include "tkEngine/graphics/tkLight.h"

namespace tkEngine{
	namespace prefab {
		class CDirectionLight;
		class CPointLight;
		class CLightBase;
	}
	/*!
	 * @brief	ライトの管理者
	 * @details
	 *  インスタンス化されたCLightBaseのインスタンスはすべてCLightManagerに登録されます。
	 *  このクラスのインスタンスはCGraphicsEngineクラスのみが保持しており、その他のクラスでインスタンスを生成することはできません。
	 */
	class CLightManager{
	friend class CGraphicsEngine;
	private:
		CLightManager();
		~CLightManager();
	public:
		void Init();
		/*!
		*@brief　ライトを追加。
		*/
		void AddLight(prefab::CLightBase* light);
		/*!
		*@brief　ライトを削除。
		*/
		void RemoveLight(prefab::CLightBase* light);
		/*!
		*@brief　更新。
		*/
		void Update();
		/*!
		*@brief　描画シーケンスから呼ばれる処理。
		* ストラクチャーバッファの更新や、動的ライトのシェーダーリソースを設定する。
		*/
		void Render(CRenderContext& renderContext);
		/*!
		*@brief　１フレームの描画終了時に呼ばれる処理。
		*/
		void EndRender(CRenderContext& renderContext);
		/*!
		*@brief　ダーティフラグを立てる。
		*/
		void SetDirty()
		{
			m_isDirty = true;
		}
		/*!
		*@brief　ポイントライトのSRVを取得。
		*/
		CShaderResourceView& GetPointLightsSRV()
		{
			return m_pointLightsSB.GetSRV();
		}
		/*!
		*@brief　各タイルに含まれるポイントライトのリストのストラクチャーバッファのUAVを取得。
		*/
		CUnorderedAccessView& GetPointLightsInTileUAV()
		{
			return m_pointLightsInTileSB.GetUAV();
		}
	private:
		void InitDirectionLightStructuredBuffer();
		void InitPointLightStructuredBuffer();
		void InitLightParamConstantBuffer();
		void InitPointLightInTileStructuredBuffer();
	private:
		static const int MAX_DIRECTION_LIGHT = 8;						//!<ディレクションライトの最大数。
		static const int MAX_POINT_LIGHT = 512;							//!<ポイントライトの最大数。
		//GPUで使用するライト用のパラメータ。
		struct SLightParam {
			CVector3 eyePos;			//視線の位置。
			int numDirectionLight;		//ディレクションライトの数。
		};
		SLightParam							m_lightParam;
		CConstantBuffer						m_lightParamCB;			//!<GPUで使用するライト用のパラメータの定数バッファ。
		SDirectionLight						m_rawDirectionLights[MAX_DIRECTION_LIGHT];
		SPointLight							m_rawPointLights[MAX_POINT_LIGHT];
		std::list<prefab::CDirectionLight*>	m_directionLights;		//!<平行光源のリスト。
		CStructuredBuffer					m_directionLightSB;		//!<平行光源のリストのストラクチャーバッファ。
		std::list<prefab::CPointLight*>		m_pointLights;			//!<ポイントライトのリスト。
		CStructuredBuffer					m_pointLightsSB;		//!<ポイントライトのリストのストラクチャーバッファ。
		CStructuredBuffer					m_pointLightsInTileSB;	//!<各タイルに含まれるポイントライトのリストのストラクチャーバッファ。
		bool								m_isDirty = false;		//!<ダーティフラグ。
	};
}