/* Codigo que grafica usando root un pack de graficas una sobre la otra y 
ademas calcula el promedio y lo grafica encima. 

Tambien seleccciona un bloque de datos de una archivo más grande, en este caso el bloque . 

Tambien seleccciona un bloque de datos de una archivo más grande, en este caso el bloque 1*/

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
void segunda_parte(){
	
	TString datos; //Directorio de los .long
	datos = "./";        
	std::vector<double> promedios;
        double maxSum=0;
        double maxDepth=0;
	vector<TGraph*> arrayGraph;
	bool primerArchivo = true;
	int cantidadArchivos = 0;
	double n = TMath::Cos((TMath::Pi())/4.0);
	std::cout.precision(10);
		/********************** INICIO DEL BLOQUE 1 ************************/
	TSystemDirectory dir(datos, datos);
	TList *files = dir.GetListOfFiles();
	vector<Double_t> arraySum;
	vector<Double_t> arrayDepth;
	ofstream salida;
	if (files) {
		TSystemFile *file;
		TString fname;
		TString archivo;
		TIter next(files);
		salida.open("segunda_parte.txt",ios::out);
		while((file=(TSystemFile*)next())){
                	fname = file->GetName();
                        if (!file->IsDirectory() && fname.EndsWith(".dat")) {
                        	archivo = datos + fname;
                        }else{
                       		continue;
                        }
                        TString aux = "";
                        Double_t depth;
                        Double_t sum;
                        arraySum.clear();
                        int nroLinea = 0; 
                        cantidadArchivos++;
                        ifstream entrada;
                        entrada.open(archivo);                                //JENNIFER entrada abre el archivo para leerse

                        while(aux != "columns"){
	                        entrada >> aux; 
                        }
        	        entrada >> aux;
                        while (entrada.good() && !entrada.eof()) {
				depth = atof(aux);
				entrada >> sum;
                        	arraySum.push_back(sum);
				if(primerArchivo){                                       
                                        arrayDepth.push_back(depth);                                      //JENNIFER estaba comentado
                                        promedios.push_back(sum);
                                } else {
#                                       if 0
#                                       else
                                        if (nroLinea < promedios.size()) {
                                                promedios[nroLinea] += sum;
                                        }
                                        else {
                                                cerr << "File " << archivo << " longer than first!" <<
                                                "first: " << promedios.size() << " archivo: " << nroLinea << endl;
                                        }
#                                       endif
                                }
                                nroLinea++;
                                entrada >> aux;
                        }                                                                // } fin While "longitudinal"
                        if(primerArchivo){
                        	arrayDepth.pop_back(); 
                        }
                        arraySum.pop_back();
			promedios.pop_back();
                        primerArchivo = false;
//			
			TGraph *gr = new TGraph(promedios.size(), &(arrayDepth[0]), &(arraySum[0]));
                        arrayGraph.push_back(gr);
                        gr->SetName(fname);
		        //double maxS=0;
        		//double maxD=0;
			//unsigned int finWhile = min(arrayDepth.size(), promedios.size());
			//for(unsigned int i=0; i < arrayDepth.size(); i++){
                        //	if(maxS < arrayDepth.at(i)){
                        //     	maxS = arraySum.at(i);
                        //     	maxD = arrayDepth.at(i);
                        //	}
	//}
	}
			if (salida.is_open()){
                        Double_t altura;
                        Double_t Refin;
                        salida << "# atmospheric height [m] and refractive index columns"<<endl;
                        for(unsigned int i=0; i < promedios.size(); i++){
                        altura = arrayDepth.at(i);
                        Refin = promedios.at(i) /=cantidadArchivos;
                        salida << altura<<"  "<<Refin<<endl;    }       
			}
			salida.close();
			cout <<"Archivos leidos" <<" = "<< cantidadArchivos<<endl;    
			//promedios.pop_back();
			cout <<"Sum Tamano "<< arraySum.size()<<"  "<<"Depth tamao "<<arrayDepth.size()<<"  "<< "Promedios tamao "<<promedios.size()<<endl;
			//}
}
       /********************** INICIO DEL BLOQUE 2 ************************/

                TFile *f = new TFile("Perfil_PromedioMes_GDAS.root","RECREATE");
                TCanvas *c1 = new TCanvas("Altura","Refractive Index");


                for(int i=0; i < promedios.size(); i++){
                  //  if(maxSum < promedios.at(i)){
                  //      maxSum = promedios.at(i);
                  //      maxDepth = arrayDepth.at(i);
                  //  }
                	promedios.at(i) /= cantidadArchivos;
                }
        
               
                TGraph *gr = new TGraph(promedios.size(), &(arrayDepth[0]), &(promedios[0]));
                gr->SetTitle("FILEATM promedio con GDAS para CORSIKA");

                gr->SetName("Promedios");
                gr->SetLineWidth(4);
                gr->SetLineColor(kBlue);
                gr->GetYaxis()->SetTitle("Indice refractivo");
                gr->GetYaxis()->CenterTitle();
                gr->GetXaxis()->SetTitle("Altura");
                //gr->Write();
                gr->Draw("AL");
                //c1->Update();
                for(unsigned int i=0; i < arrayGraph.size(); i++){
                    arrayGraph[i]->SetLineColor(kBlack);
                    arrayGraph[i]->Draw("L");
                    arrayGraph[i]->Write();

                }
                    

                //c1->Write();
                c1->Update();
		c1->Write();
                //return;
                f->Close();
                
                //delete gr;               
	        //dir->Close();
		//break;
                
}
