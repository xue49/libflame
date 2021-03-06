/*

    Copyright (C) 2014, The University of Texas at Austin

    This file is part of libflame and is available under the 3-Clause
    BSD license, which can be found in the LICENSE file at the top-level
    directory, or at http://opensource.org/licenses/BSD-3-Clause

*/

#include "FLAME.h"

#ifdef FLA_ENABLE_NON_CRITICAL_CODE

FLA_Error FLA_Gemm_hn_unb_var6( FLA_Obj alpha, FLA_Obj A, FLA_Obj B, FLA_Obj beta, FLA_Obj C )
{
  FLA_Obj AT,              A0,
          AB,              a1t,
                           A2;

  FLA_Obj BT,              B0,
          BB,              b1t,
                           B2;

  FLA_Scal_external( beta, C );

  FLA_Part_2x1( A,    &AT, 
                      &AB,            0, FLA_BOTTOM );

  FLA_Part_2x1( B,    &BT, 
                      &BB,            0, FLA_BOTTOM );

  while ( FLA_Obj_length( AB ) < FLA_Obj_length( A ) ){

    FLA_Repart_2x1_to_3x1( AT,                &A0, 
                                              &a1t, 
                        /* ** */            /* *** */
                           AB,                &A2,        1, FLA_TOP );

    FLA_Repart_2x1_to_3x1( BT,                &B0, 
                                              &b1t, 
                        /* ** */            /* *** */
                           BB,                &B2,        1, FLA_TOP );

    /*------------------------------------------------------------*/

    /* C = a1t' * b1t + C */
    FLA_Gerc_external( FLA_CONJUGATE, FLA_NO_CONJUGATE, alpha, a1t, b1t, C );

    /*------------------------------------------------------------*/

    FLA_Cont_with_3x1_to_2x1( &AT,                A0, 
                            /* ** */           /* *** */
                                                  a1t, 
                              &AB,                A2,     FLA_BOTTOM );

    FLA_Cont_with_3x1_to_2x1( &BT,                B0, 
                            /* ** */           /* *** */
                                                  b1t, 
                              &BB,                B2,     FLA_BOTTOM );

  }

  return FLA_SUCCESS;
}

#endif
