AC_PREREQ([2.69])
AC_INIT
AC_CONFIG_SRCDIR([DESCRIPTION])
AC_CONFIG_HEADERS(src/config.h)

: ${R_HOME=`R RHOME`}
if test -z "${R_HOME}"; then
  echo "could not determine R_HOME"
  exit 1
fi

R_SCMD="${R_HOME}/bin/R CMD config"

# Get C compiler from R
CC=`${R_SCMD} CC`
CFLAGS=`${R_SCMD} CFLAGS`
CPPFLAGS=`${R_SCMD} CPPFLAGS`
LDFLAGS=`${R_SCMD} LDFLAGS`

FC=`${R_SCMD} FC`
FLIBS=`${R_SCMD} FLIBS`

# Obtain BLAS/LAPACK libs from R.
BLAS_LIBFLAGS=`${R_SCMD} BLAS_LIBS`
LAPACK_LIBFLAGS=`${R_SCMD} LAPACK_LIBS`



# ------------------------------------------------------------------------------
# Check for various system deps/requirements
# ------------------------------------------------------------------------------

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
  OMPFLAGS_F="\$(SHLIB_OPENMP_FFLAGS)"
else
  OMPFLAGS_C=""
  OMPFLAGS_F=""
fi



AC_CHECK_PROG([echo_ok], [echo], [yes], [no], ,)
AC_CHECK_PROG([grep_ok], [grep], [yes], [no], ,)



# ------------------------------------------------------------------------------
# Look for BLAS/LAPCK that support single precision
# ------------------------------------------------------------------------------

# These can be present/absent in almost any imaginable combination. For example,
# OpenBLAS (and others?) ship LAPACK symbols in the blas.[so|dylib|dll] file.

# Check libRblas and libRlapack first
HAVE_SP_BLAS="no"
if test "X${echo_ok}" = "Xyes" -a "X${grep_ok}" = "Xyes"; then
  USE_R_BLAS=`echo ${BLAS_LIBFLAGS} | grep "\-lRblas"`
  if test "X${USE_R_BLAS}" != "X"; then
    LDFLAGS_OLD="${LDFLAGS}"
    LDFLAGS="${LDFLAGS} ${BLAS_LIBFLAGS}"
    AC_CHECK_LIB(Rblas, [sgemm_], [HAVE_SP_BLAS=yes], [HAVE_SP_BLAS=no], [${FLIBS}])
    AC_CHECK_LIB(Rblas, [sgetrf_], [HAVE_SP_LAPACK=yes], [HAVE_SP_LAPACK=no], [${FLIBS}])
    LDFLAGS="${LDFLAGS_OLD}"
    
    if test "X${HAVE_SP_BLAS}" = "Xyes"; then
      LAPACK_REPORT="using R BLAS library"
      BLAS_LIBFLAGS="$(BLAS_LIBS)"
      
    fi
    if test "X${HAVE_SP_LAPACK}" = "Xyes"; then
      LAPACK_REPORT="using R LAPACK library"
      LAPACK_LIBFLAGS="$(LAPACK_LIBS)"
    fi
  fi
fi

HAVE_SP_LAPACK="no"
if test "X${HAVE_SP_LAPACK}" = "X" -o "X${HAVE_SP_LAPACK}" = "Xno"; then
  if test "X${echo_ok}" = "Xyes" -a "X${grep_ok}" = "Xyes"; then
    USE_R_LAPACK=`echo ${LAPACK_LIBFLAGS} | grep "\-lRlapack"`
    if test "X${USE_R_LAPACK}" != "X"; then
      LDFLAGS_OLD="${LDFLAGS}"
      LDFLAGS="${LDFLAGS} ${LAPACK_LIBFLAGS}"
      AC_CHECK_LIB(Rlapack, [sgetrf_], [HAVE_SP_LAPACK=yes], [HAVE_SP_LAPACK=no], [${FLIBS}])
      LDFLAGS="${LDFLAGS_OLD}"
      
      if test "X${HAVE_SP_LAPACK}" = "Xyes"; then
        LAPACK_REPORT="using R LAPACK library"
        LAPACK_LIBFLAGS="$(LAPACK_LIBS)"
      fi
    fi
  fi
fi


# Check the system if checking R failed
BLAS_LIBFLAGS=""
if test "X${HAVE_SP_BLAS}" = "Xno"; then
  AC_CHECK_LIB(openblas, [sgemm_], [HAVE_SP_BLAS=yes], [HAVE_SP_BLAS=no])
  if test "X${HAVE_SP_BLAS}" = "Xyes"; then
    BLAS_LIBFLAGS="-lopenblas"
    BLAS_REPORT="using system OpenBLAS library"
  fi
fi
if test "X${HAVE_SP_BLAS}" = "Xno"; then
  AC_CHECK_LIB(mkl, [sgemm_], [HAVE_SP_BLAS=yes], [HAVE_SP_BLAS=no])
  if test "X${HAVE_SP_BLAS}" = "Xyes"; then
    BLAS_LIBFLAGS="-lmkl"
    BLAS_REPORT="using system MKL library"
  fi
