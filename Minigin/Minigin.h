#pragma once
struct SDL_Window;


class Minigin
{
public:
	void Initialize();
	void LoadGame() const;
	void Cleanup();
	void Run();
protected:
	void virtual UserInitialize();
 	void virtual UserLoadGame()const;
 	void virtual UserUpdate(float);
	void virtual UserCleanUp();
	void Quit();
private:
	static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
	bool* m_Quit{};
	SDL_Window* m_Window{};
};
