#pragma once
struct SDL_Window;

namespace divengine
{
	class Minigin
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();

		Minigin() = default;
		~Minigin();

		struct GameSettings
		{
			GameSettings();
			GameSettings(int screenWidth, int screenHeight):m_Width{screenWidth}, m_Height{screenHeight}{}
			int m_Width;
			int m_Height;
		};
		
	private:
	//	static const int MsPerFrame = 16; //MsPerFrame 16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};	
		GameSettings m_GameSettings;
	};
}