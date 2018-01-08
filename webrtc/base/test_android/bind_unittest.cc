#include "webrtc/base/bind.h"
#include "webrtc/base/callback.h"
#include <stdio.h>
using namespace rtc;

void f() {printf("f\n");}
int g() { printf("g\n");return 42; }
int h(int x) { printf("h\n");return x * x; }
void i(int& x) { printf("i\n");x *= x; }  // NOLINT: Testing refs

struct BindTester {
  int a() { return 24; }
  int b(int x) const { return x * x; }
};


int main()
{
	{
		printf("------------------- 1\n");
		Callback0<void> cb;
		cb();

		cb = Callback0<void>(&f);
		cb();
	}
	{
		printf("------------------- 2\n");
		Callback0<int> cb;
		cb();

		cb = Callback0<int>(&g);
		printf("%d\n", cb());
		printf("%d\n", cb());
	}
	{
		printf("------------------- 3\n");
		Callback1<int, int> cb1;
		cb1(1);

		cb1 = Callback1<int, int>(&h);
		printf("%d\n", cb1(-3));
		printf("%d\n", cb1(10));
	}
	{
		printf("------------------- 4\n");
		Callback1<void, int&> cb1(&i);
		int x = 3;
		cb1(x);
		printf("%d\n", x);
		cb1(x);
		printf("%d\n", x);
	}
	{
		printf("------------------- 5\n");
		BindTester t;
		Callback0<int> cb1 = Bind(&BindTester::a, &t);
		printf("%d\n", cb1());
		printf("%d\n", cb1());

		int x = 10;
		cb1 = Bind(&BindTester::b, &t, x);
		printf("%d\n", cb1());
		x = 5;
		printf("%d\n", cb1()); // 100 not 25

		cb1 = Bind(&BindTester::b, &t, x);
		printf("%d\n", cb1());
	}

	return 0;
}
