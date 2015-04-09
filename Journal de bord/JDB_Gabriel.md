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

### 16 Mars 2015

Xavier, Richer et moi avons discuté sur qui allait géré les objets qui sont influencé par la physique, on en a conclu qu'il y aurait une classe abstraite Objet qui pourrait être un piège à vent, du aimant, un objet fixe, ou un objet physique. Ils vont nous passer tous les objet lors de l'application de la physique et nous allons gérer ceux qui sont influencés.

### 17 mars 2015

J'ai codé le rebonds d'un objet sur une surface de la map, j'attends les collision à julien pour pouvoir les tester de manière plus concraite qu'en me disant que ca l'air correct. En attends, j'ai demandé au groupe de graphique s'ils avaient un engine de base que je pourrais utilisé. Il me l'on donné et j'ai fait quelques modifications, j'ai ajouté nos classe de physique et des objet en blender pour pouvoir faire des tests. J'ai aussi modifié la classe physique en ajout un ratio pour l'augmentation de la vitesse d'un objet selon le frametime, j'ai fait des modifications pour que le programme compile. J'ai voulu mettre l'engine sur git, mais on m'a FORTEMENT conseillé de ne pas mettre de vs sur git, heureusement que j'avais oublié de faire git add, il n'y a pas eu de problème. Je vais donc redistribuer l'engine au membres de mon équipe. Il y a aussi eu des changements dans les équipes, Xavier et Dean travaillent maintenant sur les menus.

### 18 mars 2015

Petite modification dans la classe Vecteur: Ajout d'un soustraire et remplacement du SDL_acos() qui ne semblait pas fonctionner par acos(). J'ai aussi testé le rebonds sur une surface plane avec un event de barre d'espace qui appel la procédure, il semble y avoir un problème, le vecteur de l'objet semble être modifié correctement, pourtant dans le monde 3D il ne semble pas se déplacer avec le nouveau vecteur, il rebondit a peine et retombe instantannément.

### 19 mars 2015

Tout d'abord, nous avons eu un petit cours de git pour apprendre l'utilisation des commandes. Ensuite j'ai réussi à régler mon problème, enfait lorsque j'appuyais sur la touche space, le gestionnaire d'événement ne remettait pas le "booléen" à false donc le rebonds se faisant sans arrêt au lieu d'une seule fois. Maintenant qu'il fonctionne, j'ai testé le rebond sous plusieurs angles et tout est bon! Après j'ai testé le vent, encore une fois tout s'applique bien, le nouveau vecteur est à un échelle respective de la force du vent et de la forme de l'objet, mais quand je sort de la procédure j'obtiens un DEGUB ASSERTION FAIL très fatiguant que je n'ai toujours pas pu régler. Avant de détruire mon odrinateur j'ai décidé d'allé testé le magnétisme, tout fonctionne parfaitement. J'ai fait quelques modification par-ci, par-là dans la classe physique et j'ai aussi mis à jour notre fichier de formules de physique. Il faudrait probablement metter aussi notre diagramme de classes à jour... peut-être... un jour... d'ici la fin de la session...

###22 mars 2015

J'ai corrigé plusieurs erreurs dans des classes faites par d'autres personnes dont j'avais besoin...(~30 min de gossage et il en reste encore)

J'ai commencé à faire un procédure qui va parcourrir tous les objets d'un salle pour appliquer la physique, j'ai un peu de difficullté avec les dynamic_cast, il me donne des erreurs, j'ai fait quelques recherches sur internet, mais ce que j'ai fait devrais fonctionner.

Bon après avoir travaillé pendant 5 min en commençant par l'application du vent je me suis tanné parce que les classes des objets, incluant le vent, ne sont pas complète je vais en discuter avec ceux qui travaillaient dessus.

J'ai ajouté le rebond entre deux objet en mouvement (de base) dans la classe physique.

###24 mars 2014

J'ai commencé à faire une procédure qui applique la physique sur une liste d'objet qui contient les objets physique, les objets fixes, le vent, les aimant, etc...

Suite à une discution, nous avons finalement décidé de faire le physique(sauf les collisions pour le moment) dans les classes respectives. Par exemple, l'application du vent se fera dans la classe vent. Je vais travailler là dessus.

###25 mars 2015

J'ai commencé à faire un avion en blender!

###26 mars 2015

**1h00** : Création des procédure appliquerPhysique dans les classes vent, aimant et objetPhysique.

**0h20** : Ajout des includes dans les classes à dominique et damien.

**0h20** : Test du "parcours" de la physique dans les classes vent, aimant et objet physique. L'application de la physique semble être correct, par contre je vais devoir faire afficher pour le voir vraiment bien mais l'affichage ne fonctionne pas...

**0h20** : Bon j'ai réussi à faire afficher, le vent, le magnétisme, la gravité s'appliquent correctement!!

**0h20** : Corrections et update dans le fichier Formules de physique.

**1h20** : Travail sur mon avion, ça avance bien et je crois que je vais être fier du résultat!

Durant la soiré j'ai discuté avec richer et, comme je m'y attendais parce que du côté physique Julien semble pouvoir gérer les collisions, je vais allé aider Damien et Dominique à faire les travail puisqu'ils semblent avoir de la difficulté. Pour l'instant ilsont un gros paquet de classes qui semblent trop nombreuses, je vais leur proposer une idée, l'utilisation d'un enum pour gérer les actions faites sur un objet. Leur travail consiste principalement à mettre en place tou ce qui est utile à l'utilisation des différents objets alors il me semble pertinent qu'au lieu de créer tout plein de classes, on se fait un enum d'action du genre:

`enum action { Ramasser, Lancer, Manger, FaireExploser};`

