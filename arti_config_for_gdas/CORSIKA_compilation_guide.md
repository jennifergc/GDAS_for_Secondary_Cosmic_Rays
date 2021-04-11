# Package:  arti_config_for_gdas   
# File:     CORSIKA_compilation_guide
## Authors:  J. Grisales-Casadiegos, C. Sarmiento-Cano, Luis A. Núñez @nunezluis 
## e-mail:   jennifer.grisales@saber.uis.edu.co   
### Description: Lets configure CORSIKA and ARTI for using GDAS profiles in 'one particle simulations' and flux estimations.  Show the required configuration for CORSIKA simulations with GDAS profiles.
************************************************************************
## Grupo Halley (UIS), Colombia
## All rights reserved.
************************************************************************

Standard Configutation for CORSIKA compilation for use GDAS:

>Arq: 64 bit mode.

>High Energy Hadronic Interactions: QGSJETII-04.

>Low Energy Hadronic Interactions: GHEISHA 2002d.

>Detector Geometry: non-flat (volume) detector geometry.

>Other: EFIELD, CURVED, LPM.

*Without GDAS, you should add the ATMEXT option tho the list.*

### Example of datacard Required for CORSIKA:
```
{
_______________________________________________________________
RUNNR       999900
EVTNR       1
NSHOW       10

PRMPAR      5626
ESLOPE      -2.7
ERANGE      1E8 1E8
THETAP      0 0
PHIP        -180 180

OBSLEV      1000
ATMFILE        '/home/cristians/jennifer/Atm_enero.dat'
MAGNET      27.0263 17.176
FIXCHI      0.
SEED        7234400   0   0
SEED        2350336   0   0
SEED        9183290   0   0
SEED        779658   0   0
ECUTS       0.05 0.05 5e-05 5e-05



MUMULT      T
MAXPRT      0
ELMFLG      F   T
LONGI       T  10.  T  T
ECTMAP      1.E3


DIRECT      /home/cristians/jennifer/corsika-conGDAS/corsika-76400/run/Fe_1E8_bga_1000cm_10shw/
DATBAS      T
PAROUT      T F
THIN        1E-06  1E02  25E02

 

 

USER        jennifer
EXIT
___________________________________________________________
}
```

