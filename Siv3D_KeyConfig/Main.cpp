
#include"KeyConfig.hpp"
#include"KeyManager.hpp"

class SampleKeyConfig :public s3dkc::KeyManager
{
private:
	Font m_font;
	s3dkc::KeyConfig m_config;
	std::pair<uint32, uint32> m_currentSelect;

	//選択中のタグ取得
	const String getCurrentTag()const
	{
		uint32 i = 0;
		for (auto& elm : this->getKeys())
		{
			if (m_currentSelect.first == i)
			{
				return elm.first;
			}
			++i;
		}
		return L"";
	}
	void select()
	{

		if (Input::KeyUp.clicked)
		{
			if (m_currentSelect.first > 0)
				m_currentSelect.first--;
		}
		else if (Input::KeyDown.clicked)
		{
			if (m_currentSelect.first < this->getKeys().size() - 1)
			{
				m_currentSelect.first++;
			}

		}
		if (Input::KeyLeft.clicked)
		{
			if (m_currentSelect.second > 0)
				m_currentSelect.second--;
		}
		else if (Input::KeyRight.clicked)
		{
			if (m_currentSelect.second < this->getKeys().at(this->getCurrentTag()).size() - 1)
			{
				m_currentSelect.second++;
			}
		}

	}
public:
	SampleKeyConfig(const FilePath& path) :
		KeyManager(path),
		m_currentSelect(0, 0)
	{}


	void update()
	{
		m_config.update((*this)[this->getCurrentTag()][m_currentSelect.second]);

		if (m_config.isSetting())
			return;

		//選択中の場所変更
		this->select();

	}
	void draw()const
	{
		uint32 i = 0;
		for (auto&&elm : this->getKeys())
		{
			m_font(elm.first).drawCenter(100, 100 + i * 50);

			for (uint32 j = 0; j < elm.second.size(); ++j)
			{
				auto& key = elm.second[j];

				//色取得
				Color color = Palette::White;

				bool isSelected = i == m_currentSelect.first&&j == m_currentSelect.second;
				if (isSelected)
				{
					color = Palette::Red;
					if (m_config.isSetting() &&
						System::FrameCount() / 10 % 2 == 0)
					{
						color.a = 0;
					}
				}

				m_font(s3dkc::GetKeyName(key)).drawCenter(200 + j * 100, 100 + i * 50, color);
			}

			++i;
		}
	}
};
void Main()
{
	SampleKeyConfig keyConfig(L"keyconfig.csv");

	keyConfig.add(L"Jump", { Input::KeyZ, Input::KeyUp, Key() });
	keyConfig.add(L"Attack", { Input::KeyX, Input::KeySpace, Key() });


	while (System::Update())
	{

		keyConfig.update();

		if (keyConfig[L"Jump"].clicked)
		{
			Println(L"Jump");
		}
		if (keyConfig[L"Attack"].clicked)
		{
			Println(L"Attack");
		}


		keyConfig.draw();


	}

	keyConfig.save();
}
