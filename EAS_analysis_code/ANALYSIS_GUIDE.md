# Package:  EAS_analysis_code                                          
## Authors:  J. Grisales-Casadiegos, C. Sarmiento-Cano , Luis A. Núñez @nunezluis
## e-mail:   jennifer.grisales@saber.uis.edu.co                         
### Description: Calculates longitudinal distributions, porcentual differences and error for .long files
************************************************************************
## Grupo Halley (UIS), Colombia
## All rights reserved.
************************************************************************

This codes are writed in ROOT. For compile a file (search errors), write: g++ -o xxxxx.C, for compile and run a file use: g++ -o xxxxx.C
For visualization you can use VIM and move across.

1) graph_longi_dis.C ----> create ---->  *particle_conGDAS.dat* and
                                        *particle_sinGDAS.dat*

	>This code use '.long' files to show the average of longitudinal distribution of charged particles and muons with a determinate number of showers.
	>WARRING: You should write DATA in first line of .dat files for the next analysis.

2) diff_porcent.C  ----> create ----> *dif_longi_particle.difl*

	
	>This code calculate the porcentual differences between two files '*.dat' whit and without GDAS, and the error in the calculation. 
	>The output has 5 columns (Depth  %charged  error  %muons  error)

3) graph_missing_energy.C ----> create ----> *particle_energy_conGDAS.emi* and
					     *particle_energy_sinGDAS.emi*

	>This code use '.long' files to show the average of energy distribution deposited in atmosphere in the EAS development. 
	>The output has 6 columns (Depth  Echarged error Emuons error Etotal).
	>WARRING: You should write DATA in first line of .dat files for the next analysis.

4) diff_porc_miss.C ----> create ----> *dif_energy_particle.den*

	>This code calculate the porcentual differences between the losing energy values for each particle and total, using '.emi' files. 
	>The output has 6 columns (Depth  %Charged error  %muons error  %total).


