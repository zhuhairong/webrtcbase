#include "webrtc/base/bytebuffer.h"
#include "webrtc/base/thread.h"
#include "webrtc/base/bind.h"
#include <stdio.h>
#include <unistd.h>

using namespace rtc;



void test1()
{
	ByteBuffer buf(ByteBuffer::ORDER_HOST);
	buf.WriteUInt32(32);
	buf.WriteUInt8(8);
	buf.WriteUInt24(10);
	buf.WriteBytes("abcd", 4);
	buf.WriteString("efg");



	uint32 val32 = 0;
	buf.ReadUInt32(&val32);
	printf("%u\n", val32);

	uint8 val8 = 0;
	buf.ReadUInt8(&val8);
	printf("%u\n", val8);

	uint32 val24 = 0;
	buf.ReadUInt24(&val24);
	printf("%u\n", val24);

	char buf_str[128];
	buf.ReadBytes(buf_str, 4);
	buf_str[4] = '\0';
	printf("%s\n", buf_str);

	std::string str;
	buf.ReadString(&str, 3);
	printf("%s\n", str.c_str());
}


class TEST2 : public Runnable
{
public:
	TEST2()
		:m_exit(0)
	{
		m_thr.Start(this);
		m_thw.Start(this);
	}

	virtual void Run(Thread* thread)
	{
		while(!m_exit)
		{
			if(thread == &m_thr)
			{
				char str[3];
				this->read(str, sizeof(str));
			}
			else if(thread == &m_thw)
			{
				char* str = "abcdef";
				this->write(str, strlen(str));
			}
		}

	}

	bool read(char* buf, int size)
	{
		if(m_bf.ReadBytes(buf, size))
		{
			printf("read\n");

		}
		return true;
	}

	bool write(char* buf, int size)
	{
		printf("write\n");
		m_bf.WriteBytes(buf, size);
		usleep(1000000);

		return true;
	}

	void stop()
	{
		m_exit = 1;
	}

private:
	ByteBuffer m_bf;
	int m_exit;
	Thread m_thw, m_thr;
};

void test2()
{
	TEST2 tt;
	usleep(5000000);
	tt.stop();

//	Thread th, thw;
//	th.Start();
//	thw.Start();
//	char* strw = "abcdefg";
//	char str[256];
//	th.Invoke<bool>(Bind(&TEST2::read, &tt, str, strlen(str)));
//	thw.Invoke<bool>(Bind(&TEST2::write, &tt, strw, strlen(strw)));
}

int main()
{
	test1();
	test2();

	return 0;
}
