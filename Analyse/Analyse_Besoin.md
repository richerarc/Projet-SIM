#Analyse pour le projet d'intégration

##Description du jeu

###Mise en contexte
Le but du jeu est de s'échapper d'un labyrinthe (Escape Game).  Le jeu se déroulera à la première personne: Le personnage principal (Joueur) débute dans une pièce prédéfinie. En avançant dans le jeu, le joueur sera confronté à différents choix qui affecteront son parcours vers la sortie (exemple: chemins plus longs, plus risqués, pièges différents). Le joueur aurait comme principale difficulté de devoir s'échapper avant qu'un gaz toxique ne l'asphyxie totalement (représenté par un décompte). Pour se protéger du gaz, des cartouches d'oxygène seront disposées de façon aléatoire et donneront plus de temps au joueur pour atteindre son but. La santé physique et la santé mentale seront deux facteurs que le joueur devra surveiller. La santé physique le maintiendra en vie (évidement), alors que la santé mentale, en se dégradant, affectera la capacité du joueur à progresser dans le jeu (exemple: déplacement plus lent, moins de temps pour résoudre les casse-têtes, faire des choix). Le chemin vers la sortie sera généré aléatoirement selon une liste de pièces (pièces, couloirs, culs-de-sac) prédéfinis.

###Histoire
Le personnage principal est un journaliste. Jeune dans le métier et envieux d'une histoire qui fera sa renommée, il choisit de s'intéresser au cas particulier d'un camp de concentration abandonné afin d'y découvrir les secrets laissés par ses derniers occupants. C'est alors qu'il sera confronté à des complications inattendues...

###Exemple d'un déroulement d'une partie
Pour commencer, le joueur se réveille dans une pièce, sa santé physique est à 75% et sa santé mentale à 90%. Dès le départ, il se rend compte  q'un gaz menace de le tuer par asphyxie, et qu'il a 2 heures (en temps de jeu) pour s'échapper.

Il ouvre donc la première porte et se retrouve dans une pièce carré avec 3 portes devant lui, une sur chaque mur. Au centre de la pièce, il y a une table sur laquelle se trouve une note (la première de plusieurs) et une balle de billard. Le joueur ramasse donc la note et la balle. La porte de gauche est barrée, donc inaccessible, alors qu'on peut observer une croix rouge sur la porte d'en face. La porte de droite semble ordinaire, il choisit donc d'entrer dans celle-ci.

De l'autre côté de la porte se trouve un escalier que le joueur monte pour finir par se trouver dans la même pièce qu'au départ. Le personnage est troublé et perd donc 20% de santé mentale. Il retourne ensuite dans la pièce à trois portes et n'a pas le choix d'ouvrir celle en face de lui (celle avec la croix rouge).

Il arrive dans une pièce ronde où des débris sur le sol rendent le déplacement difficile. Une bibliothèque git sur le plancher et un tas de déchets se trouve devant un petit bureau. Dans la bibliothèque, le joueur trouve une autre note et, en escaladant le tas de débris, il trouve une arme à feu vide sur le bureau. Il décide de ramasser ces objets puisqu'ils pourraient être utiles dans le futur. À sa gauche il trouve une autre porte qui mène sur un long couloir. Il décide donc d'aller voir ce qui se trouve de l'autre côté.

En le traversant le couloir, il voit sur le mur une indication de courant électrique. En continuant, il arrive devant ce qui semble être un piège, un courant électrique traversant la largeur du corridor. À terre se trouve une balle de fusil et il voit au loin un petit fusible qui pourrait être celui qui permet au piège de fonctionner. Il a le choix de passer au travers du piège, recevant du dommage pour garder sa balle ou de tenter de désactiver le piège en tirant sa seule balle. Après mûre réflexion, il décide de tirer et atteint le fusible. Par contre, le piège ne s'éteint pas. Il se rend compte que le fusible qu'il aurait dû tirer était derrière lui, et qu'il a gaspillé sa seule balle.

Il décide donc de passer au travers du piège (en courant), et perd 10% de sa vie. Il accède à une pièce dans laquelle se trouve une clé derrière une fenêtre de vitre et où un conduit d'aération produit un fort courant d'air. Il lance sa balle de billard pour casser la vitre et manque sa cible. Elle rebondit sur le mur et revient près de lui, il la ramasse alors et recommence quelques fois avant de réussir à atteindre la vitre. Cela lui permet donc de ramasser la clé. Ne voyant rien d'autre à faire, le joueur décide de revenir sur ses pas.

