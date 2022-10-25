#!/bin/bash

# clone BLAS and SRC of the LAPACK tarball here

cd BLAS/SRC
rm -f C* c* d* z* x*
cd ../..

cd SRC
rm -rf DEPRECATED/ VARIANTS/
rm -f C* c* d* z*
rm -f sgesvxx.f sgerfsx.f sla_gerfsx_extended.f sla_geamv.f \
  sla_gercond.f sla_rpvgrw.f ssysvxx.f ssyrfsx.f \
  sla_syrfsx_extended.f sla_syamv.f sla_syrcond.f sla_syrpvgrw.f \
  sposvxx.f sporfsx.f sla_porfsx_extended.f sla_porcond.f \
  sla_porpvgrw.f sgbsvxx.f sgbrfsx.f sla_gbrfsx_extended.f \
  sla_gbamv.f sla_gbrcond.f sla_gbrpvgrw.f sla_lin_berr.f slarscl2.f \
  slascl2.f sla_wwaddw.f
cd ..

# There are mixed F77 and F90 subroutines now...
blas=`ls BLAS/SRC/*.f | sed -e "s/BLAS\/SRC\///g" | grep "^s"`
blas="${blas} isamax.f"

lapack=`ls SRC/*.f | sed -e "s/SRC\///g" | grep "^s"`
lapack="${lapack} ssytrd_sb2st.F"

ilas=`ls SRC | grep "^ilas"`
ilas="${ilas} ilaenv2stage.f"

sf90_blas=`ls BLAS/SRC/*.f90 | grep "^BLAS/SRC/s"`
sf90_lapack=`ls SRC/*.f90 | grep "^SRC/s"`
sf90="${sf90_blas} ${sf90_lapack}"

cp SRC/la_constants.f90 .
cp SRC/la_xisnan.F90 ./la_xisnan.f90 # bruh



NUM_SPLITS="4"

rm -f sf90.f90
touch sf90.f90
rm -f sblas.f
touch sblas.f
rm -f ilas.f
touch ilas.f

for x in `eval echo {1..${NUM_SPLITS}}`; do
  rm -f slapack${x}.f
  touch slapack${x}.f
done

for f in $blas; do
  cat "BLAS/SRC/$f" >> sblas.f
  echo "" >> sblas.f
done

for f in ${sf90}; do
  cat "$f" >> sf90.f90
  echo "" >> sf90.f90
done

lapack=($lapack)

for (( i=0; i<${#lapack[@]}; i+=${NUM_SPLITS} )); do
  for j in `eval echo {1..${NUM_SPLITS}}`; do
    cat "SRC/${lapack[$(( $i + $j - 1 ))]}" >> slapack${j}.f
    echo "" >> slapack${j}.f
  done
done

for f in $ilas; do
  cat "SRC/$f" >> ilas.f
  echo "" >> ilas.f
done



# rm -rf SRC/ BLAS/
