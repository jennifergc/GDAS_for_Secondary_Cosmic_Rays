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
void errores_longi(){

	
	TString datos; //Directorio de los .long
	datos = "./";  //los .long estan en la misma direcci�n que este programa        
	std::vector<double> promedios; //declración de vectores donde vamos a guardar algunas cuentas
	std::vector<double> promedios2;
	std::vector<double> errorM;
	std::vector<double> errorC;
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
	salida.open("errores_longi_sinGDAS_proton_1E8.misl", ios::out);
//	
	if (files) { //************************************************si el archivo existe, haga las denes que siguen****************BLOQUE 1**************************
		TSystemFile *file; //direcciona el archivo al string
		TString fname;     //crea un nuevo string con el nombre fname
		TString archivo;
		TIter next(files);
		while((file=(TSystemFile*)next())){ //**********************************************************************WHILE QUE LEE EL ARCHIVO********************
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
                            while(aux != "CHERENKOV"){ //si el string aux es diferente a la palabra CHERENKOV, renombra aux con esa entada
                                    entrada >> aux; 
                            }
                            entrada >> aux >> aux2; //igual si no se cumple se guardará
//                            
                            while(aux != "LONGITUDINAL" && aux2 != "ENERGY"){ //********************************************LLENADO DE VCTORES**************************
				if(nroLinea == 0){
				cout << "Numero de linea: "<< nroLinea <<" Depth: "<< aux << " y gammas:  " << aux2 <<endl;
				}
                            	depth = atof(aux); //convierte aux en una variable numerica un entero
				gamma = atof(aux2);
                                entrada >> emI >> emC >> muI >> muC >> hadrI >> hadrC >> neutrino >> sum; //lee las otras entrada
				Double_t mode = hadrC; // llama una nueva variable mode con el valor de hadrC PARTICULAS CARGADAS
                            	Double_t mode2 = muI + muC;
                                if(shower == 1){
					arrayDepth.push_back(depth);
                                	promedios.push_back(mode); //el vector promedios también guarda los valores de mode
                            		promedios2.push_back(mode2);
				}else{
					promedios[nroLinea] += mode;
					promedios2[nroLinea] += mode2;
				}
			        nroLinea++;
                                entrada >> aux >> aux2;
//
				if(aux == "LONGITUDINAL" && aux2 == "ENERGY"){
					shower++;
					if(shower == 11){
					break;
					}
					while(aux != "CHERENKOV"){
					entrada >> aux;
					}
					cout << "CHERENKOV IS: "<< aux << endl;
					if(aux == "CHERENKOV"){
						nroLinea = 0;
						entrada >> aux >> aux2;
						cout << "Descartada seccion no deseada. Comienzo de la lectura de la lluvia numero: "<< shower <<endl;
						}
				}
//                            
			}//***********************************************************************************FIN LLENADO DE VECTORES POR BLOQUES*************************
//			    
		} //**************************************************************************************FIN DEL WHILE QUE LEE EL ARCHIVO********************************
		for(unsigned int i=0; i<arrayDepth.size(); i++){
			promedios.at(i) /= 10;
			promedios2.at(i) /= 10;
		}

	}//FIN IF SI EXISTEN FILES****************************************************************************************************FIN BLOQUE 1************************

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
	   if (files) { //si el rchivo existe, haga las odenes que siguen
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
                        while(aux != "CHERENKOV"){ //si el string aux es diferente a la palabra CHERENKOV, renombra aux con esa entada
	                        entrada2 >> aux; 
	                }
                        entrada2 >> aux >> aux2; //igual si no se cumple se guarda
                       while(aux != "LONGITUDINAL" && aux2 != "ENERGY"){
//			       cout << "LEYENDO VLORES DE RCHIVOS"<<endl;
			       depth = atof(aux); //convierte aux en una variable numerica un entero
			       entrada2 >> emI >> emC >> muI >> muC >> hadrI >> hadrC >> neutrino >> sum; //lee las otras entrada
//			       cout << "DEPTH: " << depth <<"  emI: " << emI <<endl;
			       Double_t sigmaC = pow((hadrC-promedios[nroLinea2]),2); // llama una nueva variable mode con el valor de hadrC PARTICULAS CARGADAS
			       Double_t sigmaM = pow(((muI + muC)-promedios2[nroLinea2]),2);
			       if(shower2 == 1){
				       errorC.push_back(sigmaC); //el vector promedios tambn guarda los valores de mode
				       errorM.push_back(sigmaM);
			       }else{
				       errorC[nroLinea2] += sigmaC;
				       errorM[nroLinea2] += sigmaM;
			       }
			       nroLinea2++;
			       entrada2 >> aux >> aux2;

			       
			       if(aux == "LONGITUDINAL" && aux2 == "ENERGY"){
				       shower2++;
				       if(shower2 == 11){
					       break;
				       }
				       while(aux != "CHERENKOV"){
					       entrada2 >> aux;
				       }
				       cout << "CHERENKOV IS: "<< aux << endl;
				       if(aux == "CHERENKOV"){
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
						}	
	
if (salida.is_open()){ //IF QUE ESCRIBEE EL ARCHIVO DE SALIDA
	Double_t c1;
	Double_t c2;
	Double_t c3;
	Double_t c4;
	Double_t c5;
	Double_t c6;
	for(unsigned int i=0; i< arrayDepth.size(); i++){
		c1= arrayDepth.at(i);
		c2= promedios.at(i);
		c3= errorC.at(i);
		c4= promedios2.at(i);
		c5= errorM.at(i);
		salida << c1<<"  "<<c2<<"  "<<c3<<"  "<<c4<<"  "<<c5<<endl;
	}
}//FIN DEL IF QUE ESCRIBE EL ARCHIVO DE SALIDA



//**************************************FIN RUTINA ERRORES*********************************	  
				}//IF QUE CONSIDERA AL ARCHIVO si el archivo existe haga las érdenes que siguen
salida.close();
	} //CIERRA EL VOID
