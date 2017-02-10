/***********************************************************************
	INCLUDES
***********************************************************************/
#include <gtest/gtest.h>

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

/***********************************************************************
	GLOBAL VARIABLES
***********************************************************************/

/***********************************************************************
	LOCAL FUNCTIONS
***********************************************************************/
TEST(common_checks, sanity_check_1)
{
    ASSERT_TRUE(true);	// We certainly hope that true is true
    EXPECT_EQ(2,1+1);	// The value 1+1 should equal 2
}

TEST(common_checks, sanity_check_2)
{
    ASSERT_FALSE(false);	// We certainly hope that true is true
}

/***********************************************************************
	EXPORTED FUNCTIONS
***********************************************************************/

/***********************************************************************
	END OF NAMESPACE
***********************************************************************/