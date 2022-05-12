#ifndef ALIGN_H
#define ALIGN_H

#define ALIGN16(x) (((u32)(x) + 0xF) & -0x10)
#define ALIGN8(x) (((u32)(x) + 7) & -8)
#define ALIGN4(x) (((u32)(x) + 3) & -4)

#endif
