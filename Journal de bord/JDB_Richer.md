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