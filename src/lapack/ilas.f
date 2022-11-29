*> \brief \b ILASLC scans a matrix for its last non-zero column.
*
*  =========== DOCUMENTATION ===========
*
* Online html documentation available at
*            http://www.netlib.org/lapack/explore-html/
*
*> \htmlonly
*> Download ILASLC + dependencies
*> <a href="http://www.netlib.org/cgi-bin/netlibfiles.tgz?format=tgz&filename=/lapack/lapack_routine/ilaslc.f">
*> [TGZ]</a>
*> <a href="http://www.netlib.org/cgi-bin/netlibfiles.zip?format=zip&filename=/lapack/lapack_routine/ilaslc.f">
*> [ZIP]</a>
*> <a href="http://www.netlib.org/cgi-bin/netlibfiles.txt?format=txt&filename=/lapack/lapack_routine/ilaslc.f">
*> [TXT]</a>
*> \endhtmlonly
*
*  Definition:
*  ===========
*
*       INTEGER FUNCTION ILASLC( M, N, A, LDA )
*
*       .. Scalar Arguments ..
*       INTEGER            M, N, LDA
*       ..
*       .. Array Arguments ..
*       REAL               A( LDA, * )
*       ..
*
*
*> \par Purpose:
*  =============
*>
*> \verbatim
*>
*> ILASLC scans A for its last non-zero column.
*> \endverbatim
*
*  Arguments:
*  ==========
*
*> \param[in] M
*> \verbatim
*>          M is INTEGER
*>          The number of rows of the matrix A.
*> \endverbatim
*>
*> \param[in] N
*> \verbatim
*>          N is INTEGER
*>          The number of columns of the matrix A.
*> \endverbatim
*>
*> \param[in] A
*> \verbatim
*>          A is REAL array, dimension (LDA,N)
*>          The m by n matrix A.
*> \endverbatim
*>
*> \param[in] LDA
*> \verbatim
*>          LDA is INTEGER
*>          The leading dimension of the array A. LDA >= max(1,M).
*> \endverbatim
*
*  Authors:
*  ========
*
*> \author Univ. of Tennessee
*> \author Univ. of California Berkeley
*> \author Univ. of Colorado Denver
*> \author NAG Ltd.
*
*> \ingroup realOTHERauxiliary
*
*  =====================================================================
      INTEGER FUNCTION ILASLC( M, N, A, LDA )
*
*  -- LAPACK auxiliary routine --
*  -- LAPACK is a software package provided by Univ. of Tennessee,    --
*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
*
*     .. Scalar Arguments ..
      INTEGER            M, N, LDA
*     ..
*     .. Array Arguments ..
      REAL               A( LDA, * )
*     ..
*
*  =====================================================================
*
*     .. Parameters ..
      REAL             ZERO
      PARAMETER ( ZERO = 0.0E+0 )
*     ..
*     .. Local Scalars ..
      INTEGER I
*     ..
*     .. Executable Statements ..
*
*     Quick test for the common case where one corner is non-zero.
      IF( N.EQ.0 ) THEN
         ILASLC = N
      ELSE IF( A(1, N).NE.ZERO .OR. A(M, N).NE.ZERO ) THEN
         ILASLC = N
      ELSE
*     Now scan each column from the end, returning with the first non-zero.
         DO ILASLC = N, 1, -1
            DO I = 1, M
               IF( A(I, ILASLC).NE.ZERO ) RETURN
            END DO
         END DO
      END IF
      RETURN
      END

