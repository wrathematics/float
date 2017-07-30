AC_PREREQ([2.69])
AC_INIT(DESCRIPTION)

AC_PROG_CC_C99

AC_CHECK_LIB(blas, [sgemm_], [HAVESBLAS=yes], [HAVESBLAS=no])
AC_CHECK_LIB(lapack, [sgetrf_], [HAVESLAPACK=yes], [HAVESLAPACK=no])


# set additional files as needed
ADD_OBJS=""

if test "X${HAVESBLAS}" = "Xno"; then
  ADD_OBJS="${ADD_OBJS} lapack/sblas.o"
fi

if test "X${HAVESLAPACK}" = "Xno"; then
  ADD_OBJS="${ADD_OBJS} lapack/slapack1.o lapack/slapack2.o lapack/slapack3.o lapack/slapack4.o"
fi


AC_SUBST(ADD_OBJS)
AC_OUTPUT(src/Makevars)
