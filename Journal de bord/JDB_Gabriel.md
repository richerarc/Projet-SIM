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

###09 avril 2015

**1h00**: Travail sur le pendule, quelques modifications dans la classe pendule, dans la procédure obtAnglePendule et application de la physique du pendule dans la procédure appliquerPhysiqueSurObjets
Il foncitonne bien!

**0h30**: Travail sur l'avion en blender, l'arrière est fini, il me reste l'avant de joindre les ailes.

###11 avril 2015

**0h30**: Corrections dans le rebond pour les rares fois qu'un objet tombe et qu'il ne gagne pas de rotation du genre une sphère sur un plancher droit, j'avais des divisions par zéro. Ça ma aussi permis d'optimiser un peu le code.

###14 avril 2015

J'ai eu un petit moment sans travail, et avant de m'avancé sur autre chose je préférais attendre notre super rencontre de groupe!

**0h30**: Petite rencontre entre Kevin, Richer, Julien et moi pour parler de la prochaine étape du projet et de problème à résoudre en ce qui concerne la méthode de travail de tout le monde. Nous nous sommes ressortis avec trois prochaines étapes pour l'avancement du projet:

- Interface: Ce qui concerne l'affichage 2D des menus et l'interface de jeu. (Julien)
- Joueur: Intéraction/Mouvement/Collision du joueur dans le jeu (Kevin)
- Carte/Salle: Génération des salles avec les trucs de Richer et Nicolas C., création des portes(Génération à la bonne place, interaction avec le joueur et passage du joueur dans la pièce suivante), gestion des objets dans le jeu. (Moi)
- Son : (Richer) <--- *Temporaire, devrait prendre 1 sem.*

Je crois être confortable dans ma nouvelle position, je vais me familiariser avec ce qu'ils auront de fait.

**1h00**: Discutions avec presque tout le monde de présent, nous avons parler de l'avancement du projet, de la méthode de travail à suivre pour la prochaine étape, de l'importance de respecter le cycle itératif et nous avons répartis les nouvelles équipes, je travaillerai avec Nicolas C. et Damien.

**3h00**: Première étape de notre groupe, nous avons choisi et compléter ce qui a trait aux portes/génération de la map. Tou d'abord nous nous sommes fait une petite analyse qui divise notre tâche en trois partie distincte(ITÉRATIF!!!). Premièrement, il nous faudra pouvoir générer des porte aux bon endroit, nous avons aussi spécifié plusieurs conditions à respecter(À voir dans notre analyse). Ensuite, nous allons gérer la demande que le joueur nous enverra pour ouvrir une porte, à voir pour plus tard l'ajout d'un verrou. Finalement nous allons travailler sur la transition d'une salle à une autre.

Nous avons aussi travaillé sur le diagramme de classe d'algo pour ajouter ce dont nous aurons besion. Nous sommes donc près à coder notre premier cycle!

Nicolas avait déjà commencé à coder le positionnement des portes, nous avons travaillé dessus en groupe pour régler plusieurs bug et problèmes, nous avons aussi modifié quelque chose dans la classe jeu afin que la salle active se décide selon la génération de graphe de Richer et Nicolas. Au début nous avions de nombreux problème de violation d'accès et de débordement de tableau, mais après un acharnement intensif, nous sommes parvenus à les corriger. Je suis assez satisfait de mon équipe et je crois qu'on va bien performer et bien sur respecter le plus possible le cycle itératif.

###15 avril 2015

**0h30**: Travail dans la classe carte pour que les portes affichent, les portes ne sont pas bien placées!

**1h00**: Réglage d'erreur dans la procédure creer de carte, par exemple, il ne réinitialisait pas la salle lorsqu'il travaillait sur une nouvelle et rendu à la vingtième salle elle avait beaucoup de boîtes de collision. J'ai aussi regardé l'algo de Nico quant-au positionnement des portes, il y a quelques trucs à régler que j'ai pris en note pour lui en parler demain, mais la position finale que ça donne semble être correct même si la porte n'est apparament pas à la bonne place lors de l'affichage. Je me suis aussi assuré que l'origine de l'obj de la porte était à la bonne position.

###16 avril 2015

