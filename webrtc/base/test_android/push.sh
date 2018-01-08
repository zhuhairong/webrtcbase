#/bin/sh

if [ -z $1 ]
then 
	echo "useage push.sh 1"
else
echo $1

adb.sh $1  push /home/zhr/android/mountfs1/a31_4.4/android4.4/out/target/product/fiber-a31st/system/lib/libwebrtc_base.so /system/lib/
adb.sh $1  push /home/zhr/android/mountfs1/a31_4.4/android4.4/out/target/product/fiber-a31st/system/bin/webrtc_base_bind_unittest /system/bin/
adb.sh $1  shell chmod 777 /system/bin/webrtc_base_bind_unittest
adb.sh $1  push /home/zhr/android/mountfs1/a31_4.4/android4.4/out/target/product/fiber-a31st/system/bin/webrtc_base_bytebuffer_unittest /system/bin/
adb.sh $1  shell chmod 777 /system/bin/webrtc_base_bytebuffer_unittest
adb.sh $1  push /home/zhr/android/mountfs1/a31_4.4/android4.4/out/target/product/fiber-a31st/system/bin/webrtc_base_thread_unittest /system/bin/
adb.sh $1  shell chmod 777 /system/bin/webrtc_base_thread_unittest
adb.sh $1  push /home/zhr/android/mountfs1/a31_4.4/android4.4/out/target/product/fiber-a31st/system/bin/webrtc_base_signalthread_unittest /system/bin/
adb.sh $1  shell chmod 777 /system/bin/webrtc_base_signalthread_unittest
adb.sh $1  push /home/zhr/android/mountfs1/a31_4.4/android4.4/out/target/product/fiber-a31st/system/bin/webrtc_base_fileutils_unittest /system/bin/
adb.sh $1  shell chmod 777 /system/bin/webrtc_base_fileutils_unittest
adb.sh $1  push /home/zhr/android/mountfs1/a31_4.4/android4.4/out/target/product/fiber-a31st/system/bin/webrtc_base_optionsfile_unittest /system/bin/
adb.sh $1  shell chmod 777 /system/bin/webrtc_base_optionsfile_unittest
adb.sh $1  push /home/zhr/android/mountfs1/a31_4.4/android4.4/out/target/product/fiber-a31st/system/bin/webrtc_base_network_unittest /system/bin/
adb.sh $1  shell chmod 777 /system/bin/webrtc_base_network_unittest
adb.sh $1  push /home/zhr/android/mountfs1/a31_4.4/android4.4/out/target/product/fiber-a31st/system/bin/webrtc_base_socket_unittest /system/bin/
adb.sh $1  shell chmod 777 /system/bin/webrtc_base_socket_unittest

adb.sh $1  shell sync

fi