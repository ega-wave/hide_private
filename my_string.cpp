
#include "my_string.h"
#include <string>
#include <iostream>

my_string::my_string(const char* str)
{
	new (member_) std::string(str);
}

my_string::operator const char* () const
{
	const std::string* p =
		reinterpret_cast<const std::string*>(&member_[0]);
	return p->c_str();
}

int main()
{
	my_string str("Hello, World!");
	std::cout << str << std::endl;
	return 0;
}

