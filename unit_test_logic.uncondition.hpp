// unit_test_logic.bool.hpp written by Jae Hyuk Kwak
#define STRINGFICATION2( s )	#s
#define STRINGFICATION( s )		STRINGFICATION2( s )
#define EXCEPTION_MSG			STRINGFICATION( TEST_UNCONDITION_VALUE )
#define EXCEPTION_NAME3( v )	test_exception_ ## v
#define EXCEPTION_NAME2( v )	EXCEPTION_NAME3( v )
#define EXCEPTION_NAME			EXCEPTION_NAME2( TEST_UNCONDITION_VALUE )
#define FUNC_NAME2( v )			test_ ## v
#define FUNC_NAME( v )			FUNC_NAME2( v )
template< typename... Args >
void FUNC_NAME( TEST_UNCONDITION_VALUE )( Args... args )
{
	if ( constexpr size_t nArgs = sizeof...( Args ) )
	{
		stringstream ss;
		using namespace implementation_ns;
		msg_r( ss, args... );
		throw EXCEPTION_NAME( ss.str() + ": unconditional " EXCEPTION_MSG );
	} else throw EXCEPTION_NAME( "unconditional " EXCEPTION_MSG );
}
#undef FUNC_NAME
#undef FUNC_NAME2
#undef STRINGFICATION
#undef STRINGFICATION2
