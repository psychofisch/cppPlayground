#include <iostream>
#include <limits>

struct MyClass {
	int* data;
	MyClass() { 
		data = new int[10000];
		std::cout << "constructed [" << this << "]\n"; 
	}

	~MyClass() { 
		delete[] data;
		std::cout << "destructed  [" << this << "]\n"; 
	}

	void* operator new(size_t s)
	{
		std::cout << "CLASS NEW\n";
		return ::operator new(s);
	}

	void* operator new(size_t s, void* where)
	{
		std::cout << "CLASS PLACEMENT NEW\n";
		return ::operator new(s, where);
	}
};

struct largeString
{
	char str[1048576];
};

int main(int argc, char **argv)
{
	if (argc <= 1)
	{
		std::cout << "no test specified...exiting\n";
	}

	// max RAM allocation
	else if (strcmp(argv[1], "ram") == 0)
	{
		largeString* largeArray = new largeString[15300];

		largeArray[512].str[0] = 'l';

		std::cin.ignore();

		delete[] largeArray;
	}
	// *** mra

	// instance construction and destruction
	else if (strcmp(argv[1], "icd") == 0)
	{
		MyClass * p1 = new MyClass;

		std::cin.ignore();
		p1->~MyClass();

		std::cin.ignore();
		new (p1) MyClass;

		p1->~MyClass();

		std::cin.ignore();
		::operator new(sizeof(MyClass), p1);

		// Notice though that calling this function directly does not construct an object:
		//MyClass * p2 = (MyClass*) ::operator new (sizeof(MyClass));
		// allocates memory by calling: operator new (sizeof(MyClass))
		// but does not call MyClass's constructor

		std::cin.ignore();
		delete p1;
		//delete p2;
	}
	// *** icad

	// data type sizes
	else if (strcmp(argv[1], "dts") == 0)
	{
		int a;
		long b;
		long int c;
		long long d;
		long long int e;
		double f;
		long double g;

		std::cout << sizeof(a) << std::endl;
		std::cout << sizeof(b) << std::endl;
		std::cout << sizeof(c) << std::endl;
		std::cout << sizeof(d) << std::endl;
		std::cout << sizeof(e) << std::endl;
		std::cout << sizeof(f) << std::endl;
		std::cout << sizeof(g) << std::endl;

		std::cout << INT_MAX << std::endl;
		std::cout << LONG_MAX << std::endl;
		std::cout << INT64_MAX << std::endl;
		std::cout << UINT64_MAX << std::endl;
		std::cout << HUGE_VAL << std::endl;
		std::cout << HUGE_VALF << std::endl;
	}
	// *** dts

	// memory access tests
	else if (strcmp(argv[1], "mat") == 0)
	{
		char* memory = new char[4];
		float* p = new(memory) float();
		*p = 66.6f;
		unsigned int data = 0xDEADBEEF;
		memcpy(memory, &data, 4);
	}
	// *** mat

	// References and Pointers
	else if (strcmp(argv[1], "ref") == 0)
	{
		int i = 666;
		int *iP;
		{
			int& iR = i;
			iP = &iR;
		}
		std::cout << iP << std::endl;
		// *** rp

		// unsigned signed tests
		unsigned int test;

		while (1)
		{
			std::cout << "Enter new int pls: ";
			std::cin >> test;
			test = UINT_MAX;
			std::cout << "uint -> " << test << std::endl;

			int testu = test;
			std::cout << "int=uint -> " << testu << std::endl;

			testu = static_cast<int>(test);
			std::cout << "int=static_cast -> " << testu << std::endl;

			testu = int(test);
			std::cout << "int=() -> " << testu << std::endl;
		}
	}
	// *** ust

	std::cin.ignore();
	return 0;
}
