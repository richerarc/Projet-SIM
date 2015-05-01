###**`12 février 2015`**

- 10h à 10h30 : J'ai participé à l'élaboration finale du concept du jeu. Le gameplay et
le principe des changements de salles sont maintenant plus clairs. 

- 11h40 à 12h : Nous avons aussi divisé notre projet en 3 sous-parties, soit la physique,
la partie graphique et la partie algorithmique... Je n'ai pas peu resté plus longtemps malheureusement, mais il a été déterminé que je suis le "chef" de la partie physique.

Temps : 50 min

###**`15 février 2015`**

- 11h à 11h45: Je suis allé parler à Patrick, avec Richer et Damien, sur le contenu de l'analyse et sur ce qu'il faut y modifier. Nous sommes ensuite allés peaufiner l'analyse. J'ai participé à la création d'un exemple d'une partie de jeu et à la création de quelques puzzles et quelques pièces.

- 20h40 à 21h00 : J'ai commencé une brève analyse sur la physique afin d'avoir une base de discussion pour demain. 

Temps : 1h05 

###**`17 février 2015`**

- 8h30 à 9h : J'ai discuté de la structuration et de l'analyse de notre physique avec Gabriel et Xavier. 

- 12h40 à 14h40 : Nous avons commencé un petit diagramme de classe pour bien imager notre physique. Nous avons discuté avec les autres équipes afin de savoir leur besoin dans la physique.

- 14h40 à 17h40 : Nous avons élaboré sur le projet, nous avons fixé les normes de programmations et quelques notions du c++. Nous savons exactement ce qu'il faut ajouter à notre analyse pour pouvoir commencer à développer le programme.

Temps : 5h30

###**`19 février 2015`**

- 13h à 14h : Richer, Kevin, Jessy et moi avons pensé à d'autre idée de puzzles et de salles. (Avec la collaboration de Félix) 

Temps : 1h

###**`24 février 2015`**

- 14h40 à 17h20 : Nous avons parlé des patrons de conceptions, le singleton et la factory. Nous avons commencé la conception de nos formules de physiques.

Temps : 2h40

###**`26 février 2015`**

- 10h à 12h : Nous avons continué la conception de nos formules. Nous savons maintenant quoi demander en paramètre à nos fonctions et ce qu'ils retournent.

Temps : 2h

###**`1er mars 2015`**

