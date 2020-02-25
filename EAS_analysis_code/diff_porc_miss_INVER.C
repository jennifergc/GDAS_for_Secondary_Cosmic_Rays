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
void diff_porc_miss_INVER(){

        TString datos; //Directorio de los .long
        datos = "./";
        vector<Double_t> arraySinG_char;
	vector<Double_t> arraySinG_muon;
	vector<Double_t> total_energy_ConG;
	vector<Double_t> total_energy_SinG;
	vector<Double_t> arrayConG_char;
	vector<Double_t> arrayConG_muon;
	vector<Double_t> errorSinG_char;
	vector<Double_t> errorSinG_muon;
	vector<Double_t> errorConG_char;
	vector<Double_t> errorConG_muon;
	vector<Double_t> errorConG_total;
	vector<Double_t> errorSinG_total;
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
	vector<Double_t> arrayDif_Total;
        ofstream salida;
	salida.open("dif_energy_fe_1E6.den",ios::out);
	Double_t depth;
	Double_t charg;
	Double_t muon;
	Double_t total;
	Double_t echarg;
	Double_t emuon;
	Double_t etotal;
        if (files) {
                TSystemFile *file;
                TString fname;
                TString archivo;
                TIter next(files);
                while((file=(TSystemFile*)next())){
                        fname = file->GetName();
                        if (!file->IsDirectory() && fname.EndsWith(".mise")) {
                                archivo = datos + fname;
                                cout <<"Abriendo el archivo: " <<archivo << endl;                                      //revivido
                        }else{
                                continue;
                        }
                        TString aux = "";
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
                                entrada >> charg >> echarg >> muon >> emuon >> total >> etotal;
                       		cout << "depth "<<depth<<"cargadas "<<charg <<"muon "<<muon<< "total"<<total <<endl;
//
				if(primerArchivo){
				arrayDepth.push_back(depth);
				arraySinG_char.push_back(charg);
				arraySinG_muon.push_back(muon);
				total_energy_SinG.push_back(total);
				errorSinG_char.push_back(echarg);
				errorSinG_muon.push_back(emuon);
				errorSinG_total.push_back(etotal);
				}else{
				if (nroLinea < arrayDepth.size()) {
				arrayConG_char.push_back(charg);
				arrayConG_muon.push_back(muon);
				total_energy_ConG.push_back(total);
				errorConG_char.push_back(echarg);
				errorConG_muon.push_back(emuon);
				errorConG_total.push_back(etotal);
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
			Double_t c6;
			Double_t c7;
			cout<<"tamanos de los vectores con GDAS "<<arrayDepth.size()<<"  "<<arrayConG_muon.size()<<"  "<<arrayConG_char.size()<<endl;
		        cout<<"tamanos de los vectores sin GDAS "<<arrayDepth.size()<<"  "<<arraySinG_muon.size()<<"  "<<arraySinG_char.size()<<endl;	
			cout <<"#########################################-----viene el FOR---->##################"<<endl;
                        for(int i=0; i < arraySinG_char.size(); i++){
                        c1 = arrayDepth.at(i);
                        c2 = ((arrayConG_char.at(i)-arraySinG_char.at(i))*100)/arrayConG_char.at(i);
			c3 = ((arrayConG_muon.at(i)-arraySinG_muon.at(i))*100)/arrayConG_muon.at(i);
			c4 = ((total_energy_ConG.at(i)-total_energy_SinG.at(i))*100)/total_energy_ConG.at(i);
			c5 = sqrt((pow((arraySinG_char.at(i)/pow(arrayConG_char.at(i),2)),2)*pow(errorConG_char.at(i),2))+(pow((-1/arrayConG_char.at(i)),2)*(pow(errorSinG_char.at(i),2)))); //ERROR PARA CARGADAS
			c6 = sqrt((pow((arraySinG_muon.at(i)/pow(arrayConG_muon.at(i),2)),2)*pow(errorConG_muon.at(i),2))+(pow((-1/arrayConG_muon.at(i)),2)*(pow(errorSinG_muon.at(i),2)))); //ERROR PARA MUONES
			c7 = sqrt((pow((total_energy_SinG.at(i)/pow(total_energy_ConG.at(i),2)),2)*pow(errorConG_total.at(i),2))+(pow((-1/total_energy_ConG.at(i)),2)*(pow(errorSinG_total.at(i),2))));//ERRORTOT

			arrayDif_Muon.push_back(c3);
			arrayDif_Total.push_back(c4);
                        salida << c1<<"  "<<c2<<"  "<<c5<<"  "<<c3<<"  "<<c6<<"  "<<c4<<"  "<<c7<<"  "<<endl;
			}
                        cout <<"Archivos leidos" <<" = "<< cantidadArchivos<<endl;  //JENNIFER NUEVA LINEA
			 }
			salida.close();
}
}

