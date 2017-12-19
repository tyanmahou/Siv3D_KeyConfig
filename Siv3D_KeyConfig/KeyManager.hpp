#pragma once
#include"KeyConfig.hpp"
namespace s3dkc
{

	//�d������邷KeyCombination
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
	///�L�[�}�l�[�W���[
	///</summary>
	class KeyManager
	{
		using Dictionary = std::unordered_map < String, KeyList >;
	private:
		//csv�t�@�C���̃p�X
		FilePath m_filePath;
		Dictionary m_dictionary;
	public:

		KeyManager() = default;

		KeyManager(const FilePath& path);

		virtual ~KeyManager() = default;


		/// <summary>
		/// �Ǘ�����L�[�̓o�^
		/// </summary>
		/// <param name="name">
		/// �A�N�Z�X�L�[
		/// </param>
		/// <param name="initKeys">
		/// �����̃L�[���X�g
		/// </param>
		/// <returns>
		/// �o�^�ɐ��������ꍇ true, ���łɓo�^�ς݂̏ꍇ false
		/// </returns>
		bool add(const String& name, std::initializer_list<Key> initKeys);

		/// <summary>
		/// �L�[���X�g�̎擾
		/// </summary>
		/// <param name="name">
		/// �A�N�Z�X�L�[
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
		/// ���[�h
		/// </summary>
		bool load();

		/// <summary>
		/// ���[�h
		/// </summary>
		/// <param name="path">
		/// �ǂݍ��ރt�@�C���p�X
		/// </param>
		bool load(const FilePath & path);

		/// <summary>
		/// �Z�[�u
		/// </summary>
		bool save()const;

		/// <summary>
		/// �Z�[�u
		/// </summary>
		/// <param name="path">
		/// �ۑ�����t�@�C���p�X
		/// </param>
		bool save(const FilePath & path)const;



		const Dictionary& getDictionary()const
		{
			return m_dictionary;
		}
	};

}