**2h00**: Damien, Nicolas C. et moi avons continué de travailler sur le premier cycle de création des portes. Maintenant, la portes se positionnent au milieu des murs et il ne peut pas y avoir deux portes supperposées. Par contre, les portes sont positionnées `parfois à des endroits anormaux, mais je crois que c'est la boite de collision de Richer qui n'est pas bonne.

**1h30**: Modélisationd'une porte plus legit et officielle avec une texture ainsi que la pieceL en L dont je doutais encore l'exactitude, la boîte de collision d'était pas bonne alors j'ai décidé de la refaire au complet pour être sur et certain qu'elle ne causerait plus de porblème.

###17 avril 2015

**3h00**: Travail sur la génération des salles et des portes, fin du cycle 1(je crois). J'ai pu tester avec un bonne pieceL et le code fonctionnait, tout ce qu'il manquait, c'est que les portes ne se positionnent que sur les mur ou plutôt les faces verticales formées par les boite de collision qui sont liées à un mur. Pour cela, j'ai regardé si la position de la porte était à la jonction par quatres points de deux boîtes de collisions. j'ai aussi ajouté un échelle random sur nos pièce comme me l'a sugéré Kevin, maintenant la pièce carrée par exemple peu être dew forme rectangulaire.

Le prochain cycle à entammer est la réception d'un message par le joueur qui nous dit qu'une porte a été ouverte, comme j'ai dit plus tôt:

> Ensuite, nous allons gérer la demande que le joueur nous enverra pour ouvrir une porte, à voir pour plus tard l'ajout d'un verrou.

###21 avril 2015

**3h00**: Aujourd'hui Damien Nicolas et moi avons travaillé sur le changement de salle. Pour l'instant, je "bind" le changement de salle à la touche space puisqu'on n'a pas de réponse du joueur encore. Le joueur se téléporte à la bonne place, soit au milieu et en face de la porte. J'ai parlé à l'équipe qui travaille sur le joueur pour qu'il ajoutent une intéraction joueur-porte pour s'assurer que lorsque nous sommes rendu à la partie de l'animation de changement de salle, on pourra bien travailler. Pour ce qui est du cycle de réception du message, il est plutôt inexistant pour nous, c'est surtout du côté à l'équipe Joueur.

Bugs:

-Un porte qui s'affiche dans le mauvais 1 fois sur 10 pour une raison inconnue!

Prochain cycle (déjà entammé):

>Travailler sur la transition d'une salle à une autre.
 
###23 avril 2015

**0h30**: Modification sur le travail de Samuel pour l'appel de changement de salle lorsqu'une porte est ouverte.

**0h20**: Création d'un faux mur en blender pour Damien.

**0h15**: Petite répartition des tâche entre Nicolas, Damien et moi, j'ai donné à Damien le mandat de la transition de salle, soit l'animation de changement de salle. Nicolas et moi allons retravailler sur la génération des portes pour qu'elles soitent  meilleur.

**2h00**: Finalement, nous allons utiliser une autre technique pour placer nos portes! Nous allons d'abord placer des portes au hasard dans nos boîtes de collision tout en tenant compte que deux portes qui ont la même direction ne doivent pas être vis-à-vis. En ce qui concerne la direction, c'est ce qui nous permettra de placer les portes sur les murs. Nous allons leur donner un vecteur vitesse à leur création et tant qu'il n'y a pas de collision, nous allons incrémenter la position de la porte selon sa direction.

###24 avril 2015

**1h30**: En testant le jeux, j'ai remarqué que certaines piece boucle sur elles-même. J'en ai parlé avec Richer puis nous avons travaillé à régler le problème. Nous avons eu à dessiner le graphe et faire quelques test pour trouver le problème.

**0h30**: Nous avons abordé le sujet des choses qui reste à faire et en parlant, nous avons comme eu un élan sur une discution sur la façon de calculer la perte de point de mentalité. Nous en sommes dabord venu avec l'idée que pour perdre des points de vie, il fallait que le trajet effectué par le joueur soit physiquement impossible. Pour ça, nous avons dabord établi que si le joueur doit faire passe par une sortie/entrée et que les deux portes n'ont pas la direction opposée, c'est physiquement anormal. En étudiant d'autres cas, nous avons aussi établi que : 

![](http://i.imgur.com/kT5ExIf.png)

Donc si le joueur entre dans une porte en sens opposé, ce qui est physiquement possible selon nos restrictions d'avant, maintenant, la prochaine condition à ajouter serait que si le joueur va par exemple vers la gauche, donc vers le négatif, et que sa position est incrémentée positivement lors du transfert de salle, c'est physiquement impossible!

**3h00**: Travail en alternance sur la génération des portes j'ai fait une nouvelle pièce, il y a des problèmes à régler. J'ai synthétisé du code, réglé plusieurs problèmes, j'ai aussi ajouté un bool dans PhaseJeu d'où on appel changementDeSalle() afin que de un on n'utilise plus la toucheAppuyée parce qu'il faut appuyer anormalement vite! et que toucheRelachée ne dit pas si une touche a été relachée, mais plutôt si elle est relaché, ce qui est quand même inutile... J'ai modifié un peu les collision pour qu'elles fonctionnent différamment avec le porte à la génération. Étant donné que j'ai fait plusieurs modifications j'ai pris le temps de vérifier avec certitude que je ne créerais pas d'erreurs de compilation. Je suis assez content de l'avancement dans la génération des portes, je crois pouvoir compléter le tout en fin de semaine. Déjà on peut circuler sans problème dans la "labirynthe"! Je constate que le cycle itératif n'a pas vraiment été respecté, mais étant donné que nous ne pouvions pas vraiment être trois à travailler sur le même cycle, je crois qu'il est plus profitable d'en faire plusieurs en même temps. Voici ce qui me resterait à faire côté génération des portes:

- Donner une rotation à la porte selon la normale de collision(peut-être faire des collisions spécifiquement pour la génération des portes parce qu'elles commencent à différer énormément des collisions objet-salle).
- Faire un clean-up du code de génération!­­

###25 avril 2015

**0h30**: Commentaire et clean up du code de génération de porte.

**1h00**: Création d'une nouvelle salle pour faire des tests sur les portes en angle, la salle est correct, mais je suis complètement incapable de me déplacer avec le joueur...

**1h00**: J'ai créée une procédure spécifique pour les collisions des portes puisqu'elles commençaient à diverger beaucoup de collisionObjetSalle. J'ai aussi ajouté une orientation pour les portes donc elles devraient pouvoir maintenant se positionner sur un mur dont l'orientation n'est pas parallèle à l'axe X et Z. Par contre, étant donné que le joueur ne peu pas bouger dans ma salle convergente, je vais devoir attendre avant de tester.

**0h20**: J'ai retirer la physique du joueur pour pouvoir me mouvoir comme je le veux! les orientation sont bonnes sur le mur désaxés, par contre, dans ma nouvelle salle, toutes les portes sont dans le mauvais sens(180°), pourtant dans la pièceL et Salle4x4 elles sont correctes. J'essaie de comprendre pourquoi!

**0h30**: Après de longue minutes de "Mais pourquoi ça marche pas!?!?!?" j'ai finalement découvert que les normales de ma pièce n'étaient pas dans la bon sens...

**0h15**: J'ai testé un peu les portes sur des murs désaxés(avec un salle qui fonctionne), ça fonctionne à moitié, des fois elles sont parfaitement sur le mur, d'autres fois elles ne semblent pas avoir eu de rotation.

Voici ma façon de trouve l'angle:

![](http://i.imgur.com/Xh6EyCq.png)

**1h00**: J'ai modifié la collisionPorte pour qu'elle ne se fasse qu'avec l'origine de la porte(nécessaire pour les rotations), j'ai restructuré un peu le code dans carte pour qu'il y ait moins de répétage de code inutile, j'ai réglé le bug que Dean avait signalé sans vraiment aucune précision sur gitter.

###26 avril 2015

**0h05**: Correction d'une erreur de compilation mentionnée par Damien.

###28 avril 2015

>Personnellement, je suis quelqu'un qui aime beaucoup programmer, et surtout­, qui aime faire les chose bien, par exemple les rebonds(que je finierai en temps j'espère). Pour certaines personne le positionnement des portes pourrait être satisfaisant si elles pouvaient aller sur de mur plat en ligne droite, pour moi non. Recemment j'ai travaillé à donner un angle aux portes ce qui semble être de mieux en mieux. Pour la suite, j'essaierai de faire en sorte que mes portes puissent passer par des marches et se positionner correctement. J'ai déjà un idée de comment faire!(pas sur si ça va fonctionner par contre)

**3h00**: Travail sur l'angulation des portes sur des murs désaxés. La technique que j'emploie est bonne, mais je me suis rendu compte qu'il y avait deux cas différents. J'ai déterminé que le calcul variera si l'angle entre ma normale et le vecteur directeur de ma porte est moins ou plus de 180°. Par contre, dans le calcul de l'angle entre deux vecteurs, l'agnle retourné est toujours plus petit que 180°. Après réflexion et une petite visite chez nos sympathiques proffesseurs de mathématique, j'ai pu déterminer plusieurs conditions qui me disent si, pour trouver l'angle, je doit faire l'angle entre mes deux vecteurs ou 360 - l'angle entre mes deux vecteurs. Grâce à ça, mes porte se désaxent correctement!

**6h00(école) + 3h00(maison)**: Travail sur les portes qui montent des escaliers. Le trois quarts des heures de travail ont été destinés à des heures de débogage ardu. L'idée que j'utilise pour positionner mes portes au-delà des escaliers est la suivante: Je fais translater ma porte dans la direction de son vecteur déterminé au début jusqu'à ce que j'ai une collision(exactement comme des mur normaux). Ensuite, je vérifie aux quatres coins de la porte si ils sont tous en collision. Si ce n'est pas le cas, ça signifie que j'ai une marche. Donc je monte ma porte jusqu'à ce que je n'ai plus de collision. Quand je n'ai plus de collision, c'est que la porte est au niveau de la première marche. Je répète le procédé jusqu'à ce que je translate ma porte et que la collision des quatres coins de ma porte retourne vrai. Ensuite, je redessant la porte au niveau du sol au cas où elle serait un peu surélevée à cause des nombreuses modification que je fais dessus.

![](http://i.imgur.com/OLxJcpx.png)

Même si cela peut parraîttre simple à première vue, j'ai eu beaucoup de problèmes avec les collisions qui ne donnaient pas toujours le même résultat et il a fallu que je "tweek" plusieurs choses. Par exemple, parfois le repositionnement créait une boucle avec lui même c'est à dire que comme sur l'image, l'opération 1-2 se refaisaient sans arrête. Je translatais la porte au mur, le repositionnement se faisait, et je retraslatais, et le repositionnement, etc... Il y a eu de nombreux problème du genre, c'est pour ça que ça fait beaucoup d'heures(de débogage), d'ailleurs Julien m'a donné un coup de pouce pour trouver les chose louche que les collisions créaient involontairement et faire les modifications appropriées. Il y a encore différents problèmes à repérer, je ne suis pas encore sorti du bois...

Durant l'après midi(6h00 école) j'ai aussi aidé Damien pour l'animation, j'ai aidé Richer et Julien pour trouver une façon de calculer la perte de santé mentale du joueur, etc...

###29 avril 2015

**3h00**: Un beau dernier trois heures de travail pour complèter les portes/escaliers. Elles se positionnement maintenant bien et il ne devrait plus y avoir de boucles infinis, assez fier du résultat je suis.

###30 avril 2015

**1h00**: Présentation de l'oral et petite réunions de groupe, je me suis fixé comme but de terminer la génération de porte d'ici dimanche 24h00.

**0h15**: Petite discution avec Julien et Richer de l'impact des puzzles sur la génération des portes.

**2h00**: Travail sur la génération de porte.

###01 mai 2015

***4h00**: Plus de débogage aka travail sur la génération des portes...

###02 mai 2015

**3h00**: Travail sur la génération des portes, il n'y a plus de boucles infinis, mais certaines portes n'arrivent pas à monter les marches. Par contre elles montent/descendent des pentes...

###03 mai 2015

>Bon, bon, bon... Je suis comment dire tanné de travailler sur les portes. Cela était dit, je vais persévérer à les faire se positionner correctement. J'ai alors décidé de faire ce que j'aurais dû faire au tout début, comme bon analyste et penser à comment m'y prendre. Je me rends bien compte que les collisions ne sont pas une option étant donné qu'elles sont très, disons, suseptibles. Après mûr réflexion, j'en suis venu à la conclusion qu'il existait un autre moyen de positionner les portes, beaucoup plus rapide et probablement infaillible. Je vais d'abord accéder au modele de la salle où je suis en train de positionner mes portes. Dans ce modele, je vais me trouver un triangle qui répond aux critères suivants:

1.  La composante y de sa normale doit être nulle
2.  Sa hauteur en Y dans être de minimum 2 mètres
3.  Sa largeur en X et Z doit être de minimum 1 mètre

À partir de là, je n'ai qu'à posiitonner la porte sur cette face et le tour est joué, il faudra aussi que je valide si deux portes s'entremêlent.

**6h00**: Travail sur la nouvelle génération, ça marche.

Je crois que je peux retirer une belle leçons de mon périple:

> Réfléchir avant de travailler, parce que si j'avais pensé un peu plus à comment positionner mes portes, j'aurais eu fini il y a bien longtemps...

Si j'étais en deuil du temps que j'ai "perdu"(J'ai quand même appris des choses et réglé des bugs ailleurs), je dirais que je suis à la phase d'acceptation en ce moment...

AU MOINS J'AI ATTEIND MON BUT!!!