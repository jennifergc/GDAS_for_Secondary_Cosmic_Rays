# This guide tells you how to simulate a certain number of showers for an specific particle (CORSIKA ID)

To allow a easier interaction with corsika, we're going to use a pearl routine for generate the datacards of each sigle shower.
This routine is the ARTI Package and are named 'rain.pl'. ./rain.pl -r . -v 76400 -s bga -m 1E6 -q 0 -p 5626

1. Copy the location from your ARTI's directory like this: ~/arti/sims/rain.pl to the RUN directory in CORSIKA: ~/corsika-76400/run
2. Now, run the rain.pl settin the initial parameters: for example: ./rain.pl -r . -v 76400 -s bga -m 1E6 -q 0 -p 5626 where:

```
A simple input files generator for CORSIKA
       (C) 2013 - H. Asorey - asoreyh\@cab.cnea.gov.ar
       Usage: See $0 -?  - If you enjoy it, please send me an email\n
       $0\n
       -b                                  Activates batch mode
       -i                                  Disable PLOTSH and PLOTSH2 modes (usual simms production)
       -d                                  Debug mode: only shows what it should do. Don't start simulation
       -r  <working directory>             Specify where corsika bin files are located
       -v  <version>                       Corsika version number
       -h  <high energy interaction model> High energy interaction model used for compilation of CORSIKA (EPOS|QGSII|SIBYLL)
       -l  <cluster user name>             Enables OAR cluster compatibility (UIS style), use -l \$USER
       -t  <EFRCTHN> <WMAX> <RMAX>         Enables THIN Mode (see manual for pg 62 for values)
       -th <THINRAT> <WEITRAT>             If THIN Mode, select different thining levels for Hadronic (THINH) ...
       -te <THINRAT> <WEITRAT>             ... and electromagnetic particles (THINEM)
       -a                                  Enables high energy cuts for ECUTS - for now, hardcoded
       -z                                  Enables CHERENKOV mode
       -mu                                 Enables additional information from muons and EM particles
       -g                                  Enables GRID mode
       -s <site>                           Choice site for simulation (some predefined sites: hess|sac|etn|ber|bga|lim|glr|mch|mge|and|mpc|cha|cid|mor|ccs|lsc|mbo)
       -m <energy>                         Defines energy (in GeV) for monoenergetic showers (CHERENKOV)
       -q <theta>                          Defines zenith angle (in degs) for fixed angle showers (CHERENKOV)
       -p <prmpar>                         Defines primary particle (see table 4 pg 87) (CHERENKOV)
  ```
Remember that for LAGO sites, you can set -s and digite the site identifier inside the rain.pl routine (you can review this since the 405 line).
If you'll not use this sites, don't set the site and you'll set the geomagnetic field and level manually then.
  
3. Run rain.pl the output:

```
WARNING! Site selected for simulation: bga.

Working directory (where CORSIKA run files are located)?
<WDIR .>: .
Project name (Results will go into ./<project> dir)?
<DIRECT monobga>: prueba_massterclass  
<USER LAGO>: jennifer (your name)
  
###################################################################
# I will run this script 1 times
# in ./prue/
# Press enter to continue...
###################################################################

###################################################################
# RUN 1
###################################################################
###################################################################
# Simulation parameters
###################################################################
number of showers to generate?
<NSHOW 100000>: (put a integer number)

###################################################################
# Primary particle parameters
###################################################################
Low edge of azimuth angle (PHIP) [deg]?
<PHIPR(1) -180>: (enter/default)
<PHIPR(2) 180>: (enter/default)

###################################################################
# Observatory parameters
###################################################################
Atmospheric model selection ?
<ATMOSPHERE E1>: (set the MODATM profiles here (E2, E1, E3, etc) or if you are using GDAS, your selection here doesn't matter... in this case, press ENTER)

###################################################################
# General (T or F) parameters
###################################################################
Write add- files for track plot of secondaries?
<PLOTSH F>: (ENTER/default)
Write .dbase file?
<DATBAS T>: (ENTER/default)
Track longitudinal development of secondaries (LONGI)?
<LLONGI F>: T (F or ENTER if you are using ARTI for flux calculations)
```
	
4. Final datacard... in screen 'rain.pl' show you the datacard model, you should confirm it press ENTER
```
RUNNR       999900
EVTNR       1
NSHOW       1

PRMPAR      5626
ESLOPE      -2.7
ERANGE      1E6 1E6
THETAP      0 0
PHIP        -180 180

OBSLEV      95000
ATMFILE     '/scratch/jgrisales/Atm_abril.dat'
MAGNET      27.0263 17.176
FIXCHI      0.
SEED        7784562   0   0
SEED        3290942   0   0
SEED        7834248   0   0
SEED        1799534   0   0
ECUTS       0.1 0.5 0.000264 0.256



MUMULT      T
MAXPRT      0
ELMFLG      F   T
LONGI       T  10.  T  T
ECTMAP      1.E3


DIRECT      ./fsdf/
DATBAS      T
PAROUT      T F
 

 

 

USER        jen
EXIT
###################################################################
# I will run this simulation using those parameters
# Please check and press ENTER to continue; CTRL-C to abort
###################################################################
```

5. After ENTER, the simulation will be launched and should show you in screen:
```
###################################################################
# I will run this simulation using those parameters
# Please check and press ENTER to continue; CTRL-C to abort
###################################################################

closedir() attempted on invalid dirhandle IMD at ./rain.pl line 750, <> line 13.
###################################################################
# Starting simulations 999900-5626-00000000001-master
# in screen 999900-5626-00000000001-master
###################################################################
There is a screen on:
	6222.999900-5626-00000000001-master	(27/04/21 15:08:51)	(Detached)
1 Socket in /run/screen/S-jgrisales.
###################################################################
# BYE BYE
###################################################################
```

6. You need wait... and then enjoy the .long file.





  

