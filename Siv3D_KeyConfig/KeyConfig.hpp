#pragma once
#include<Siv3D.hpp>

namespace s3dkc
{
	///<summary>
	///�L�[�R���t�B�O�N���X
	///</summary>
	class KeyConfig
	{
	public:
		enum class State
		{
			Normal,		//�ʏ펞
			IsSetting,	//�Z�b�e�B���O��
			OnChange,	//�Z�b�g����
			OnDelete,	//�ݒ�̏�����
		};
	private:
		Key m_configStartKey, m_deleteKey;
		bool m_isSetting;

	public:

		///<summary>
		///�R���X�g���N�^
		///</summary>
		/// <param name="configStartKey">
		/// �ύX�J�n���ɓ��͂���L�[
		/// </param>
		/// <param name="deleteKey">
		/// �ݒ肳�ꂽ�L�[�̏����ɓ��͂���L�[
		/// </param>
		KeyConfig(const Key& configStartKey=Input::KeyEnter, const Key& deleteKey = Input::KeyDelete):
			m_configStartKey(configStartKey),
			m_deleteKey(deleteKey),
			m_isSetting(false)
		{}

		/// <summary>
		/// �L�[�R���t�B�O�̍X�V
		/// </summary>
		/// <param name="key">
		/// �ύX����L�[
		/// </param>
		State update(Key& key);

		/// <summary>
		/// �ύX�����ǂ���
		/// </summary>
		bool isSetting()const
		{
			return m_isSetting;
		}

	};


	/// <summary>
	/// �L�[�̖��O�擾
	/// </summary>
	const String GetKeyName(const Key& key);
}