- 12h à 15h : J'ai retravaillé le diagramme de classe du moteur de physique. J'ai aussi travaillé avec Gabriel pour expliquer clairement chaque fonction (ce que la fonctionne retourne et les paramètres qu'elle demande).

Temps : 3h

###**`2 mars 2015`**

- 20h30 à 21h : Ajout d'un morceau assez important dans le diagramme de classe du moteur de physique, la gestion du temps.

Temps : 30 min

###**`3 mars 2015`**

- 7h30 à 7h35 : La classe Vecteur3 est maintenant totalement en français. La classe s'appelait Vecteur3 et Vector3...

Temps : 5 min

###**`5 mars 2015`**

- 8h25 à 8h35 : J'ai ajouté deux includes dans la classe Physique et cette classe hérite maintenant de la classe Singleton.

Temps : 10 min

###**`6 mars 2015`**

- 21h à 21h20 : J'ai travaillé sur la fonction déterminant de quel côté d'une droite le point est, mais je ne suis pas certain à 100% que ça fonctionne.

Temps : 20 min

###**`9 mars 2015`**

- 19h40 à 21h : J'ai fait quelque modification dans le diagramme de classe du moteur de physique. J'ai ensuite expliqué les changements dans le documents des formules. Dans les changements, j'ai ajouté les fonctions qui calcul les collisions.

Temps : 20 min

###**`10 mars 2015`**

- 12h30 à 13h : J'ai refait la fonction déterminant de quel côté d'une droite un point se trouve, elle gère maintenant les points en 3D.

- 14h40 à 17h : J'ai discuté avec les autres membres de mon équipe sur le fonctionnement des collisions et sur d'autres formules. Nous nous sommes divisés en sous-équipe : une équipe sur les collisions, une sur le magnétisme et l'autre sur les formules de physiques indépendantes. 

Temps : 2h50

###**`15 mars 2015`**

- 11h à 14h30 : J'ai fait la première version des collisions entre un objet et une salle, mais je n'ai pas encore vérifié selon la position exacte de l'objet, car les calculs n'ont pas encore été faits. Je demande aussi temporairement une salle en paramètre, mais quand le gestionnaire de liens sera terminé je n'aurai plus besoins de demander une salle en paramètre.

Temps : 3h30

###**`17 mars 2015`**

- 14h40 à 17h20 : J'ai continué a faire l'algorithme des collisions avec un objet et une salle. J'ai fait une fonction et une procédure pour enlever la redondance de code.

Temps : 2h40

###**`21 mars 2015`**

- 11h à 14h et 15h à 20h : J'ai réglé tous les problèmes avec les classes et fonctions que j'ai de besoins pour implémenter mes collisions. La droite ne se créait pas de la bonne manière, mainteant oui et je l'ai testé avec des exemples d'algèbres linéaires. Même chose pour le plan, la variable d était un vecteur, mais c'est plutôt un double qu'il fallait mettre (un erreur de ma part quand j'ai expliqué comment créé un plan à Gab) et la fonction qui calculait un intersection entre une droite et un plan n'était pas bonne. Je l'ai donc refait et maintenant ça fonctionne. Finalement Kevin avait oublier un petit quelque chose dans la tranformation du tableaux de vertices dans la Classe Modele3D, je l'ai rajouté.

Temps : 8h

###**`24 mars 2015`**

- 13h  à 17h20 : J'ai continué les collisions avec un objet et une salle, je regarde maintenant selon chaque vertex de la boîte de collision de l'objet. J'ai aussi remplacé le formule qui déterminait si un point était d'un côté ou de l'autre d'une droite. Maintenant il y a une fonction qui détermine si un poit est dans un triangle. 

Temps : 4h20

###**`25 mars 2015`**

- 11h à 13h et de 14h20 à 17h : J'ai remarqué que mes collisions ne fonctionnaient pas s'il y avait un plafon dans la pièce, car j'obtient deux point de collisions. J'ai tenté de comprendre pourquoi, mais sans succès.

Temps : 4h20

###**`26 mars 2015`**

- 9h30 à 14h40 et 16h à 17h : J'ai avancé dans les collisions avec une nouvelle théorie, qui ne fonctionne pas vraiment pour l'instant, mais j'ai débugger toute la journée pour trouver le problème, sans succès pour le moment.

Temps : 6h10

###**`27 mars 2015`**

- 10h30 à 12h30 et 13h45 à 14h30 : J'ai finalement trouvé l'emplacement de mon bug : la fonction qui déterminait si mon point était dans un triangle ne fonctionnenait pas totalement en trois dimensions je l'ai donc transformé entre deux dimensions et tout fonctionnait. Je regarde aussi maintenant l'angle entre le vecteur vitesse de l'objet et la normale de la face qui est en collision, si l'angle est dans près de 180 il y a collision.

Temps : 2h45

###**`30 mars 2015`**

- 10h à 10h10 : J'ai optimisé mes collisions en enlevant les piles que je demandais en paramètre dans la fonction collisionDroiteModele. Ces piles n'étaient plus utiles, car j'ai réglé le problème de de plusieurs points de collisions.

Temps : 10 min

###**`31 mars 2015`**

- 13h40 à 17h40 : J'ai fait un CMake avec Richer, on travail tous les deux avec CLion. J'ai continué à travailler sur la compatibilité entre Linux, Apple et Windows, j'ai enfin trouvé ce qui ne fonctionnait pas. J'ai mis le code compatible entre Windows et Linux. J'ai aussi ajouté quelques lignes de codes pour remonter mon objet lors d'une collision. J'ai commencé à penser au collision objet objet : je vais créer une nouvelle fonction déterminant s'il y a une collision entre une droite et une boîte de collision.

Temps : 4h

###**`2 avril 2015`**

- 10h à 13h : J'ai commencer la fonction déterminant s'il y a une collision entre un objet et une droite. Nous avons discuté de l'avancement du projet et nous avonx regroupé quelques personnes pour commencer à afficher quelque chose dans le jeu. La physique est maintenant à jour dans le projet.

Temps : 3h

###**`6 avril 2015`**

- 11h30 à 13h30 : J'ai réarrangé la classe physique parce qu'elle n'était plus update (un problème de destruction de branche). Elle compile maintenant à 100% et elle est utilisable dans le projet sans problème pour la plupart de ses fonctions. Il reste les collisions à perfectionner.

Temps : 2h

###**`7 avril 2015`**

- 13h à 14h40 : J'ai aider Kevin, avec la complissité de Richer et Gabriel, pour crééer un projet contenant toutes les classes du projet. Nous nous sommes assuré que tout compilait. Nous avons fait quelques constats avec la physique : on ne peut pas gérer la physique dans les objets et dans le joueur.

- 14h40 à 17h20 : Grosse conversation avec tout le groupe pour discuter de l'avancement du projet et de la pertinance de chacune des classes du projet. Nous avons éliminé quelques classes et quelques fonctions. J'ai ensuite discuté avec Brandon des façons de gérer la physique et nous avons déterminé que la physique des objets allait être géré dans la classe Salle et que celle du joueur allait être dans la classe Jeu.

- 19h30 à 21h : J'ai rendu le projet compatible sur linux en mettant tous les Modele3D en pointeur. J'ai aussi fait le constat que la physique ne pouvait pas être faite dans la classe Salle, parce que ça créait des inclusions circulaires. J'ai donc déplacé la procédure qui gérait la physique de la classe Salle vers la classe Physique en faisant un petit ajustement pour l'obtention de la liste d'objet de la salle.

Temps : 4h50

###**`8 avril 2015`**

- 17h30 à 18h10 et 20h à 21h : J'ai fait des modifications dans la classe Jeu : j'ai ajouté un joueur, un chrono et une variable représentant le frameTime. Ces variables sont toutes statiques. J'ai aussi ajouter une procédure appliquant la physique de tout (Joueur et objets). J'ai aussi créé une salle temporairement pour que tout le monde puisse tester.

Temps : 1h40

###**`9 avril 2015`**

- 9h à 12h : J'ai discuté avec Richer et nous allons mettre tout le projet en pointeur. On a commencé avant le cours, mais on a arrêté pour ne pas empêcher les autres de travailler. J'ai ensuite refait mon CMakeliste pour utiliser SDL2_ttf et SDL2_mixer. J'ai ensuite aidé Kevin pour faire affiché les éléments dans la fenêtre avec leur texture, il manquait un glEnable(TEXTURE_2D). 

Temps : 3h

###**`10 avril 2015`**

- 19h à 21h : J'ai finalement terminé les collisions entre deux objets, il manque les collisions interne, ce qui ne devrait pas prender trop de temps. J'ai ajouté un tableau de normales et d'indices dans la classe Modele pour faire mes collisions.

###**`13 avril 2015`**

- J'ai travaillé sur le joueur et la classe Jeu.h pour avoir une salle qui s'affichait en plus d'avoir un joueur qui bouge dans la salle.

Temps : 1h30

###**`14 avril 2015`**

- 12h à 12h30 : J'ai été en réunion avec Richer, Kevin et Gabriel pour discuter de l'avenir du projet et sur quoi il fallait se consenter. Nous avons déterminer trois aspects, soit les Interfaces, le joueur, et les salles. Je suis responsable de la partie des interfaces.

- 12h30 à 1h30 : Grosse rencontre d'équipe, nous avons d'abord expliquer la situation de notre projet, tout en essayant de motiver les personnes qui n'ont pas travaillées beaucoup. Nous avons divisés le groupe en trois partie, tout en laissant Richer seul dans le son. 

- 13h30 à 14h40 : Première rencontre avec Xavier et Jessy pour parler de ce qui a déjà fait dans les Interaces.

- 14h40 à 5h : Nous avons travaillé sur l'analyse et les diagrammes en équipe. Brandon nous avons montré les phases qu'il avait déjà coder, nous les avons donc intégré les phases et le gestionnaire de phase dans le projet. J'ai commencé à afficher le menu principal, mais j'ai des problèmes avec le Texte2D et le Sprite2D.

Temps : 5h

###**`15 avril 2015`**

- 11h à 15h : Travail sur les menus, j'ai partiellement réglé les problèmes avec le Texte2D, avec l'aide de Richer, mais notre solution est vraiment temporaire. J'ai donc pu maintenant crééer des menus et les gérer complètement, il y a un menu principal, un menu nouvelle partie et un menu pause quand le joueur est dans le jeu. Par contre le monde 3D n'affiche plus.

Temps : 4h

###**`16 avril 2015`**

- 10h à 12h : J'ai continué les menus avec Brandon, nous avons réglé le poblème de l'affichage du monde 3D et régler des problème par rapport à l'affichage 3D et 2D en même temps. Nous avons donc des menus fonctionnels et le jeu démarre comme avant.

- 16h à 17h40 : J'ai mis les menus sur la master en m'assurant que la branche interface était à jour avec le master. J'ai du régler plusieurs conflits avec le travail des autres équipes, mais tout est maintenant correcte, le joueur est a jour dans la classe PhaseJeu.

- 20h à 21h : J'ai régler le problème avec la classe Sprite2D avec l'aide de Jessy, nous pouvons maintenant afficher un logo et un fond. J'en ai donc profité pour mettre les menus un peu plus beau.

Temps : 4h40

###**`20 avril 2015`**

- 18h30 à 20h : J'ai terminé le glisseur, pour qu'il soit fonctionnel pour les autres menus pour demain. Il fonctionne parfaitement.

Temps : 1h30

###**`21 avril 2015`**

- 14h40 à 18h40 : J'ai traivaillé dans le gestionnaire de ressources pour mettre les polices de caractères, comme cela nous ne chargeons plus des polices pareilles plusieurs fois. J'ai aider toute mon équipe dans leur partie et j'ai rendu le projet fonctionnel, car il avait beaucoup d'erreur avec les commits fait dans mon équipe.

Temps : 4h

###**`22 avril 2015`**

- 11h à 17h : J'ai découvert que le gestionnaire d'événement de détruisait pas les pointeurs de fonctions. J'ai donc essayé de mettre une fonction qui enlevait un pointeur de fonction de la std::map de pointeurs de fonction. Étant donné que les pointeurs de fonctions sont de std::function, cela a causé beaucoup de problèmes. J'ai cherché d'abord à parcourir la std::map de std::vector d'une façon simple et de supprimer un élément du vector, mais comme un std::vector n'est pas la meilleur chose pour supprimer un élément, j'ai eu quelques problèmes. J'ai donc découvert qu'il fallait un itérateur de std::vector pour supprimer un élément. Par contre, il est impossible de comparer deux std::function. J'ai cherché avec Richer un moyen de règler cela et nous n'avons rien trouvé a ce sujet et nos essais ce sont avérés infructueux. Nous avons donc créé une classe Fonction, qui contient la std::function et un ID, nous comparons le Fonction, avec l'opérateur ==, et maintenant ça fonctionne. La std::map du gestionnaire d'événement contient maintenant un std::vector de Fonction. Après avoir fait tous les modifications dans toutes les classes par rapport au gestionnaire d'événement, le programme compilait, mais il plantait dans l'appel d'événement, parce qu'une des fonctions modifiait la std::map de fonction pendant que celle-ci était parcourue. J'ai donc fait un patch pour régler cela (il n'est pas très beau soit dit en passant, mais il faut faire avec la conception de départ des gestionnaires). Maintenant le programme fonctionne, ne plante plus dans dans le gestionnaire d'événement, mais il plante une fois sur deux dans la librairie sdl, à cause des std::function.

Temps : 6h (Avec la grande collaboration de Richer)

###**`23 avril 2015`**

- 8h à 10h : Richer et moi avons regardé ce que les patchs que nous  avons fait hier ont donné et comme ceux-ci ont créé beaucoup trop de problèmes, nous avons décidé de laisser tout ce que l'on a fait hier de côté. Nous allons garder tous les menus en mémoire et ne pas enlever les std::function du gestionnaire d'événement.

- 10h à 14h : J'ai travaillé à modifier tous les menus et le gestionnaire de phases pour que nous menus fonctionnent bien (je n'ai pas tous fait les menus). J'ai fait des modifications dans tous les phases et j'ai commencé le menu son.

