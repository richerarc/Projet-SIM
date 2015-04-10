#include <map>

class Lecteur {
private:
	std::map<const char*, Mix_Chunk*> sons;
	std::map<const char*, int> chaines;
	std::map<const char*, Mix_Music*> musiques;
public:
	Lecteur(){
		Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048);
	}
	
	~Lecteur(){
		for (auto it: sons){
			Mix_FreeChunk(it.second);
		}
		for (auto it: musiques){
			Mix_FreeMusic(it.second);
		}
		Mix_CloseAudio();
	}
	
	void allouerChaines(int chaine){
		Mix_AllocateChannels(chaine);
		chaines["toutes"] = -1;
	}
	
	void volume(const char* nom, int volume){
		Mix_Volume(chaines[nom], volume);// "toutes" pour toute les chaines
	}
	
	void creerChaine(int chaine, const char* nom){
		chaines[nom] = chaine;
	}
	
	void jouerSon(const char* nom, int repetitions, int ticksFondu, int ticksDuree){
		Mix_FadeInChannelTimed(chaines[nom], sons[nom], repetitions, ticksFondu, ticksDuree); // "toutes" pour toute les chaines et -1 pout durée max
	}
	
	void arreterSon(const char* nom, int ticksFondu){
		Mix_FadeOutChannel(chaines[nom], ticksFondu); // "toutes" pour toute les chaines
	}
	
	void arretNetSon(const char* nom){
		Mix_HaltChannel(chaines[nom]); // "toutes" pour toute les chaines
	}
	
	int sonEnEcoute(const char* nom){
		return Mix_Playing(chaines[nom]);
	}
	
	int sonEnPause(const char* nom){
		return Mix_Paused(chaines[nom]);
	}
	
	void ajouterSon(const char* chemin, const char* nom){
		sons[nom] = Mix_LoadWAV(chemin);
	}
	
	void jouerMusique(const char* nomMusique, int repetitions, int ticksFondu){
		Mix_FadeInMusic(musiques[nomMusique], repetitions, ticksFondu); // "toutes" pour toute les chaines et -1 pout durée max
	}
	
	void arreterMusique(int ticksFondu){
		Mix_FadeOutMusic(ticksFondu); // "toutes" pour toute les chaines
	}
	
	void arretNetMusique(){
		Mix_HaltMusic(); // "toutes" pour toute les chaines
	}
	
	int musiqueEnEcoute(){
		return Mix_PlayingMusic();
	}
	
	int musiqueEnPause(){
		return Mix_PausedMusic();
	}
	
	void ajouterMusique(const char* chemin, const char* nom){
		musiques[nom] = Mix_LoadMUS(chemin);
	}
};
