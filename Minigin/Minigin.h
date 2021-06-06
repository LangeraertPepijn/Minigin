#pragma once
struct SDL_Window;


class Minigin
{
public:
	void Initialize();
	void LoadGame();
	void Cleanup();
	void Run();
protected:
	void virtual UserInitialize()=0;
 	void virtual UserLoadGame()=0;
 	void virtual UserUpdate(float)=0;
 	void virtual UserRender()=0;
	void virtual UserCleanUp()=0;
	void Quit();
	SDL_Window* m_Window{};
private:
	static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
	bool* m_Quit{};
};
