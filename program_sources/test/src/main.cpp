/***********************************************************************
	INCLUDES
***********************************************************************/
#include <gtest/gtest.h>
#include <getopt.h>
#include <iostream>

/***********************************************************************
	DEFINITIONS AND MACROS
***********************************************************************/

/***********************************************************************
	NAMESPACE
***********************************************************************/

/***********************************************************************
	TYPEDEFS AND STRUCTURES
***********************************************************************/

/***********************************************************************
	PROTOTYPES OF LOCAL FUNCTIONS
***********************************************************************/
int main(int argc, char* argv[]);

/***********************************************************************
	GLOBAL VARIABLES
***********************************************************************/

/***********************************************************************
	LOCAL FUNCTIONS
***********************************************************************/
static void show_usage(std::string name)
{
    std::cerr << "Usage: " << name << " <option(s)>\n"
              << "Options:\n"
              << "\t-a,--arg\t\tSets an argument for this program\n"
              << "\t-v,--version\t\tPrints program version\n"
              << "\t-h,--help\t\tShow this help message\n"
              << std::endl;
}

int main(int argc, char* argv[])
{
	int ret;

	const struct option longopts[] =
	{
		{"arg",       required_argument,  0, 'a'},
		{"version",   no_argument,        0, 'v'},
		{"help",      no_argument,        0, 'h'},
		{0,0,0,0},
	};


	int index;
	int iarg=0;

	//turn off getopt error message
	opterr=1; 

	while(iarg != -1)
	{
		iarg = getopt_long(argc, argv, "a:vh", longopts, &index);

		switch (iarg)
		{
			case 'h':
			std::cout << "You hit help" << std::endl;
			show_usage(argv[0]);
			break;

			case 'v':
			std::cout << "You hit version" << std::endl;
			break;

			case 'a':
			std::cout << "You hit arguments" << " and argument is " << optarg << std::endl;
			break;

			default:
			show_usage(argv[0]);
			return 0;
			break;
		}
	}

	::testing::InitGoogleTest(&argc, argv);

	::testing::GTEST_FLAG(repeat) = 2;
	::testing::GTEST_FLAG(filter) = "sanity_check:*";
	::testing::GTEST_FLAG(shuffle) = true;

	ret = RUN_ALL_TESTS();
	// Can be run again with different filters and iterations

	return ret;
}

/***********************************************************************
	EXPORTED FUNCTIONS
***********************************************************************/

/***********************************************************************
	END OF NAMESPACE
***********************************************************************/
