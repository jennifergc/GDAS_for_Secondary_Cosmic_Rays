/* Codigo que grafica usando root la distribucion longitudinal de una cantidad de lluvias generadas con Rain.pl
 * para una particula con una energia determinada, calcula el promedio entre los observables de esas lluvias definidas 
 * en el archivo de salida de la simulacion.
 * El codigo tambien puede hacer esta labor para varios archivos promediandolos entre si. 
*/

#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TFile.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TVectorT.h"
#include "TSystemDirectory.h"
#include "TMath.h"


/*File format *
 *

DEPTH GAMMAEM IONIZ EM CUTMU IONIZMU CUTHADR IONIZHADR CUT NEUTRINOSUM
*
 * */
void errores_missing(){

	
	TString datos; //Directorio de los .long
	datos = "./";  //los .long estan en la misma direcci�n que este programa        
	std::vector<double> promedios; //declración de vectores donde vamos a guardar algunas cuentas
	std::vector<double> promedios2;
	std::vector<double> TotalEnergy;
	std::vector<double> errorM;
	std::vector<double> errorC;
	std::vector<double> errorT;
	bool primerArchivo = true;
	int cantidadArchivos = 0;
	int cantidadArchivos2 = 0;
	cout <<"----"<<endl;
	int shower = 1;
	int shower2 = 1;
//	
	TSystemDirectory dir(datos, datos); 
	TList *files = dir.GetListOfFiles();
	vector<Double_t> arrayDepth;
	ofstream salida;
	salida.open("errores_missing_sinGDAS_proton_1E8.mise", ios::out);
//	
	if (files) { //si el rchivo existe, haga las denes que siguen
		TSystemFile *file; //direcciona el archivo al string
		TString fname;     //crea un nuevo string con el nombre fname
		TString archivo;
		TIter next(files);
		while((file=(TSystemFile*)next())){ //WHILE QUE LEE EL ARCHIVO
                            fname = file->GetName(); //fname guardará el nombre de los archivos en un array de valores
                            if (!file->IsDirectory() && fname.EndsWith("proton_1E8_sinGDAS.long")) {
                            	archivo = datos + fname;
                                    cout << archivo << endl;
                            }else{
                                    continue;
                            }
                            TString aux = "";//declara la variable aux como un string vacio
			    TString aux2 = "";//variable aux2 como string para determinar si detenerse o no
                            Double_t depth; //declara nuevas variables con las que leeremos las lineas del archivo una a una
                            Double_t gamma;
                            Double_t emI;
                            Double_t emC;
                            Double_t muI;
                            Double_t muC;
                            Double_t hadrI;
                            Double_t hadrC;
                            Double_t neutrino;
                            Double_t sum;
                            int nroLinea = 0; //variable para contar los numeros de lineas de cada archivo
                            cantidadArchivos++; //contamos cada archivo que entra a este while
                            ifstream entrada;   //la variable entrada es la señal del archivo
                            entrada.open(archivo); //abrimos el archivo
//===============================================================================================================
while(aux != "SUM"){ //si el string aux es diferente a la palabra CHERENKOV, renombra aux con esa entada
	entrada >> aux; 
}

entrada >> aux >> aux2; //igual si no se cumple se guarda

while(aux != "FIT" && aux2 != "OF"){ //se seguieyendo al archivo, llea un lan los datos.
	if(nroLinea == 0){
		cout << "Numero de linea: "<< nroLinea <<" Depth: "<< aux << " y gammas:  " << aux2 <<endl;
	}
	depth = atof(aux); //convierte aux en una variable numerica un entero
	gamma = atof(aux2);
	entrada >> emI >> emC >> muI >> muC >> hadrI >> hadrC >> neutrino >> sum; //lee las otras entrada
	Double_t mode = hadrC; // llama una nueva variable mode con el valor de hadrC PARTICULAS CARGADAS
	Double_t mode2 = muI + muC;
	Double_t total = sum;
	if(shower == 1){
		arrayDepth.push_back(depth);
		promedios.push_back(mode); //el vector promedios tambiÃ©n guarda los valores de mode
		promedios2.push_back(mode2);
		TotalEnergy.push_back(total);
	}else{
		promedios[nroLinea] += mode;
		promedios2[nroLinea] += mode2;
		TotalEnergy[nroLinea] += total;
	}
	nroLinea++;
	entrada >> aux >> aux2;
	if(aux == "FIT" && aux2 == "OF"){
		shower++;
		if(shower == 11){
			break;
		}
		while(aux != "SUM"){
			entrada >> aux;
		}
		cout << "SUM IS: "<< aux << endl;
		if(aux == "SUM"){
			nroLinea = 0;
			entrada >> aux >> aux2;
			cout << "Descartada seccion no deseada. Comienzo de la lectura de la lluvia numero: "<< shower <<endl;
		}
	}
}
cout << "lluvias detectadas en el archivo "<< archivo <<"= "<< shower<<endl;
} //FIN DEL WHILE QUE LEE EL ARCHIVO

//===============================================================================================================		
		for(unsigned int i=0; i<arrayDepth.size(); i++){
			promedios.at(i) /= 10;
			promedios2.at(i) /= 10;
			TotalEnergy.at(i) /= 10;
		}

	}//FIN IF SI EXISTEN FILES

	TString aux = "";//declara la variable aux como un string vacio
	TString aux2 = "";//variable aux2 como string para determinar si detenerse o no
	Double_t depth = 0; //declara nuevas variables con las que leeremos las lineas del archivo una a una
	Double_t gamma = 0;
	Double_t emI = 0;
	Double_t emC = 0;
	Double_t muI = 0;
	Double_t muC = 0;
	Double_t hadrI = 0;
	Double_t hadrC = 0;
	Double_t neutrino = 0;
	Double_t sum = 0;
	int nroLinea2 = 0;
        
//***********************COMIENZO RUTINA QUE LEE NUEVAMENTE EL ARCHIVO*************************************************************//
	   //
	   if (files) { //si el rchivo existe, haga la ordenes que siguen
		   TSystemFile *file2; //direcciona el archivo al string
		   TString fname2;     //crea un nuevo string con el nombre fname
		   TString archivo2;
		   TIter next(files);
      		while((file2=(TSystemFile*)next())){ //WHILE QUE LEE EL ARCHIVO
			fname2 = file2->GetName();
               		if (!file2->IsDirectory() && fname2.EndsWith("proton_1E8_sinGDAS.long")) {
                    		archivo2 = datos + fname2;
                        	cout << archivo2 <<"  >>ENTRA A SEGUNDA PARTE ARCHIVO RECONOCIDO"<<endl;
                        }else{
                              continue;
                              }
                        cantidadArchivos2++; //contamos cada archivo que entra a este while
                        ifstream entrada2;   //la variable entrada es la s del archivo
                        entrada2.open(archivo2); //abrimos el archivo
	                while(aux != "SUM"){        
				entrada2 >> aux; 
	                }
                        entrada2 >> aux >> aux2; //igual si no se cumple se guarda
			while(aux != "FIT" && aux2 != "OF"){       
//				cout << "LEYENDO VLORES DE RCHIVOS"<<endl;
				       depth = atof(aux); //convierte aux en una variable numerica un entero
				       entrada2 >> emI >> emC >> muI >> muC >> hadrI >> hadrC >> neutrino >> sum; //lee las otras entrada
//				       cout << "DEPTH: " << depth <<"  emI: " << emI <<endl;
			       		Double_t sigmaC = pow((hadrC-promedios[nroLinea2]),2); // llama una nueva variable mode con el valor de hadrC PARTICULAS CARGADAS
			       		Double_t sigmaM = pow(((muI + muC)-promedios2[nroLinea2]),2);
					Double_t sigmaT = pow((sum - TotalEnergy[nroLinea2]),2);
			       if(shower2 == 1){
				       errorC.push_back(sigmaC); //el vector promedios tambn guarda los valores de mode
				       errorM.push_back(sigmaM);
				       errorT.push_back(sigmaT);
			       }else{
				       errorC[nroLinea2] += sigmaC;
				       errorM[nroLinea2] += sigmaM;
				       errorT[nroLinea2] += sigmaT;
			       }
			       nroLinea2++;
			       entrada2 >> aux >> aux2;

			       
			if(aux == "FIT" && aux2 == "OF"){	       
				       shower2++;
				       if(shower2 == 11){
					       break;
				       }
				while(aux != "SUM"){	       
				       entrada2 >> aux;
				       }
				       cout << "SUM IS: "<< aux << endl;
				if(aux == "SUM"){	       
					       nroLinea2 = 0;
					       entrada2 >> aux >> aux2;
					       cout << "Descartada seccion no deseada. Comienzo de la lectura de la lluvia numero: "<< shower2 <<endl;
				       }
		       }
		       }
	  } //FIN DEL WHILE QUE LEE EL ARCHIVO	
for(unsigned int i=0; i<arrayDepth.size(); i++){                //calcula el maximo de muones y particulas cargadas sobre el promedio
	errorC.at(i)= sqrt(errorC.at(i)/10);
	errorM.at(i)= sqrt(errorM.at(i)/10);
	errorT.at(i)= sqrt(errorT.at(i)/10);
						}	
	
if (salida.is_open()){ //IF QUE ESCRIBEE EL ARCHIVO DE SALIDA
	Double_t c1;
	Double_t c2;
	Double_t c3;
	Double_t c4;
	Double_t c5;
	Double_t c6;
	Double_t c7;
	for(unsigned int i=0; i< arrayDepth.size(); i++){
		c1= arrayDepth.at(i);
		c2= promedios.at(i);
		c3= errorC.at(i);
		c4= promedios2.at(i);
		c5= errorM.at(i);
		c6= TotalEnergy.at(i);
		c7= errorT.at(i);
		salida << c1<<"  "<<c2<<"  "<<c3<< "  "<< c4 <<"  "<< c5 <<"  "<< c6 <<"  "<< c7 <<endl;
	}
}//FIN DEL IF QUE ESCRIBE EL ARCHIVO DE SALIDA



//**************************************FIN RUTINA ERRORES*********************************	  
				}//IF QUE CONSIDERA AL ARCHIVO si el archivo existe haga las érdenes que siguen
salida.close();
	} //CIERRA EL VOID
