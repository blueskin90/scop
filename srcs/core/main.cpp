#include "scop.hpp"

int		usage(void)
{
	std::cout << "usage: ./scop obj_file" << std::endl;
	return (1);
}

int		main(int ac, char **av)
{
	Obj	*myObj;

	if (ac != 2)
		return (usage());
	try	{
		myObj = new Obj(av[1]);
	}
	catch (std::exception* &e){
		std::cout << "The problem was: " << e->what() << std::endl;
	}

	Vector test;
	Vector test2(10, 5, -3.5);

	test[2] = 2;
	test.y = 10;
	test.x = 1;

	std::cout << test << std::endl;
	std::cout << test2 << std::endl;
	std::cout << test2 + test << std::endl;
	std::cout << test2 - test << std::endl;
	std::cout << test2 << std::endl;
	test2 -= test;
	std::cout << test2 << std::endl;
	test2 = test;
	std::cout << test2.norm() << std::endl;
	std::cout << test2.normalize() << std::endl;
	std::cout << test2.norm() << std::endl;

	delete myObj;
	return (0);
}
