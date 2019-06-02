# hide_private
The challenge to hide private members completely.

1. Create dummy.h file
Write class-declaration as usual, but you'd better save as "*_dummy.h".
Only you need to write is private members (and base class if any).

```C++
$ cat my_string_dummy.h

#include <string>

class my_string_dummy
{
private:
	std::string str_;
};
```

2. Generate "*_size.dat"
You can generate "*_size.dat" by following bash function.

size_gen () {
	local my_class=$1
	sed "s/CLASS/${my_class}/" size_gen.cpp	|
	g++ -xc++ - && ./a.out > ${my_class}_size.dat && rm ./a.out
}
size_gen my_string

3. Write class-declaration as usual, except but private members

$ cat my_string.h

typedef char int8_t;

class my_string
{
public:
	my_string(const char* str);
	operator const char* () const;
private:
	int8_t member_[
#include "my_string_size.dat"
];
};

4. Write class-implementation.

$ cat my_string.cpp

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

6. That's it.

$ g++ my_string.cpp && ./a.out
Hello, World!

This program runs as you expected if you are lucky.
It is not portable.

Happy Hacking!

