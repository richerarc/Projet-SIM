
#[Pré]Analyse pour le projet d'intégration

##Description du jeux

###Mise en contexte
Le but du jeu est de s'échapper d'un "maze" (Escape Game).  Le jeu se déroulera à la première personne: le personnage principal (Joueur) débute dans une pièce, prédéfinie. En avancent dans le jeu, le joueur sera confronté à différents choix, qui modifieront la façon  de trouver la sortie (ex. chemins plus longs, plus risqués, etc.). Le joueur aurait comme principale difficulté: de devoir s'échapper avant qu'un gaz toxique ne l'asphyxie totalement (représenté par un décompte). Pour se protéger du gaz, des cartouches d'oxygènes seront disposés de façon aléatoire et qui donneront plus de temps au joueur pour atteindre son but. La santé physique et la santé mentale seraient deux facteurs que le joueur devra surveiller. La santé physique le maintiendra en vie (évidement); la santé mentale, en se dégradant, affectera la capacité du joueur à progresser dans le jeu (ex. déplacement plus lent, moins de temps pour les puzzle/choix, etc.). Le chemin vers la sortie, sera généré aléatoirement selon une liste de pièce (pièce, couloir, cul-de-sac) prédéfinie.

###Histoire
Le personnage principal est un journaliste. Jeune dans le métié, et envieux d'une histoire que fera de lui un grand éditorialiste, il choisi de s'intérèsser au cas particulié d'un camps de concentration abbandonné pour y découvrir les secrets laisser par les derniers occupants, mais il sera confronté à des complications inatendu...

###Déroulement de la parti
Le joueur se réveille dans une pièce, sa santé, ça va, phsycologiquement, tout va encore bien. En avancant, le joueur fais face à différent puzzle/piège/choix. Il ouvre la première porte, une indication sur le mur lui dicte d'apuyer sur un bouton; il débare deux porte (gauche et droite), il choisi celle de gauche (pourquoi pas), au centre de la piece, une note. Il la rammase (achievement get : First object!). il continue ça progression de porte en porte, jusqu'à ce qui franchisse ce couloir, celui qui, malgré sa longueur anormalement courte, le ramène à la case départ. "mais qu'est-ce qui ce passe ici". La santé mentale du joueur en prend un coup. Ça progression pénible dans ce environement rencontre différent obstacles, dont un principal : il est entrain de se faire gazer, il doit sortir... mais il n'y arrivera peut être pas.

###Liste des Piège/puzzle/choix 
####Puzzles
Reconnecter des portes logiques (et ou xor) avec des fils receuillie en chemin.

Tir sur cible, dans le but de débaré une porte.

Limitation physique (modulation de gavité, ventilation intense) qui l'obligerons à une précision absolue.

####Pièges

Porte truqué avec un courant éléctrique. (impacte la santé physique)

Agencement de pièces et couloirs fesant un chemin circulaire, dont seulement 1 chemin peut l'en sortir (impacte la santé mentale)

Piège armé tirant un quelconque projectile.

####Choix

Menacer la vie d'un autre pour sauver la sienne.

Découvrir tout les secrets (notes), ou s'échapper au plus vite. 

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

##Programe pour la gestion de projet

GanttProject : [www.ganttproject.biz](http://www.ganttproject.biz/index.php)