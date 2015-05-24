// unit_test_logic.bool.hpp written by Jae Hyuk Kwak
#define STRINGFICATION2( s )	#s
#define STRINGFICATION( s )		STRINGFICATION2( s )
#define EXCEPTION_MSG			STRINGFICATION( TEST_UNCONDITION_VALUE )
#define EXCEPTION_NAME3( v )	test_exception_ ## v
#define EXCEPTION_NAME2( v )	EXCEPTION_NAME3( v )
#define EXCEPTION_NAME			EXCEPTION_NAME2( TEST_UNCONDITION_VALUE )
if ( constexpr size_t nArgs = sizeof...( Args ) )
{
	stringstream ss;
	using namespace implementation_ns;
	msg_r( ss, args... );
	throw EXCEPTION_NAME( ss.str() + ": unconditional " EXCEPTION_MSG );
} else throw EXCEPTION_NAME( "unconditional " EXCEPTION_MSG );
#undef STRINGFICATION
#undef STRINGFICATION2
