// test_4.cpp written by JaeHyuk Kwak
#include "stdafx.h"
#include "unit_test_logic.hpp"
int main( int, const char ** )
{
	using namespace unit_test_logic_ns;
	fixture f;

	const float point_two = 0.2f;
	f.test_case( "Float compare with error; bool", [&]
	{
		TEST_TRUE( point_two != 0.2 );
		TEST_TRUE( point_two != 0.2 + 0.00_value_error );
		TEST_TRUE( point_two == 0.2 + 0.01_value_error );
		TEST_TRUE( point_two == 0.2 * 0.01_value_error );
	} );
	f.test_case( "Float compare with error; logic", [&]
	{
		TEST( logic( point_two ) != 0.2 );
		TEST( logic( point_two ) != 0.2 + 0.00_value_error );
		TEST( logic( point_two ) == 0.2 + 0.01_value_error );
		TEST( logic( point_two ) == 0.2 * 0.01_value_error );
	} );

	return f.failed_count();
}
