# Makefile to build mini-gfx

TARGET_STRING := gdl
TARGET := $(TARGET_STRING)

# Preprocessor definitions
DEFINES := _FINALROM=1 NDEBUG=1 F3DEX_GBI=1 _MIPS_SZLONG=32 _LANGUAGE_C_PLUS_PLUS=1 __sgi=1

IGNORE_WARNS := -Wno-builtin-declaration-mismatch -Wno-write-strings

SRC_DIRS :=

# Whether to hide commands or not
VERBOSE ?= 0
ifeq ($(VERBOSE),0)
  V := @
endif

# Whether to colorize build messages
COLOR ?= 1

#==============================================================================#
# Target Executable and Sources                                                #
#==============================================================================#
# BUILD_DIR is the location where all build artifacts are placed
BUILD_DIR := build
ROM            := $(BUILD_DIR)/$(TARGET_STRING).z64
ELF            := $(BUILD_DIR)/$(TARGET_STRING).elf
LD_SCRIPT      := $(TARGET_STRING).ld
BOOT		:= /usr/lib/n64/PR/bootcode/boot.6102
BOOT_OBJ	:= $(BUILD_DIR)/boot.6102.o

# Directories containing source files
SRC_DIRS += src

C_FILES           := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
CPP_FILES           := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
S_FILES           := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.s))

CPP_OFILES := $(foreach file,$(CPP_FILES),$(BUILD_DIR)/$(file:.cpp=.o))

