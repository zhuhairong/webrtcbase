LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE    := webrtc_base_bind_unittest
LOCAL_CPP_EXTENSION := .cc

LOCAL_SRC_FILES := \
        bind_unittest.cc
		

LOCAL_SHARED_LIBRARIES := libdl liblog libwebrtc_base
LOCAL_STATIC_LIBRARIES += 

LOCAL_CFLAGS += -DWEBRTC_POSIX -DWEBRTC_LINUX -DWEBRTC_ANDROID -std=c++11

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
					$(LOCAL_PATH)/../../../

LOCAL_SHARED_LIBRARIES += libstlport
include external/stlport/libstlport.mk

include $(BUILD_EXECUTABLE)

###################################################################################

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE    := webrtc_base_bytebuffer_unittest
LOCAL_CPP_EXTENSION := .cc

LOCAL_SRC_FILES := \
        byte_unittest.cc
		

LOCAL_SHARED_LIBRARIES := libdl liblog libwebrtc_base
LOCAL_STATIC_LIBRARIES += 

LOCAL_CFLAGS += -DWEBRTC_POSIX -DWEBRTC_LINUX -DWEBRTC_ANDROID -std=c++11

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
					$(LOCAL_PATH)/../../../

LOCAL_SHARED_LIBRARIES += libstlport
include external/stlport/libstlport.mk

include $(BUILD_EXECUTABLE)
###################################################################################

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE    := webrtc_base_thread_unittest
LOCAL_CPP_EXTENSION := .cc

LOCAL_SRC_FILES := \
        thread_unittest.cc
		

LOCAL_SHARED_LIBRARIES := libdl liblog libwebrtc_base
LOCAL_STATIC_LIBRARIES += 

LOCAL_CFLAGS += -DWEBRTC_POSIX -DWEBRTC_LINUX -DWEBRTC_ANDROID -std=c++11

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
					$(LOCAL_PATH)/../../../

LOCAL_SHARED_LIBRARIES += libstlport
include external/stlport/libstlport.mk

include $(BUILD_EXECUTABLE)

###################################################################################

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE    := webrtc_base_signalthread_unittest
LOCAL_CPP_EXTENSION := .cc

LOCAL_SRC_FILES := \
        signalthread_unittest.cc
		

LOCAL_SHARED_LIBRARIES := libdl liblog libwebrtc_base
LOCAL_STATIC_LIBRARIES += 

LOCAL_CFLAGS += -DWEBRTC_POSIX -DWEBRTC_LINUX -DWEBRTC_ANDROID -std=c++11

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
					$(LOCAL_PATH)/../../../

LOCAL_SHARED_LIBRARIES += libstlport
include external/stlport/libstlport.mk

include $(BUILD_EXECUTABLE)

###################################################################################

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE    := webrtc_base_fileutils_unittest
LOCAL_CPP_EXTENSION := .cc

LOCAL_SRC_FILES := \
        fileutils_unittest.cc
		

LOCAL_SHARED_LIBRARIES := libdl liblog libwebrtc_base
LOCAL_STATIC_LIBRARIES += 

LOCAL_CFLAGS += -DWEBRTC_POSIX -DWEBRTC_LINUX -DWEBRTC_ANDROID -std=c++11

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
					$(LOCAL_PATH)/../../../

LOCAL_SHARED_LIBRARIES += libstlport
include external/stlport/libstlport.mk

include $(BUILD_EXECUTABLE)
###################################################################################

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE    := webrtc_base_optionsfile_unittest
LOCAL_CPP_EXTENSION := .cc

LOCAL_SRC_FILES := \
        optionsfile_unittest.cc
		

LOCAL_SHARED_LIBRARIES := libdl liblog libwebrtc_base
LOCAL_STATIC_LIBRARIES += 

LOCAL_CFLAGS += -DWEBRTC_POSIX -DWEBRTC_LINUX -DWEBRTC_ANDROID -std=c++11

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
					$(LOCAL_PATH)/../../../

LOCAL_SHARED_LIBRARIES += libstlport
include external/stlport/libstlport.mk

include $(BUILD_EXECUTABLE)

###################################################################################

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE    := webrtc_base_network_unittest
LOCAL_CPP_EXTENSION := .cc

LOCAL_SRC_FILES := \
        network_unittest.cc
		

LOCAL_SHARED_LIBRARIES := libdl liblog libwebrtc_base
LOCAL_STATIC_LIBRARIES += 

LOCAL_CFLAGS += -DWEBRTC_POSIX -DWEBRTC_LINUX -DWEBRTC_ANDROID -std=c++11

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
					$(LOCAL_PATH)/../../../

LOCAL_SHARED_LIBRARIES += libstlport
include external/stlport/libstlport.mk

include $(BUILD_EXECUTABLE)

###################################################################################

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE    := webrtc_base_socket_unittest
LOCAL_CPP_EXTENSION := .cc

LOCAL_SRC_FILES := \
        socket_unittest.cc
		

LOCAL_SHARED_LIBRARIES := libdl liblog libwebrtc_base
LOCAL_STATIC_LIBRARIES += 

LOCAL_CFLAGS += -DWEBRTC_POSIX -DWEBRTC_LINUX -DWEBRTC_ANDROID -std=c++11

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
					$(LOCAL_PATH)/../../../

LOCAL_SHARED_LIBRARIES += libstlport
include external/stlport/libstlport.mk

include $(BUILD_EXECUTABLE)