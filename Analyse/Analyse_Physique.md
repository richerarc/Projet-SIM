#Analyse pour la physique du projet d'intégration

##Description des éléments du jeu contenant de la physique

###Physique de l'environnement
La gravité : Tous les objets et personnages sont bien sûr affectés par la gravité. Elle peut changer en cours de partie.

Le vent : Le vent affecte les projectiles et le mouvement des personnages. Plus le vent sera fort, plus le déplacement sera difficile ou plus il sera facile, tout dépendra de l'orientation du vent.

L'électricité : Les fils électriques et les courants électriques créeront des champs électriques et les balles de fusil seront affectées par ce champ. Tout autre objet métallique aussi affecté à cette force.

###Physique du personnage
Mouvement du personnage : Le personnage est affecté par la gravité dans chaque déplacement qu'il fait, il pourrait aussi être affecté par un vent dans un piège ou puzzle, etc...

Saut du personnage : Le personnage pourra atteindre une hauteur maximale et avoir une portée qui varie selon sa vitesse.

Chute libre : Le personnage pourra tomber en chute libre, par exemple lorsqu'il passe par les connexions appelées "trous".

###Physique des objets
Chute libre : Un objet tombe en chute libre lorsqu'on le lâche et rebondit au sol. 

Projectile de lancée : Le projectile suit une trajectoire parabolique, mais il rebondit quand il atteint un autre objet. Les rebonds varient d'un objet à l'autre. Le projectile crée des dommages lorsqu'il atteint le joueur avec une certaine énergie cinétique.

Arme à projectile : L'arme envoie une balle de fusil, ou autre. Le projectile qui est lancée avance en ligne droite très rapidement, mais ne rebondit pas, il inflige seulement des dégâts au personnage ou il s'incruste dans un objet.

##Librairie utilisée
SDL [www.libsdl.org](https://www.libsdl.org "www.libsdl.org").

OpenGl [www.opengl.org](https://www.opengl.org "www.opengl.org"). 

##Programme pour la gestion de projet

GanttProject : [www.ganttproject.biz](http://www.ganttproject.biz/index.php)