*> \brief \b ILASLR scans a matrix for its last non-zero row.
*
*  =========== DOCUMENTATION ===========
*
* Online html documentation available at
*            http://www.netlib.org/lapack/explore-html/
*
*> \htmlonly
*> Download ILASLR + dependencies
*> <a href="http://www.netlib.org/cgi-bin/netlibfiles.tgz?format=tgz&filename=/lapack/lapack_routine/ilaslr.f">
*> [TGZ]</a>
*> <a href="http://www.netlib.org/cgi-bin/netlibfiles.zip?format=zip&filename=/lapack/lapack_routine/ilaslr.f">
*> [ZIP]</a>
*> <a href="http://www.netlib.org/cgi-bin/netlibfiles.txt?format=txt&filename=/lapack/lapack_routine/ilaslr.f">
*> [TXT]</a>
*> \endhtmlonly
*
*  Definition:
*  ===========
*
*       INTEGER FUNCTION ILASLR( M, N, A, LDA )
*
*       .. Scalar Arguments ..
*       INTEGER            M, N, LDA
*       ..
*       .. Array Arguments ..
*       REAL               A( LDA, * )
*       ..
*
*
*> \par Purpose:
*  =============
*>
*> \verbatim
*>
*> ILASLR scans A for its last non-zero row.
*> \endverbatim
*
*  Arguments:
*  ==========
*
*> \param[in] M
*> \verbatim
*>          M is INTEGER
*>          The number of rows of the matrix A.
*> \endverbatim
*>
*> \param[in] N
*> \verbatim
*>          N is INTEGER
*>          The number of columns of the matrix A.
*> \endverbatim
*>
*> \param[in] A
*> \verbatim
*>          A is REAL array, dimension (LDA,N)
*>          The m by n matrix A.
*> \endverbatim
*>
*> \param[in] LDA
*> \verbatim
*>          LDA is INTEGER
*>          The leading dimension of the array A. LDA >= max(1,M).
*> \endverbatim
*
*  Authors:
*  ========
*
*> \author Univ. of Tennessee
*> \author Univ. of California Berkeley
*> \author Univ. of Colorado Denver
*> \author NAG Ltd.
*
*> \ingroup realOTHERauxiliary
*
*  =====================================================================
      INTEGER FUNCTION ILASLR( M, N, A, LDA )
*
*  -- LAPACK auxiliary routine --
*  -- LAPACK is a software package provided by Univ. of Tennessee,    --
*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
*
*     .. Scalar Arguments ..
      INTEGER            M, N, LDA
*     ..
*     .. Array Arguments ..
      REAL               A( LDA, * )
*     ..
*
*  =====================================================================
*
*     .. Parameters ..
      REAL             ZERO
      PARAMETER ( ZERO = 0.0E+0 )
*     ..
*     .. Local Scalars ..
      INTEGER I, J
*     ..
*     .. Executable Statements ..
*
*     Quick test for the common case where one corner is non-zero.
      IF( M.EQ.0 ) THEN
         ILASLR = M
      ELSEIF( A(M, 1).NE.ZERO .OR. A(M, N).NE.ZERO ) THEN
         ILASLR = M
      ELSE
*     Scan up each column tracking the last zero row seen.
         ILASLR = 0
         DO J = 1, N
            I=M
            DO WHILE((A(MAX(I,1),J).EQ.ZERO).AND.(I.GE.1))
               I=I-1
            ENDDO
            ILASLR = MAX( ILASLR, I )
         END DO
      END IF
      RETURN
      END

