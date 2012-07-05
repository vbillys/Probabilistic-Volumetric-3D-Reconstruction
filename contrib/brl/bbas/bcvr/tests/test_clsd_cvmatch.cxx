#include <testlib/testlib_test.h>
#include <bcvr/bcvr_clsd_cvmatch.h>
#include <bcvr/bcvr_clsd_cvmatch_sptr.h>
#include <vcl_string.h>

MAIN_ARGS(test_clsd_cvmatch)
{
  vcl_string dir_base;

  if ( argc >= 2 ) {
    dir_base = argv[1];
#ifdef VCL_WIN32
    dir_base += "\\";
#else
    dir_base += "/";
#endif
  } else dir_base = "";

  testlib_test_start("testing closed curve matching ");

  vcl_string data_file = "line1.con";
  // Test generic file loads
  bsol_intrinsic_curve_2d_sptr curve_2d1 = new bsol_intrinsic_curve_2d;
  curve_2d1->readCONFromFile( (dir_base+data_file).c_str() );
  TEST("load line1.con ", curve_2d1->size(), 10);

  bsol_intrinsic_curve_2d_sptr curve_2d2 = new bsol_intrinsic_curve_2d(*curve_2d1);
  //: Actually testing copy constructor of bsol_intrinsic_curve_2d
  TEST("create curve2 from curve1 ", curve_2d2->size(), 10);

  curve_2d1->setOpen(false);
  curve_2d2->setOpen(false);
  
  bcvr_clsd_cvmatch_sptr clsd_cvmatch = new bcvr_clsd_cvmatch(curve_2d1,curve_2d2,(double)10.0f,3);
  clsd_cvmatch->setStretchCostFlag(false);
  clsd_cvmatch->Match();  
  
  double minCost=1E10;
  int minIndex;
  for (int count=0;count<curve_2d1->size();count++){
    if (minCost>clsd_cvmatch->finalCost(count)){
      minCost=clsd_cvmatch->finalCost(count);
      minIndex=count;
    }
  }
  
  TEST("matching curve1 with itself ", minCost, 0.0);

  return testlib_test_summary();
}
