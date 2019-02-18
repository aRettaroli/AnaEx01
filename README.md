 # Geant4 - an Object-Oriented Toolkit for Simulation in HEP                #

 ###                    example from AnaEx01                              ###


 This example is a modified version of the AnaEx01 in the "extended" folder
 of the examples.
                            
 Examples AnaEx01, AnaEx02 and AnaEx03 show the usage of histogram and tuple 
 manipulations using G4Analysis, ROOT and AIDA compliant systems on the same
 scenario. All analysis manipulations (histo booking, filling, saving histos 
 in a file, etc...) are located in one class : HistoManager, implementation of 
 which is different in each example. All the other classes are same in all 
 three examples.
 
 This example shows the usage of histogram and tuple manipulations using 
 G4Analysis system. 
 

 The example is further modified to simulate a very simple cloud chamber, for
 didactic aims.
	
## Detector description ##
 
 The chamber is a 40cmx40cmx80cm parallelepiped made of a supersaturated gas. This can be either
 water vapour or alcohol.
 	
 Two parameters define the calorimeter :
    * the material of vapour,
    * the height in the y direction (the x height is equal to that of y, and the dimension
      in the z direction is fixed at 80cm). 
 
 The default geometry is constructed in DetectorConstruction class,
 but all of the above parameters can be modified interactively via
 the commands defined in the DetectorMessenger class.

```
                  80 cm
        ============================
        |		 	    |
        |			    | 40 cm
	|			    |
	|			    |
	============================
```   
   
 ## Physics list ##
 
 
   The particle's type and the physic processes which will be available
   in this example are set in the FTFP_BERT physics list.
  
 ## Action Initialization ##

   A newly introduced class, ActionInitialization, 
   instantiates and registers to Geant4 kernel all user action classes 
   which are defined thread-local and a run action class
   which is defined both thread-local and global.
   
   The thread-local action classes are defined in 
     ActionInitialization::Build() 
   and  the global run action class is defined in 
     ActionInitialization::BuildForMaster().
   Note that ActionInitialization::Build() is also used to 
   instatiate user action clasess in sequential mode.
  
 ## An event: PrimaryGeneratorAction ##

   Primaries are generated with the General Particle Source (GPS)
   http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/GettingStarted/generalParticleSource.html
   therefore all the configuration of the primaries can be done via macro

 ## Histograms ##

 ClouChamber can produce 4 histograms : //(CAMBIARE)
  
  Edep : total energy deposit in the chamber per event	  
  Ltrack : total track length of charged particles in the chamber per event
 
 And 2 Ntuples : //(CAMBIARE)
 * Ntuple1:
   ..* one row per event : EnergyAbs EnergyGap
 * Ntuple2:
   ..* one row per event : TrackLAbs TrackLGap
  
 These histos and ntuples are booked in HistoManager and filled from 
 EventAction.
 
 One can control the name of the histograms file and its format:
 default name     : CloudChamber   
 The format of the histogram file can be : root (default),
 xml, csv. Include correct g4nnn.hh in HistoManager.hh 
 
 ## How to build ## 

 mkdir <build dir>
 cd <build dir>
 cmake ../
 make -j<Nprocessors>