*> \brief \b ILAENV2STAGE
*
*  =========== DOCUMENTATION ===========
*
* Online html documentation available at
*            http://www.netlib.org/lapack/explore-html/
*
*> \htmlonly
*> Download ILAENV2STAGE + dependencies
*> <a href="http://www.netlib.org/cgi-bin/netlibfiles.tgz?format=tgz&filename=/lapack/lapack_routine/ilaenv2stage.f">
*> [TGZ]</a>
*> <a href="http://www.netlib.org/cgi-bin/netlibfiles.zip?format=zip&filename=/lapack/lapack_routine/ilaenv2stage.f">
*> [ZIP]</a>
*> <a href="http://www.netlib.org/cgi-bin/netlibfiles.txt?format=txt&filename=/lapack/lapack_routine/ilaenv2stage.f">
*> [TXT]</a>
*> \endhtmlonly
*
*  Definition:
*  ===========
*
*       INTEGER FUNCTION ILAENV2STAGE( ISPEC, NAME, OPTS, N1, N2, N3, N4 )
*
*       .. Scalar Arguments ..
*       CHARACTER*( * )    NAME, OPTS
*       INTEGER            ISPEC, N1, N2, N3, N4
*       ..
*
*
*> \par Purpose:
*  =============
*>
*> \verbatim
*>
*> ILAENV2STAGE is called from the LAPACK routines to choose problem-dependent
*> parameters for the local environment.  See ISPEC for a description of
*> the parameters.
*> It sets problem and machine dependent parameters useful for *_2STAGE and
*> related subroutines.
*>
*> ILAENV2STAGE returns an INTEGER
*> if ILAENV2STAGE >= 0: ILAENV2STAGE returns the value of the parameter
*>                       specified by ISPEC
*> if ILAENV2STAGE < 0:  if ILAENV2STAGE = -k, the k-th argument had an
*>                       illegal value.
*>
*> This version provides a set of parameters which should give good,
*> but not optimal, performance on many of the currently available
*> computers for the 2-stage solvers. Users are encouraged to modify this
*> subroutine to set the tuning parameters for their particular machine using
*> the option and problem size information in the arguments.
*>
*> This routine will not function correctly if it is converted to all
*> lower case.  Converting it to all upper case is allowed.
*> \endverbatim
*
*  Arguments:
*  ==========
*
*> \param[in] ISPEC
*> \verbatim
*>          ISPEC is INTEGER
*>          Specifies the parameter to be returned as the value of
*>          ILAENV2STAGE.
*>          = 1: the optimal blocksize nb for the reduction to BAND
*>
*>          = 2: the optimal blocksize ib for the eigenvectors
*>               singular vectors update routine
*>
*>          = 3: The length of the array that store the Housholder 
*>               representation for the second stage 
*>               Band to Tridiagonal or Bidiagonal
*>
*>          = 4: The workspace needed for the routine in input.
*>
*>          = 5: For future release.
*> \endverbatim
*>
*> \param[in] NAME
*> \verbatim
*>          NAME is CHARACTER*(*)
*>          The name of the calling subroutine, in either upper case or
*>          lower case.
*> \endverbatim
*>
*> \param[in] OPTS
*> \verbatim
*>          OPTS is CHARACTER*(*)
*>          The character options to the subroutine NAME, concatenated
*>          into a single character string.  For example, UPLO = 'U',
*>          TRANS = 'T', and DIAG = 'N' for a triangular routine would
*>          be specified as OPTS = 'UTN'.
*> \endverbatim
*>
*> \param[in] N1
*> \verbatim
*>          N1 is INTEGER
*> \endverbatim
*>
*> \param[in] N2
*> \verbatim
*>          N2 is INTEGER
*> \endverbatim
*>
*> \param[in] N3
*> \verbatim
*>          N3 is INTEGER
*> \endverbatim
*>
*> \param[in] N4
*> \verbatim
*>          N4 is INTEGER
*>          Problem dimensions for the subroutine NAME; these may not all
*>          be required.
*> \endverbatim
*
*  Authors:
*  ========
*
*> \author Univ. of Tennessee
*> \author Univ. of California Berkeley
*> \author Univ. of Colorado Denver
*> \author NAG Ltd.
*> \author Nick R. Papior
*
*> \ingroup OTHERauxiliary
*
*> \par Further Details:
*  =====================
*>
*> \verbatim
*>
*>  The following conventions have been used when calling ILAENV2STAGE
*> from the LAPACK routines:
*>  1)  OPTS is a concatenation of all of the character options to
*>      subroutine NAME, in the same order that they appear in the
*>      argument list for NAME, even if they are not used in determining
*>      the value of the parameter specified by ISPEC.
*>  2)  The problem dimensions N1, N2, N3, N4 are specified in the order
*>      that they appear in the argument list for NAME.  N1 is used
*>      first, N2 second, and so on, and unused problem dimensions are
*>      passed a value of -1.
*>  3)  The parameter value returned by ILAENV2STAGE is checked for validity in
*>      the calling subroutine.
*>     
*> \endverbatim
*>
*  =====================================================================
      INTEGER FUNCTION ILAENV2STAGE( ISPEC, NAME, OPTS, N1, N2, N3, N4 )