Temps : 6h

###**`24 avril 2015`**

- 11h à 12h et de 15h à 17h : J'ai fini le menu son et je fini le menu graphique, j'ai réglé tous les problèmes dans les menus, des boutons qui s'appelaient à des places pas rapport et des plantages à quelques places. J'ai mis le tout sur la branche Menus.

Temps : 3h

###**`27 avril 2015`**

- 11h à 11h15 : J'ai mis plusieurs textures à jour pour que le glisseur fonctionne bien et un fichier texte pour les controles afin d'afficher le menu controle parfaitement.

- En soirée : J'ai mis les menus sur le master, pour que tout le monde ait la vrai version des menus. J'ai aussi fait un petit ajustement dans le menu graphique pour qu'il affiche toutes les résolutions de 16/9 possible selon l'ordinateur. J'ai aussi fait une modification dans pointDansFace pour que la fonction fonctionne dans tous les cas possibles.

Temps : 3h15

###**`28 avril 2015`**

- Durant la journée : Richer et moi avons fini le menu son, il gère complètement l'intensité des sons du jeux. Nous avons ensuite travaillé sur le système qui fait en sorte que le joueur perd de la santé mentale. Je commençai a aider Jessy avec l'intégration de la manette pour le jeu.

Temps : 6h

###**`29 avril 2015`**

- 11h à 13h : Richer et moi avons analysé les besoins des puzzles que notre jeu va comporter. Nous avons déterminé les grands points essentiels pour le bon fonctionnement du projet et nous avons fait un diagramme de classe pour les puzzles. 

Temps : 2h

###**`30 avril 2015`**

- 10h40 à 12h : J'ai aider un peu de monde dans le groupe pour qu'il avance dans le projet, cela n' a pas été concluant dans certain cas. Richer et moi avons fait un petit meeting pour savoir l'avancement de tout le monde et nous avons parler avec Gabriel pour s'assurer que notre conception de puzzle ne détruira pas la génération de porte.

16h à 18h : J'ai fini le curseur et l'application de la manette dans les menus. Richer a fait quelques modifications avec moi, mais le curseur bouge super bien dans les menus. 

Temps : 3h40


Temps total : 121h30