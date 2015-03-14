###30 janvier 2015

J'ai proposé une idée de jeu du genre escape game dans lequel deux joueur s'affronte, un cherche à trouver l'autre alors que le deuxième lui en empèche par divers moyens(pièges, mobs, etc...). Elle semble avoir été très bien reçus.

###2 février 2015

Nous avons eu une rencontre dans le C-220 pour discuter du projet où j'ai peu élaborer plus mon idée, à savoir le déroulement d'une partie. Nous avons proposé des style de jeux et ceux qui ont ressortis le plus sont : escape game, shooter et infinite runner.


###3 février 2015

Nous avons fait un vote avec toute la classe et je crois que nous sommes pas mal tous décidé à faire un escape game!

###10 février 2015

Je me pratique dans blender et j'ai fait un lit!

###12 février 2015

Nous nous sommes séparés les tâches pour débuter le projet, je travaillerai la physique du jeu avec Julien, Xavier, Nicolas et Nathan. Nous nous sommes aussi fixé une date limite pour ce qui est de l'élaboration des premiers UML qui sera mardi le 17 février.

###16 février 2015

J'ai révisé un peu l'analyse des besoins avec Richer.

###17 février 2015

Durant l'avant-midi, moi et Xavier avons travaillés sur les diagrammes en ce qui concerne la physique, nous pensons que le diagramme d'état n'est pas vraiment nécessaire. Nous avons aussi avancé l'analyse des besoins de la physique. Par la suite, la classe s'est réunie vers 1h pour parler du projet et échanger nos idées entrautre sur la manière de construire les classes pour la physique. Nous aurons probablement une classe qui contient les formules et calculs nécessaire avec plusieurs #define pour ce qui est des constantes. Nous avons aussi abordé un peu le sujet des collisions, Brandon nous a apporté une idée certainement fiable et simple, mais qui demanderas probablement trop au processeur pour qu'elle soit justifié. Nous avons ensuite eu un petit cours de C++11 pour apprendre à utiliser les structure de donné déjà présente dans visual studio. Finalement, nous avons établi des normes de programmation pas trop exigente, qui se rapprochent selon moi du "Bon sens" parce qu'on ne perdra plus de temps à faire trop de commentaires sans non plus rendre notre code incompréhensible. Finalement, nous avons donnés en groupe quelques nouvelles idées de pièges.

### 24 février 2015

Nous avons d'abord apris quelques patrons de conception dont le singleton et la factory. Je crois avoir bien compris le principe, mais je vais probablement essayé d'en faire une moi-même afin de mieux comprendre! Ensuite, nous nous sommes regroupé en équipes et avons fais un remue-méninges, nous avons parlé de pendules, de projectiles, gravité qui ne s'appliquera pas su les projectiles, etc... Nous avons aussi débuté un diagramme pour notre classe physique qui contiendra majoritairement des fonctions ou procédures statiques.

### 26 février 2015

Aujourd'hui, nous avons complèté en partie le diagramme de classe physique et avons discuté sur la manière qu'on va calculer le mouvement d'un pendule. Nous avons aussi établi des normes de modélisation.

### 27 février 2015

Je me suis fait une classe singleton et une factory, ca bien été et je comprend mieux comment ca marche.

### 01 mars 2015

Moi et julien avons avancé l'analyse pour la physique, pendant qu'il travaillait sur le diagramme de classe, j'ai fait une brève description des fonctions et des procédures que nous allons utilisé dans le fichier Formule de physique, nous avons ajouté quelques nouvelles fonctions et deux classes(plan/droite). J'ai aussi envoyé un mio à mon professeur de physique pour savoir comment intégrer le magnétisme dans notre projet, bref les formules dont nous aurons besoin.

### 02 mars 2015

Ajout d'un chronomètre à la conception de la physique, création d'un pièce dans blender selon les normes!

### 04 mars 2015

3/4/2015 9:02:39 AM 

Nous discutons au cégep des sons dont nous aurons besoin éventuellement pour le jeu, sons de pas, de vent, etc...

3/4/2015 9:41:45 AM 

Merge des modifications apportées au diagramme de classe de la physique du jeu.

3/4/2015 9:50:42 PM 

Début du codage de la physique, j'ai codé la classe chrono et j'ai commencé à coder la classe physique, les fonctions et procédures de base que j'ai par la suite testé, tout marche bien jusqu'à maintenant.

3/4/2015 1:38:39 PM 

Nous sommes allé faire des enregistrement de sons avec un ami en musique, très plaisant comme activité, nous avons une panoplie de sons, malheureusement nous n'avons pas eu le temps de tous les enregistrer.

3/4/2015 5:54:01 PM 

