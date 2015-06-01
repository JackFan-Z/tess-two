LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := liblept

# leptonica (minus freetype)

BLACKLIST_SRC_FILES := \
  %endiantest.c \
  %freetype.c \
  %xtractprotos.c

LEPTONICA_SRC_FILES := \
  $(subst $(LOCAL_PATH)/,,$(wildcard $(LEPTONICA_PATH)/src/*.c))

LOCAL_SRC_FILES := \
  $(filter-out $(BLACKLIST_SRC_FILES),$(LEPTONICA_SRC_FILES))

LOCAL_CFLAGS := \
  -DHAVE_CONFIG_H

LOCAL_LDLIBS := \
  -lz

# jni

ifeq ($(TESS_INSTALL_MODULES),on)
else
LOCAL_SRC_FILES += \
  box.cpp \
  boxa.cpp \
  pix.cpp \
  pixa.cpp \
  utilities.cpp \
  readfile.cpp \
  writefile.cpp \
  jni.cpp
  
endif
LOCAL_C_INCLUDES += \
  $(LOCAL_PATH) \
  $(LEPTONICA_PATH)/src

LOCAL_LDLIBS += \
  -ljnigraphics \
  -llog

# common

LOCAL_PRELINK_MODULE:= false

ifeq ($(TESS_INSTALL_MODULES),on)
  LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)
  LOCAL_SRC_FILES := ../../libs/$(TARGET_ARCH_ABI)/$(LOCAL_MODULE).so
  include $(PREBUILT_SHARED_LIBRARY)
else
  include $(BUILD_SHARED_LIBRARY)
endif
