// unit_test_logic.test_exception.hpp written by JaeHyuk Kwak
class test_exception : public logic_error
{
public:
	test_exception( const string msg )
		: logic_error( msg )
	{}
};

class test_exception_fail : public test_exception
{
public:
	test_exception_fail( const string msg )
		: test_exception( msg )
	{}
};

class test_exception_success : public test_exception
{
public:
	test_exception_success( const string msg )
		: test_exception( msg )
	{}
};