Petite modification dans la classe vecteur pour la procédure normaliser, l'appel de la fonction norme n'était pas exacte et le nom de la variable qui prend la norme s'appelait norme, comme la fonction, donc le programme ne compilait pas. Ajout d'un dossier "Classes et code pour le moteur physique" avec la classe Chrono.

### 09 mars 2015

Aujourd'hui je suis allé voir le professeur de physique Charles Naaman pour discuter de l'application du magnétisme dans notre jeux. Suite à une longue discution et simplification de formule nous somme arrivé à trouver la formule suivante :

    F = -6 * khi * Bext / Z
    où khi est la suseptibilité magnétique du matériaux
    , Bext est le champs magnétique créé par l'aimant 
    et Z la distance entre l'aimant et l'objet aimanté.

Le problème avec cette formule, c'est qu'elle ne tient compte que d'un plan. Alors il va probablement que je retravaille là-dessus avec mon professeur pour l'amélioré, mais je sens qu'on est proche! Je l'ai mis en code et je l'ai testé, bien qu'il nous faut un champs magnétique de 1 tesla pour que ça fonctionne, les résultats semblent acceptables.

### 10 mars 2015

Nous avons discuté en groupe de l'utilisation de github (les issues) et des sons qui remplaceront en partie l'interface graphique.

Nous nous sommes ensuite distribué les diverses tâches reliées à la physique, j'ai reçus le mandat de travailler sur le magnétisme. J'avais déjà avancé le sujet, il ne me restait plus qu'à l'appliquer à l'ordinateur. En normalisant mon vecteur que je créais avec la distance entre l'objet et l'aimant, comme tu m'as conseillé et avec d'autres ajustements, j'ai pu arrivé à un calcul plus que satisfaisant. J'ai ajouté le tout à la classe Physique et j'ai fermé l'issue #20. Je vais retourné voir mon professeur de physique avec mon programme pour être sur que le résultat est valide.

J'ai aussi fait une modification à la classe vecteur par l'ajout d'un opération qui multiplie le vecteur en mémoire par un autre.

### 12 mars 2015

Avec l'accord de mes coéquippiers, j'ai commencé à travailler sur l'application du vent sur un objet dans le jeu. J'ai tout d'abord été cherché la formule requise et je l'ai compris du mieux que j'ai pu pour ensuite voir comment je pourrais l'adaptée au code. Tout d'abord, selon ce tableau :

http://upload.wikimedia.org/wikipedia/commons/thumb/2/26/Drag-fr.svg/220px-Drag-fr.svg.png

Il semble que plus l'objet est courbé, plus le coefficient de trainée est petit. Donc je me suis vite rendu compte que je devrai me servir des normales pour faire une somme de tous les angles entre le vecteur du vent et la normale qui sont plus petit que 90 (négatif jusqu'à -90). Je diviserai ensuite le résultat par le nombre de face touchées par le vent. Ainsi le coefficient ne devrait pas dépaser 1(en radian) et une surface planne me donnera 1, comme le cube dans le tableau. Pour ce qui est de la surface, à chaque fois qu'un angle est plus petit que 90, cela implique que le vent applique une force sur la surface donc j'additionne toutes les surfaces poussées.

J'ai travaillé à le mettre en code, je crois être dans la bonne voie.
J'ai aussi aidé mes coéquippiers dans ce qu'ils avaient à faire.

### 13 mars 2015

Après avoir fini de mettre le tout en code, je me suis rendu compte que je n'avais pas à utiliser le arccos pour voir mon angle entre 90 et -90, après avoir fais quelque calculs dans les quatres quadrants d'un angle, le vent ne pouvait avoir un impacte que quand l'angle était plus petit que 0 (négatif jusqu'à 1). J'ai aussi testé le tout avec les diverses forme du tableau que j'ai lié un peu plus haut et, par exemple, pour une sphère, mon coefficient était de 0.43. Considérant le nombre limité de faces, je suis très satisfait du résultat! J'ai push ma procédure dans notre classe physique.

### 14 mars 2015

Ce matin j'ai retravaillé les formules pour le magnétisme et le vent dans notre fichier markdown pour qu'elles soient cohérentes. J'ai aussi commenté les deux procédure plus tôt pour expliquer mieux comment elles fonctionnent.

Je suis maintenant assigné à la gestion des rebond, je me suis créé une issue, et j'ai regardé comment coder une telle chose. J'ai regardé dans le livre *Physics for game developpers* pour trouver une formule que j'ai décortiquée et essayé de comprendre. Je vérifie aussi avec le groupe pour savoir s'il y aura des collisions entre deux objets en mouvement.

J'ai fini de codé la collision entre deux objets en mouvement, je vais l'intégrée en même temps que les autres types de rebonds quand j'aurai fini.