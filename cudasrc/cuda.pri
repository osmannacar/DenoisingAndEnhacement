
# Cuda sources

# Project dir and outputs
PROJECT_DIR = $$system(pwd)
OBJECTS_DIR = $$PROJECT_DIR/Obj
DESTDIR = ../bin

 cu.name = Cuda ${QMAKE_FILE_IN}
 cu.input = CUSOURCES
 cu.CONFIG += no_link
 cu.variable_out = OBJECTS

 isEmpty(QMAKE_CUC) {
        win32:QMAKE_CUC = $$quote($$(CUDA_BIN_PATH)\\nvcc.exe)
         else:QMAKE_CUC = /usr/local/cuda/bin/nvcc
 }
 isEmpty(CU_DIR):CU_DIR = .
 isEmpty(QMAKE_CPP_MOD_CU):QMAKE_CPP_MOD_CU =
 isEmpty(QMAKE_EXT_CPP_CU):QMAKE_EXT_CPP_CU = .cu

 win32:INCLUDEPATH += $$quote($$(CUDA_INC_PATH))
 unix:INCLUDEPATH += /usr/local/cuda/include
 unix:QMAKE_LIBDIR += /usr/local/cuda/lib
 unix:QMAKE_LIBDIR += /usr/local/cuda/lib64

 QMAKE_CUFLAGS += $$QMAKE_CXXFLAGS
 mac:QMAKE_CUFLAGS += -stdlib=libstdc++
 win32:QMAKE_CUFLAGS += -Zc:wchar_t
 DebugBuild:QMAKE_CUFLAGS += $$QMAKE_CXXFLAGS_DEBUG
 ReleaseBuild:QMAKE_CUFLAGS += $$QMAKE_CXXFLAGS_RELEASE
 QMAKE_CUFLAGS += $$QMAKE_CXXFLAGS_RTTI_ON $$QMAKE_CXXFLAGS_WARN_ON $$QMAKE_CXXFLAGS_STL_ON
 mac:!x86:QMAKE_CUFLAGS += -arch x86_64 -Xarch_x86_64
 mac:!x86_64:QMAKE_CUFLAGS += -arch i386 -Xarch_i386
 win32:contains(QMAKE_TARGET.arch, x86):QMAKE_CUEXTRAFLAGS += -m32
 win32:contains(QMAKE_TARGET.arch, x86_64):QMAKE_CUEXTRAFLAGS += -m64
#message(QMAKE_CUFLAGS: $$QMAKE_CUFLAGS)

 QMAKE_CUEXTRAFLAGS += -Xcompiler $$join(QMAKE_CUFLAGS, ",") $$CUFLAGS
 QMAKE_CUEXTRAFLAGS += $(DEFINES)
 win32:QMAKE_CUEXTRAFLAGS += $$join(QMAKE_COMPILER_DEFINES, " -D", -D)
 win32:QMAKE_CUEXTRAFLAGS += $(INCPATH)
 mac:QMAKE_CUEXTRAFLAGS += -ccbin clang
 unix:contains(QMAKE_CUFLAGS, -m64):QMAKE_CUEXTRAFLAGS += -m64
 unix:contains(QMAKE_CUFLAGS, -m32):QMAKE_CUEXTRAFLAGS += -m32
 QMAKE_CUEXTRAFLAGS += -c
#QMAKE_CUEXTRAFLAGS += -v
#QMAKE_CUEXTRAFLAGS += -keep
#QMAKE_CUEXTRAFLAGS += -clean
#message(QMAKE_CUEXTRAFLAGS: $$QMAKE_CUEXTRAFLAGS)
 QMAKE_EXTRA_VARIABLES += QMAKE_CUEXTRAFLAGS

 cu.commands = $$QMAKE_CUC $(EXPORT_QMAKE_CUEXTRAFLAGS) -o $$OBJECTS_DIR/$${QMAKE_CPP_MOD_CU}${QMAKE_FILE_BASE}$${QMAKE_EXT_OBJ} ${QMAKE_FILE_NAME}$$escape_expand(\\n\\t)
 cu.output = $$OBJECTS_DIR/$${QMAKE_CPP_MOD_CU}${QMAKE_FILE_BASE}$${QMAKE_EXT_OBJ}
 silent:cu.commands = @echo nvcc ${QMAKE_FILE_IN} && $$cu.commands
 QMAKE_EXTRA_COMPILERS += cu

 build_pass|isEmpty(BUILDS):cuclean.depends = compiler_cu_clean
 else:cuclean.CONFIG += recursive
 QMAKE_EXTRA_TARGETS += cuclean


CUSOURCES += \
    $$PWD/cuda/bpr/bpr.cu \
    $$PWD/cuda/stretch/stretcher.cu \
    $$PWD/cuda/radix_sort/scan.cu \
    $$PWD/cuda/radix_sort/sort.cu \
    $$PWD/cuda/dehaze/boxfilter.cu \
    $$PWD/cuda/dehaze/transpose.cu \
    $$PWD/cuda/dehaze/darkchannel.cu \
    $$PWD/cuda/dehaze/dehaze_kernel.cu \
    $$PWD/cuda/dehaze/minimum_filter.cu \
    $$PWD/cuda/dehaze/dehaze.cu \
    $$PWD/cuda/dehazeImage.cu \

HEADERS += \
    $$PWD/cuda/Utils.h \
    $$PWD/cuda/bpr/bpr.h \
    $$PWD/cuda/dehazeImage.h \
    $$PWD/cuda/dehaze/transpose.h \
    $$PWD/cuda/dehaze/minimum_filter.h \
    $$PWD/cuda/dehaze/boxfilter.h \
    $$PWD/cuda/dehaze/darkchannel.h \
    $$PWD/cuda/dehaze/dehaze_kernel.h \
    $$PWD/cuda/dehaze/dehaze.h \
    $$PWD/cuda/dehazeImage/dehazeImage.h \
    $$PWD/cuda/stretch/stretcher.h \
    $$PWD/cuda/radix_sort/scan.h \
    $$PWD/cuda/radix_sort/sort.h \
    $$PWD/cuda/test.h \

DISTFILES += \
    $$PWD/cuda/dehazeImage/dehazeImage.cu \
    $$PWD/cuda/dehazeImage/dehazeImageV2.cu



