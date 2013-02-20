#define codigo_cxx
#include "codigo.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TPaveStats.h>
#include <TPave.h>
#include <TList.h>
#include <TVector.h>
#include <TClonesArray.h>

#include <iostream>
#include <iomanip>
#include <typeinfo>
#include <string>
#include <vector>

using namespace std;

void codigo::Loop(string argumento1)
{
  Int_t icol=0;
  gStyle->SetFrameBorderMode(icol);
  gStyle->SetFrameFillColor(icol);
  gStyle->SetCanvasBorderMode(icol);
  gStyle->SetCanvasColor(icol);
  gStyle->SetPadBorderMode(icol);
  gStyle->SetPadColor(icol);
  gStyle->SetStatColor(icol);
  gStyle->SetTitleFillColor(icol);

  gStyle->SetPadTopMargin(0.15);
  gStyle->SetPadRightMargin(0.26);
  gStyle->SetPadBottomMargin(0.16);
  gStyle->SetPadLeftMargin(0.12); 

  // todas las ramas encendidas
  fChain->SetBranchStatus("*",1);  
  if (fChain == 0) return;

  // defino tres variables mi x_minimo, mi x_maximo y n segundos
  ULong64_t mixmin, mixmax, nseg; 
  Long64_t nentries, nbytes, nb;

  nentries = fChain->GetEntries();

  nbytes = 0; 
  nb = 0;  

  // en la primera entrada cojame la variable gps y almacenela en mixmin
  nb = fChain->GetEntry(0);   
  mixmin=gps;
  // en la ultima entrada cojame la variable gps y almacenela en mixmax
  nb = fChain->GetEntry(nentries-1);
  mixmax=gps;
  // numero de segundos
  nseg = mixmax - mixmin + 1;
  for(ULong64_t i=0; i<nseg; i++){
    // me armo un arreglo de valores de gps ideal (avanzo de a uno en uno)
    migps[i]=mixmin+i;
    // inicializo un arreglo de contadores a ceros
    cont[i]=0;
  }

  //nentries = fChain->GetEntriesFast();
  nbytes = 0; 
  nb = 0;
  for(Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if(ientry < 0) break;
    nb = fChain->GetEntry(jentry);   
    nbytes += nb;
    //cout << gps << endl;
    for(ULong64_t i=0; i<nseg; i++){
      // para cada entrada de mi arreglo de migps la comparo con la entrada actual del valor de la rama gps del arbol
      if(migps[i]!=gps) continue;
      else{  
        // cuento las que sean iguales 
        cont[i]++;
      }

    }
  }


  bool foundatleastone = false;
  for(ULong64_t i=0; i<nseg; i++){
    if(cont[i]==200) {
      cout << "if(s==\"" << argumento1 << "\" && (" << endl;  
      foundatleastone = true;
      break;
    }
  }

  if(!foundatleastone) return;

  int huecos[4601];
  vector<ULong64_t> extrLeft;
  vector<ULong64_t> extrRight;
  vector<ULong64_t> autoextr;

  for(ULong64_t i=0; i<nseg; i++){
    if(cont[i]!=200) {
      huecos[i]=-1;
    } else huecos[i]=1;
  }

  if(huecos[0]>0 && huecos[1]>0) extrLeft.push_back(migps[0]);
  if(huecos[0]>0 && huecos[1]<0) autoextr.push_back(migps[0]);
  for(ULong64_t i=1; i<nseg-1; i++){
    if(huecos[i]>0 && huecos[i-1]>0 && huecos[i+1]<0) extrRight.push_back(migps[i]);
    if(huecos[i]>0 && huecos[i-1]<0 && huecos[i+1]>0) extrLeft.push_back(migps[i]);
    if(huecos[i]>0 && huecos[i-1]<0 && huecos[i+1]<0) autoextr.push_back(migps[i]);
  }
  if(huecos[nseg-1]>0 && huecos[nseg-2]>0) extrRight.push_back(migps[nseg-1]);
  if(huecos[nseg-1]>0 && huecos[nseg-2]<0) autoextr.push_back(migps[nseg-1]);


  bool wereIntervals=false;
  if(extrRight.size()>0) wereIntervals=true;

  for(int i=0; i<extrRight.size(); i++){
    cout << "(g>=" << extrLeft[i] << " && g<=" << extrRight[i] << ")";
    if((i+1)%5 == 0) cout << endl;
    if(i==extrRight.size()-1) break;
    cout << " || ";
  }

  for(unsigned int i=0; i<autoextr.size(); i++){
    if(i==0 && wereIntervals) cout << endl << " || ";
    cout << "(g==" << autoextr[i] << ")";
    if((i+1)%5 == 0) cout << endl;
    if(i==autoextr.size()-1) break;
    cout << " || ";
  }

  cout << endl << ") ) return true;" << endl << endl;

}

