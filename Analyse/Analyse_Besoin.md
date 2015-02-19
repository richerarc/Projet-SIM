#Analyse pour le projet d'intégration

##Description du jeu

###Mise en contexte
Le but du jeu est de s'échapper d'un labyrinthe (Escape Game).  Le jeu se déroulera à la première personne: le personnage principal (Joueur) débute dans une pièce prédéfinie. En avançant dans le jeu, le joueur sera confronté à différents choix, qui modifieront la façon  de trouver la sortie (exemple : chemins plus longs, plus risqués, etc.). Le joueur aurait comme principale difficulté: de devoir s'échapper avant qu'un gaz toxique ne l'asphyxie totalement (représenté par un décompte). Pour se protéger du gaz, des cartouches d'oxygène seront disposées de façon aléatoire et donneront plus de temps au joueur pour atteindre son but. La santé physique et la santé mentale seraient deux facteurs que le joueur devra surveiller. La santé physique le maintiendra en vie (évidement); la santé mentale, en se dégradant, affectera la capacité du joueur à progresser dans le jeu (exemple : déplacement plus lent, moins de temps pour les puzzle/choix, etc.). Le chemin vers la sortie sera généré aléatoirement selon une liste de pièces (pièces, couloirs, culs-de-sac) prédéfinies.

###Histoire
Le personnage principal est un journaliste. Jeune dans le métier et envieux d'une histoire que fera sa renommée, il choisit de s'intéresser au cas particulier d'un camp de concentration abandonné pour y découvrir les secrets laissés par les derniers occupants, mais il sera confronté à des complications inattendues...

###Déroulement de la parti
Le joueur se réveille dans une pièce, sa santé physique est à 75% et sa santé mentale à 90%.
Dès le départ, un gaz menace de le tuer par asphyxie. Il a 2 heures (temps de jeu) pour s'échapper. Il ouvre la première porte, se retrouve dans une pièce carré et face à 3 portes. Au centre de la pièce, il y a une table sur laquelle se trouve une note (la première) et une balle de billard. Le joueur prend la note et la balle. La porte à gauche est barrée, la porte en face de lui a une croix rouge dessus et la porte de droite est... une porte. Il choisit d'aller à droite.
La porte donne sur un escalier; le joueur monte et arrive dans la pièce de départ. Le personnage est troublé il perd 20% de santé mentale. Il retourne dans la pièce à trois portes, choisit celle en face de lui (avec la croix rouge).
Il arrive dans une pièce ronde où des débris sur le sol rendent le déplacement difficile, une bibliothèque git sur le plancher et un tas de déchets se trouve devant un petit bureau. Dans la bibliothèque, le joueur trouve une autre note et, en escaladant le tas de débris, il trouve une arme à feu vide sur le bureau. Il la ramasse. 
À sa gauche se trouve une autre porte qui mène sur un long couloir. En le traversant, il voit sur le mur une indication de courant électrique. En continuant, il arrive devant le piège. Par terre se trouve une balle de fusil et il voit au loin un petit fusible qui pourrait être celui du piège. Il a le choix de passer au travers pour garder sa balle ou de tenter de désactiver le piège en tirant sa seule balle. Il tire et atteint le fusible. Par contre, c’était le mauvais fusible, le bon étant derrière lui. Il n'a plus de balle.
Il passe à travers le piège (en courant), et perd 10% de sa vie. Il accède à une pièce dans laquelle se trouve une clé derrière une vitre et où un conduit d'aération produit un fort courant d'air. Il lance la balle de billard pour casser la vitre et manque sa cible. Elle rebondit sur le mur, il la ramasse et recommence quelques fois avant d'y arriver. Il ramasse donc la clé et revient sur ses pas.
En retournant dans le couloir, le piège électrique a disparu. Il continue son chemin et arrive sur une toute autre pièce pas encore visitée. Il est encore une fois troublé et perd cette fois 10% de santé mentale. Dans cette pièce se trouve un lit. Il peut s'y étendre pour récupérer de la santé physique/mentale, mais perd du temps au compteur. Il choisit de dormir. Il perd 20 minutes (temps de jeu), sa vie a été augmentée de 10% et sa santé mentale de 30%. Comme il a dormi, il ne sera plus surpris par les étranges évènements qui se déroulent autour de lui.
Il emprunte la seule autre porte de la pièce qui le ramène encore une fois à la pièce de départ qui a changé. Sur le mur à droite se trouve une inscription:  "You got one key...". Il se dirige dans la pièce suivante (à trois portes) et se sert de la clé pour la débarrer la porte de gauche. Il hésite; il peut sortir, mais peut aussi rester et essayer d'en découvrir plus sur ce lieu étrange. Il choisit de sortir. Le jeu prend fin et affiche deux accomplissements : "First game!" et "Easy path", laissant croire que plus de notes, d’autres pièces et d’objets étaient à découvrir. 

