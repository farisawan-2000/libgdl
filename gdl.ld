OUTPUT_ARCH (mips)
/* Starts a segment */
#define BEGIN_SEG(name, addr) \
    _##name##SegmentStart = ADDR(.name); \
    _##name##SegmentRomStart = __romPos; \
    .name addr : AT(__romPos)

/* Ends a segment */
#define END_SEG(name) \
    _##name##SegmentEnd = ADDR(.name) + SIZEOF(.name); \
    _##name##SegmentRomEnd = __romPos + SIZEOF(.name); \
    __romPos += SIZEOF(.name);

/* Starts a noload segment which is intended to contain variables which do not have data yet. */
#define BEGIN_NOLOAD(name) \
    _##name##SegmentBssStart = ADDR(.name.noload); \
    .name.noload (NOLOAD) :

/* Ends a noload segment */
#define END_NOLOAD(name) \
    _##name##SegmentBssEnd = ADDR(.name.noload) + SIZEOF(.name.noload); \
    _##name##SegmentBssSize = SIZEOF(.name.noload);

SECTIONS
{
   __romPos = 0;

   BEGIN_SEG(boot, 0x04000000)
   {
      BUILD_DIR/asm/rom_header.o(.text); /* ROM Header */
      BUILD_DIR/boot.6102.o(.data); /* CIC 6102 bootcode */
   }
   END_SEG(boot)
   
   BEGIN_SEG(code, 0x80000400) SUBALIGN(16)
   {
      BUILD_DIR/asm/entry.o(.start);
      obj*.o(.text);
      BUILD_DIR/shapes*.o(.text);
      */libultra_rom.a:*.o(.text);
      */libgcc.a:*.o(.text);
      /usr/lib/n64/PR/rspboot.o(.text);
      /usr/lib/n64/PR/gspFast3D.o(.text);
      /usr/lib/n64/PR/gspTurbo3D.o(.text);
      /usr/lib/n64/PR/gspFast3D.dram.o(.text);
      /usr/lib/n64/PR/gspFast3D.fifo.o(.text);
      /usr/lib/n64/PR/gspLine3D.o(.text);
      /usr/lib/n64/PR/gspF3DEX.fifo.o(.text);
      /usr/lib/n64/PR/gspF3DLX.Rej.fifo.o(.text);
      /usr/lib/n64/PR/gspF3DLP.Rej.fifo.o(.text);

      /usr/lib/n64/PR/rspboot.o(.data);
      /usr/lib/n64/PR/gspFast3D.o(.data);
      /usr/lib/n64/PR/gspTurbo3D.o(.data);
      /usr/lib/n64/PR/gspFast3D.dram.o(.data);
      /usr/lib/n64/PR/gspFast3D.fifo.o(.data);
      /usr/lib/n64/PR/gspLine3D.o(.data);
      /usr/lib/n64/PR/gspF3DEX.fifo.o(.data);
      /usr/lib/n64/PR/gspF3DLX.Rej.fifo.o(.data);
      /usr/lib/n64/PR/gspF3DLP.Rej.fifo.o(.data);

      BUILD_DIR/shapes*.o(.*data*);
      obj*.o(.*data*);
      */libultra_rom.a:*.o(.*data*);
      */libgcc.a:*.o(.*data*);

      BUILD_DIR/shapes*.o(.*rodata*);
      obj*.o(.*rodata*);
      */libultra_rom.a:*.o(.*rodata*);
      */libgcc.a:*.o(.*rodata*);
   }
   END_SEG(code)
   BEGIN_NOLOAD(code)
   {
      obj*.o(.*bss*);
      BUILD_DIR/shapes*.o(.*bss*);
      */libultra_rom.a:*.o(.*bss*);
      */libgcc.a:*.o(.*bss*);

      */libultra_rom.a:*.o(COMMON);
      */libultra_rom.a:*.o(.scommon);
      */libultra_rom.a:*.o(.*bss*);
   }
   END_NOLOAD(code)

   /* Discard everything not specifically mentioned above. */
   /DISCARD/ :
   {
      /usr/lib/n64/libultra_rom.a(string.o);
      *(*);
   }
}
