AC_PREREQ([2.69])
AC_INIT(DESCRIPTION)

AC_PROG_CC_C99
AC_CHECK_LIB(m, [sinf], [], 
  [AC_MSG_ERROR([float math functions unavailable])]
)



AC_C_BIGENDIAN([BOBE=1], [BOBE=0], 
  [AC_MSG_ERROR([unable to determine endianness; not dealing with you])]
)


AC_CHECK_SIZEOF(int)
AC_PREPROC_IFELSE([AC_LANG_SOURCE([
  #if SIZEOF_INT != 4
  #error
  #endif
])], [INTSTORAGE=true], [INTSTORAGE=false])
if test "X${INTSTORAGE}" = "Xtrue"; then
  BACKEND_REPORT="using 'int' for internal float storage"
else
  AC_MSG_ERROR([sizeof(int) != 4. no other backend available at this time.])
fi



dnl Determine R_HOME.
: ${R_HOME=`R RHOME`}
if test -z "${R_HOME}"; then
  AC_MSG_ERROR([could not determine R_HOME])
fi

# Obtain from R.
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
  BLAS_REPORT="NOTE: using package's single precision blas"
  ADD_OBJS="${ADD_OBJS} lapack/sblas.o"
else
  BLAS_REPORT="using system single precision blas"
fi

if test "X${HAVESLAPACK}" = "Xno"; then
  LAPACK_REPORT="NOTE: using package's single precision lapack"
  ADD_OBJS="lapack/slapack1.o lapack/slapack2.o lapack/slapack3.o lapack/slapack4.o lapack/slamchf77.o lapack/ilas.o ${ADD_OBJS}"
else
  LAPACK_REPORT="using system single precision lapack"
fi

if test "X${HAVESBLAS}" = "Xno"; then
  AC_PROG_F77
  
  WARN_EXTRA="
The internal single precision BLAS are inefficient. Please \
consider installing high performance implementations, such as OpenBLAS \
(open source software) or MKL (available for free from the Microsoft R \
Open R distribution).

If you believe you are seeing this message in error, please contact the \
package maintainer.
  "
else
  WARN_EXTRA=" "
fi




# Report
echo " "
echo "******************** Results of spm package configure *******************"
echo " "
echo "* ${BACKEND_REPORT}"
echo "* ${BLAS_REPORT}"
echo "  >> BLAS_LIBS=${BLAS_LIBS}"
echo "* ${LAPACK_REPORT}"
echo "  >> LAPACK_LIBS=${LAPACK_LIBS}"
echo "${WARN_EXTRA}"
echo "*************************************************************************"
echo " "


AC_SUBST(BOBE)
AC_OUTPUT(src/endianness.h)

AC_SUBST(ADD_OBJS)
AC_OUTPUT(src/Makevars)
