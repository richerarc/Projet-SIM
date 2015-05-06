12/02/2015 : J'ai discuté du projet avec une partie du groupe, on semble s'entendre sur le projet à réaliser.

24/02/2015 : Nous (l'équipe chargée de l'algorithme du labyrinthe) avons commencé l'UML de nos besoins et avons discuté de diverses façons de réaliser la génération du labyrinthe. J'ai aussi commencé un modèle 3D de main pour le projet.

02/03/2015 : J'ai fait les classes contenu et porte pour la partie Algorythme, elles sont toujours incomplètes mais c'est parce qu'elles dépendent d'éléments pas encore codés.

03/03/2015 : Légère corrections dans les classes soumises hier au niveau des normes de programmation.

06/03/2015 : Ajout de constructeurs pour les contenus.

10/03/2015 (cours) : Début de la création d'un afficheur de labyrinthe pour tester l'algorithme avec Damien.

12/03/2015 (cours) : Continuation de la création de l'afficheur de labyrinthe avec Damien.

17/03/2015 (8h30 - 9h30): Finition de l'afficheur de labyrinthe.
                          + Cours

23/03/2015 : Modifications dans les classes objets 

24/03/2015 : Continuation des objets avec Damien

26/03/2015 : Continuation des umls des objets avec Damien

31/03/2015 (2h40 à 5h20) : J'ai mis à jour les objets suivant la nouvelle façon décidée avec Damien. Ensuite, nous avons commencé l'analyse des actions effectuables par ces objets.

02/04/2015 (10h00 à 12h45) : J'ai (encore) mis à jour l'uml des objets des objets avec Damien, on ne se sert maintenant plus d'un enum pour les objets, ils ont maintenant repris leur classe comme avant. La classe objet a reçu plusieurs nouvelles variables pour combler aux besoins du projet. Il reste maintenant à coder les modifications dans les classes.
(2h30 à 3h40): J'ai codé les classes qui m'était assignée dans notre nouvelle analyse, il ne reste qu'à leur assigner leurs actions possibles et les cas particuliers de physique.

07/04/2015 (2h40 à 5h25) : J'ai mis ensemble les Objets Physiques et Objets Inventaire et ajusté les héritages en conséquences, car les Objets Inventaires n'étaient pas vraiment pertinents. J'ai aussi modélisé une clé, qui n'est pas encore dans le projet parce sa texture n'est pas faite.

09/04/2015 (9h45 à 11h50) : J'ai finis de modéliser la clé et je l'ai texturé, et j'ai commencé à modelisé de la nourriture.

14/04/2015 (8h30 à 9h15) : J'ai déplacé l'UML des objets dans son propre fichier, puis j'ai ajouté les switch des actions dans Objet.h, ObjetFixe.h et ObjetPhysique.h. Ils sont vides mais présents pour indiquer ce qu'ils peuvent faire.
(12h35 à 5h15) : Nous avons (en groupe) discuté d'une nouvelle répartition des tâches dans le projet. Moi, Nathan, Samuel et Kevin sommes chargés de faire fonctionner le joueur et en avons fait l'analyse et les diagrammes. Nous avons ensuite modifié son code pour correspondre à cette analyse et avons ensuite reglé un bug où le joueur tremblait continuellement.

16/04/2015 (10h00 à 12h00) : J'ai commencé à débugger le bug qui fait coller le personnage au mur, je vais le terminer et le commit plus tard dans la journée.
(1h15 à 4h00) : J'ai debuggé le joueur qui collait au mur et qui avais aussi plusieurs autre problèmes mineurs. Il peut maintenant se déplacer,sauter et toucher la salle sans problèmes.

21/04/2015 (2h45 à 5h30) : Notre épique s'est consulté pour se répartir les tâches. J'ai ensuite fait une partie des interactions avec Sam puis j'ai tenté d'enlever le bug qui fait voir à travers les murs. Je n'ai rien commit parce qu'il bug encore.

22/04/2015 (3H00 À 3H30) : J'ai continué la fonction qui fait longé, pas encore commit parce qu'elle marche pas encore à 100%.

23/04/2015 (9h10 à 11h50) : J'ai commit mon code pour longer, j'ai ensuite debuggé le reste du cours.

24/04/2015 (10h45 à 11h40) : J'ai ajouté des données membres dont Kevin avait besoin, puis j'ai continuer à debugger mon code pour longer suite au nouveau déplacement de Kevin/Nathan.

27/04/2015 (11h30 à 12h55) : J'ai continué à faire le longement, qui n'a maintenant plus que 2 bugs. Ceux-ci dépendent en partie des futures fonctions de Kevin/Nathan, donc je ne commit rien pour l'instant.

28/04/2015 (13h00 à 15h00) : J'ai ajouté du code pour mieux vérifier si le personnage peut interagir avec une porte, car pour l'instant ce n'est basé que sur la proximité. Je ne l'ai pas commit parce que ce n'est pas tout à fait complet, je le finierai demain matin.

30/04/2015 (10h00 à 12h00) : J'ai discuté avec Kevin,Nathan et Samuel du progrès de notre tâche, puis j'ai continué mon longer.

04/05/2015 (12h00 à 2h15) : J'ai mis en commun mon longer avec les déplacements de Kevin et Nathan. J'ai ensuite commencé à débugger le tout, ça marche actuellement assez bien, le longement contre les murs ne marche pas que lorsque le joueur a un certain angle avec le mur. J'ai aussi commencé à modeler une pièce.

05/05/2015 (2h00 à 5h15) : J'ai finis mon modèle de pièce et je l'ai texturé. J'ai ensuite continuer débugger le longement, ça ne devrait plus prendre beaucoup de temps.

06/05/2015 (12h00 à 12h35) : J'ai continué à débugger mon longer, j'ai eu le temps de bien identifier mais pas de rectifier un bug.
