AC_PREREQ([2.69])
AC_INIT(DESCRIPTION)

AC_PROG_CC_C99


dnl Determine R_HOME.
: ${R_HOME=`R RHOME`}
if test -z "${R_HOME}"; then
  echo "could not determine R_HOME"
  exit 1
fi


# Obtain from R.
R_SCMD="${R_HOME}/bin/R CMD config"
BLAS_LIBS=`${R_SCMD} BLAS_LIBS`
LAPACK_LIBS=`${R_SCMD} LAPACK_LIBS`

echo "BLAS_LIBS=${BLAS_LIBS}"
echo "LAPACK_LIBS=${LAPACK_LIBS}"

# Check tools.
AC_CHECK_PROG([echo_ok], [echo], [yes], [no], ,)
AC_CHECK_PROG([grep_ok], [grep], [yes], [no], ,)

# Check Rblas.
if test "X${echo_ok}" = "Xyes" -a "X${grep_ok}" = "Xyes"; then
  useRblas=`echo ${BLAS_LIBS} | grep "\-lRblas"`
  if test "X${useRblas}" = "X"; then
    AC_CHECK_LIB(blas, [sgemm_], [HAVESBLAS=yes], [HAVESBLAS=no])
  else
    LDFLAGS_OLD="${LDFLAGS}"
    LDFLAGS="${LDFLAGS} ${BLAS_LIBS}"
    AC_CHECK_LIB(Rblas, [sgemm_], [HAVESBLAS=yes], [HAVESBLAS=no])
    LDFLAGS="${LDFLAGS_OLD}"
  fi
else
  HAVESBLAS="no"
fi

# Check Rlapack.
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



# set additional files as needed
if test "X${HAVESBLAS}" = "Xno" -o "X${HAVESLAPACK}" = "Xno"; then
  AC_PROG_F77
fi


ADD_OBJS=""

if test "X${HAVESBLAS}" = "Xno"; then
  echo "Using internal single precision blas"
  ADD_OBJS="${ADD_OBJS} lapack/sblas.o"
else
  echo "Using system single precision blas"
fi

if test "X${HAVESLAPACK}" = "Xno"; then
  echo "Using internal single precision lapack"
  ADD_OBJS="lapack/slapack1.o lapack/slapack2.o lapack/slapack3.o lapack/slapack4.o lapack/slamchf77.o lapack/ilas.o ${ADD_OBJS}"
else
  echo "Using system single precision lapack"
fi


AC_SUBST(ADD_OBJS)
AC_OUTPUT(src/Makevars)
