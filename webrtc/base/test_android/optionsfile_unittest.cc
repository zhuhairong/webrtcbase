#include <stdio.h>
#include "webrtc/base/optionsfile.h"
#include "webrtc/base/scoped_ptr.h"

using namespace rtc;


void test1()
{
	const std::string opts1 = "opts1";
	const std::string opts2 = "opts2";
	scoped_ptr<OptionsFile> store;
	store.reset(new OptionsFile("/mnt/sdcard/opt.txt"));
	store->SetStringValue(opts1, "str1");
	store->Save();

	store->Load();
	std::string out1;
	store->GetStringValue(opts1, &out1);
	printf("get %s : %s\n", opts1.c_str(), out1.c_str());

	store->RemoveValue(opts1);
	store->SetIntValue(opts2, 33);
	store->Save();

}

int main()
{
	test1();
	return 0;
}
