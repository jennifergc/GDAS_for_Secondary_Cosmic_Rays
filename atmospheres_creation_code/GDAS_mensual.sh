#!/bin/bash
echo Corriendo gdastool...
for i in {1512104400..1514739600..43200}; do python3 gdastool -t $i -o Atm_$i.dat -c 7.11 -73.11 -p gdas_path > salida_$i.dat
	echo Creando perfiles para la UNIXTIME: $i
	sleep 1m
	echo Perfil para $i terminado...
done
