##Formule de physiques

- Formule de pendule (composé et/ou simple)					(fait)
- Formule avec la gravité									(fait)
- Formule trajectoire des profectiles
- Formules de magnétisme									(fait)
- Formule d'un plan											(fait)
- Formule indicant de quel côté d'une droite le point est	(fait)
- Formule de distance entre deux point						(fait)
- Formule de frottement
- Formule pour appliquer le vent

##Détail sur les procédure et fonctions de la classe Physique:

####Vecteur3 obtenirNormalSurface(Vecteur3, Double);

Cette fonction permet d'obtenir la normal d'un face ou d'un groupe de faces. Elle prend un vecteur qui sera la position  du vecteur de la normale et un double qui est le rayon dans lequel on fait nos calculs. Ca ve servir principalement pour les rebonds.

####Vecteur3 obtenirForceNormal(Double masse, Vecteur3 Position);

Fonction qui retourne la force normale d'un plan par rapport à un objet:

    Fn = m*g*cos( theta )

- m = Masse de l'objet
- g = gravité
- theta = angle entre la surface et l'axe vertical(Donc entre obtenirNormaleSurface et l'axe!)

####appliquerGravite(Vecteur3);

Procédure qui applique la gravité sur un objet en l'additionnant à la composante verticale de son vecteur de déplacement.


####appliquerVent(Vecteur3);

Procédure qui applique le vent au vecteur d'un objet en addition de vecteur.

####appliquerFrottement(Objet);

Applique le frottement à un objet lorsqu'il est en collision selon une constante de frottement(identique pour tous les matériaux pour l'instant, donc le bois glisse autant que la glace!) et la force normale.

####Double penduleSimple(Double angleMaximal, Double frequenceAngulaire);

Fonction qui retourne l'angle d'un pendule simple selon le temps, son angle maximal et sa fréquence angulaire.

    θ(t) = θm*cos( wt )

- θ(t) = Angle retourné(Position angulaire du pendule)
- θm = angle maximal du pendule
- w = fréquence angulaire du pendule
- t = temps

####Double distanceEntreDeuxPoints(Vecteur3 Point1, Vecteur3 Point2);

Fonction qui retourne la distance entre deux point!!!!!!

####Integer positionPointDroite(Vecteur3, Vecteur3, Vecteur3);

Fonction qui retourne la position d'un point par rapport à une droite:

- -1 = Point à gauche de la droite
- 0 = Point sur la droite
- 1 = Point à droite de la droite

Les deux premiers vecteurs(point) servent à représenter la droite, le troisième est le point et le dernier vecteur est la normale du plan dans lequel le point se trouve.

####Double obtenirEnergieCinetique(Double masse Vecteur3 Vitesse);

Fonction qui retourne l'énergie cinétique à partir d'une masse et d'un vecteur vitesse.

    k = ½m*v²

##Détails sur les procédures et fonctions de la classe Plan:

####Plan(Vecteur3 p1, Vecteur3 p2, Vecteur3 p3);

http://www.ilemaths.net/maths_t-droites-plans-cours.php

Équation d'un plan:

    ax+by+cz+d = 0

- u = p1 - p2
- v = p1 - p3
- normale = u X v
- d = u * p1

####Vecteur3 intersectionPlanDroite(Droite);

http://homeomath.imingo.net/geoesp7.htm

Fonction qui retourne les point d'intersection entre un plan et une droite. Retourne NULL si il n'y en a pas.

####void recalculerPlan(Vecteur3 p1, Vecteur3 p2, Vecteur3 p3);

Fonction qui recalcule un plan.

##Détails sur les procédures et fonctions de la classe Droite:

####Droite(Vecteur3 p1, Vecteur3 p2);

Calcul du vecteur directeur:

    vecteurDirecteur = A X B


##Détails sur la classe Chrono

Cette classe va nous donner la variable t pour nos fonctions. Par exemple, pour trouver l'angle du pendule simple, nous avons besoin du temps:

    θ(t) = θm*cos( wt )

que nous donnera cette classe!

Le chrono sera activé au début de la partie.