fi
if test "X${HAVE_SP_BLAS}" = "Xno"; then
  AC_CHECK_LIB(atlas, [sgemm_], [HAVE_SP_BLAS=yes], [HAVE_SP_BLAS=no])
  if test "X${HAVE_SP_BLAS}" = "Xyes"; then
    BLAS_LIBFLAGS="-latlas"
    BLAS_REPORT="using system Atlas library"
  fi
fi
if test "X${HAVE_SP_BLAS}" = "Xno"; then
  AC_CHECK_LIB(blas, [sgemm_], [HAVE_SP_BLAS=yes], [HAVE_SP_BLAS=no], [${FLIBS}])
  if test "X${HAVE_SP_BLAS}" = "Xyes"; then
    BLAS_LIBFLAGS="-lblas"
    BLAS_REPORT="using system BLAS library"
  fi
fi

LAPACK_LIBFLAGS=""
if test "X${HAVE_SP_LAPACK}" = "Xno"; then
  AC_CHECK_LIB(openblas, [sgetrf_], [HAVE_SP_LAPACK=yes], [HAVE_SP_LAPACK=no])
  if test "X${HAVE_SP_LAPACK}" = "Xyes"; then
    LAPACK_LIBFLAGS="-lopenblas"
    LAPACK_REPORT="using system OpenBLAS library"
  fi
fi
if test "X${HAVE_SP_LAPACK}" = "Xno"; then
  AC_CHECK_LIB(mkl, [sgetrf_], [HAVE_SP_LAPACK=yes], [HAVE_SP_LAPACK=no])
  if test "X${HAVE_SP_LAPACK}" = "Xyes"; then
    LAPACK_LIBFLAGS="-lmkl"
    LAPACK_REPORT="using system MKL library"
  fi
fi
if test "X${HAVE_SP_LAPACK}" = "Xno"; then
  AC_CHECK_LIB(atlas, [sgetrf_], [HAVE_SP_LAPACK=yes], [HAVE_SP_LAPACK=no])
  if test "X${HAVE_SP_LAPACK}" = "Xyes"; then
    LAPACK_LIBFLAGS="-latlas"
    LAPACK_REPORT="using system Atlas library"
  fi
fi
if test "X${HAVE_SP_LAPACK}" = "Xno"; then
  AC_CHECK_LIB(lapack, [sgetrf_], [HAVE_SP_LAPACK=yes], [HAVE_SP_LAPACK=no], [${FLIBS}])
  if test "X${HAVE_SP_LAPACK}" = "Xyes"; then
    LAPACK_LIBFLAGS="-llapack"
    LAPACK_REPORT="using system LAPACK library"
  fi
fi



# Set additional object files and messages
ADD_OBJS=""
ADD_DEPS=""

if test "X${HAVE_SP_BLAS}" = "Xno"; then
  BLAS_REPORT="NOTE: no single precision BLAS symbols found. Building reference version"
  ADD_OBJS="${ADD_OBJS} lapack/sblas.o"
fi

if test "X${HAVE_SP_LAPACK}" = "Xno"; then
  LAPACK_REPORT="NOTE: no single precision LAPACK symbols found. Building reference version"
  ADD_OBJS="lapack/la_xisnan.o lapack/la_constants.o lapack/sf90.o lapack/slapack1.o lapack/slapack2.o lapack/slapack3.o lapack/slapack4.o lapack/slamchf77.o lapack/ilas.o ${ADD_OBJS}"
  ADD_DEPS="
lapack/la_xisnan.o: lapack/la_constants.o
lapack/sf90.o: lapack/la_constants.o
lapack/slapack3.o: lapack/sf90.o
"
fi

if test "X${HAVE_SP_BLAS}" = "Xno"; then
  WARN_EXTRA="
No single precision BLAS functions detected in your R BLAS library, so \
we are using the reference implementation shipped with the float \
package. If you believe you are seeing this message in error, please contact \
the package maintainer."
else
  WARN_EXTRA=""
fi



# ------------------------------------------------------------------------------
# Report
# ------------------------------------------------------------------------------

echo " "
echo "******************* Results of float package configure *******************"
echo "* OpenMP Report:"
echo "    >> OPENMP_CFLAGS=${OPENMP_CFLAGS}"
echo "    >> OMPFLAGS_C=${OMPFLAGS_C}"
echo "    >> OMPFLAGS_F=${OMPFLAGS_F}"
echo "* ${BOBE_REPORT}"
echo "* ${BLAS_REPORT}"
echo "    >> BLAS_LIBFLAGS=${BLAS_LIBFLAGS}"
echo "* ${LAPACK_REPORT}"
echo "    >> LAPACK_LIBFLAGS=${LAPACK_LIBFLAGS}"
if test "X${WARN_EXTRA}" != "X"; then
  echo "${WARN_EXTRA}"
fi
echo "*************************************************************************"
echo " "


AC_SUBST(BOBE)
AC_SUBST(BLAS_LIBFLAGS)
AC_SUBST(LAPACK_LIBFLAGS)
AC_SUBST(ADD_OBJS)
AC_SUBST(ADD_DEPS)
AC_SUBST(OMPFLAGS_C)
AC_SUBST(OMPFLAGS_F)
AC_CONFIG_FILES([src/Makevars src/endianness.h R/02-libflags.r])
AC_OUTPUT
