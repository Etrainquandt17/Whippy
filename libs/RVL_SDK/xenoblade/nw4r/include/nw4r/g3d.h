#ifndef NW4R_PUBLIC_G3D_H
#define NW4R_PUBLIC_G3D_H

#include <xenoblade/nw4r/include/nw4r/g3d/g3d_anmchr.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_anmclr.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_anmobj.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_anmscn.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_anmshp.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_anmtexpat.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_anmtexsrt.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_anmvis.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_calcmaterial.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_calcview.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_calcvtx.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_calcworld.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_camera.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_dcc.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_draw.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_draw1mat1shp.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_fog.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_init.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_light.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_obj.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_rtti.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_scnmdl.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_scnmdl1mat1shp.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_scnmdlsmpl.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_scnobj.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_scnproc.h>
//#include <nw4r/g3d/g3d_scnrfl.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_scnroot.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_state.h>
#include <xenoblade/nw4r/include/nw4r/g3d/g3d_workmem.h>

/*****************************************************************************
 *
 * Digital content creation
 *
 *****************************************************************************/

 #include <xenoblade/nw4r/include/nw4r/g3d/dcc/g3d_3dsmax.h>
 #include <xenoblade/nw4r/include/nw4r/g3d/dcc/g3d_basic.h>
 #include <xenoblade/nw4r/include/nw4r/g3d/dcc/g3d_maya.h>
 #include <xenoblade/nw4r/include/nw4r/g3d/dcc/g3d_xsi.h>

/******************************************************************************
 *
 * Resources
 *
 ******************************************************************************/

#include <xenoblade/nw4r/include/nw4r/g3d/res/g3d_resanm.h>
#include <xenoblade/nw4r/include/nw4r/g3d/res/g3d_resanmamblight.h>
#include <xenoblade/nw4r/include/nw4r/g3d/res/g3d_resanmcamera.h>
#include <xenoblade/nw4r/include/nw4r/g3d/res/g3d_resanmchr.h>
#include <xenoblade/nw4r/include/nw4r/g3d/res/g3d_resanmclr.h>
#include <xenoblade/nw4r/include/nw4r/g3d/res/g3d_resanmfog.h>
#include <xenoblade/nw4r/include/nw4r/g3d/res/g3d_resanmlight.h>
#include <xenoblade/nw4r/include/nw4r/g3d/res/g3d_resanmscn.h>
#include <xenoblade/nw4r/include/nw4r/g3d/res/g3d_resanmshp.h>
#include <xenoblade/nw4r/include/nw4r/g3d/res/g3d_resanmtexpat.h>
#include <xenoblade/nw4r/include/nw4r/g3d/res/g3d_resanmtexsrt.h>
#include <xenoblade/nw4r/include/nw4r/g3d/res/g3d_resanmvis.h>
#include <xenoblade/nw4r/include/nw4r/g3d/res/g3d_rescommon.h>
#include <xenoblade/nw4r/include/nw4r/g3d/res/g3d_resdict.h>
#include <xenoblade/nw4r/include/nw4r/g3d/res/g3d_resfile.h>
#include <xenoblade/nw4r/include/nw4r/g3d/res/g3d_reslightset.h>
#include <xenoblade/nw4r/include/nw4r/g3d/res/g3d_resmat.h>
#include <xenoblade/nw4r/include/nw4r/g3d/res/g3d_resmdl.h>
#include <xenoblade/nw4r/include/nw4r/g3d/res/g3d_resnode.h>
#include <xenoblade/nw4r/include/nw4r/g3d/res/g3d_respltt.h>
#include <xenoblade/nw4r/include/nw4r/g3d/res/g3d_resshp.h>
#include <xenoblade/nw4r/include/nw4r/g3d/res/g3d_restev.h>
#include <xenoblade/nw4r/include/nw4r/g3d/res/g3d_restex.h>
#include <xenoblade/nw4r/include/nw4r/g3d/res/g3d_resvtx.h>

/******************************************************************************
 *
 * Platform-specific
 *
 ******************************************************************************/

#include <xenoblade/nw4r/include/nw4r/g3d/platform/g3d_allocator.h>
#include <xenoblade/nw4r/include/nw4r/g3d/platform/g3d_cpu.h>
#include <xenoblade/nw4r/include/nw4r/g3d/platform/g3d_gpu.h>
#include <xenoblade/nw4r/include/nw4r/g3d/platform/g3d_tmem.h>

#endif