# Object files
O_FILES := $(foreach file,$(C_FILES),$(BUILD_DIR)/$(file:.c=.o)) \
					 $(CPP_OFILES) \
					$(foreach file,$(S_FILES),$(BUILD_DIR)/$(file:.s=.o)) \
		   $(BOOT_OBJ) \
		   $(wildcard obj/*.o)

# Automatic dependency files
DEP_FILES := $(O_FILES:.o=.d) $(ASM_O_FILES:.o=.d)  $(BUILD_DIR)/$(LD_SCRIPT).d

#==============================================================================#
# Compiler Options                                                             #
#==============================================================================#

AS        := mips-n64-as
CC        := mips-n64-gcc
# CFRONT    := tools/cfront/cfront
CFRONT    := ~/qemu-irix -L ~/Decomps/kirby64/tools/ido7.1/ ~/Decomps/kirby64/tools/ido7.1/usr/lib/c++/cfront
CPP       := cpp
LD        := mips-n64-ld
AR        := mips-n64-ar
OBJDUMP   := mips-n64-objdump
OBJCOPY   := mips-n64-objcopy

IDO_CC := tools/ido53/cc
IDO_CFLAGS := -G 0 -O2 -nostdinc -DTARGET_N64 -D_LANGUAGE_C -mips2 -Iinclude -Ibuild/us -Ibuild/us/include -Isrc -I. -Iinclude/libc -DVERSION_US=1 -DF3D_OLD=1 -non_shared -Wab,-r4300_mul -Xcpluscomm -Xfullwarn -signed -32

INCLUDE_DIRS += /usr/include/n64 include $(BUILD_DIR) $(BUILD_DIR)/include src .

C_DEFINES := $(foreach d,$(DEFINES),-D$(d))
DEF_INC_CFLAGS := $(foreach i,$(INCLUDE_DIRS),-I$(i)) $(C_DEFINES)

CFLAGS = -G 0 -O2 -g -mabi=32 -ffreestanding -mfix4300 $(DEF_INC_CFLAGS)
ASFLAGS     := -march=vr4300 -mabi=32 $(foreach i,$(INCLUDE_DIRS),-I$(i)) $(foreach d,$(DEFINES),--defsym $(d))

# C preprocessor flags
CPPFLAGS := -P -Wno-trigraphs $(DEF_INC_CFLAGS)

# tools
PRINT = printf

ifeq ($(COLOR),1)
NO_COL  := \033[0m
RED     := \033[0;31m
GREEN   := \033[0;32m
BLUE    := \033[0;34m
YELLOW  := \033[0;33m
BLINK   := \033[33;5m
endif

# Common build print status function
define print
  @$(PRINT) "$(GREEN)$(1) $(YELLOW)$(2)$(GREEN) -> $(BLUE)$(3)$(NO_COL)\n"
endef

#==============================================================================#
# Main Targets                                                                 #
#==============================================================================#

# Default target
default: $(ROM)

clean:
	$(RM) -r $(BUILD_DIR)

test: $(ROM)
	~/Devel/m64p/mupen64plus/mupen64plus-gui $<

ALL_DIRS := $(BUILD_DIR) $(addprefix $(BUILD_DIR)/,$(SRC_DIRS))

# Make sure build directory exists before compiling anything
DUMMY != mkdir -p $(ALL_DIRS)

#==============================================================================#
# Compilation Recipes                                                          #
#==============================================================================#

# Compile C code
$(BUILD_DIR)/%.o: %.c
	$(call print,Compiling:,$<,$@)
	$(IDO_CC) -c $(IDO_CFLAGS) -o $@ $<
$(BUILD_DIR)/%.o: %.cpp
	$(call print,Compiling:,$<,$@)
	g++ -fsigned-char -m32 -nostdinc -std=c++98 $(IGNORE_WARNS) -fsyntax-only $(DEF_INC_CFLAGS) $<
	cpp -P $(DEF_INC_CFLAGS) -MMD -MF $(BUILD_DIR)/$*.d -o $(@D)/$(@F).cc $<
	$(CFRONT) < $(@D)/$(@F).cc > $(@D)/$(@F).i
	$(IDO_CC) -c $(IDO_CFLAGS) -o $@ $(@D)/$(@F).i
$(BUILD_DIR)/%.o: $(BUILD_DIR)/%.c
	$(call print,Compiling:,$<,$@)
	$(V)$(CC) -c $(CFLAGS) -MMD -MF $(BUILD_DIR)/$*.d  -o $@ $<

# Assemble assembly code
$(BUILD_DIR)/%.o: %.s
	$(call print,Assembling:,$<,$@)
	$(V)$(CC) -c $(CFLAGS) $(foreach i,$(INCLUDE_DIRS),-Wa,-I$(i)) -x assembler-with-cpp -MMD -MF $(BUILD_DIR)/$*.d  -o $@ $<

# Run linker script through the C preprocessor
$(BUILD_DIR)/$(LD_SCRIPT): $(LD_SCRIPT)
	$(call print,Preprocessing linker script:,$<,$@)
	$(V)$(CPP) $(CPPFLAGS) -DBUILD_DIR=$(BUILD_DIR) -MMD -MP -MT $@ -MF $@.d -o $@ $<

$(BOOT_OBJ): $(BOOT)
	$(V)$(OBJCOPY) -I binary -B mips -O elf32-bigmips $< $@

# Link final ELF file
$(ELF): $(O_FILES) $(BUILD_DIR)/$(LD_SCRIPT)
	@$(PRINT) "$(GREEN)Linking ELF file:  $(BLUE)$@ $(NO_COL)\n"
	$(V)$(LD) -L $(BUILD_DIR) -T $(BUILD_DIR)/$(LD_SCRIPT) -Map $(BUILD_DIR)/$(TARGET).map --no-check-sections -o $@ $(O_FILES) -L/usr/lib/n64 -lultra_rom -L$(N64_LIBGCCDIR) -lgcc

# Build ROM
$(ROM): $(CPP_OFILES) $(O_FILES)
	$(call print,done!)

.PHONY: clean default
# with no prerequisites, .SECONDARY causes no intermediate target to be removed
.SECONDARY:

# Remove built-in rules, to improve performance
MAKEFLAGS += --no-builtin-rules

-include $(DEP_FILES)

print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
