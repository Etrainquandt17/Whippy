#ifndef NW4R_PUBLIC_G3D_H
#define NW4R_PUBLIC_G3D_H

// IWYU pragma: begin_keep
#include "kdc/nw4r/g3d/g3d_3dsmax.h"
#include "kdc/nw4r/g3d/g3d_anmchr.h"
#include "kdc/nw4r/g3d/g3d_anmclr.h"
#include "kdc/nw4r/g3d/g3d_anmobj.h"
#include "kdc/nw4r/g3d/g3d_anmscn.h"
#include "kdc/nw4r/g3d/g3d_anmshp.h"
#include "kdc/nw4r/g3d/g3d_anmtexpat.h"
#include "kdc/nw4r/g3d/g3d_anmtexsrt.h"
#include "kdc/nw4r/g3d/g3d_anmvis.h"
#include "kdc/nw4r/g3d/g3d_basic.h"
#include "kdc/nw4r/g3d/g3d_calcmaterial.h"
#include "kdc/nw4r/g3d/g3d_calcview.h"
#include "kdc/nw4r/g3d/g3d_calcvtx.h"
#include "kdc/nw4r/g3d/g3d_calcworld.h"
#include "kdc/nw4r/g3d/g3d_camera.h"
#include "kdc/nw4r/g3d/g3d_dcc.h"
#include "kdc/nw4r/g3d/g3d_draw.h"
#include "kdc/nw4r/g3d/g3d_draw1mat1shp.h"
#include "kdc/nw4r/g3d/g3d_fog.h"
#include "kdc/nw4r/g3d/g3d_init.h"
#include "kdc/nw4r/g3d/g3d_light.h"
#include "kdc/nw4r/g3d/g3d_maya.h"
#include "kdc/nw4r/g3d/g3d_obj.h"
#include "kdc/nw4r/g3d/g3d_rtti.h"
#include "kdc/nw4r/g3d/g3d_scnmdl.h"
#include "kdc/nw4r/g3d/g3d_scnmdl1mat1shp.h"
#include "kdc/nw4r/g3d/g3d_scnmdlsmpl.h"
#include "kdc/nw4r/g3d/g3d_scnobj.h"
#include "kdc/nw4r/g3d/g3d_scnproc.h"
#include "kdc/nw4r/g3d/g3d_scnrfl.h"
#include "kdc/nw4r/g3d/g3d_scnroot.h"
#include "kdc/nw4r/g3d/g3d_state.h"
#include "kdc/nw4r/g3d/g3d_transform.h"
#include "kdc/nw4r/g3d/g3d_workmem.h"
#include "kdc/nw4r/g3d/g3d_xsi.h"

/******************************************************************************
 *
 * Resources
 *
 ******************************************************************************/

#include "kdc/nw4r/g3d/res/g3d_resanm.h"
#include "kdc/nw4r/g3d/res/g3d_resanmamblight.h"
#include "kdc/nw4r/g3d/res/g3d_resanmcamera.h"
#include "kdc/nw4r/g3d/res/g3d_resanmchr.h"
#include "kdc/nw4r/g3d/res/g3d_resanmclr.h"
#include "kdc/nw4r/g3d/res/g3d_resanmfog.h"
#include "kdc/nw4r/g3d/res/g3d_resanmlight.h"
#include "kdc/nw4r/g3d/res/g3d_resanmscn.h"
#include "kdc/nw4r/g3d/res/g3d_resanmshp.h"
#include "kdc/nw4r/g3d/res/g3d_resanmtexpat.h"
#include "kdc/nw4r/g3d/res/g3d_resanmtexsrt.h"
#include "kdc/nw4r/g3d/res/g3d_resanmvis.h"
#include "kdc/nw4r/g3d/res/g3d_rescommon.h"
#include "kdc/nw4r/g3d/res/g3d_resdict.h"
#include "kdc/nw4r/g3d/res/g3d_resfile.h"
#include "kdc/nw4r/g3d/res/g3d_reslightset.h"
#include "kdc/nw4r/g3d/res/g3d_resmat.h"
#include "kdc/nw4r/g3d/res/g3d_resmdl.h"
#include "kdc/nw4r/g3d/res/g3d_resnode.h"
#include "kdc/nw4r/g3d/res/g3d_respltt.h"
#include "kdc/nw4r/g3d/res/g3d_resshp.h"
#include "kdc/nw4r/g3d/res/g3d_restev.h"
#include "kdc/nw4r/g3d/res/g3d_restex.h"
#include "kdc/nw4r/g3d/res/g3d_resuser.h"
#include "kdc/nw4r/g3d/res/g3d_resvtx.h"

/******************************************************************************
 *
 * Platform-specific
 *
 ******************************************************************************/

#include "kdc/nw4r/g3d/platform/g3d_allocator.h"
#include "kdc/nw4r/g3d/platform/g3d_cpu.h"
#include "kdc/nw4r/g3d/platform/g3d_gpu.h"
#include "kdc/nw4r/g3d/platform/g3d_tmem.h"

// IWYU pragma: end_keep
#endif
