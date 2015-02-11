
#[Pré]Analyse pour le projet d'intégration

##Déroulement d'une parti
Le but du jeu est de s'échaper d'un "maze" (escape game).  Le jeux se déroulera à la première personne: le personnage principal (player) débute dans une pièce, prédéfinie. En avanceant dans le jeux, le joueur sera confronté à différents choix, qui modifieront la façon  de trouver la sortie (ex. chemins plus longs, plus risqués, etc.). Le joueur aurait comme principale difficulté: de devoir s'échapper avant qu'un gaz toxique ne l'asfixie totalement (représenté par un décompte). Pour se protéger du gaz, des cartouches d'oxygènes seront disposés de façons aléatoire et qui donneront plus de temps au joueur pour atteindre sont but. La santé physique et la santé mentale seraient deux facteurs que le joueur devra surveiller. La santé physique le maintiendra en vie (évidement); la santé mentale, en se dégradant, affectera la capacité du joueur à progresser dans le jeux (ex. déplacement plus lent, moins de temps pour les puzzle/choix, etc.). Le chemin vers la sortie, sera généré aléatoirement selon une liste de pièce (pièce, couloir, cul-de-sac) prédéfinie. Des Ennemis tenteront également de ralentir le joueur et devront être éliminés a l'aide de différentes armes

##Intégration des différente matières
	Maths: À travers la programmation et dans l'implémentation de la physique.
	
	Physique: Il y aura des saut et trajectoire de projectile.
	
	Chimie: Le gaz mortel et les cartouche d'oxygène/antidotes.
	
	Philosophie: Différents choix proposé au joueur qui modifieront le cours de la partie.
	
	Anglais: Le jeux sera programmé en anglais.

	Français: Le code sera commenté en français.


##Librairie utilisé
SDL [www.libsdl.org](https://www.libsdl.org "www.libsdl.org").

OpenGl [www.opengl.org](https://www.opengl.org "www.opengl.org"). 


-On fais un escape game: le but c'est de sortir vivant et dans un ceratin laps de temps un Labyrinthe ou un Batiment selon des "salles" ou des couloirs choisis aléatoirement parmis une liste.
	- Un systeme pts de vie et de santé mentale pt pour l'éduc
	- Un gaz toxique pour la chimie ,
	- Un choix de porte éventuel pour la Philo
	-Pour la physique on peut inclure des trajectoirs de saut ou d'objets genre grenades ballon balle les collision entre différents objets.
	-Ajout d'un masque é gas ainsi que des cartouches de masque afin de stopper le timmer du gas afin de donner plus de temps au joueur pour sortir du labyrinthe. Les cartouches seront quand même rare et ne dureront pas trop longtemps. Leur durée pourrait étre générée aléatoirement. 
	-On peut inclure des Mobs qui tente de te voler de l'oxygene (Shooter) et des piéges déamorsables
	-De petis puzzles simples porraient aussi etre implémentés genre appuyer un un bouton ou tirer sur une cible pour acceder a une porte.