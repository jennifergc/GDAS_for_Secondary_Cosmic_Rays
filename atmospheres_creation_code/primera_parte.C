/*codigo que imprime la primera parte del FILEATM*/
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
void primera_parte(){


        TString datos; //Directorio de los .long
        datos = "./";
        std::vector<double> promedios1;
	std::vector<double> promedios2;
	std::vector<double> promedios3;
	std::vector<double> promedios4;
	std::vector<double> promedios5;
        double maxSum=0;
        double maxDepth=0;
        vector<TGraph*> arrayGraph;
        bool primerArchivo = true;
        int cantidadArchivos = 0;
        double n = TMath::Cos((TMath::Pi())/4.0);
        std::cout.precision(10);
        cout <<"----"<<n<<endl;
                /********************** INICIO DEL BLOQUE 1 ************************/
        TSystemDirectory dir(datos, datos);
        TList *files = dir.GetListOfFiles();
	vector<Double_t> arraySum;
	vector<Double_t> arrayDepth;
	vector<Double_t> arrayCol2;
	vector<Double_t> arrayCol3;
	vector<Double_t> arrayCol4;
        ofstream salida;
	salida.open("primera_parte.txt",ios::out);
                salida << "# atmospheric parameters ATMLAY, A, B, C respectively"<<endl;
        if (files) {
                TSystemFile *file;
                TString fname;
                TString archivo;
                TIter next(files);
                while((file=(TSystemFile*)next())){
                        fname = file->GetName();
                        if (!file->IsDirectory() && fname.EndsWith(".dat")) {
                                archivo = datos + fname;
                                cout << archivo << endl;                                      //revivido
                        }else{
                                continue;
                        }
                        TString aux = "";
                        Double_t depth;
                        Double_t col2;
			Double_t col3;
			Double_t col4;
			Double_t sum;
			
                        arraySum.clear();
                        arrayDepth.clear();
                        arrayCol2.clear();
                        arrayCol3.clear();
                        arrayCol4.clear();
			int nroLinea = 0;
                        cantidadArchivos++;
			cout << "Leyendo archivo:"<<cantidadArchivos<<endl;
                        ifstream entrada;
                        entrada.open(archivo);                                //JENNIFER entrada abre el archivo para leerse

                        while(aux != "respectively"){
                                entrada >> aux;
                        cout << "AUX is=  "<<aux<<endl;
			}
                        entrada >> aux;
//
			while (aux != "#") {
  				depth = atof(aux);
                                entrada >> col2 >> col3 >> col4 >> sum;
                       		cout << "ultima columna" <<sum<<endl;
                                arrayDepth.push_back(depth);
                                arraySum.push_back(sum);
                                arrayCol2.push_back(col2);
                                arrayCol3.push_back(col3);
                                arrayCol4.push_back(col4);
//
				if(primerArchivo){
				promedios1.push_back(depth);
				promedios2.push_back(col2);
				promedios3.push_back(col3);
				promedios4.push_back(col4);
				promedios5.push_back(sum);
				}else{
				if (nroLinea < promedios1.size()) {
				promedios1[nroLinea] += (depth);
				promedios2[nroLinea] += (col2);
				promedios3[nroLinea] += (col3);
				promedios4[nroLinea] += (col4);
				promedios5[nroLinea] += (sum);
				}
			}
//                                
				nroLinea++;
                                entrada >> aux;
                                }
			if(primerArchivo){
			arrayDepth.pop_back();
                        arrayCol2.pop_back();
                        arrayCol3.pop_back();
                        arrayCol4.pop_back();
                        arraySum.pop_back();
                        }
                        primerArchivo = false;
			cout <<"numero_lineas_leidas del archivo"<<nroLinea<<endl;	
}
			 if (salida.is_open()){
                        Double_t c1;
                        Double_t c2;
                        Double_t c3;
                        Double_t c4;
                        Double_t c5;
                        for(unsigned int i=0; i < arrayDepth.size(); i++){
                        c1 = promedios1.at(i) /=cantidadArchivos;
                        c2 = promedios2.at(i) /=cantidadArchivos;
                        c3 = promedios3.at(i) /=cantidadArchivos;
                        c4 = promedios4.at(i) /=cantidadArchivos;
                        c5 = promedios5.at(i) /=cantidadArchivos;
                        salida << c1<<"  "<<c2<<"  "<<c3<<"  "<<c4<<"  "<<c5<<endl;}
                      }
                        cout <<"Archivos leidos" <<" = "<< cantidadArchivos<<endl;                                     //JENNIFER NUEVA LINEA
                   } 
salida.close();
}
