#include"KeyManager.hpp"

namespace s3dkc
{



	/***************************************

	KeyList

	***************************************/
	KeyList::KeyList(const std::initializer_list<Key>& initKey)
	{
		for (auto&& key : initKey)
		{
			m_keys.emplace_back(key);
		}
	}

	KeyList & KeyList::operator|=(const Key & key)
	{
		this->m_keys.emplace_back(key);
		return *this;
	}

	bool KeyList::_get_clicked()const
	{
		return s3d::AnyOf(m_keys, [](const Key& key) {return key.clicked; });
	}

	bool KeyList::_get_pressed()const
	{
		return s3d::AnyOf(m_keys, [](const Key& key) {return key.pressed; });
	}

	bool KeyList::_get_released()const
	{
		return s3d::AnyOf(m_keys, [](const Key& key) {return key.released; });
	}

	int32 KeyList::_get_num_pressed()const
	{
		int32 num = 0;

		for (auto&& key : m_keys)
		{
			num += key.pressed;
		}
		return num;
	}
	int32 KeyList::_get_pressedDuration()const
	{
		int32 duration = 0;

		for (auto&& key : m_keys)
		{
			duration = s3d::Max(duration, key.pressedDuration);
		}
		return duration;
	}


	/***************************************

	KeyManager

	***************************************/

	KeyManager::KeyManager(const FilePath & path) :
		m_filePath(path)
	{
		this->load();
	}

	bool KeyManager::add(const String & name, std::initializer_list<Key> initKeys)
	{
		if (m_dictionary.find(name) != m_dictionary.end())
		{
			return false;
		}

		m_dictionary.emplace(name, initKeys);

		return true;

	}


	bool KeyManager::load()
	{
		return this->load(m_filePath);
	}
	bool KeyManager::load(const FilePath & path)
	{
		CSVReader csv(path);
		if (!csv)return false;

		this->m_dictionary.clear();

		String name;

		for (size_t i = 0; i < csv.rows; ++i)
		{
			auto head = csv.get<String>(i, 0);
			if (head[0] == '#')
			{
				name = head.substr(1);
				this->add(name, {});
			}
			else
			{
				s3d::Key key;
				const KeyDeviceType device = static_cast<KeyDeviceType>(csv.getOr<int>(i, 0, 0));
				const uint8 userIndex = csv.getOr<uint8>(i, 1, 0);
				const uint8 code = csv.getOr<uint8>(i, 2, 0);
				if (device == KeyDeviceType::Gamepad)
				{
					key = Key(userIndex, code, Key::GamepadKeyCode{});
				}
				else if (device == KeyDeviceType::XInput)
				{
					key = Key(userIndex, code, Key::XInputKeyCode{});
				}
				else
				{
					key = Key(code, Key::VirtualKeyCode{});
				}

				m_dictionary.at(name) |= key;

			}
		}
		return true;
	}
	bool KeyManager::save()const
	{
		return this->save(m_filePath);
	}

	bool KeyManager::save(const FilePath & path)const
	{
		CSVWriter csv(path);

		if (!csv)return false;

		for (auto&& elm : m_dictionary)
		{
			csv.writeRow(L"#" + elm.first);

			for (auto&& key : elm.second)
			{
				csv.writeRow(static_cast<uint8>(key.device), key.userIndex, key.code);
			}
		}
		return true;
	}
}//namespace s3dkc