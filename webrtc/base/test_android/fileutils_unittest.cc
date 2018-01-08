#include "webrtc/base/fileutils.h"
#include "webrtc/base/pathutils.h"
#include "webrtc/base/stream.h"
#include "webrtc/base/thread.h"
#include "webrtc/base/event.h"
#include "webrtc/base/scoped_ptr.h"
#include "webrtc/base/filelock.h"
#include <stdio.h>

using namespace rtc;

void test1()
{
	Pathname path("/mnt/sdcard/test.txt");

	FileStream* fs;
	char buf[256];
	size_t bytes;

	fs = Filesystem::OpenFile(path, "wb");
	fs->Write("test", 4, &bytes, NULL);
	delete fs;

	fs = Filesystem::OpenFile(path, "rb");
	fs->Read(buf, sizeof(buf), &bytes, NULL);
	buf[bytes] = '\0';
	printf("read buf:%s\n", buf);

	Filesystem::DeleteFile(path);
	printf("end %s =======================================\n", __FUNCTION__);
}

void test2()
{
	Pathname path("/mnt/sdcard/");

	printf("is folder:%d\n", Filesystem::IsFolder(path));

	int64 free = 0;
	Filesystem::GetDiskFreeSpace(path, &free);
	float freeK = free/1024;
	float freeM = freeK/1024;
	float freeG = freeM/1024;
	if(freeK < 1.0)
		printf("%s free %.2f\n", path.pathname().c_str(), free);
	else if(freeM < 1.0)
		printf("%s free %.2fK\n", path.pathname().c_str(), freeK);
	else if(freeG < 1.0)
		printf("%s free %.2fM\n", path.pathname().c_str(), freeM);
	else
		printf("%s free %.2fG\n", path.pathname().c_str(), freeG);

	printf("current directory:%s\n", Filesystem::GetCurrentDirectory().pathname().c_str());
	printf("end %s =======================================\n", __FUNCTION__);
}


class FileLockTest : public Runnable
{
public:
	FileLockTest()
		:done_(false, false),
		 thread_lock_failed_(false)
	{
	}

	void SetUp()
	{
		thread_lock_failed_ = false;
		temp_file_.SetPathname("/mnt/sdcard/mix.aac");
	}

	virtual void Run(Thread* t)
	{
		scoped_ptr<FileLock> lock(FileLock::TryLock(temp_file_.pathname()));
		thread_lock_failed_ = lock.get() == NULL;
		done_.Set();
	}

	void LockOnThread()
	{
		locker_.Start(this);
		done_.Wait(5000);
	}


	Event done_;
	Thread locker_;
	bool thread_lock_failed_;
	Pathname temp_file_;
};

void test3()
{
	FileLockTest flt;
	flt.SetUp();
	scoped_ptr<FileLock> lock(FileLock::TryLock(flt.temp_file_.pathname()));
	printf("is absent:%d\n", Filesystem::IsAbsent(flt.temp_file_.pathname()));
	lock->Unlock();
	printf("is absent:%d\n", Filesystem::IsAbsent(flt.temp_file_.pathname()));
	printf("end %s =======================================\n", __FUNCTION__);
}

int main()
{
	test1();
	test2();
	test3();
	return 0;
}
