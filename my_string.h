
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