En retournant dans le couloir, il se rend compte que le piège électrique a disparu. Il continue son chemin et au lieu d'entrer dans la pièce où il pensait arriver il débouche sur une toute autre pièce qui n'a pas encore été visitée. Il est encore une fois troublé et perd cette fois 10% de santé mentale (moins cette fois-ci puisqu'il est plus habitué).

Dans cette pièce se trouve un lit où il peut s'étendre pour récupérer de la santé physique/mentale, avec la conséquence de perdre du temps au compteur. Il y a aussi une autre porte à l'autre bout de la pièce. Il choisit de dormir, ce qui lui fait perdre 20 minutes (en temps de jeu). Sa vie est donc augmentée de 10% et sa santé mentale de 30%. Puisqu'il a dormi, il ne sera plus surpris par certains étranges évènements qui se déroulent autour de lui, comme traverser une porte et se retrouver dans une autre pièce que celle où il devrait être. Il sera donc plus facile pour lui de conserver sa santé mentale.

Pour sortir de la pièce, il emprunte la porte par laquelle il n'est pas entré, ce qui le ramène encore une fois à la pièce de départ qui a changé. Sur le mur à sa droite se trouve une inscription en anglais:  "You got one key...". Il se dirige dans la pièce suivante (à trois portes) et se sert de la clé qu'il a obtenue pour ouvrir la porte de gauche.

Ressentant qu'il a atteint la fin du niveau, il hésite. Il pourrait sortir, mais il pourrait aussi rester et essayer d'en découvrir plus sur ce lieu étrange. Il y a encore plusieurs pièce qu'il n'a pas visitées. Il décide finalement qu'avec le danger ça n'en vaut pas la peine et il choisit de sortir. Le jeu prend alors fin et affiche deux accomplissements en anglais, "First game!" et "Easy path", laissant croire que plus de notes, d’autres pièces et objets découverts lui aurait accordé plus de mérite. 

###Interface de l'utilisateur
####Menus
Un menu de début de partie, un menu d'options et un menu de pause seront les différents menus principaux. Un gestionnaire d'inventaire sera aussi nécéssaire.

####Interface graphique
Une barre de vie et une barre de santé mentale sera affichée en bas à gauche de l'écran. Une minuterie sera également affichée en haut de l'écran et elle représentra le temps restant pour terminer le jeu.

###Liste des pièges/casse-têtes/choix/objets/salles
###Génération aléatoire du labyrinthe
À chaque nouvelle partie, on génère la pièce aléatoirement, en tenant compte de trois aspects: Les chemins possibles, leurs formes et leur contenu (objets et pièges). Le but est que d'une partie à l'autre, les pièces génerées ne soient pas les mêmes mais que leur difficulté reste semblable. Par exemple, il pourrait y avoir deux pièces différentes qui ont le même piège. Les pieces, les casse-têtes et les objets changeraient d'une partie à l'autre dans le but de créer des parties très différentes les unes des autres en laissant un nombre de possibilités toujours égale. Le jeu sera équilibré de façon à éviter qu'un joueur se retrouve face à une partie trop facile ou trop difficile. La carte sera consitué de pièces qui seront de différentes tailles et de différentes formes et qui seront reliées par des connecteurs.

####Objets
Une arme à projectiles (exemple : fusil)

Des projectiles de lancer (exemple : balles, grenades, roches)

Objets pour régénérer la santé physique/mentale (exemple : nourriture, boissons spéciales, magazines louches...)

Couteau

Objets utiles aux casse-têtes (exemple : fils électriques, fusible, clés, et autres objets déjà nommés)

Objets à retrouver (les notes du journal)

Munitions

Objets qui modifient la condition physique du joueur (potion de force pour sauter plus haut, courir plus vite).


Il y aura un inventaire accessible au joueur, dans lequel se retrouveront les objets uniques (armes à feu, couteau) et les objets qui peuvent être empilés (munitions, fils électriques, notes, projectiles).

####Salles
Salle de départ : Vide avec une seule porte de sortie et une indication du danger d'asphyxie au gaz avec une minuterie.

Salle #1 : Salle rectangle avec un certain nombre de portes, qui comporte un objet fréquent (exemple : roche)

Salle #2 : Salle rectangle avec un certain nombre de portes et un puzzle/piège qui donne accès à un objet plus vital (exemple : clé)

Salle #3 : Salle ronde avec un certain nombre de portes qui comporte un objet fréquent (exemple : roche)

Salle #4 : Salle ronde avec un certain nombre de portes et un puzzle/piège qui donne accès à un objet plus vital (exemple : clé)

Salle #5 : Salle ronde ou rectangle qui possède un plancher non plat (exemple : débris au sol, plancher ondulé, de biais) et des puzzles / pièges / choix.

Salle #6 Salle avec les inscriptions qui indiquent l'avancement au joueur.

Salle de repos (avec le lit et/ou magazines louches...)

Salle de sortie : Elle possède à la fois un choix, piège et un puzzle, pour ajouter à la difficulté du jeu.

####Connecteurs

Couloir droit

Couloir arqué / avec un coude 

Escalier  (monte ou descend)

Trou au sol

Porte qui s'ouvre directement sur une autre pièce

####Casse-têtes
Reconnecter des portes logiques (et/ou/ou exclusif) avec des fils recueillis en chemin.

Tir sur cible dans un but quelconque.

Une porte sera surmontée d'une "Balance" débalancée que nous devrons mettre à niveau à l'aide d'objets trouvés sur le sol de la pièce en les lançant dans les plaquettes de la balance.

Une très longue pièce contiendra un plafond qui tombe et qui remonte dans lequel il y a quelques trous sécuritaires qui permettraient au joueur de traverser à l'autre pièce (exemple: https://www.youtube.com/watch?v=N2_mN5DgJaM). 

Une salle où un casse-tête nécéssite de connaitre un certain code qui serait sur une note trouvée dans une salle précédente pour débloquer la porte. 

Casse-tête de vitesse (ex. objet non vital à attraper avant qu'une corde ne soit sectionnée).

Agencement de pièces et de couloirs dans lesquels il faut prendre un chemin précis pour avancer. Si le joueur prend la mauvaise porte, il est ramené à la pièce ou au couloir du début du casse-tête. (impacte la santé mentale)

####Pièges

Porte/couloir truqué(e) avec un courant électrique. (impacte la santé physique)

Piège armé tirant un quelconque projectile.

Douche d'acide.

Chemin de barbelés, besoin de pince/couteau pour passer

piège à fréquence : un pendule avec une lame au bout

Le joueur a le choix d'activer un levier à la main où à distance à l'aide d'un objet trouvé à travers les pièces précédentes. Deux courants d'air seront activés, l'un permettant l'accès a une porte et l'autre coinçant le joueur si il active le levier à la main.

####Choix éthiques

Sauver quelqu'un au risque de perdre la partie: Un homme crie à l'aide. Si vous l'aidez, cela pourrait avoir comme conséquence de vous faire perdre du temps et un peu de vie. Par contre, il vous remercierait en vous donnant une note et deux balles de fusil. Si vous le laissez à son sort, une porte pourrait s'ouvrir où le casse-tête à résoudre nécessite deux balles que vous n'avez peut-être pas et votre santé mentale baisserait alors.

Menacer la vie d'un autre pour sauver la sienne: Un piège menace vous et un autre personnage. Si vous choisissez de vous en sauver, l'autre personnage fait face à une mort inévitable, mais vous pourrez continuer sans aucun dommage, sauf une baisse de santé mentale. Si vous restez en danger, vous risquez la mort, mais avez une chance de vous en sortir et l'autre personnage vous serait très reconnaissant.

Découvrir tous les secrets (notes) ou s'échapper au plus vite : Si le personnage finit le jeu au plus vite, il sort sain et sauf, mais l'histoire nous dit qu'il fut ridiculisé pour n'avoir fait aucune découverte. Le joueur n'obtient aucun point moral. Si on trouve des notes, plus de points moraux seront obtenus. Si tous les secret du jeu sont mis à découvert, c'est une victoire absolue. Toutefois, en cherchant plus de secrets, le personnage augmente ses chances de mourir.

##Intégration des différentes matières
	Maths: À travers la programmation et dans l'implémentation de la physique. Il y aura des circuits logiques qui devront être complétés/réparés afin de pouvoir ouvrir une porte ou obtenir un objet.
	
	Physique: Il y aura des sauts, des trajectoires de projectiles, de la gravité, de la physique du vent et de la physique électrique et la physique des rebonds.
	
	Chimie: Le gaz mortel, les cartouches d'oxygène et les antidotes.
	
	Philosophie: Différents choix proposés au joueur qui modifieront le cours de la partie.
	
	Anglais: La langue du jeu sera l'anglais.

	Français: Le code sera en français.


##Librairie utilisée
SDL [www.libsdl.org](https://www.libsdl.org "www.libsdl.org").

OpenGl [www.opengl.org](https://www.opengl.org "www.opengl.org"). 

##Programme pour la gestion de projet

GanttProject : [www.ganttproject.biz](http://www.ganttproject.biz/index.php)
