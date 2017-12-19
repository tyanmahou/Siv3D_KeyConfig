#pragma once
#include<Siv3D.hpp>

namespace s3dkc
{
	///<summary>
	///キーコンフィグクラス
	///</summary>
	class KeyConfig
	{
	public:
		enum class State
		{
			Normal,		//通常時
			IsSetting,	//セッティング中
			OnChange,	//セット完了
			OnDelete,	//設定の消去時
		};
	private:
		Key m_configStartKey, m_deleteKey;
		bool m_isSetting;

	public:

		///<summary>
		///コンストラクタ
		///</summary>
		/// <param name="configStartKey">
		/// 変更開始時に入力するキー
		/// </param>
		/// <param name="deleteKey">
		/// 設定されたキーの消去に入力するキー
		/// </param>
		KeyConfig(const Key& configStartKey=Input::KeyEnter, const Key& deleteKey = Input::KeyDelete):
			m_configStartKey(configStartKey),
			m_deleteKey(deleteKey),
			m_isSetting(false)
		{}

		/// <summary>
		/// キーコンフィグの更新
		/// </summary>
		/// <param name="key">
		/// 変更するキー
		/// </param>
		State update(Key& key);

		/// <summary>
		/// 変更中かどうか
		/// </summary>
		bool isSetting()const
		{
			return m_isSetting;
		}

	};


	/// <summary>
	/// キーの名前取得
	/// </summary>
	const String GetKeyName(const Key& key);
}