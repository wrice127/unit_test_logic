// unit_test_logic.test.hpp written by JaeHyuk Kwak
void msg_r( stringstream &ss )
{}

template< typename First, typename... Args >
void msg_r( stringstream &ss, First first, Args... args )
{
	ss << first;
	msg_r( ss, args... );
}

template< typename ExceptionType >
bool test_must_throw_exception_r( function< void() > func )
{
	try { func(); }
	catch ( ExceptionType &e ) { return true; }
	catch ( ... ) { throw; }
	return false;
}

template< typename ExceptionType1, typename ExceptionType2, typename... Args >
bool test_must_throw_exception_r( function< void() > func )
{
	try
	{
		return test_must_throw_exception_r< ExceptionType2, Args... >( func );
	}
	catch ( ExceptionType1 &e ) { return true; }
	catch ( ... ) { throw; }
	return false;
}

template< typename ExceptionType >
void test_ignore_exception_r( function< void() > func )
{
	try { func(); }
	catch ( ExceptionType &e ) { return; }
	catch ( ... ) { throw; }
}

template< typename ExceptionType1, typename ExceptionType2, typename... Args >
void test_ignore_exception_r( function< void() > func )
{
	try { test_ignore_exception_r< ExceptionType2, Args... >( func ); }
	catch ( ExceptionType1 &e ) { return; }
	catch ( ... ) { throw; }
}
