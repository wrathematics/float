AC_PREREQ([2.69])
AC_INIT
AC_CONFIG_SRCDIR([DESCRIPTION])
AC_CONFIG_HEADERS(src/config.h)

# Get C compiler from R
: ${R_HOME=`R RHOME`}
if test -z "${R_HOME}"; then
  echo "could not determine R_HOME"
  exit 1
fi
CC=`"${R_HOME}/bin/R" CMD config CC`
CFLAGS=`"${R_HOME}/bin/R" CMD config CFLAGS`
CPPFLAGS=`"${R_HOME}/bin/R" CMD config CPPFLAGS`
LDFLAGS=`"${R_HOME}/bin/R" CMD config LDFLAGS`


AC_PROG_CC
AC_CHECK_LIB(m, [sinf], [], 
  [AC_MSG_ERROR([float math functions unavailable])]
)



# 1=big endian, 0=little endian
AC_C_BIGENDIAN([BOBE=1], [BOBE=0], 
  [AC_MSG_ERROR([unable to determine endianness; not dealing with you])]
)

if test "X${BOBE}" = "X1"; then
  BOBE_REPORT="byte order: big endian"
else
  BOBE_REPORT="byte order: little endian"
fi



### Prof Ripley: "R cannot be built on a platform with sizeof(int) != 4."
AC_CHECK_SIZEOF(int)
AC_PREPROC_IFELSE([AC_LANG_SOURCE([
  #if SIZEOF_INT != 4
  #error
  #endif
])], [INTSTORAGE=true], [INTSTORAGE=false])
if test "X${INTSTORAGE}" != "Xtrue"; then
  AC_MSG_ERROR([sizeof(int) != 4, this should be impossible...])
fi



AC_OPENMP
if test -n "${OPENMP_CFLAGS}"; then
  OMPFLAGS_C="\$(SHLIB_OPENMP_CFLAGS)"
else
  OMPFLAGS_C=""
fi



# Obtain BLAS/LAPACK libs from R.
R_SCMD="${R_HOME}/bin/R CMD config"
BLAS_LIBS=`${R_SCMD} BLAS_LIBS`
LAPACK_LIBS=`${R_SCMD} LAPACK_LIBS`

# Check tools.
AC_CHECK_PROG([echo_ok], [echo], [yes], [no], ,)
AC_CHECK_PROG([grep_ok], [grep], [yes], [no], ,)



### Check for single precision BLAS/LAPACK symbols. These can be present/absent
### in almost any imaginable combination. For example, OpenBLAS (and others?)
### ship LAPACK symbols in the blas.[so|dylib|dll] file.

# Check Rblas.
if test "X${echo_ok}" = "Xyes" -a "X${grep_ok}" = "Xyes"; then
  useRblas=`echo ${BLAS_LIBS} | grep "\-lRblas"`
  if test "X${useRblas}" = "X"; then
    AC_CHECK_LIB(blas, [sgemm_], [HAVESBLAS=yes], [HAVESBLAS=no])
    AC_CHECK_LIB(blas, [sgetrf_], [HAVESLAPACK=yes], [HAVESLAPACK=no])
  else
    LDFLAGS_OLD="${LDFLAGS}"
    LDFLAGS="${LDFLAGS} ${BLAS_LIBS}"
    AC_CHECK_LIB(Rblas, [sgemm_], [HAVESBLAS=yes], [HAVESBLAS=no])
    AC_CHECK_LIB(Rblas, [sgetrf_], [HAVESLAPACK=yes], [HAVESLAPACK=no])
    LDFLAGS="${LDFLAGS_OLD}"
  fi
else
  HAVESBLAS="no"
fi

# Check for single precision LAPACK symbols.
if test "X${HAVESLAPACK}" = "X" -o "X${HAVESLAPACK}" = "Xno"; then
  if test "X${echo_ok}" = "Xyes" -a "X${grep_ok}" = "Xyes"; then
    useRlapack=`echo ${LAPACK_LIBS} | grep "\-lRlapack"`
    if test "X${useRlapack}" = "X"; then
      AC_CHECK_LIB(lapack, [sgetrf_], [HAVESLAPACK=yes], [HAVESLAPACK=no])
    else
      LDFLAGS_OLD="${LDFLAGS}"
      LDFLAGS="${LDFLAGS} ${LAPACK_LIBS}"
      AC_CHECK_LIB(Rlapack, [sgetrf_], [HAVESLAPACK=yes], [HAVESLAPACK=no])
      LDFLAGS="${LDFLAGS_OLD}"
    fi
  else
    HAVESLAPACK="no"
  fi
fi



# Set additional object files and messages
ADD_OBJS=""

if test "X${HAVESBLAS}" = "Xno"; then
  BLAS_REPORT="NOTE: no single precision BLAS symbols found. Building reference version"
  ADD_OBJS="${ADD_OBJS} lapack/sblas.o"
else
  BLAS_REPORT="using system BLAS library"
fi

if test "X${HAVESLAPACK}" = "Xno"; then
  LAPACK_REPORT="NOTE: no single precision LAPACK symbols found. Building reference version"
  ADD_OBJS="lapack/slapack1.o lapack/slapack2.o lapack/slapack3.o lapack/slapack4.o lapack/slamchf77.o lapack/ilas.o ${ADD_OBJS}"
else
  LAPACK_REPORT="using system LAPACK library"
fi

if test "X${HAVESBLAS}" = "Xno"; then
  WARN_EXTRA="
No single precision BLAS functions detected in your R BLAS library, so \
we are using the reference implementation shipped with the float \
package. If you believe you are seeing this message in error, please contact \
the package maintainer."
else
  WARN_EXTRA=""
fi




# Report
echo " "
echo "******************* Results of float package configure *******************"
echo "* OpenMP Report:"
echo "  >> OPENMP_CFLAGS=${OPENMP_CFLAGS}"
echo "  >> OMPFLAGS_C=${OMPFLAGS_C}"
echo "* ${BOBE_REPORT}"
echo "* ${BLAS_REPORT}"
echo "  >> BLAS_LIBS=${BLAS_LIBS}"
echo "* ${LAPACK_REPORT}"
echo "  >> LAPACK_LIBS=${LAPACK_LIBS}"
if test "X${WARN_EXTRA}" != "X"; then
  echo "${WARN_EXTRA}"
fi
echo "*************************************************************************"
echo " "


AC_SUBST(BOBE)
AC_SUBST(ADD_OBJS)
AC_SUBST(OMPFLAGS_C)
AC_CONFIG_FILES([src/Makevars src/endianness.h])
AC_OUTPUT
