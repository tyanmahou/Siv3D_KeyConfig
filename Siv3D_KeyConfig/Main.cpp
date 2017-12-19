
# include <Siv3D.hpp>
#include"KeyConfig.hpp"
#include"KeyManager.hpp"
class SampleKeyConfig :public s3dkc::KeyManager
{
	Font m_font;
	s3dkc::KeyConfig m_config;
	std::pair<String, uint32> m_currentSelect;
public:
	SampleKeyConfig(const FilePath& path) :
		KeyManager(path)
	{}
	void init(const String& name, uint32 index)
	{
		m_currentSelect = std::make_pair(name, index);
	}
	void update()
	{

		m_config.update((*this)[m_currentSelect.first][m_currentSelect.second]);

		if (m_config.isSetting())
			return;

		auto it = this->getDictionary().find(m_currentSelect.first);
		if (Input::KeyDown.clicked)
		{
			it++;
			if (it != this->getDictionary().end())
			{
				m_currentSelect.first = (*it).first;
			}
		}
		else if (Input::KeyUp.clicked)
		{
			if (it != this->getDictionary().begin())
			{
				m_currentSelect.first = (*--it).first;
			}
		}
		if (Input::KeyLeft.clicked)
		{
			if (m_currentSelect.second > 0)
				m_currentSelect.second--;
		}
		else if (Input::KeyRight.clicked)
		{
			if (m_currentSelect.second < this->getDictionary().at(m_currentSelect.first).size() - 1)
			{
				m_currentSelect.second++;
			}
		}
	}
	void draw()const
	{
		int i = 0;
		for (auto&&elm : this->getDictionary())
		{
			m_font(elm.first).drawCenter(100, 100 + i * 50);

			for (uint32 j = 0; j < elm.second.size(); ++j)
			{
				auto&& key = elm.second[j];

				//色取得
				Color color = Palette::White;

				bool isSelected = elm.first == m_currentSelect.first&&j == m_currentSelect.second;
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

	keyConfig.add(L"Jump", { Input::KeyZ, Key(), Key() });
	keyConfig.add(L"Attack", { Input::KeyX, Key(), Key() });
	keyConfig.init(L"Jump", 0);

	using namespace s3dkc;

	//KeyConfig config;

	//Key key;

	while (System::Update())
	{
		//ClearPrint();

		//auto state = config.update(key);

		//if (state == KeyConfig::State::Normal ||
		//	state == KeyConfig::State::IsSetting&&System::FrameCount() / 10 % 2 == 0)
		//	PutText(s3dkc::GetKeyName(key)).at(Window::Center());

		//if (state == KeyConfig::State::Delete)
		//{
		//	Println(L"キーを消去しました");
		//}
		//if (state == KeyConfig::State::OnChange)
		//{
		//	Println(L"キーを変更しました");
		//}

		if (keyConfig[L"Jump"].clicked)
		{
			Println(L"Jump");
		}
		if (keyConfig[L"Attack"].clicked)
		{
			Println(L"Attack");
		}
		keyConfig.update();
		keyConfig.draw();


	}

	keyConfig.save(L"keyconfig.csv");
}
