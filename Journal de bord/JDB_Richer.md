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