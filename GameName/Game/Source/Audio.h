#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "Module.h"

#define DEFAULT_MUSIC_FADE_TIME 2.0f

struct _Mix_Music;
struct Mix_Chunk;

class Audio : public Module
{
public:

	Audio(bool isActive);

	// Destructor
	virtual ~Audio();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

	// Play a music file
	bool PlayMusic(const char* path, float fadeTime = DEFAULT_MUSIC_FADE_TIME);
	void StopMusic();

	// Load / Save
	bool LoadState(pugi::xml_node& data) override;
	bool SaveState(pugi::xml_node& data) const override;
	bool SaveConfig(pugi::xml_node& data) const override;

	// Load a WAV in memory
	unsigned int LoadFx(const char* path);

	// Play a previously loaded WAV
	bool PlayFx(unsigned int fx, int repeat = 0);

	int SetMusicVolume(int volume);
	int GetMusicVolume();
	int SetFxVolume(int volume);
	int GetFxVolume();
private:

	_Mix_Music* music;
	p2List<Mix_Chunk *>fx;

	int fxVolume;
	int musicVolume;
};

#endif // __AUDIO_H__