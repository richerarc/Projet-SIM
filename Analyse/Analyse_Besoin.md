
#[Pré]Analyse pour le projet d'intégration

##Déroulement d'une parti
Le but du jeu est de s'échaper d'un "maze" (escape game).  Le jeux se déroulera à la première personne: le personnage principal (player) débute dans une pièce, prédéfini. En avanceant dans le jeux, le joueur sera confronté à différents choix, qui modifierons la façons  de retrouver la sorti (ex. chemins plus longs, plus risqués, etc.). Le joueur aurait comme principale difficulté de devoir s'échapper avant qu'un gaz toxique ne l'asfixie totalement (représenter par un décompte). Pour se protéger du gaz, des cartouches d'oxygènes seront disposé de façons aléatoire et qui donneront plus de temps au joueur pour atteindre sont but. La santé physique et la santé mentale serait deux facteurs que le joueur devra surveiller. la santé physique le maintiendra en vie (évidement); la santé mentale, en se dégradant, affectera la capacité du joueur à progresser dans le jeux (ex. déplacement plus lent, moins de temps pour les puzzle/choix, etc.). Le chemin vers la sortie, sera généré aléatoirement selon une liste de pièce (pièce, couloir, cul-de-sac) prédéfinie.

##Intégration des différente matières
	Maths : à travers la programmation et dans l'implémentation de la physique.
	
	Physique : il y aura des saut et trajectoire de projectile.
	
	Chimie : Le gaz mortel et les cartouche d'oxygène/antidotes.
	
	Philosophie : Différents choix proposé au joueur qui modifierons le sort du joueur.
	
	Anglais : le jeux sera programmé en anglais.

##Librairie utilisé
SDL [www.libsdl.org](https://www.libsdl.org "www.libsdl.org").

OpenGl [www.opengl.org](https://www.opengl.org "www.opengl.org"). 





-On fais un escape game: le but c'est de sortir vivant et dans un ceratin laps de temps un Labyrinthe ou un Batiment selon des "salles" ou des couloirs choisis al�atoirement parmis une liste.
	- Un systeme pts de vie et de sant�e mentale pt pour l'�duc
	- Un gaz toxique pour la chimie ,
	- Un choix de porte �ventuel pour la Philo
	-Pour la physique on peut inclure des trajectoirs de saut ou d'objets genre grenades ballon balle les collision entre diff�rents objets.
	-Ajout d'un masque � gas ainsi que des cartouches de masque afin de stopper le timmer du gas afin de donner plus de temps au joueur pour sortir du labyrinthe. Les cartouches seront quand m�me rare et ne dureront pas trop longtemps. Leur dur�e pourrait �tre g�n�r�e al�atoirement. 
	-On peut inclure des Mobs qui tente de te voler de l'oxygene (Shooter) et des pi�ges d�amorsables
	-De petis puzzles simples porraient aussi etre impl�ment�s genre appuyer un un bouton ou tirer sur une cible pour acceder a une porte.