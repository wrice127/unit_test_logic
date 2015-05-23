// unit_test_logic.hpp written by Jae Hyuk Kwak
namespace unit_test_logic_ns
{
	using namespace std;

	namespace implementation_ns
	{
		#include "unit_test_logic.test_exception.hpp"
		#include "unit_test_logic.logic_stream.hpp"
		#include "unit_test_logic.test.hpp"
	}
	using namespace implementation_ns;

	#include "unit_test_logic.fixture.hpp"

	template< typename Type >
	const logic_stream< Type > logic( Type &&in )
	{
		logic_stream_static_type_check< Type >();
		return logic_stream< Type >( forward< Type >( in ), true, "" );
	}

	// This macro include could be replaced with template base function.
	// But it wasn't any easier to read.
	#define OPERATOR_SYMBOL ==
	#include "unit_test_logic.compare.hpp"
	#undef OPERATOR_SYMBOL

	#define OPERATOR_SYMBOL !=
	#include "unit_test_logic.compare.hpp"
	#undef OPERATOR_SYMBOL

	#define OPERATOR_SYMBOL >
	#include "unit_test_logic.compare.hpp"
	#undef OPERATOR_SYMBOL

	#define OPERATOR_SYMBOL >=
	#include "unit_test_logic.compare.hpp"
	#undef OPERATOR_SYMBOL

	#define OPERATOR_SYMBOL <
	#include "unit_test_logic.compare.hpp"
	#undef OPERATOR_SYMBOL

	#define OPERATOR_SYMBOL <=
	#include "unit_test_logic.compare.hpp"
	#undef OPERATOR_SYMBOL

	template< typename Type, typename... Args >
	void test( const logic_stream< Type > &&in, Args... args )
	{
		if ( in.out() ) return;

		if ( constexpr size_t nArgs = sizeof...( Args ) )
		{
			stringstream ss;
			using namespace implementation_ns;
			msg_r( ss, args... );
			throw test_exception_fail( ss.str() + ": " + in.msg() );
		} else throw test_exception_fail( in.msg() );
	}

	template< typename... Args >
	void test_must_throw_exception( function< void() > func )
	{
		using namespace implementation_ns;
		if ( test_must_throw_exception_r< Args... >( func ) )
			return;
		throw test_exception_fail( "Expected expection is not thrown" );
	}

	template< typename... Args >
	void test_ignore_exception( function< void() > func )
	{
		using namespace implementation_ns;
		test_ignore_exception_r< Args... >( func );
	}

	#define TEST_BOOL_VALUE true
	#include "unit_test_logic.bool.hpp"
	#undef TEST_BOOL_VALUE

	#define TEST_BOOL_VALUE false
	#include "unit_test_logic.bool.hpp"
	#undef TEST_BOOL_VALUE

	#define TEST_UNCONDITION_VALUE fail
	#include "unit_test_logic.uncondition.hpp"
	#undef TEST_UNCONDITION_VALUE

	#define TEST_UNCONDITION_VALUE success
	#include "unit_test_logic.uncondition.hpp"
	#undef TEST_UNCONDITION_VALUE

	string lowercase_string( string in )
	{
		transform( in.begin(), in.end(), in.begin(), (int(*)(int)) tolower );
		return in;
	}

	namespace implementation_ns
	{
		template< typename FunctionType >
		class function_stream
		{
			typedef result_of< FunctionType > ReturnType;
			function< FunctionType > func_;
			ReturnType out_;
		public:
			function_stream( function< FunctionType > func )
				: func_( func )
			{}
			const ReturnType out() const { return out_; }
		};
	}

	
	// perfect forwarding
	//template< typename Function, typename... Args >
	//const function_stream< FunctionType > call( Function&& f, Args&&... args )
	//{
		// not yet implemented
	//}
}

#include "unit_test_logic.macro.hpp"
