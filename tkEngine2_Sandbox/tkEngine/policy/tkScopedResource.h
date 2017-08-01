/*!
 * @brief	スコープを抜けたら自動的に開放されるリソース。
 */

#pragma once

namespace tkEngine{
	template<class T>
	class TScopedResource{
	private:
		
	public:
		T* res = nullptr;
		~TScopedResource()
		{
			if (res) {
				res->Release();
			}
		}
		
	};
}