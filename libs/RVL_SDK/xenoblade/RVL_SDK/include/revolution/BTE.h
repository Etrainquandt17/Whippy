#ifndef RVL_SDK_PUBLIC_BTE_H
#define RVL_SDK_PUBLIC_BTE_H
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 *
 * BTE
 *
 ******************************************************************************/
#include <xenoblade/RVL_SDK/include/revolution/bte/include/bt_target.h>
#include <xenoblade/RVL_SDK/include/revolution/bte/include/bt_trace.h>
#include <xenoblade/RVL_SDK/include/revolution/bte/include/bte.h>
#include <xenoblade/RVL_SDK/include/revolution/bte/include/bte_appl.h>
#include <xenoblade/RVL_SDK/include/revolution/bte/include/bte_common.h>
#include <xenoblade/RVL_SDK/include/revolution/bte/include/gki_target.h>

/******************************************************************************
 *
 * BTA
 *
 ******************************************************************************/
#include <xenoblade/RVL_SDK/include/revolution/bte/bta/include/bta_api.h>
#include <xenoblade/RVL_SDK/include/revolution/bte/bta/include/bta_hh_api.h>

/******************************************************************************
 *
 * API
 *
 ******************************************************************************/
#include <xenoblade/RVL_SDK/include/revolution/bte/stack/include/l2c_api.h>

/******************************************************************************
 *
 * RVL
 *
 ******************************************************************************/
#include <xenoblade/RVL_SDK/include/revolution/bte/rvl/uusb_ppc.h>

// Yeah...
#undef TRUE

#ifdef __cplusplus
}
#endif
#endif