*
*  -- LAPACK auxiliary routine --
*  -- LAPACK is a software package provided by Univ. of Tennessee,    --
*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
*     July 2017
*
*     .. Scalar Arguments ..
      CHARACTER*( * )    NAME, OPTS
      INTEGER            ISPEC, N1, N2, N3, N4
*     ..
*
*  =====================================================================
*     ..
*     .. Local Scalars ..
      INTEGER            IISPEC
*     ..
*     .. External Functions ..
      INTEGER            IPARAM2STAGE
      EXTERNAL           IPARAM2STAGE
*     ..
*     .. Executable Statements ..
*
      GO TO ( 10, 10, 10, 10, 10 )ISPEC
*
*     Invalid value for ISPEC
*
      ILAENV2STAGE = -1
      RETURN
*
   10 CONTINUE
*
*     2stage eigenvalues and SVD or related subroutines.
*
      IISPEC = 16 + ISPEC
      ILAENV2STAGE = IPARAM2STAGE( IISPEC, NAME, OPTS,
     $                             N1, N2, N3, N4 )
      RETURN
*
*     End of ILAENV2STAGE
*
      END

*> \brief \b IPARAM2STAGE
*
*  =========== DOCUMENTATION ===========
*
* Online html documentation available at 
*            http://www.netlib.org/lapack/explore-html/ 
*
*> \htmlonly
*> Download IPARAM2STAGE + dependencies 
*> <a href="http://www.netlib.org/cgi-bin/netlibfiles.tgz?format=tgz&filename=/lapack/lapack_routine/iparam2stage.F"> 
*> [TGZ]</a> 
*> <a href="http://www.netlib.org/cgi-bin/netlibfiles.zip?format=zip&filename=/lapack/lapack_routine/iparam2stage.F"> 
*> [ZIP]</a>
*> <a href="http://www.netlib.org/cgi-bin/netlibfiles.txt?format=txt&filename=/lapack/lapack_routine/iparam2stage.F"> 
*> [TXT]</a>
*> \endhtmlonly 
*
*  Definition:
*  ===========
*
*       INTEGER FUNCTION IPARAM2STAGE( ISPEC, NAME, OPTS, 
*                                    NI, NBI, IBI, NXI )
*       #if defined(_OPENMP)
*           use omp_lib
*       #endif
*       IMPLICIT NONE
*
*       .. Scalar Arguments ..
*       CHARACTER*( * )    NAME, OPTS
*       INTEGER            ISPEC, NI, NBI, IBI, NXI
*
*> \par Purpose:
*  =============
*>
*> \verbatim
*>
*>      This program sets problem and machine dependent parameters
*>      useful for xHETRD_2STAGE, xHETRD_HE2HB, xHETRD_HB2ST,
*>      xGEBRD_2STAGE, xGEBRD_GE2GB, xGEBRD_GB2BD 
*>      and related subroutines for eigenvalue problems. 
*>      It is called whenever ILAENV is called with 17 <= ISPEC <= 21.
*>      It is called whenever ILAENV2STAGE is called with 1 <= ISPEC <= 5
*>      with a direct conversion ISPEC + 16.
*> \endverbatim
*
*  Arguments:
*  ==========
*
*> \param[in] ISPEC
*> \verbatim
*>          ISPEC is integer scalar
*>              ISPEC specifies which tunable parameter IPARAM2STAGE should
*>              return.
*>
*>              ISPEC=17: the optimal blocksize nb for the reduction to
*>                        BAND
*>
*>              ISPEC=18: the optimal blocksize ib for the eigenvectors
*>                        singular vectors update routine
*>
*>              ISPEC=19: The length of the array that store the Housholder 
*>                        representation for the second stage 
*>                        Band to Tridiagonal or Bidiagonal
*>
*>              ISPEC=20: The workspace needed for the routine in input.
*>
*>              ISPEC=21: For future release.
*> \endverbatim
*>
*> \param[in] NAME
*> \verbatim
*>          NAME is character string
*>               Name of the calling subroutine
*> \endverbatim
*>
*> \param[in] OPTS
*> \verbatim
*>          OPTS is CHARACTER*(*)
*>          The character options to the subroutine NAME, concatenated
*>          into a single character string.  For example, UPLO = 'U',
*>          TRANS = 'T', and DIAG = 'N' for a triangular routine would
*>          be specified as OPTS = 'UTN'.
*> \endverbatim
*>
*> \param[in] NI
*> \verbatim
*>          NI is INTEGER which is the size of the matrix
*> \endverbatim
*>
*> \param[in] NBI
*> \verbatim
*>          NBI is INTEGER which is the used in the reduciton, 
*>          (e.g., the size of the band), needed to compute workspace
*>          and LHOUS2.
*> \endverbatim
*>
*> \param[in] IBI
*> \verbatim
*>          IBI is INTEGER which represent the IB of the reduciton,
*>          needed to compute workspace and LHOUS2.
*> \endverbatim
*>
*> \param[in] NXI
*> \verbatim
*>          NXI is INTEGER needed in the future release.
*> \endverbatim
*
*  Authors:
*  ========
*
*> \author Univ. of Tennessee 
*> \author Univ. of California Berkeley 
*> \author Univ. of Colorado Denver 
*> \author NAG Ltd. 
*
*> \ingroup auxOTHERauxiliary
*
*> \par Further Details:
*  =====================
*>
*> \verbatim
*>
*>  Implemented by Azzam Haidar.
*>
*>  All detail are available on technical report, SC11, SC13 papers.
*>
*>  Azzam Haidar, Hatem Ltaief, and Jack Dongarra.
*>  Parallel reduction to condensed forms for symmetric eigenvalue problems
*>  using aggregated fine-grained and memory-aware kernels. In Proceedings
*>  of 2011 International Conference for High Performance Computing,
*>  Networking, Storage and Analysis (SC '11), New York, NY, USA,
*>  Article 8 , 11 pages.
*>  http://doi.acm.org/10.1145/2063384.2063394
*>
*>  A. Haidar, J. Kurzak, P. Luszczek, 2013.
*>  An improved parallel singular value algorithm and its implementation 
*>  for multicore hardware, In Proceedings of 2013 International Conference
*>  for High Performance Computing, Networking, Storage and Analysis (SC '13).
*>  Denver, Colorado, USA, 2013.
*>  Article 90, 12 pages.
*>  http://doi.acm.org/10.1145/2503210.2503292
*>
*>  A. Haidar, R. Solca, S. Tomov, T. Schulthess and J. Dongarra.
*>  A novel hybrid CPU-GPU generalized eigensolver for electronic structure 
*>  calculations based on fine-grained memory aware tasks.
*>  International Journal of High Performance Computing Applications.
*>  Volume 28 Issue 2, Pages 196-209, May 2014.
*>  http://hpc.sagepub.com/content/28/2/196 
*>
*> \endverbatim
*>
*  =====================================================================
      INTEGER FUNCTION iparam2stage( ISPEC, NAME, OPTS, 
     $                              NI, NBI, IBI, NXI )
#if defined(_OPENMP)
      use omp_lib
#endif
      IMPLICIT NONE
*
*  -- LAPACK auxiliary routine --
*  -- LAPACK is a software package provided by Univ. of Tennessee,    --
*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
*
*     .. Scalar Arguments ..
      CHARACTER*( * )    name, opts
      INTEGER            ispec, ni, nbi, ibi, nxi
*
*  ================================================================
*     ..
*     .. Local Scalars ..
      INTEGER            i, ic, iz, kd, ib, lhous, lwork, nthreads,
     $                   factoptnb, qroptnb, lqoptnb
      LOGICAL            rprec, cprec
      CHARACTER          prec*1, algo*3, stag*5, subnam*12, vect*1
*     ..
*     .. Intrinsic Functions ..
      INTRINSIC          char, ichar, max
*     ..
*     .. External Functions ..
      INTEGER            ilaenv
      EXTERNAL           ilaenv
*     ..
*     .. Executable Statements ..
*
*     Invalid value for ISPEC
*
      IF( (ispec.LT.17).OR.(ispec.GT.21) ) THEN
          iparam2stage = -1
          RETURN
      ENDIF
*
*     Get the number of threads
*      
      nthreads = 1
#if defined(_OPENMP)
!$OMP PARALLEL 
      nthreads = omp_get_num_threads()
!$OMP END PARALLEL
#endif
*      WRITE(*,*) 'IPARAM VOICI NTHREADS ISPEC ',NTHREADS, ISPEC
*
      IF( ispec .NE. 19 ) THEN
*
*        Convert NAME to upper case if the first character is lower case.
*
         iparam2stage = -1
         subnam = name
         ic = ichar( subnam( 1: 1 ) )
         iz = ichar( 'Z' )
         IF( iz.EQ.90 .OR. iz.EQ.122 ) THEN
*
*           ASCII character set
*
            IF( ic.GE.97 .AND. ic.LE.122 ) THEN
               subnam( 1: 1 ) = char( ic-32 )
               DO 100 i = 2, 12
                  ic = ichar( subnam( i: i ) )
                  IF( ic.GE.97 .AND. ic.LE.122 )
     $               subnam( i: i ) = char( ic-32 )
  100          CONTINUE
            END IF
*
         ELSE IF( iz.EQ.233 .OR. iz.EQ.169 ) THEN
*
*           EBCDIC character set
*
            IF( ( ic.GE.129 .AND. ic.LE.137 ) .OR.
     $          ( ic.GE.145 .AND. ic.LE.153 ) .OR.
     $          ( ic.GE.162 .AND. ic.LE.169 ) ) THEN
               subnam( 1: 1 ) = char( ic+64 )
               DO 110 i = 2, 12
                  ic = ichar( subnam( i: i ) )
                  IF( ( ic.GE.129 .AND. ic.LE.137 ) .OR.
     $                ( ic.GE.145 .AND. ic.LE.153 ) .OR.
     $                ( ic.GE.162 .AND. ic.LE.169 ) )subnam( i:
     $                i ) = char( ic+64 )
  110          CONTINUE
            END IF
*
         ELSE IF( iz.EQ.218 .OR. iz.EQ.250 ) THEN
*
*           Prime machines:  ASCII+128
*
            IF( ic.GE.225 .AND. ic.LE.250 ) THEN
               subnam( 1: 1 ) = char( ic-32 )
               DO 120 i = 2, 12
                 ic = ichar( subnam( i: i ) )
                 IF( ic.GE.225 .AND. ic.LE.250 )
     $             subnam( i: i ) = char( ic-32 )
  120          CONTINUE
            END IF
         END IF
*
         prec  = subnam( 1: 1 )
         algo  = subnam( 4: 6 )
         stag  = subnam( 8:12 )
         rprec = prec.EQ.'S' .OR. prec.EQ.'D'
         cprec = prec.EQ.'C' .OR. prec.EQ.'Z'
*
*        Invalid value for PRECISION
*      
         IF( .NOT.( rprec .OR. cprec ) ) THEN
             iparam2stage = -1
             RETURN
         ENDIF
      ENDIF
*      WRITE(*,*),'RPREC,CPREC ',RPREC,CPREC,
*     $           '   ALGO ',ALGO,'    STAGE ',STAG
*      
*
      IF (( ispec .EQ. 17 ) .OR. ( ispec .EQ. 18 )) THEN 
*
*     ISPEC = 17, 18:  block size KD, IB
*     Could be also dependent from N but for now it
*     depend only on sequential or parallel
*
         IF( nthreads.GT.4 ) THEN
            IF( cprec ) THEN
               kd = 128
               ib = 32
            ELSE
               kd = 160
               ib = 40
            ENDIF
         ELSE IF( nthreads.GT.1 ) THEN
            IF( cprec ) THEN
               kd = 64
               ib = 32
            ELSE
               kd = 64
               ib = 32
            ENDIF
         ELSE
            IF( cprec ) THEN
               kd = 16
               ib = 16
            ELSE
               kd = 32
               ib = 16
            ENDIF
         ENDIF
         IF( ispec.EQ.17 ) iparam2stage = kd
         IF( ispec.EQ.18 ) iparam2stage = ib
*
      ELSE IF ( ispec .EQ. 19 ) THEN
*
*     ISPEC = 19:  
*     LHOUS length of the Houselholder representation
*     matrix (V,T) of the second stage. should be >= 1.
*
*     Will add the VECT OPTION HERE next release
         vect  = opts(1:1)
         IF( vect.EQ.'N' ) THEN
            lhous = max( 1, 4*ni )
         ELSE
*           This is not correct, it need to call the ALGO and the stage2
            lhous = max( 1, 4*ni ) + ibi
         ENDIF
         IF( lhous.GE.0 ) THEN
            iparam2stage = lhous
         ELSE
            iparam2stage = -1
         ENDIF
*
      ELSE IF ( ispec .EQ. 20 ) THEN
*
*     ISPEC = 20: (21 for future use)  
*     LWORK length of the workspace for 
*     either or both stages for TRD and BRD. should be >= 1.
*     TRD:
*     TRD_stage 1: = LT + LW + LS1 + LS2
*                  = LDT*KD + N*KD + N*MAX(KD,FACTOPTNB) + LDS2*KD 
*                    where LDT=LDS2=KD
*                  = N*KD + N*max(KD,FACTOPTNB) + 2*KD*KD
*     TRD_stage 2: = (2NB+1)*N + KD*NTHREADS
*     TRD_both   : = max(stage1,stage2) + AB ( AB=(KD+1)*N )
*                  = N*KD + N*max(KD+1,FACTOPTNB) 
*                    + max(2*KD*KD, KD*NTHREADS) 
*                    + (KD+1)*N
         lwork        = -1
         subnam(1:1)  = prec
         subnam(2:6)  = 'GEQRF'
         qroptnb      = ilaenv( 1, subnam, ' ', ni, nbi, -1, -1 )
         subnam(2:6)  = 'GELQF'
         lqoptnb      = ilaenv( 1, subnam, ' ', nbi, ni, -1, -1 )
*        Could be QR or LQ for TRD and the max for BRD
         factoptnb    = max(qroptnb, lqoptnb)
         IF( algo.EQ.'TRD' ) THEN
            IF( stag.EQ.'2STAG' ) THEN
               lwork = ni*nbi + ni*max(nbi+1,factoptnb) 
     $              + max(2*nbi*nbi, nbi*nthreads) 
     $              + (nbi+1)*ni
            ELSE IF( (stag.EQ.'HE2HB').OR.(stag.EQ.'SY2SB') ) THEN
               lwork = ni*nbi + ni*max(nbi,factoptnb) + 2*nbi*nbi
            ELSE IF( (stag.EQ.'HB2ST').OR.(stag.EQ.'SB2ST') ) THEN
               lwork = (2*nbi+1)*ni + nbi*nthreads
            ENDIF
         ELSE IF( algo.EQ.'BRD' ) THEN
            IF( stag.EQ.'2STAG' ) THEN
               lwork = 2*ni*nbi + ni*max(nbi+1,factoptnb) 
     $              + max(2*nbi*nbi, nbi*nthreads) 
     $              + (nbi+1)*ni
            ELSE IF( stag.EQ.'GE2GB' ) THEN
               lwork = ni*nbi + ni*max(nbi,factoptnb) + 2*nbi*nbi
            ELSE IF( stag.EQ.'GB2BD' ) THEN
               lwork = (3*nbi+1)*ni + nbi*nthreads
            ENDIF
         ENDIF
         lwork = max( 1, lwork )
 
         IF( lwork.GT.0 ) THEN
            iparam2stage = lwork
         ELSE
            iparam2stage = -1
         ENDIF
*
      ELSE IF ( ispec .EQ. 21 ) THEN
*
*     ISPEC = 21 for future use 
         iparam2stage = nxi
      ENDIF
*
*     ==== End of IPARAM2STAGE ====
*
      END
