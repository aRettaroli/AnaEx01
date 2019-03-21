#include <iostream>
#include <TFile.h>
using namespace std;

int main() {
  
  TFile* myf = new TFile("../build/CloudChamber.root","r");

  return 0;
}