Puis dans la classe de l'objet il y aurait un appliquer action comme suit:

`void appliquerAction(action) {`

	`switch (action) {`
		case RAMASSER:
		case LANCER:
		case MANGER:
		case FAIREEXPLOSER:
	}
`}`

Reste à voir si c'est une bonne façon de faire. Je vais probablement continué à faire un peu de physique par-ci par-là, mais Julien semble ne pas vouloir d'aide même après lui avoir demandé plusieurs fois...

###28 mars 2015

**1h30**: Réflexion profonde sur la manière de structurer nos classes objet, j'ai fait une nouvelle version puis je demanderai l'avis à mes coéquipiers.

###30 mars 2015

**1h**: Discution avec M.Charles Naaman, professeur de physique, sur les rebonds de fou que je veux coder, c'est-à-dire des moment de force, etc.. Nous avons réussi à obtenir des formule(très grosse) pour calculer le tout, c'est quand même beau.

**1h**: Travail sur le formule de physique, j'ai plusieurs calculs à faire, un grosse berta avec un quadratique et autres.

###31 mars 2015

**2h20**: Plus de travail sur les formule, j'ai pu obtenir la vitesse final de l'objet qui me servira pour calculer la vitesse angulaire et la vitesse de rebond.

**1h30**: Création d'un projet pour commencer à coder les formules, je n'ai pas encore fait de tests, mais la formule pour trouver la vitesse finale est codée.

**2h20**: Codage de la nouvelle fonction de rebond, pas pire comme résultat jusqu'à maintenant, mais il reste encore beaucoup de chemin à faire j'ai l'impression.

**3h00**: Codage de la nouvelle fonction, plus ça avance, plus c'est gros! Je devrai probablement allé voir mon professeur de physique pour m'assurer que ce que j'ai fait jusqu'à maintenant respecte la vie en général...

###32 mars 2015(hehe)

**1h00**: Discution intense entre physicien aka moi et mon prof pour résoudre des problèmes, on commence à arriver à quelque chose.

**0h45**: Codage des nouvelles formules, le rebond, visuellement, est mon bon qu'il était, mais je sais qu'il est en fait meilleur, genre tsé comme... En fait, le calcul est c'est juste que la vitesse angulaire semble être proportionnellement correct, mais trop petite. Si je la multiplie, elle ressemble à l'ancienne, mais en mieux, bref encore du travail à faire.

###02 Avril 2015

**2h30**: Travail sur les formules de physique/Aide Damien et Dominique.

###04 Avril 2015

**2h30**: Travail sur les formules.

**2h00**: Codage des formules, ça fonctionne, mais l'objet accumule la vitesse angulaire et il se met à spiner n'importe comment après un certain temps, et au début, il n'en a presque pas.

###05 Avril 2015

**1h00**: Révision des formules... Quelques erreurs...

**1h00**: ÇA FONCTIONNE!!! J'ai presque fini la procédure, il aurait quelques ajustements à faire, mais en dehors de la procédure :

- Identifier un point de collision plus précis
- Pouvoir définir un point de rotation

Pour la définition d'un point de rotation, j'ai essayé avec l'origine, mais ça déplace légèrement l'objet lorsque je le modifie ou il disparait à l'infinit ce qui très mal. Je suis quand même très content du résultat et l'effort en a valu la peine!

###06 avril 2015

**2h30**: Test et optimisation de la procédure rebondObjetCarte, optimisation du genre au lieu d'avoir plusieurs sin(angle), je le calcul avant puis je l'utilise dans la formule. Le collision ne fonctionnent pas très bien, il reste aussi quelques problèmes dans la procédure, mais en général elle fonctionne bien:

- Je multiplie la vitesse angulaire finale par 20 pour que ce soit plus 'réaliste'
- Ne réagit pas bien lors de collision lente
- Point de rotation au centre, je crois qu'il devrait plutôt être au point de collision
- Point de collision imprécis
- Commenter et optimisation à réviser

###07 avril 2015

**1h00**: Aide à la création du dossier ClasseProjet avec Richer, Kevin et Julien. Nous avons réglé les erreurs de compilation.

**1h00**: Discution de groupe sur le nouveau dossier ClasseProjet, explication des diverses classes du dossier. Explication des BoiteCollision lors de la création d'une pièce.

Dorénavant, je m'occupe de faire l'application de la physique sur tous les objets d'une salle. J'avais déjà commencé à le faire, avec les dynamic cast, mais on avait changé de méthode alors je dois recommencé.

Pas vrai, j'ai été fouillé un peu sur github jusqu'au commit qui contenait la version la plus recente de mon appliquerPhysique!

**0h10**:Ajout de l'ancienne procédure qui appliquait la physique sur une liste d'objets, réglage de quelques erreurs de compilation.

###08 avril 2015

**0h30**: Travail sur le formules du rebond avec le professeur.

Pour ce qui est du rebond, celui que j'ai présentemment est décent, il respecte plutôt bien la physique. Il y a bien sur des tonnes d'amélioration que je pourrais faire pour le rendre meilleur. Je veux continué à travailler dessus, mais je comprend qu'il y a d'autres choses de plus importantes à faire dans le projet comme l'application de la physique sur les objets d'une salle dont j'ai été mandaté. Je vais donc continué à travailler sur le rebond mais de manière plus personnelle, dans mes temps libre puisque c'est quand même quelque chose que j'aime faire.

**0h30**: Travail sur l'application de la physique des objets d'une salle, je crois que c'est presque fini, pour le reste je devrai la mettre à jour losrque les collisions objet-objet seront faites, et qu'il y aura d'autres objets avec une physique spécifique. La prochaine étape sera de me créer une salle qui contient des objet de différents types et les faire intéragir.