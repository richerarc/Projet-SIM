

class Contenu {
protected:
	Model3d modele;
	Vecteur3<double> position;
};

class Objet : public Contenu{
};
class Obstacle : public Contenu{
};
class Piege : public Contenu{
};
class Choix : public Contenu{
};
class Puzzle : public Contenu{
};