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
Nous avons réparti les tâches afin de déterminer où était rendu le développement afin de lancer la phase "Sauver les meubles." Ceci étant fait, j'ai été affecté à la team des Interfaces afin de faire avancer un peu cette section. J'ai expliqué au reste de l'équipe ma vision des choses concernant la conception des menus et les liens entre ceux-ci (Système de phases implémenté cette fin de semaine.) Après débat, nous en avons convenu que nous ferions nos menus au plus simple, soit avec des Texte2D directement, sans Étiquette ni Bouton. J'Ai donc implémenté la classe Rect qui permet de composé un rectangle avec les méthodes contient() et intersecte(). J'ai ensuite contribué en concevant la classe MenuNouvellePartie et en guidant le reste de la sous-team vers un développement stable des interfaces graphiques ainsi que la bonne utilisation des évènements.
# 14 avril 2015 pendant 30 min (23h à 23h30). #
J'ai finalisé la classe MenuNouvellePartie et j'ai révisé la classe Menu.¸
# 16 avril 2015 pendant 1h30 (10h à 11h30) #
J'ai fixé une grande quantité de bugs avec Julien ce matin. Nous avons tout d'abord commencé par trouver pourquoi il fallait reloader la surface du texte à chaque fois qu'on l'affichait. Ensuite, nous avons trouvé pourquoi la scène 3D ne s'affichait pas correctement dans dans la phase, nous nous sommes rendu compte que c'était la caméra orthographique qui cancellait notre 3D. Enfin, nous avons trouvé pourquoi notre 3D "flickait", c'est parce que notre framtime se trouvait à être cummulatif plutôt que de calculer entre 2 frames.
# 21 avril pendant 3h #
J'ai commencé à concevoir mon inventaire et à penser à son intégration sur le joueur et à travers les interfaces, j'en suit venu à conclusion que le joueur possèdera un inventaire en donnée membre qui contiendra son sac à dos ainsi que le menu d'accès rapide. En plein milieu de début d'implémentation, on vint m'annoncer qu'il fallait revoir la conception des menus, on a donc mis le focus là-dessus moi et l'équipe d'interfaces. J'ai donc conçu la classe Bouton qui utilise des callback pour les clicks et les survols. J'ai ensuite reconçu la classe MenuPrincipal.
## Pendant 30 min ##
J'ai fini la conception de la classe MenuPrincipal selon les nouvelles normes.
