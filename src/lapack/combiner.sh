#!/bin/bash

# remove xblas
cd SRC
rm -f sgesvxx.f sgerfsx.f sla_gerfsx_extended.f sla_geamv.f \
  sla_gercond.f sla_rpvgrw.f ssysvxx.f ssyrfsx.f \
  sla_syrfsx_extended.f sla_syamv.f sla_syrcond.f sla_syrpvgrw.f \
  sposvxx.f sporfsx.f sla_porfsx_extended.f sla_porcond.f \
  sla_porpvgrw.f sgbsvxx.f sgbrfsx.f sla_gbrfsx_extended.f \
  sla_gbamv.f sla_gbrcond.f sla_gbrpvgrw.f sla_lin_berr.f slarscl2.f \
  slascl2.f sla_wwaddw.f
cd ..



blas=`ls BLAS/SRC | grep "^s"`
blas="${blas} isamax.f"
lapack=`ls SRC | grep "^s"`
ilas=`ls SRC | grep "^ilas"`

rm -f sblas.f
touch sblas.f
rm -f ilas.f
touch ilas.f

for x in {1..4}; do
  rm -f slapack${x}.f
  touch slapack${x}.f
done



for f in $blas; do
  cat "BLAS/SRC/$f" >> sblas.f
  echo "" >> sblas.f
done


lapack=($lapack)

for (( i=0; i<${#lapack[@]}; i+=4 )); do
  for j in {1..4}; do
    cat "SRC/${lapack[$(( $i + $j - 1 ))]}" >> slapack${j}.f
    echo "" >> slapack${j}.f
  done
done

for f in $ilas; do
  cat "SRC/$f" >> ilas.f
  echo "" >> ilas.f
done

