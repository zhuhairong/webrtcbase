/*
 *  Copyright 2004 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */
#include <stdio.h>
#include "webrtc/base/signalthread.h"
#include "webrtc/base/thread.h"

using namespace rtc;

class SignalThreadTest : public sigslot::has_slots<>
{
 public:
  class SlowSignalThread : public SignalThread {
   public:
    SlowSignalThread(SignalThreadTest* harness) : harness_(harness) {
    }

    virtual ~SlowSignalThread() {
      //EXPECT_EQ(harness_->main_thread_, Thread::Current());
      ++harness_->thread_deleted_;
    }

    const SignalThreadTest* harness() { return harness_; }

   protected:
    virtual void OnWorkStart() {
    	printf("OnWorkStart\n");
      //ASSERT_TRUE(harness_ != NULL);
      ++harness_->thread_started_;
      //EXPECT_EQ(harness_->main_thread_, Thread::Current());
      //EXPECT_FALSE(worker()->RunningForTest());  // not started yet
    }

    virtual void OnWorkStop() {
    	printf("OnWorkStop\n");
      ++harness_->thread_stopped_;
      //EXPECT_EQ(harness_->main_thread_, Thread::Current());
      //EXPECT_TRUE(worker()->RunningForTest());  // not stopped yet
    }

    virtual void OnWorkDone() {
    	printf("OnWorkDone\n");
      ++harness_->thread_done_;
      //EXPECT_EQ(harness_->main_thread_, Thread::Current());
      //EXPECT_TRUE(worker()->RunningForTest());  // not stopped yet
    }

    virtual void DoWork() {
    	printf("DoWork\n");
      //EXPECT_NE(harness_->main_thread_, Thread::Current());
      //EXPECT_EQ(worker(), Thread::Current());
      Thread::Current()->socketserver()->Wait(250, false);
    }

   private:
    SignalThreadTest* harness_;
    DISALLOW_EVIL_CONSTRUCTORS(SlowSignalThread);
  };

  void OnWorkComplete(rtc::SignalThread* thread) {
	  printf("OnWorkComplete\n");
    SlowSignalThread* t = static_cast<SlowSignalThread*>(thread);
    //EXPECT_EQ(t->harness(), this);
    //EXPECT_EQ(main_thread_, Thread::Current());

    ++thread_completed_;
    if (!called_release_) {
      thread->Release();
    }
  }

  virtual void SetUp() {
    main_thread_ = Thread::Current();
    thread_ = new SlowSignalThread(this);
    thread_->SignalWorkDone.connect(this, &SignalThreadTest::OnWorkComplete);
    called_release_ = false;
    thread_started_ = 0;
    thread_done_ = 0;
    thread_completed_ = 0;
    thread_stopped_ = 0;
    thread_deleted_ = 0;
  }

  virtual void TearDown() {
  }

  Thread* main_thread_;
  SlowSignalThread* thread_;
  bool called_release_;

  int thread_started_;
  int thread_done_;
  int thread_completed_;
  int thread_stopped_;
  int thread_deleted_;
};

class OwnerThread : public Thread, public sigslot::has_slots<> {
 public:
  explicit OwnerThread(SignalThreadTest* harness)
      : harness_(harness),
        has_run_(false) {
  }

  virtual ~OwnerThread() {
    Stop();
  }

  virtual void Run() {
	  printf("OwnerThread Run\n");
    SignalThreadTest::SlowSignalThread* signal_thread =
        new SignalThreadTest::SlowSignalThread(harness_);
    signal_thread->SignalWorkDone.connect(this, &OwnerThread::OnWorkDone);
    signal_thread->Start();
    Thread::Current()->socketserver()->Wait(1000*5, false);
    signal_thread->Release();
    // Delete |signal_thread|.
    signal_thread->Destroy(true);
    has_run_ = true;
  }

  bool has_run() { return has_run_; }
  void OnWorkDone(SignalThread* signal_thread) {
    printf(" This shouldn't get called.\n");
  }

 private:
  SignalThreadTest* harness_;
  bool has_run_;
  DISALLOW_EVIL_CONSTRUCTORS(OwnerThread);
};

void test1()
{
	SignalThreadTest stt;
	stt.SetUp();
	{
		scoped_ptr<OwnerThread> owner(new OwnerThread(&stt));
		stt.main_thread_ = owner.get();
		owner->Start();
		while (!owner->has_run()) {
		  Thread::Current()->socketserver()->Wait(10, false);
		}
	}
	Thread::Current()->socketserver()->Wait(500, false);
	printf("end %s =======================================\n", __FUNCTION__);
}

#define EXPECT_STATE(index, stt) \
  printf("[%d] started:%d, done:%d, completed:%d, stopped:%d, deleted:%d\n", index, stt.thread_started_, stt.thread_done_, stt.thread_completed_, stt.thread_stopped_, stt.thread_deleted_);

void test2()
{
	SignalThreadTest stt;
	stt.SetUp();

	stt.thread_->Start();
	EXPECT_STATE(1, stt);
	Thread::SleepMs(500);
	EXPECT_STATE(2, stt);
	Thread::Current()->ProcessMessages(0);
	EXPECT_STATE(3, stt);
	printf("end %s =======================================\n", __FUNCTION__);
}

void test3()
{
	SignalThreadTest stt;
	stt.SetUp();

	stt.thread_->Start();
	EXPECT_STATE(1, stt);
	stt.thread_->Release();
	stt.called_release_ = true;
	EXPECT_STATE(2, stt);
	Thread::SleepMs(500);
	EXPECT_STATE(3, stt);
	Thread::Current()->ProcessMessages(0);
	EXPECT_STATE(4, stt);
	printf("end %s =======================================\n", __FUNCTION__);
}

void test4()
{
	SignalThreadTest stt;
	stt.SetUp();

	stt.thread_->Start();
	EXPECT_STATE(1, stt);
	stt.thread_->Destroy(true);
	EXPECT_STATE(2, stt);
	Thread::Current()->ProcessMessages(0);
	EXPECT_STATE(3, stt);
	printf("end %s =======================================\n", __FUNCTION__);
}

void test5()
{
	SignalThreadTest stt;
	stt.SetUp();

	stt.thread_->Start();
	EXPECT_STATE(1, stt);
	stt.thread_->Destroy(false);
	EXPECT_STATE(2, stt);
	Thread::SleepMs(500);
	EXPECT_STATE(3, stt);
	Thread::Current()->ProcessMessages(0);
	EXPECT_STATE(4, stt);
	printf("end %s =======================================\n", __FUNCTION__);
}

int main()
{
	test1();
	test2();
	test3();
	test4();
	test5();
	return 0;
}
