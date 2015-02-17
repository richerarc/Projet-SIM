#Analyse pour la physique du projet d'intégration

##Description des éléments du jeu contenant de la physique

###Physique de l'environnement
La gravité : Tous les objets et personnages sont bien sûr affectés par la gravité. Elle peut changer en cours de partie.

Le vent : Le vent affecte les projectiles et le mouvement des personnages. Plus le vent sera fort, plus le déplacement sera difficile ou plus il sera facile, tout dépendra de l'orientation du vent.

L'électricité : Les fils électriques et les courants électriques créeront des champs électriques et les balles de fusil seront affectées à ce champ. Tout autre objet métallique aussi affecté à cette force.

###Physique du personnage
Mouvement du personnage : Le personnage est affecté par la gravité dans chaque déplacement qu'il fait.

Saut du personnage : Le personnage pourra atteindre une hauteur maximale et avoir une portée qui varie selon sa vitesse.

###Physique des objets
Projectile de lancée : Le projectile suit une trajectoire normale, mais qui rebondit quand il atteint un autre objet. Les rebonds varient d'un objet à l'autre. Le projectile crée des dommages.

Arme à projectile : L'arme envoie une balle de fusil, ou autre. La particule qui est lancée avance en ligne droite très rapidement, mais ne rebondit pas, elle inflige seulement des dégâts.

##Librairie utilisée
SDL [www.libsdl.org](https://www.libsdl.org "www.libsdl.org").

OpenGl [www.opengl.org](https://www.opengl.org "www.opengl.org"). 

##Programme pour la gestion de projet

GanttProject : [www.ganttproject.biz](http://www.ganttproject.biz/index.php)
