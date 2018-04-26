#ifndef _DRVPAN1026_H
#define _DRVPAN1026_H

#include "DrvPic18f67J10.h"
#include "DrvMcc18.h"
#include "DrvMdxP600.h"

#define BT_PWR_ENABLE_IO  MDX_BT_PWR_ENABLE_IO
#define BT_WP_ENABLE_IO   MDX_BT_WP_IO
#define BT_RESET_IO       MDX_BT_RESET_IO
#define BT_CLKREQ_IO      MDX_BT_CLKREQ_IO

#define BT_PWR_ENABLE_TRIS  MDX_BT_PWR_ENABLE_TRIS
#define BT_WP_ENABLE_TRIS   MDX_BT_WP_TRIS
#define BT_RESET_TRIS       MDX_BT_RESET_TRIS
#define BT_CLKREQ_TRIS      MDX_BT_CLKREQ_TRIS

#define BT_ON    		1
#define BT_OFF   		0


#define DrvBluetoothOff()                   (BT_PWR_ENABLE_IO=BT_OFF)
#define DrvBluetoothOn()                   (BT_PWR_ENABLE_IO	=BT_ON)
#define DrvBluetoothResetOff()          (BT_RESET_IO =	BT_OFF)
#define DrvBluetoothResetOn()           (BT_RESET_IO = BT_ON)

extern void DrvPan1026Init(void);
extern void DrvPan1026Off(void);

#endif // DRVPAN1026_H
