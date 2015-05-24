// unit_test_logic.bool.hpp written by Jae Hyuk Kwak
#define STRINGFICATION2( s ) #s
#define STRINGFICATION( s ) STRINGFICATION2( s )
if ( TEST_BOOL_VALUE == in ) return;

if ( constexpr size_t nArgs = sizeof...( Args ) )
{
	stringstream ss;
	using namespace implementation_ns;
	msg_r( ss, args... );
	throw test_exception_fail( ss.str() + ": expected " STRINGFICATION( TEST_BOOL_VALUE ) );
} else throw test_exception_fail( "expected " STRINGFICATION( TEST_BOOL_VALUE ) );
#undef STRINGFICATION
#undef STRINGFICATION2
