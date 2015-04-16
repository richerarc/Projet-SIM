,##Analyse des portes (description des prochains cycles ittératif)
**1. Génération des portes.  
2. Interactions porte-joueur.  
3. Changement de salle.**
##Cycle 1 : Génération des portes
- Placer les portes sur les murs;
- Éviter les collisions entre les portes;
- Les tourner selon le mur.
##Cycle 2 : Interactions porte-joueur
- Obtenir l'ID de la porte via la classe joueur quand il y a une interaction avec une porte;  
- Défénir le chemin à prendre.
##Cycle 3 : Changement de salle  
- Transporter le joueur dans la nouvelle salle avec une fausse porte sur un faux mur devant;  
- Suprimmer les salles non-adjacente et charger les salles adjacentes à la nouvelle salle;
- Ouvrir la porte et faire avancer le joueur;
- Supprimer la fausse porte et le faux mur.