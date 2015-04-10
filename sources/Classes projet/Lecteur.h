#include <map>

class Lecteur {
private:
	std::map<std::string, Mix_Chunk*> sons;
	std::map<std::string, int> chaines;
	std::map<std::string, Mix_Music*> musiques;
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
	
	void volume(std::string nom, int volume){
		Mix_Volume(chaines[nom], volume);// "toutes" pour toute les chaines
	}
	
	void creerChaine(int chaine, std::string nom){
		chaines[nom] = chaine;
	}
	
	void jouerSon(std::string nom, int repetitions, int ticksFondu, int ticksDuree){
		Mix_FadeInChannelTimed(chaines[nom], sons[nom], repetitions, ticksFondu, ticksDuree); // "toutes" pour toute les chaines et -1 pout durée max
	}
	
	void arreterSon(std::string nom, int ticksFondu){
		Mix_FadeOutChannel(chaines[nom], ticksFondu); // "toutes" pour toute les chaines
	}
	
	void arretNetSon(std::string nom){
		Mix_HaltChannel(chaines[nom]); // "toutes" pour toute les chaines
	}
	
	int sonEnEcoute(std::string nom){
		return Mix_Playing(chaines[nom]);
	}
	
	int sonEnPause(std::string nom){
		return Mix_Paused(chaines[nom]);
	}
	
	void ajouterSon(std::string chemin, std::string nom){
		sons[nom] = Mix_LoadWAV(chemin.c_str());
	}
	
	void jouerMusique(std::string nomMusique, int repetitions, int ticksFondu){
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
	
	void ajouterMusique(std::string chemin, std::string nom){
		musiques[nom] = Mix_LoadMUS(chemin.c_str());
	}
};
