#!/bin/bash
echo copiando archivos a carpeta
for i in {1512104400..1514739600..43200}; do mv Atm_$i.dat /scratch/jgrisales/perfiles_gdas/diciembre/
done
