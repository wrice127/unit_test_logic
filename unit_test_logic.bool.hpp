// unit_test_logic.bool.hpp written by Jae Hyuk Kwak
#define STRINGFICATION2( s ) #s
#define STRINGFICATION( s ) STRINGFICATION2( s )
#define FUNC_NAME2( v )		test_ ## v
#define FUNC_NAME( v )		FUNC_NAME2( v )
template< typename... Args >
void FUNC_NAME( TEST_BOOL_VALUE )( bool in, Args... args )
{
	if ( TEST_BOOL_VALUE == in ) return;

	if ( constexpr size_t nArgs = sizeof...( Args ) )
	{
		stringstream ss;
		using namespace implementation_ns;
		msg_r( ss, args... );
		throw test_exception_fail( ss.str() + ": expected " STRINGFICATION( TEST_BOOL_VALUE ) );
	} else throw test_exception_fail( "expected " STRINGFICATION( TEST_BOOL_VALUE ) );
}
#undef FUNC_NAME
#undef FUNC_NAME2
#undef STRINGFICATION
#undef STRINGFICATION2
