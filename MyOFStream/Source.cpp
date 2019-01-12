#include "ofstream.h"
#include <iostream>

void printtf(stf::MyOFStream & file2, char* k, int i)
{
	std::string text = "Trapped in my own head.";
	double z = 266347.2332424;
	bool s = 2;

	file2 << text << stf::endl;
	file2 << i << stf::endl;

	file2.setf(stf::hex);
	file2 << i << stf::endl;

	file2 << stf::bin << i << stf::endl;

	file2.unsetf();
	file2 << i << stf::endl;

	file2.setf(stf::oct);
	file2 << i << stf::endl;

	file2.unsetf();
	file2 << i << stf::endl;

	file2 << s << stf::endl;
	file2 << z << stf::endl << k;
}

int main()
{
	char k[] = "testMyFile.txt";
	int i = 10408080;
	stf::MyOFStream file1;
	
	file1.open("text.txt");
	file1 << '1';
	file1 << "Hello World!" << stf::endl;
	file1 << k << stf::endl;
	file1 ? std::cout << "open" << std::endl : std::cout << "not open" << std::endl;
	file1.close();

	stf::MyOFStream file2(k);
	printtf(file2, k, i);
	file2.close();
	file2 ? std::cout << "open" << std::endl : std::cout << "not open" << std::endl;

	file2.open(k, stf::add);
	file2 << stf::endl << "It Never Ends!";
	file2 ? std::cout << "open" << std::endl : std::cout << "not open" << std::endl;

	stf::MyOFStream file3;
	file3.open("text.txt", stf::add);
	file3 << "Sometime it ends" << stf::endl << "This is smth new for me!" << stf::endl;
	file3 << stf::endl;
	file3 ? std::cout << "open" << std::endl : std::cout << "not open" << std::endl;

	getchar();
	return 0;
}