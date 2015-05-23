// unit_test_logic.macro.hpp written by JaeHyuk Kwak
#if defined( __GNUC__ )

	#define TEST( in, args... )			unit_test_logic_ns::test(  in, __FILE__ "(", __LINE__, "): \"" #in "\": " , ##args )
	#define TEST_TRUE( in, args... )	unit_test_logic_ns::test_true(  in, __FILE__ "(", __LINE__, "): \"" #in "\": " , ##args )
	#define TEST_FALSE( in, args... )	unit_test_logic_ns::test_false( in, __FILE__ "(", __LINE__, "): \"" #in "\": ", ##args )
	#define TEST_SUCCESS()				unit_test_logic_ns::test_success( __FILE__ "(", __LINE__, ")" )
	#define TEST_FAIL()					unit_test_logic_ns::test_fail( __FILE__ "(", __LINE__, ")" )

#endif