###User Interface
####Menus
Un menu play, un menu options et un menu pause seront les différents menus principaux. Un gestionnaire d'inventaire sera aussi nécéssaire.

####GUI
Une barre de vie et une barre de santée mentale sera affiché en bas à gauche de l'écran. Une gauge de temps sera également affichée en haut de l'écran et elle représentra le temps restant pour terminer le jeu.

###Liste des pièges/puzzles/choix/objets/salles
###Génération Aléatoire du labyrinthe
À chaque nouvelle partie, on génère la pièce aléatoirement, en tenant compte de trois aspects:la chemins possibles, leur formes et leur contenu(objets et pièges). Le but est  que, d'une partie à l'autre, le joueur ait environ la même difficulté mais que les piece génerées ne soient pas les mêmes, exemple; une piece carré avec un piege quelconque mais une différente piece peut avoir le même piege. Ce qui change d'une partie a l'autre: les pieces, les puzzles et les objets dans le but de créer des parties les plus différentes possible en laissant un nombre de possibilités toujours égale. Un genre de "rogue like". Nous allons essayer de le faire à fin que ce soit équilibré pour éviter qu'un joueur se retrouve face à une partie trop facile ou trop difficile. La carte sera consitué de pièces de différente taille et de différente forme et inter-reliés par des connecteurs. L'implémentation de l'algorithme de génération du labyrinthe sera l'élément difficile, car ,tel qu'il est, il nécéssite de faire attention aux probabilitées.

####Objets
Une arme à projectiles (exemple : fusil)

Des projectiles de lancer (exemple : balles, grenades, roches)

Objets pour régénérer la santé physique/mentale (exemple : nourriture, boissons spéciales, magazines louches...)

Couteau

Objets utiles au puzzle (exemple : fils électriques, fusible, clés, et autres objets déjà nommés)

Objets à retrouver (les notes du journal)

Munitions

Nombre d'objets décris : 11

####Salles
Salle de départ : Vide avec une seule porte de sortie et une indication du danger d'asphyxie au gaz avec un minuteur.

Salles #1 : Salle rectangle avec un certain nombre de portes, qui comporte un objet fréquent (exemple : roche)

Salle #2 : Salle rectangle avec un certain nombre de portes et un puzzle/piège qui donne accès à un objet plus vital (exemple : clé)

Salle #3 : Salle ronde avec un certain nombre de portes qui comporte un objet fréquent (exemple : roche)

Salle #4 : Salle ronde avec un certain nombre de portes et un puzzle/piège qui donne accès à un objet plus vital (exemple : clé)

Salle #5 : Salle ronde ou rectangle qui possède un plancher non plat (exemple : débris au sol, plancher ondulé, de biais) et des puzzles / pièges / choix.

Salle #6 Salle avec les inscriptions qui indiquent l'avancement au joueur.

Salle de repos (avec le lit et/ou magazines louches...)

Salle de sortie : Elle possède à la fois un choix, piège et un puzzle, pour ajouter à la difficulté du jeu.

