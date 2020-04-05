#pragma once
struct SDL_Window;

namespace dae
{
	class Minigin
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();

		static const float MsPerUpdate; //MsPerFrame 16 for 60 fps, 33 for 30 fps

	private:
	//	static const int MsPerFrame = 16; //MsPerFrame 16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
	};
}