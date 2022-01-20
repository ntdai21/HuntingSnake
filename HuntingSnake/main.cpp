#include "graphic.h"
#include <conio.h>

using namespace std;

int main() {
	FixConsole();
	cout << "12345678901234567890\n";
	cout << CenterAlign((string)"Can giua 12345", 20) << endl;
	system("pause");
	return 0;
	
}