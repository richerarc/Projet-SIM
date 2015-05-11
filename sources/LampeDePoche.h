// Class de test pour une possible lampe de poche

#include "Vecteur3.h"

class LampeDePoche {
private:

	GLfloat* ambientLight;
	GLfloat* diffuseLight;
	GLfloat* specularLight;

	GLfloat* lightPosition;
	GLfloat* lightDirection;

	UINT32 lum;

public:

	LampeDePoche() {}

	LampeDePoche(UINT32 lum, Vecteur3d position, Vecteur3d direction) {

		this->lum = lum;

		ambientLight = new GLfloat[4];
		diffuseLight = new GLfloat[4];
		specularLight = new GLfloat[4];

		lightPosition = new GLfloat[4];
		lightDirection = new GLfloat[3];

		// Ajustement de la lumière ambiante...
		ambientLight[0] = 0.0;
		ambientLight[1] = 0.0;
		ambientLight[2] = 0.0;
		ambientLight[3] = 1.0;

		glLightfv(this->lum, GL_AMBIENT, ambientLight);

		// Ajustement de la lumière diffuse...
		diffuseLight[0] = 10.5;
		diffuseLight[1] = 10.5;
		diffuseLight[2] = 10.5;
		diffuseLight[3] = 1.0;

		glLightfv(this->lum, GL_DIFFUSE, diffuseLight);

		// Ajustement de la lumière spéculaire(réflexion)...
		specularLight[0] = 1.0;
		specularLight[1] = 1.0;
		specularLight[2] = 1.0;
		specularLight[3] = 1.0;

		glLightfv(this->lum, GL_SPECULAR, specularLight);

		// Ajustement de la position de la source de lumière...
		lightPosition[0] = position.x;
		lightPosition[1] = position.y;
		lightPosition[2] = position.z;
		lightPosition[3] = 1.0;

		glLightfv(this->lum, GL_POSITION, lightPosition);
		
		// Ajustement de la direction de la source de lumière...
		/*lightDirection[0] = direction.x;
		lightDirection[1] = direction.y;
		lightDirection[2] = direction.z;

		glLightfv(this->lum, GL_SPOT_DIRECTION, lightDirection);*/

		// Ajustement de l'angle de projection des rayons lumineux...
		//glLightf(this->lum, GL_SPOT_CUTOFF, 45);
		//
		//// Ajustement de l'intensité de la lumière selon le l'angle entre la direction et le rayon lumineux...
		//glLightf(this->lum, GL_SPOT_EXPONENT, 0.5);

		glLightf(this->lum, GL_CONSTANT_ATTENUATION, 0);
		glLightf(this->lum, GL_LINEAR_ATTENUATION, 0.25); 
		glLightf(this->lum, GL_QUADRATIC_ATTENUATION, 0.001);
	}

	void defPosition(Vecteur3d position) {

		// Ajustement de la position de la source de lumière...
		glPushMatrix();
		//glLoadIdentity();
		glTranslated(lightPosition[0], lightPosition[1], lightPosition[2]);
		//glTranslated(origine.x, origine.y, origine.z);
		glLightfv(this->lum, GL_POSITION, new float[] {(float)position.x, (float)position.y, (float)position.z, 1});
		glPopMatrix();
		
	}

	void defDirection(Vecteur3d direction, double hAngle, double vAngle) {

		// Ajustement de la direction de la source de lumière...
		glPushMatrix();
		//glLoadIdentity();
		glTranslated(lightPosition[0], lightPosition[1], lightPosition[2]);
		glRotated(vAngle, 1, 0, 0);
		glRotated(hAngle, 0, 1, 0);
		glRotated(vAngle, 0, 0, 1);
		//glTranslated(origine.x, origine.y, origine.z);
		glLightfv(this->lum, GL_SPOT_DIRECTION, new float[] {(float)direction.x, (float)direction.y, (float)direction.z});
		glPopMatrix();

		
	}

	GLfloat* obtDirection() {
		return lightDirection;
	}

};