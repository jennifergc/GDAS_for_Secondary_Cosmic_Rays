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
void diff_porcent_INVER(){

        TString datos; //Directorio de los .long
        datos = "./";
        vector<Double_t> arraySinG_char;
	vector<Double_t> arraySinG_muon;
	vector<Double_t> arrayConG_char;
	vector<Double_t> arrayConG_muon;
	vector<Double_t> errorSinG_char;
	vector<Double_t> errorSinG_muon;
	vector<Double_t> errorConG_char;
	vector<Double_t> errorConG_muon;
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
	vector<Double_t> arrayDif_Char;
	vector<Double_t> arrayDepth;
	vector<Double_t> arrayDif_Muon;
        ofstream salida;
	salida.open("dif_longi_fe_1E6.difl",ios::out);
	Double_t depth;
	Double_t charg;
	Double_t muon;
	Double_t echarg;
	Double_t emuon;
        if (files) {
                TSystemFile *file;
                TString fname;
                TString archivo;
                TIter next(files);
                while((file=(TSystemFile*)next())){
                        fname = file->GetName();
                        if (!file->IsDirectory() && fname.EndsWith(".misl")) {
                                archivo = datos + fname;
                                cout <<"Abriendo el archivo: " <<archivo << endl;                                      //revivido
                        }else{
                                continue;
                        }
                        TString aux = "";
                        arrayDif_Char.clear();
                        arrayDif_Muon.clear();
			int nroLinea = 0;
                        cantidadArchivos++;
			cout << "Leyendo archivo:"<<cantidadArchivos<<endl;
                        ifstream entrada;
                        entrada.open(archivo);                                //JENNIFER entrada abre el archivo para leerse

                        while(aux != "DATA"){
                                entrada >> aux;
                        cout << "AUX is=  "<<aux<<endl;
			}
                        entrada >> aux;
//
			while (entrada.good() && !entrada.eof()) {
  				depth = atof(aux);
                                entrada >> charg>> echarg >> muon>> emuon;
                       		cout << "depth "<<depth<<"cargadas "<<charg <<"muon "<<muon<<endl;
//
				if(primerArchivo){
				arrayDepth.push_back(depth);
				arraySinG_char.push_back(charg);
				arraySinG_muon.push_back(muon);
				errorSinG_char.push_back(echarg);
				errorSinG_muon.push_back(emuon);
				}else{
				if (nroLinea < arrayDepth.size()) {
				arrayConG_char.push_back(charg);
				arrayConG_muon.push_back(muon);
				errorConG_char.push_back(echarg);
				errorConG_muon.push_back(emuon);
				}
			}
//                                
				nroLinea++;
                                entrada >> aux;
                                }//FIN BUCLE DE LECTURA DE ARCHIVOS
			if(primerArchivo){
			cout <<"TAMANO DEL DEPTH  "<<arrayDepth.size()<<endl;
                        }
                        primerArchivo = false;
			cout <<"numero_lineas_leidas del archivo  "<<nroLinea <<endl;
				
}
			
			if (salida.is_open()){
                        Double_t c1;
                        Double_t c2;
                        Double_t c3;
			Double_t c4;
			Double_t c5;
			cout<<"tamanos de los vectores con GDAS "<<arrayDepth.size()<<"  "<<arrayConG_muon.size()<<"  "<<arrayConG_char.size()<<endl;
		        cout<<"tamanos de los vectores sin GDAS "<<arrayDepth.size()<<"  "<<arraySinG_muon.size()<<"  "<<arraySinG_char.size()<<endl;	
			cout <<"#########################################-----viene el FOR---->##################"<<endl;
                        for(int i=0; i < 89; i++){
                        c1 = arrayDepth.at(i);
                        c2 = ((arrayConG_char.at(i)-arraySinG_char.at(i))*100)/arrayConG_char.at(i);
			c3 = ((arrayConG_muon.at(i)-arraySinG_muon.at(i))*100)/arrayConG_muon.at(i);
			c4 = sqrt((pow((arraySinG_char.at(i)/pow(arrayConG_char.at(i),2)),2)*pow(errorConG_char.at(i),2))+(pow((-1/arrayConG_char.at(i)),2)*(pow(errorSinG_char.at(i),2)))); //ERROR PARA CARGADAS
			c5 = sqrt((pow((arraySinG_muon.at(i)/pow(arrayConG_muon.at(i),2)),2)*pow(errorConG_muon.at(i),2))+(pow((-1/arrayConG_muon.at(i)),2)*(pow(errorSinG_muon.at(i),2)))); //ERROR PARA MUONES
			arrayDif_Char.push_back(c2);
			arrayDif_Muon.push_back(c3);
                        salida << c1<<"  "<<c2<<"  "<<c4<<"  "<<c3<<"  "<<c5<<endl;
			}
                        cout <<"Archivos leidos" <<" = "<< cantidadArchivos<<endl;  //JENNIFER NUEVA LINEA
			 }
			salida.close();
}
}

