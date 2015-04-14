`Lun. 02 févr.` Nous nous sommes rencontrez et avons discuter sur ce que serait le projet, aussi j'ai créé un repo GitHub et une salle de chat Gitter. `1h30`

`Mar. 10 févr.` J'ai créé les journaux de bord, et nous prévoyons discuter de l'analyse.`h NA`

`Jeu. 12 févr.` Discution pour établir le level desing final `1h30`

`Jeu. 12 févr.` Discution pour établir les sous équipes, et les besoins des trois "sections" à commencer `1h00`

`Jeu. 12 févr.` Transcription de l'analyse générale du projet, et préàlable pour l"utilisation du programme de gestion de projet. + discution sur les besoins pour la génération de map" `1h00`

`Lun. 16 févr.` Finalisation de l'analyse selon les dernières exigences. J'ai discuter avec Damien pour élaboré l'idée de l'arbre pour la map, et j'ai travailler dessus de mon côté. `2h00`

`Mar. 17 févr.` Nous avons commencé à déterminer les différentes exigeances nécéssaire pour la génération aléatoire le la map. Nous avons imagine un système de porte, qui pointe sur d'autre porte et les salles (pièces et connecteurs) contiennent ces portes. Nous Avons établie les norme de programmation, vu en classe quelque nouveau concept pour certain, et nous avons discuté pour les petit point manquant de l'analyse des besoins. `4h00`

`Ven. 20 févr.` J'ai fais quelques ajout à la cédule du projet. Les modifications sont sur le serveur. `0h30`

`Mar. 24 févr.` Nous avons commencé la conception. Nous avons d'abord planché sur les pièces, porte/portail, et sur le gestionaire de lien (pour les pièce -> connecteur -> pièce) en utilisant une std::map pour associé des pièces et des portes. Nous avons aussi convenu d'utilisé le patron de conception "Singleton" et "Manufacture"(Factory). Le projet part, à mon avis, sur une bonne base. `4h00`

`Mar. 24 févr.` test sur travis, et désactivation temporaire du service `0h45`

`Jeu. 26 févr.` Finalisation du premier cicle de conception. J'ai assigné Damien sur la hiérarchie de classe des salles, Dominique sur celle du contenu des salles, Nicolas sur le gestionnaire de lien, et moi sur "l'usine". J'ai aussi continuer les test avec travis CI,ça risque de devenir concluent. `3h00`

`Mer. 04 mars` Aujourd'hui, nous avons commencer à prendre les sons pour le jeu. Nous avons fait ceci avec l'aide de Fabien(étudiant en musique) et de son matériel audio. J'ai commencer à structurer les includes pour un main plus concluant, et j'ai changé quelque chose dans le makefile en espérant qu'il compile avec SDL. j'ai commencer la fabrique (et pas mal fini aussi) il me manque quelque truc des autres avant de pouvoir commit la vrai. j'ai aussi commencer la sérialisation de mon côté, et je devrait l'ajouté sous peu. `8h00`

`Ven. 06 mars` J'ai changée quelque petit truc dans les classe héritant de Salle et de Contenu. j'ai aussi monter ce qui nous servira à sérialiser les pièces et connecteurs. En plus d'avoir fait un couteau avec blender`4h30`

`Dim. 08 mars` j'ai fait une classe qui permet de mixer des sons, et d'ajouté et de gérer la musique du projet. `2h30`

`Mar. 10 mars` J'ai montré à la classe l'utilisation des "issues" sur Github pour structurer notre travail. Du côté de notre sous-équipe, nous avons terminer l'ensemble des classes de base qui constitue le support pour le génération, et en attendant de pouvoir afficher et positionné des pièce dans l'univers 3D, nous commençons la génération. Pour ceci, j'ai mit Dominique et Damien sur la création d'un programme de "test" qui nous permettra d'afficher en 2D la génération de nos cartes. Nicolas et moi travaillons sur l'algorythme et le générateur. Nous avons aussi établie quelque changement sur la façons de traiter les différentes mise au points discuter avec Patrick. `4h00`

