LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := main.c
LOCAL_SHARED_LIBRARIES := libcutils
LOCAL_CFLAGS := -Wno-unused-parameter
LOCAL_MODULE_PATH := $(TARGET_OUT_EXECUTABLES)
LOCAL_MODULE := ducalc

include $(BUILD_EXECUTABLE)
