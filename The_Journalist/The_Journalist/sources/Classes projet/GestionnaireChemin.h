#include "Singleton.h"
#include <map>
#include <string>

class GestionnaireChemin : public Singleton<GestionnaireChemin>{
private:
    std::string chemin;
    std::map<char*, std::string> chemins;
public:

    void initialiser(std::string argv){
#if defined(__UNIX__)
		unsigned int posString = (argv.length() - 1);
        while (argv[posString] != '/'){
            argv.erase(posString, 1);
            posString--;
    }
#elif defined (_WIN32)
		unsigned int posString = (argv.length() - 1);
        while (argv[posString] != '\\'){
            argv.erase(posString, 1);
            posString--;
        }
#endif
        argv.append("ressources");
#if defined(__UNIX__)
        argv.append("/");
#elif defined (_WIN32)
        argv.append("\\");
#endif

        chemin = argv;
    }

   std::string obtChemin(char* nomFichier){
        if (chemins.find(nomFichier) !=  chemins.end()){
            std::string cheminFichier(this->chemin);
            cheminFichier.append(nomFichier);
            chemins[nomFichier] = cheminFichier;
        }
        return chemins[nomFichier];
    }

};
