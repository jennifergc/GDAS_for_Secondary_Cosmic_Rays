# /************************************************************************/
# /*                                                                      */
# /* Package:  EAS_analysis_code                                          */
# /*                                                                      */
# /************************************************************************/
# /* Authors:  J. Grisales-Casadiegos, C. Sarmiento-Cano, Luis A. Núñez   */
# /* e-mail:   jennifer.grisales@saber.uis.edu.co                         */
# /*                                                                      */
# /************************************************************************/
# /* Comments: Calculate longitudinal distributions, porcentual           */
# /*           differences and error for .long file.                      */
# /*                                                                      */
# /************************************************************************/
# /* 
#  
# Grupo Halley (UIS), Colombia
# All rights reserved.
# 
# */
# /************************************************************************/

1) graph_longi_dis.C ----> create ---->  particle_conGDAS.dat
                                        particle_sinGDAS.dat

	# This code use '.long' files to show the average of longitudinal
	# distribution of charged particles and muons with a determinate 
	# number of showers.
	# WARRING: You should write DATA in first line of .dat files for the next analysis.

2) diff_porcent.C  ----> create ----> dif_longi_particle.difl

	
	# This code calculate the porcentual differences between two files
	# '*.dat' whit and without GDAS, and the error in the calculation.
	# 5 columns (Depth  %charged  error  %muons  error)

3) graph_missing_energy.C ----> create ----> particle_energy_conGDAS.emi
					     particle_energy_sinGDAS.emi

	# This code use '.long' files to show the average of energy distribution
	# deposited in atmosphere in the EAS development. 
	# 6 columns (Depth  Echarged error Emuons error Etotal)
	# WARRING: You should write DATA in first line of .dat files for the next analysis.

4) diff_porc_miss.C ----> create ----> dif_energy_particle.den

	# This code calculate the porcentual differences between the losing energy values
	# por each particle and total, using '.emi' files. 
	# 6 columns (Depth  %Charged error  %muons error  %total)


