#include <Windows.h>
#include <string>

using namespace std;

void PlayMP3(const string& name) {
    mciSendString(TEXT("close mp3"), NULL, 0, NULL);
    string str = "open \"data\\sounds\\" + name + ".mp3\" type mpegvideo alias mp3";
    wstring temp = wstring(str.begin(), str.end());
    LPCWSTR wideString = temp.c_str();
	mciSendString(wideString, NULL, 0, NULL);
	mciSendString(TEXT("play mp3 from 0"), NULL, 0, NULL);
}