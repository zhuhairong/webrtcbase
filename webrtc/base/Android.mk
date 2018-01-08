LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE    := libwebrtc_base
LOCAL_CPP_EXTENSION := .cc


#schanneladapter.cc

LOCAL_SRC_FILES := \
        asyncfile.cc          event.cc                   linux.cc             nssidentity.cc                    stringutils.cc                                       \
		asynchttprequest.cc   exp_filter.cc              logging.cc           nssstreamadapter.cc      sha1.cc                    systeminfo.cc                	     \
		asyncinvoker.cc       filelock.cc                sharedexclusivelock.cc     task.cc                                         								 \
		asyncsocket.cc        fileutils.cc               signalthread.cc        taskparent.cc                                     									 \
		asynctcpsocket.cc     firewallsocketserver.cc    ssladapter.cc         socketadapters.cc          taskrunner.cc                                   			 \
		asyncudpsocket.cc     flags.cc                   sslsocketfactory.cc   socketaddress.cc           testclient.cc                                       		 \
		autodetectproxy.cc    helpers.cc                 optionsfile.cc       socketaddresspair.cc       thread.cc                                  				 \
		bandwidthsmoother.cc  httpbase.cc                md5.cc               pathutils.cc             socketpool.cc              thread_checker_impl.cc             \
		base64.cc             httpclient.cc              messagedigest.cc     physicalsocketserver.cc  socketstream.cc            timeutils.cc                       \
		bytebuffer.cc         httpcommon.cc              messagehandler.cc    platform_file.cc                       timing.cc               worker.cc               \
		checks.cc             httprequest.cc             messagequeue.cc      posix.cc                           transformadapter.cc                                 \
		common.cc             httpserver.cc              multipart.cc         profiler.cc                                                                            \
		cpumonitor.cc         ifaddrs-android.cc         natserver.cc         proxydetect.cc                   unixfilesystem.cc                                     \
		crc32.cc              ipaddress.cc               natsocketfactory.cc  proxyinfo.cc                     urlencode.cc                                          \
		dbus.cc               nattypes.cc          		 proxyserver.cc       versionparsing.cc                                                       				 \
		diskcache.cc          latebindingsymboltable.cc  nethelpers.cc        ratelimiter.cc           stream.cc                  virtualsocketserver.cc             \
		libdbusglibsymboltable.cc  network.cc            ratetracker.cc       stringencode.cc                                                                         


LOCAL_SHARED_LIBRARIES := libdl liblog
LOCAL_STATIC_LIBRARIES += 

LOCAL_CFLAGS += -DWEBRTC_POSIX -DWEBRTC_LINUX -DWEBRTC_ANDROID   -std=c++11

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
					$(LOCAL_PATH)/../../

LOCAL_SHARED_LIBRARIES += libstlport
include external/stlport/libstlport.mk

include $(BUILD_SHARED_LIBRARY)