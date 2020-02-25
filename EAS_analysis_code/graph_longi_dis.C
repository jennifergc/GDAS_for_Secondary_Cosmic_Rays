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
void graph_longi_dis(){

	
	TString datos; //Directorio de los .long
	datos = "./";  //los .long estan en la misma direcci�n que este programa        
	std::vector<double> promedios; //declración de vectores donde vamos a guardar algunas cuentas
	std::vector<double> promedios2;
        double maxSum=0; 
        double maxDepth=0;
	vector<TGraph*> arrayGraph;
	bool primerArchivo = true;
	int cantidadArchivos = 0;
	double n = TMath::Cos((TMath::Pi())/4.0);
//	std::cout.precision(10);
	cout <<"----"<<n<<endl;
	int shower = 1;
//	
	TSystemDirectory dir(datos, datos); 
	TList *files = dir.GetListOfFiles();
	vector<Double_t> arraySum; //vamos a guardar las variables sum y depth como vectores. Acá los declaramos
	vector<Double_t> arrayDepth;
	ofstream salida;
	salida.open("malargue_sinGDAS.dat", ios::out);
//	
	if (files) { //si el rchivo existe, haga las �rdenes que siguen
		TSystemFile *file; //direcciona el archivo al string
		TString fname;     //crea un nuevo string con el nombre fname
		TString archivo;
		TIter next(files);
		while((file=(TSystemFile*)next())){ //WHILE QUE LEE EL ARCHIVO
                            fname = file->GetName(); //fname guardará el nombre de los archivos en un array de valores
                            if (!file->IsDirectory() && fname.EndsWith("malargue_fe_1E8_sinGDAS.long")) {
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
                            arraySum.clear();
                            int nroLinea = 0; //variable para contar los numeros de lineas de cada archivo
                            cantidadArchivos++; //contamos cada archivo que entra a este while
                            ifstream entrada;   //la variable entrada es la señal del archivo
                            entrada.open(archivo); //abrimos el archivo
                            while(aux != "CHERENKOV"){ //si el string aux es diferente a la palabra CHERENKOV, renombra aux con esa entada
                                    entrada >> aux; 
                            }
                            entrada >> aux >> aux2; //igual si no se cumple se guardará
//                            
                            while(aux != "LONGITUDINAL" && aux2 != "ENERGY"){ //se seguirá leyendo al archivo, llegará a un lan los datos.
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
					if(shower == 51){
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
			}
//			    
			cout << "lluvias detectadas en el archivo "<< archivo <<"= "<< shower<<endl;
		} //FIN DEL WHILE QUE LEE EL ARCHIVO
		for(unsigned int i=0; i<arrayDepth.size(); i++){                //calcula el maximo de muones y particulas cargadas sobre el promedio
			promedios.at(i) /= 50;
			promedios2.at(i) /= 50;
		}
		Double_t maxC = 0;
		Double_t maxM = 0;
		Double_t profC = 0;
		Double_t profM = 0;
		for(unsigned int j=0; j < arrayDepth.size(); j++){
			if(promedios.at(j) > maxC){
				maxC = promedios.at(j);
				profC= arrayDepth.at(j);
			}
			if(promedios2.at(j) > maxM){
				maxM = promedios2.at(j);
				profM= arrayDepth.at(j);
			}
		}
		cout <<"Depth Muones: "<< profM<<"  " << "Maximo muones: "<< maxM << " "<<"Depth Cargadas: "<< profC<<"  "<<"Maximo Cargadas: "<<" "<< maxC <<endl;

		if (salida.is_open()){ //IF QUE ESCRIBEE EL ARCHIVO DE SALIDA
			Double_t c1;
			Double_t c2;
			Double_t c3;
			for(unsigned int i=0; i< arrayDepth.size(); i++){
				c1= arrayDepth.at(i);
				c2= promedios.at(i);
				c3= promedios2.at(i);
			salida << c1<<"  "<<c2<<"  "<<c3<<endl;
		}
		}//FIN DEL IF QUE ESCRIBE EL ARCHIVO DE SALIDA
//		
		TGraph *gr = new TGraph(arrayDepth.size(), &(arrayDepth[0]), &(promedios[0]));
		arrayGraph.push_back(gr);
		gr ->SetName(fname);
                TFile *f = new TFile("QGSII_0_Charged.root","RECREATE");
                TCanvas *c1 = new TCanvas("Charged","Charged");

                for(unsigned int i=0; i < arrayDepth.size(); i++){
                    if(maxSum < promedios.at(i)){
                    maxSum = promedios.at(i);
                    maxDepth = arrayDepth.at(i);
                    }
                    promedios.at(i);
                }
        
               
                gr->SetTitle("Distribucion longitudinal de Particulas cargadas, GDAS Malargue, fe 1E3GeV");
                gr->SetName("Particulas cargadas_fixed");
                gr->SetLineWidth(4);
                gr->SetLineColor(kBlue);
                gr->GetYaxis()->SetTitle("Numero particulas cargadas");
                gr->GetYaxis()->CenterTitle();
                gr->GetXaxis()->SetTitle("Profundidad atmosferica (g/cm^{2})");
                gr->Draw("AL");
                for(unsigned int i=0; i < arrayGraph.size(); i++){
                    arrayGraph[i]->SetLineColor(kBlack);
                    arrayGraph[i]->Draw("L");
                    arrayGraph[i]->Write();

                }
                    

                c1->Update();
		c1->Write();
                f->Close();
	
	} //IF QUE CONSIDERA AL ARCHIVO si el archivo existe haga las érdenes que siguen
salida.close();
	} //CIERRA EL VOID
