# hide_private
The challenge to hide private members completely.

## 1. Create "*_dummy.h" file
Write class-declaration as usual, but you'd better save as "*_dummy.h".
Only you need to write is private members (and base classes if any).

```bash
$ cat my_string_dummy.h
```

```C++
#include <string>

class my_string_dummy
{
private:
	std::string str_;
};
```

## 2. Generate "*_size.dat" file
You can generate "*_size.dat" file with following bash function.

```bash
size_gen () {
	local my_class=$1
	sed "s/CLASS/${my_class}/" size_gen.cpp	|
	g++ -xc++ - && ./a.out > ${my_class}_size.dat && rm ./a.out
}
size_gen my_string
```

## 3. Write class-declaration as usual, except but private members

```bash
$ cat my_string.h
```

```C++
class my_string
{
public:
	my_string(const char* str);
	operator const char* () const;
private:
	char member_[
#include "my_string_size.dat"
];
};
```

## 4. Write class-implementation.

```bash
$ cat my_string.cpp
```

```C++
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
```

## 5. That's it.

```bash
$ g++ my_string.cpp && ./a.out
Hello, World!
```

If you are lucky, this program runs as you expected.
It is NOT PORTABLE!

Happy Hacking!