Nombre de salles décrites : 9

####Connecteurs

Couloir droit

Couloir arqué / avec un coude 

Escalier  (monte ou descend)

Trou au sol

Porte qui s'ouvre directement sur une autre pièce

Nombre de connecteurs décrits : 7

####Puzzles
Reconnecter des portes logiques (et/ou/ou exclusif) avec des fils recueillis en chemin.

Tir sur cible dans un but quelconque.

Un porte sera surmontée d'une "Balance" débalancée que nous devrons la rebalencer à l'aide d'objets trouver sur le sol de la pièce et les lancer dans les plaquettes de la balance.

Une pièce consiste à activer un levier avec un objet trouvé à travers les pièces précédentes. Deux courants d'air seront activés permettant l'accès a la porte. (le levier peut être activé à la main mais le joueur sera coincé)

Une très longue pièce consistera  en un plafond qui tombe et remonte et ou seulement quelque trous sont sécuritaires qu'il faudra traverser (exemple: https://www.youtube.com/watch?v=N2_mN5DgJaM). 

Un salle où un puzzle nécéssite de connaitre une certain code qui serait sur une note trouvé dans une salle précédente pour débloquer la porte. 

Puzzle de vitesse (ex. objet non vital à rattraper avant qu'une corde ne soit sectionnée)

Nombre de puzzles décrits: 8

####Pièges

Porte / couloir truqué(e) avec un courant électrique. (impact la santé physique)

Agencement de pièces et couloirs faisant un chemin circulaire dont seulement un chemin peut l'en sortir (impact la santé mentale)

Piège armé tirant un quelconque projectile.

Douche d'acide.

Chemin de barbelés, besoin de pince/couteau pour passer

piège à fréquence : un pendule avec une lame au bout

Nombre de pièges décrits: 6 

####Choix

Sauver quelqu'un au risque de perdre : Un homme crie à l'aide. Si vous l'aidez, cela aura pour conséquence de vous faire perdre du temps et un peu de vie. Par contre, il vous remercie en vous donnant une note et deux balles de fusil. Si vous le laissez à son sort, une porte s'ouvre où le puzzle à résoudre nécessite deux balles que vous n'avez peut-être pas et votre santé mentale baisse.

Menacer la vie d'un autre pour sauver la sienne : Un piège vous menace vous et un autre personnage. Si vous choisissez de vous en sauver, l'autre personnage fait face à une mort inévitable, mais vous pourrez continuer sans aucun dommage, sauf une baisse de santé mentale. Si vous le laissez sauf, vous risquez la mort, mais avez une chance de vous en sortir.

Découvrir tous les secrets (notes) ou s'échapper au plus vite : Si le personnage finit le jeu au plus vite, il sort sain et sauf, mais l'histoire nous dit qu'il fut ridiculisé pour n'avoir fait aucune découverte. Le joueur n'obtient aucun point moral. Si on trouve des notes, plus de points moraux seront obtenus. Si tous les secret du jeu sont mis à découvert, c'est une victoire absolue. Toutefois, en cherchant plus de secrets, le personnage augmente ses chances de mourir.

##Intégration des différentes matières
	Maths: À travers la programmation et dans l'implémentation de la physique.
	
	Physique: Il y aura des sauts, des trajectoires de projectiles, de la gravité, de la physique du vent et de la physique électrique.
	
	Chimie: Le gaz mortel, les cartouches d'oxygène et les antidotes.
	
	Philosophie: Différents choix proposés au joueur qui modifieront le cours de la partie.
	
	Anglais: La langue du jeu sera l'anglais.

	Français: Le code sera en français.


##Librairie utilisé
SDL [www.libsdl.org](https://www.libsdl.org "www.libsdl.org").

OpenGl [www.opengl.org](https://www.opengl.org "www.opengl.org"). 

##Programme pour la gestion de projet

GanttProject : [www.ganttproject.biz](http://www.ganttproject.biz/index.php)
