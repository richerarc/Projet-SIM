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
	void defTemps(double tempsEnSecondes){
		this->tempsEnSecondes = tempsEnSecondes;
	}
private:
	double tempsEnSecondes;
};
