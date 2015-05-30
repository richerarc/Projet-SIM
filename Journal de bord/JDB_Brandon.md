# 2 février au 12 février 2015 #
  Discussion au sujet du game design avec l'équipe.
# 17 février de 14h40 à 17h #
  Mise à niveau de la classe en C++ moderne avec Richer.
  Discussion des normes de programmation.
# 24 février de 14h40 à 17h30 #
Discussion avec l'équipe d'engine graphique sur l'architecture de l'engine.
Discussion sur les design patterns.
## de 21h30 à 22h30 ##
Conception d'une esquisse du diagramme UML du moteur graphique.
# 26 février de 10h à 12h #
Explication du UML à l'équipe pour la bonne compréhension du fonctionnement de l'engine.	Francisation du graphique et commencement de l'ajout de certaines méthodes.
##  de 23h30 à minuit ##
Implémentation des deux classes de Vecteurs principales : Vecteur2 et Vecteur3.
Implémentation du Singleton.
# 3 mars de 13h à 15h #
Finalisation du diagramme UML.
# 4 mars de 19h à 20h #
Séparation des tâches
Implémentation des classes:	GestionnaireEvenements, Souris et Clavier.
# 9 mars de 2h40 à 3h #
Ajout des classes Chrono et Temps.
## de 3h à 5h20 ##
Aide à l'équipe sur la conception.
# 12 mars de 10h à 12h #
Aide à Kévin pour les classes Model3D.
Fix de bugs.
# 23 mars de 18h à 22h #
Implémentation des classes Fenetre et ModeVideo.
# 24 mars de 10h à minuit #
Début de l'implémentation des caméras, il reste quelques bugs à fixer.
# 30 mars de 10h30 à 11h30 #
Finalisation de la caméra GodMode, parfaitement fonctionnelle, sauf que les axes sont inversés, à revoir.
# 6 avril 2015 pendant 2h #
Nous avons eu une rencontre de toute l'équipe afin de récapituler l'avancement du projet ainsi que pour expliquer l'utlilité des nouvelles classes ajoutées depuis le début. Nous avons commencé à élaborer le contenu de la classe Jeu moi, Richer et Kevin. J'ai mis la team d'interfaces au courant de la manière dont nous allions gérer les phases durant le jeu afin de les orient er vers une conception plus stabler de leurs interfaces. Nous avons aussi convenu que je devais me mettre sur l'implémentation des classes reliées aux phases dans le projet.
# 11 avril 2015 pendant 1h30 #
J'ai discuté avec Kevin et il m'a fait part de la caméra qui ne fonctionnait pas lors de la mise en commun de la classe joueur, Caméra, Gestionnaire3D ainsi que Jeu. Du coup, j'ai donc réglé le problème. J'ai ensuite implémenté la base du système de Phases avec les classes GestionnairePhase ainsi que Phase qui servira d'interface pour les futures classes de Phase qui seront implémentées dans le futur au long de la progression du jeu.
# 14 avril 2015 pendant 2h30 (de 14h30 à 17h) #
Nous avons réparti les tâches afin de déterminer où était rendu le développement afin de lancer la phase "Sauver les meubles." Ceci étant fait, j'ai été affecté à la team des Interfaces afin de faire avancer un peu cette section. J'ai expliqué au reste de l'équipe ma vision des choses concernant la conception des menus et les liens entre ceux-ci (Système de phases implémenté cette fin de semaine.) Après débat, nous en avons convenu que nous ferions nos menus au plus simple, soit avec des Texte2D directement, sans Étiquette ni Bouton. J'ai donc implémenté la classe Rect qui permet de composé un rectangle avec les méthodes contient() et intersecte(). J'ai ensuite contribué en concevant la classe MenuNouvellePartie et en guidant le reste de la sous-team vers un développement stable des interfaces graphiques ainsi que la bonne utilisation des évènements.
# 14 avril 2015 pendant 30 min (23h à 23h30). #
J'ai finalisé la classe MenuNouvellePartie et j'ai révisé la classe Menu.¸
# 16 avril 2015 pendant 1h30 (10h à 11h30) #
J'ai fixé une grande quantité de bugs avec Julien ce matin. Nous avons tout d'abord commencé par trouver pourquoi il fallait reloader la surface du texte à chaque fois qu'on l'affichait. Ensuite, nous avons trouvé pourquoi la scène 3D ne s'affichait pas correctement dans dans la phase, nous nous sommes rendu compte que c'était la caméra orthographique qui cancellait notre 3D. Enfin, nous avons trouvé pourquoi notre 3D "flickait", c'est parce que notre framtime se trouvait à être cummulatif plutôt que de calculer entre 2 frames.
# 21 avril pendant 3h #
J'ai commencé à concevoir mon inventaire et à penser à son intégration sur le joueur et à travers les interfaces, j'en suis venu à la conclusion que le joueur possèdera un inventaire en donnée membre qui contiendra son sac à dos ainsi que le menu d'accès rapide. En plein milieu de début d'implémentation, on vint m'annoncer qu'il fallait revoir la conception des menus, on a donc mis le focus là-dessus moi et l'équipe d'interfaces. J'ai donc conçu la classe Bouton qui utilise des callback pour les clicks et les survols. J'ai ensuite reconçu la classe MenuPrincipal.
## Pendant 30 min ##
J'ai fini la conception de la classe MenuPrincipal selon les nouvelles normes.