`Mer. 11 mars` J'ai fait quelques modifications dans les classes de Salles, qui ne prendrons plus de positions, mais utiliserons celle comprise dans les modeles 3D. j'ai terminer la fabrique, mais il manque le gestionnaire de ressources de Brandon. `1h00`

`Jeu. 12 mars` J'ai appris la théorie des graphes, et je l'ai appliqué pour le début de notre algorithme de génération. Moi et nico avec travaillé dessus. `6h00`

`Ven. 13 mars` J'ai fini de corriger les classe de graphe. il ne manque que l'ajout de sous arbre prédéfinie. `1h00`

`Mar. 16 mars` Moi et Nico avons travaillé sur l'agorithme de génération de graphe. Il devrait bientôt être terminé. `3h40`

`Mar. 24 mars` J'ai terminé l'algorithme de génération pour la carte. Nous avons travailler sur l'analise des interfaces, sur la hiérarchie des objet et quelque ajustement sur l'engine 3D. Tout le monde à une tâche claire à effectuer, en espérant que tous la fassent! `3h30`

`Jeu. 26 mars` J'ai écrit la fonction qui crée les liens entre les pièces, j'ai modéliser une pièce et une porte, et j'ai aidé Jessy à remaper les includes `2h10`

`Lun. 30 mars` J'ai fait quelques petites modifications pour assurer que tout sera prêt pour finaliser la génération demain. `1h00`

`Mar. 31 mars` Moi et julien avons adapter le code pour qu'il compile sur mac, linux et windows sans problème. Nous avons créé un CMakelist.txt pour le projet. La génération continue, je pense finir le tout demain. `3h30`

`Jeu. 02 avr.` Aujourd'hui, j'ai fais un récapitulatif avec toute l'équipe, pour vérifier que tout le monde savais ce qu'il avait à faire pour qu'on atteigne nos objectifs. En gros, les menu sons en très grande parti terminé, Kevin et Jessy, ainsi que Brandon et Nathan, ayant terminer leur tâches travaille à faire un projet effectif, qui incluera tous les fichiers, affichera et gerera les évemenent. Pour ma part, en plus de ça j'ai finalisé le loading des InfoSalles, il ne reste qu'à tester pour la position des objets à l'intérieur, mais ça devrait ce faire au courant de la fin de semainde de pâques (petite incertidude sur ce point, je travaille 40 hrs cette fin de semaine...) `3h45`

`Mar. 07 avr.` Aujourd'hui, nous avons fait un récapitulatif de toute les classe du jeu pour s'assurer que tout le monde en connait l'utilisation. (Malheureusement, ce n'est pas tout le monde qui y accordait une importance raisonable...). Ensuite, Julien Kevin et moi avons mit toutes les classe en commun, en s,assurant qu'elles fonctionnent (sur Windows tout du moins) et avons commencé un main. Je laisse le reste de la génération à Nicolas C. et je commence la musique. `6h00`

`Jeu. 09 avr.` En gros, j'ai travailler beraucoup sur les sons, en plus d'aider Kev et Julien sur plusieurs truc. J'ai aussi commencer à tout mettre pointeur, mais ça reste en standby pour le moment. `7h15`

`Ven. 10 avr.` J'ai fais la conception pour l'audio, et j'ai commencé les classes de bases pour le contrôleur. J'ai aussi commencé à faire du R&D pour l'implémentation du sons 3D avec les véritable formule de physique. `4h00`

`Lun. 13 avr.` J'ai fini l'implémantation de la base permettant d'entendre du son. Par conséquent, nous entendons maintenant le bruit de fond, les battements cardiaques, et les bruits de pas. J'ai été voir un professeur de physique et j'ai commencer à faire de la recherche sur les bonnes formules à utiliser avec ses conseils. je continu de travailler la dessus. Finalement il apparait que SDL_Mixer ne permet pas de jouer avec le pitch des "sample" audio... je vais trouver un hack pour suronter ça. `6h00`

`Mar. 14 avr.` Nous avons fait une rencontre aujourd'hui pour mettre les points sur les "i". J'ai terminer le diagramme de classe de l'audio (avec 2 hrs d'apprentissage de visio..............) je continue pour le sons multidimensionnel `5h00`