NAME = libbase64.a
CFLAGS += -std=c99 -O3 -Wall -Wextra -pedantic -DBASE64_STATIC_DEFINE

# Set OBJCOPY if not defined by environment:
OBJCOPY ?= objcopy

SRC_DIR = src

OBJS = \
  $(SRC_DIR)/arch/avx512/codec.o \
  $(SRC_DIR)/arch/avx2/codec.o \
  $(SRC_DIR)/arch/generic/codec.o \
  $(SRC_DIR)/arch/neon32/codec.o \
  $(SRC_DIR)/arch/neon64/codec.o \
  $(SRC_DIR)/arch/ssse3/codec.o \
  $(SRC_DIR)/arch/sse41/codec.o \
  $(SRC_DIR)/arch/sse42/codec.o \
  $(SRC_DIR)/arch/avx/codec.o \
  $(SRC_DIR)/lib.o \
  $(SRC_DIR)/codec_choose.o \
  $(SRC_DIR)/tables/tables.o

HAVE_AVX512 = 0
HAVE_AVX2   = 0
HAVE_NEON32 = 0
HAVE_NEON64 = 0
HAVE_SSSE3  = 0
HAVE_SSE41  = 0
HAVE_SSE42  = 0
HAVE_AVX    = 0

# The user should supply compiler flags for the codecs they want to build.
# Check which codecs we're going to include:
ifdef AVX512_CFLAGS
  HAVE_AVX512 = 1
endif
ifdef AVX2_CFLAGS
  HAVE_AVX2 = 1
endif
ifdef NEON32_CFLAGS
  HAVE_NEON32 = 1
endif
ifdef NEON64_CFLAGS
  HAVE_NEON64 = 1
endif
ifdef SSSE3_CFLAGS
  HAVE_SSSE3 = 1
endif
ifdef SSE41_CFLAGS
  HAVE_SSE41 = 1
endif
ifdef SSE42_CFLAGS
  HAVE_SSE42 = 1
endif
ifdef AVX_CFLAGS
  HAVE_AVX = 1
endif
ifdef OPENMP
  CFLAGS += -fopenmp
endif

TARGET := $(shell $(CC) -dumpmachine)

.PHONY: all analyze clean

# Сборка по умолчанию: бинарник и статическая библиотека
all: $(NAME)

# Создание статической библиотеки
$(NAME): $(OBJS)
	@ar rcs $@ $^

$(SRC_DIR)/config.h:
	@echo "#define HAVE_AVX512 $(HAVE_AVX512)"  > $@
	@echo "#define HAVE_AVX2   $(HAVE_AVX2)"   >> $@
	@echo "#define HAVE_NEON32 $(HAVE_NEON32)" >> $@
	@echo "#define HAVE_NEON64 $(HAVE_NEON64)" >> $@
	@echo "#define HAVE_SSSE3  $(HAVE_SSSE3)"  >> $@
	@echo "#define HAVE_SSE41  $(HAVE_SSE41)"  >> $@
	@echo "#define HAVE_SSE42  $(HAVE_SSE42)"  >> $@
	@echo "#define HAVE_AVX    $(HAVE_AVX)"    >> $@

$(OBJS): $(SRC_DIR)/config.h
$(OBJS): CFLAGS += -Ilib

$(SRC_DIR)/arch/avx512/codec.o: CFLAGS += $(AVX512_CFLAGS)
$(SRC_DIR)/arch/avx2/codec.o:   CFLAGS += $(AVX2_CFLAGS)
$(SRC_DIR)/arch/neon32/codec.o: CFLAGS += $(NEON32_CFLAGS)
$(SRC_DIR)/arch/neon64/codec.o: CFLAGS += $(NEON64_CFLAGS)
$(SRC_DIR)/arch/ssse3/codec.o:  CFLAGS += $(SSSE3_CFLAGS)
$(SRC_DIR)/arch/sse41/codec.o:  CFLAGS += $(SSE41_CFLAGS)
$(SRC_DIR)/arch/sse42/codec.o:  CFLAGS += $(SSE42_CFLAGS)
$(SRC_DIR)/arch/avx/codec.o:    CFLAGS += $(AVX_CFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

analyze: clean
	@scan-build --use-analyzer=`which clang` --status-bugs make

clean:
	@if [ -f $(SRC_DIR)/config.h ]; then rm $(SRC_DIR)/config.h; fi
	@for obj in $(OBJS); do \
    	    if [ -f $$obj ]; then rm $$obj; fi; \
    done


uninstall: clean
	@if [ -f $(NAME) ]; then rm $(NAME); fi
