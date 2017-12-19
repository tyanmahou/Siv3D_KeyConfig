#pragma once
#include"KeyConfig.hpp"
namespace s3dkc
{

	//重複をゆるすKeyCombination
	class KeyList
	{
	public:

		KeyList() = default;
		KeyList(const std::initializer_list<Key>& initKey);

		auto begin()
		{
			return this->m_keys.begin();
		}
		auto end()
		{
			return this->m_keys.end();
		}
		auto begin()const
		{
			return this->m_keys.cbegin();
		}
		auto end()const
		{
			return this->m_keys.cend();
		}
		size_t size()const
		{
			return this->m_keys.size();
		}


		Key& operator[](uint32 index)
		{
			return this->m_keys.at(index);
		}
		const Key& operator[](uint32 index)const
		{
			return this->m_keys.at(index);
		}

		Property_Get(bool, clicked) const;
		Property_Get(bool, pressed) const;
		Property_Get(bool, released) const;
		Property_Get(int32, num_pressed) const;
		Property_Get(int32, pressedDuration) const;

		//Property_Get(bool, isSetting) const;

		KeyList& operator |= (const Key& key);

	private:
		s3d::Array<Key> m_keys;
	};


	///<summary>
	///キーマネージャー
	///</summary>
	class KeyManager
	{
		using Dictionary = std::unordered_map < String, KeyList >;
	private:
		//csvファイルのパス
		FilePath m_filePath;
		Dictionary m_dictionary;
	public:

		KeyManager() = default;

		KeyManager(const FilePath& path);

		virtual ~KeyManager() = default;


		/// <summary>
		/// 管理するキーの登録
		/// </summary>
		/// <param name="name">
		/// アクセスキー
		/// </param>
		/// <param name="initKeys">
		/// 初期のキーリスト
		/// </param>
		/// <returns>
		/// 登録に成功した場合 true, すでに登録済みの場合 false
		/// </returns>
		bool add(const String& name, std::initializer_list<Key> initKeys);

		/// <summary>
		/// キーリストの取得
		/// </summary>
		/// <param name="name">
		/// アクセスキー
		/// </param>
		KeyList& operator[](const String& name)
		{
			return m_dictionary.at(name);
		}
		const KeyList& operator[](const String& name)const
		{
			return m_dictionary.at(name);
		}

		/// <summary>
		/// ロード
		/// </summary>
		bool load();

		/// <summary>
		/// ロード
		/// </summary>
		/// <param name="path">
		/// 読み込むファイルパス
		/// </param>
		bool load(const FilePath & path);

		/// <summary>
		/// セーブ
		/// </summary>
		bool save()const;

		/// <summary>
		/// セーブ
		/// </summary>
		/// <param name="path">
		/// 保存するファイルパス
		/// </param>
		bool save(const FilePath & path)const;



		const Dictionary& getDictionary()const
		{
			return m_dictionary;
		}
	};

}