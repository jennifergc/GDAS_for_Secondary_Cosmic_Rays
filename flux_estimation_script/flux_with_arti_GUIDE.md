# Package:  ¿How to obtain fluxes with ARTI?                           
## Authors:  J. Grisales-Casadiegos, C. Sarmiento-Cano , Luis A. Núñez @nunezluis
## e-mail:   jennifer.grisales@saber.uis.edu.co   
### Description: Guide for make flux simulations with ARTI                  */
************************************************************************
## Grupo Halley (UIS), Colombia
## All rights reserved.
************************************************************************

1. Create a new project and .sh files

>./do_sims_abril.sh -w ../../corsika-76400/run -p flujo_abril_4h -t 14400 -v 76400 -u jgrisales -s bga -y

************************************************************************

2. Run the .sh files in a new screen.

- screen -S name_of_screen
- Run with a bash line: for i in go-flujo_abril_4h-*.sh; do while pgrep -fau $(id -un) 'SCREEN.*-flujo_abril'; do sleep 30s; done; ./"$i"; sleep 5m; done

************************************************************************
3. digitar ctrl+A, luego D
4. para revisar como va: screen -r name_of_screen
5. se sale de nuevo como en el punto 3

************************************************************************

### DATA ANALYSIS (bash lines)

:::::UNZIP FILES, GENERATE .PRI AND .SEC files::::::

>for i in DAT??????.bz2; do j=$(echo $i | sed -e 's/.bz2//'); u=$(echo $j | sed -e 's/DAT//'); bzip2 -d -k $i; echo $j | ../../../arti/analysis/lagocrkread | ../../../arti/analysis/analysis -p -v $u; rm $j; done

CREATE .shw.bz2 AND .hst FILE:::::::::::::::::::::::::::

>bzcat *sec.bz2 | ../../../arti/analysis/showers -a 20 -d 20 -c 956. -v SalidaE6