# 28 avril pendant 1h30 #
J'ai commencé la conception de l'inventaire. J'ai ajouté la classe Case qui contiendra un InfoObjet. Il ne me reste qu'à figurer comment intégrer l'affichage de l'inventaire et gérer les inputs.
# 29 avril pendant 3h #
J'ai commencé et terminé la conception du menu Inventaire et du menu Acces Rapide (HotBar). J'ai aussi conçu leurs textures, cependant elles ne sont que provisoires (j'imagine). Pour ce qui est des items que j'ai ajoutés, ils ne sont utilisés qu'à des fins de test.
# 3 mai pendant 2h #
J'ai commencé à intégrer les items dans le jeu. La classe crée actuellement sera abstraite dans le futur, mais elle ne l'est pas pour l'instant afin d'effectuer des tests. J'ai aussi ajouté les textes de nom et de description dans le menu d'inventaire. En jouant avec les textes dans l'inventaire, je me suis rendu compte que ceux-ci avait un problème dû au fait que le loading ne se basait pas sur la taille, donc 2 textes avec le même string étaient pareils même si ils avaient des tailles différentes, j'ai donc fixé cela.
# 5 mai pendant 3h #
Nous avons discuté longuement de la manière de gérer les items et nous en sommes venus à la conclusion que les items devraient être une sous-classe de ObjetPhysique. Nous avons ensuite effectué les changements et commencé à implémenter les changements d'état des objets.
# 7 mai pendant 2h #
Moi et Nicolas Coutu avons travaillé sur les animations d'objets lorsqu'ils sont équipés. C'est plus ou moins au point.
# 11 mai pendant 3h30 #
J'ai commencé l'intégration des menus d'inventaire dans le gameplay et j'ai implémenté le ramassage d'objets dans les salles.
# 12 mai pendant 1h #
J'ai essayé d'aider Nicolas à bien animer nos items lorsqu'ils sont équipés. On a fait un récapitulatif de semi-groupe sur l'avancement du projet.
## pendant 3h30 ##
Un autre recap. On a déterminé l'arborescence des items et comment les IDs seront attribués.
## pendant 2h ##
J'ai commencé à travailler sur les physiques de Fusil.
#19 mai pendant 3h#
Tentatives de fixer les rotations d'items avec Nicolas.
#20 mai pendant 3h#
Modification des rotations de Modele3D et ajustement des rotations de trous de balles. Début de l'implémentations des mécaniques de fusil ainsi que l'ajout de la mire.
#21 mai pendant 2h#
Début de l'animation du fusil avec Nicolas et recherche des fonctions associées.
##pendant 4h##
Continuation de l'implémentation des animations de fusil, ajout du "scoping", du recul et du spread des fusils. Ajout de sons.
#26 mai pendant 2h#
Commencement des animations d'armes de mêlée et ajout des sons et des trous. J'ai aussi redimensionné les modèles utilisés pour les armes de mêlée et les consommables avec mon grand talent de Blender afin qu'ils soient bien visibles et animables.
#27 mai pendant 2h#
J'ai aidé Nicolas à ajouter des consommables au jeu.
#29 mai pendant 3h#
Nous nous sommes rencontrés pour parler de l'oral et j'ai fini l'ajout des notes dans les items et j'ai ajouté des fonctions au menu accès rapide telles que changer d'item avec les chiffres sur le clavier ainsi que la fonction de revenir à l'item précédent avec la touche q.