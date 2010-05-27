#ifndef __SETTINGS_H
#define __SETTINGS_H

#include <endian.h>

#define ROCKBOX 1
#if __BYTE_ORDER == __LITTLE_ENDIAN
#define ROCKBOX_LITTLE_ENDIAN 1
#else
#define ROCKBOX_BIG_ENDIAN 1
#endif
#define DEBUG 1
#define SWCODEC 1
#define HAVE_RECORDING 1
#define CONFIG_CODEC SWCODEC

#define STATICIRAM static
#define IBSS_ATTR /*none*/
#define ICODE_ATTR  /*none*/
#define ICONST_ATTR  /*none*/

#endif
