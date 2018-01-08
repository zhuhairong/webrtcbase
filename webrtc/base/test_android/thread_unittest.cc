#include "webrtc/base/thread.h"
#include "webrtc/base/bind.h"
#include "webrtc/base/asyncinvoker.h"
#include <stdio.h>
#include <unistd.h>
using namespace rtc;
///////////////////////////////////////////////////////////
class TEST1 : public Runnable
{
public:
	virtual void Run(Thread* th)
	{
		printf("thread run\n");
	}
};

void test1()
{
	Thread th;
	TEST1 tc;
	th.Start(&tc);
	th.Stop();
}

///////////////////////////////////////////////////////////
class TEST2
{
public:
	int Run(char* str, int v)
	{
		printf("thread str:%s, v:%d\n", str, v);
		return 0;
	}
};

void test2()
{
	TEST2 tc;
	char* str = "abcdefggg";
	int v = 333;

	Thread th;
	th.Start();
	th.Invoke<int>(Bind(&TEST2::Run, &tc, str, v));
}
///////////////////////////////////////////////////////////

class Info : public MessageData
{
	Info(std::string str, int v)
		:m_str(str),
		 m_v(v)
	{

	}
private:
	std::string m_str;
	int m_v;
};

class TEST3 : public MessageHandler
{
public:
	TEST3()
	{
	}

	~TEST3()
	{
	}

	virtual void OnMessage(Message* msg)
	{
		printf("Thread OnMessage\n");
		sleep(1);
	}

	void InvokeRun(int a)
	{
		printf("Thread Invoke run:%d\n", a);
		sleep(1);
	}

private:

};

void test3()
{
	TEST3 tc;
	Thread th;
	th.Start();
	th.Post(&tc, 1);
	//th.Stop();

	/////////////////////////////////////////////
	//th.Start();
	AsyncInvoker invoker;
	int v = 666;
	invoker.AsyncInvoke<void>(&th, Bind(&TEST3::InvokeRun, &tc, v));
	invoker.AsyncInvoke<void>(&th, Bind(&TEST3::InvokeRun, &tc, v));
	invoker.AsyncInvoke<void>(&th, Bind(&TEST3::InvokeRun, &tc, v));
	invoker.AsyncInvoke<void>(&th, Bind(&TEST3::InvokeRun, &tc, v));
	usleep(5000000);

	/////////////////////////////////////////////
	Thread th1, th2, th3, th4;
	th1.Start();
	th2.Start();
	th3.Start();
	th4.Start();

	AsyncInvoker invoker1;
	int vv = 666;
	invoker1.AsyncInvoke<void>(&th1, Bind(&TEST3::InvokeRun, &tc, vv));
	invoker1.AsyncInvoke<void>(&th2, Bind(&TEST3::InvokeRun, &tc, vv));
	invoker1.AsyncInvoke<void>(&th3, Bind(&TEST3::InvokeRun, &tc, vv));
	invoker1.AsyncInvoke<void>(&th4, Bind(&TEST3::InvokeRun, &tc, vv));
	usleep(2000000);
}

int main()
{
	test1();
	test2();
	test3();
	return 0;
}
