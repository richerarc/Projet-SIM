#pragma once
class Temps{
public:

	Temps(){

	}

	Temps(double tempsEnSecondes){
		this->tempsEnSecondes = tempsEnSecondes;
	}

	double enSecondes(){
		return this->tempsEnSecondes;
	}

	double enMillisecondes(){
		return this->tempsEnSecondes * 1000;
	}

	double enMicrosecondes(){
		return this->tempsEnSecondes * 1000000;
	}

	double enMinutes(){
		return this->tempsEnSecondes / 60;
	}

	double enHeures(){
		return this->tempsEnSecondes / 3600;
	}

	void defTemps(double tempsEnSecondes){
		this->tempsEnSecondes = tempsEnSecondes;
	}

private:
	double tempsEnSecondes;
};
