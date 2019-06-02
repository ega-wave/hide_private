# Hide Private! - A challenge to hide private members completely.

It is said that "C++ is known as object-oriented-programming-language,
but it fails to hide private implementations".

Right. 
A C++ Class have private implementations if any,
and they should be written apparently,
regardless of whether you need to know.

A C++ class "my_string" may use one of the following classes.
- array of char
- std::string
- std::vector<char>
- ...

Programmers who use my_string class does not need to know about
what classes it uses.

```C++
class my_string
{
private:
	std::string str_;	// no need to know for user
};
```

There are many reason why.
One of the reason is that "the size of a class" is needed when compiling.

Are there any way to hide private implementations completely?
Yes, there is.
I will show you the way.

I hope you will find out that C++ is a great language.

## 1. Create "*_dummy.h" file
Write class-declaration as usual, but you'd better save as "*_dummy.h".
Only stuff you need to write is private members (and base classes if any).

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

CAUTION:

It is UNPORTABLE code!
You may have trouble during compiling or executing.
Please be careful! and Happy Hacking!

