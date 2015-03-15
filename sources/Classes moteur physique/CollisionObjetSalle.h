bool collisionObjetSalle(gfx::Modele3D& objet, Salle& salle) {

        Vecteur3d point1;
        Vecteur3d point2;
        Vecteur3d point3;
        Vecteur3d pointCollision;
        bool collision = true;
        double signe;
        double distance;
        double gaucheDroite;

        gfx::Modele3D modeleSalle = salle.obtModele();
        Vecteur3d origine = objet.origine;
        Vecteur3d vecteurSol = Vecteur3d(0.0,5.0,0.0);
        vecteurSol += origine;
        Droite rayonCollision = Droite(origine, vecteurSol);
        Plan plan;

        for (unsigned int i = 0; i <  modeleSalle.obtModele().obtNbrFaces(); i++) {

            for (int j = 0; j < 3; j++) {

                switch (j) {

                case 0:
                    point1 = { modeleSalle.obtModele().obtVertices()[j * 3], modeleSalle.obtModele().obtVertices()[j * 3 + 1], modeleSalle.obtModele().obtVertices()[j * 3 + 2] };
                    break;

                case 1:
                    point2 = { modeleSalle.obtModele().obtVertices()[j * 3], modeleSalle.obtModele().obtVertices()[j * 3 + 1], modeleSalle.obtModele().obtVertices()[j * 3 + 2] };
                    break;

                case 2:
                    point3 = { modeleSalle.obtModele().obtVertices()[j * 3], modeleSalle.obtModele().obtVertices()[j * 3 + 1], modeleSalle.obtModele().obtVertices()[j * 3 + 2] };
                    break;
                }
            }

            plan.calculerPlan(point1, point2, point3);
            pointCollision = plan.insertionDroitePlan(rayonCollision);

            if (pointCollision != NULL) {

                signe = positionPointDroite(point1, point2, pointCollision);
                distance = positionPointDroite(point2, point3, pointCollision);
                gaucheDroite = positionPointDroite(point3, point1, pointCollision)

                if (signe == 0 || distance == 0 || gaucheDroite == 0)
                    collision = true;

                else if ((distance < 0 && signe > 0) || (distance > 0 && signe < 0))
                    collision = false;

                else if ((gaucheDroite < 0 && signe > 0) || (gaucheDroite > 0 && signe < 0))
                    collision = false;
            }

            if (collision) {

                distance = distanceEntreDeuxPoints(origine, pointCollision);

                if (distance < 2 && pointCollision.y < origine.y)
                    objet.position.y += distance;

                return true;

            }
            return false;
        }

}
