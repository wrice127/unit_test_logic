// unit_test_logic.fixture.hpp written by JaeHyuk Kwak
class fixture
{
	typedef function< void() > Fn;
	const Fn setup_, tearDown_;
	uint64_t total_, succeed_;
public:
	fixture( Fn setup, Fn tearDown )
		: setup_( setup ), tearDown_( tearDown )
		, total_( 0 ), succeed_( 0 )
	{}
	fixture() : fixture( []{}, []{} )
	{}

	void test_case( const char *msg, Fn testFunc )
	{
		++total_;
		cout << "Test begin: " << msg << endl;
		if ( try_func( setup_ ) )
		{
			const bool passed = try_func( testFunc );
			if ( try_func( tearDown_ ) )
			{
				if ( passed )
				{
					++succeed_;
					cout << "Test passed." << endl;
				}
			} else cerr << "tearDown failed." << endl;
		} else cerr << "setup failed." << endl;
	}
	void test_case_must_fail( const char *msg, Fn testFunc )
	{
		++total_;
		cout << "Test begin, expected to fail: " << msg << endl;
		if ( try_func( setup_ ) )
		{
			const bool passed = try_func( testFunc );
			if ( try_func( tearDown_ ) )
			{
				if ( passed )
				{
					cout << "Test didn't fail." << endl;
				} else
				{
					 ++succeed_;
					cout << "Test failed as expected." << endl;
				}
			} else cerr << "tearDown failed unexpectedly." << endl;
		} else cerr << "setup failed unexpectedly." << endl;
	}

	uint64_t failed_count() const
	{
		return total_ - succeed_;
	}

private:
	static bool try_func( Fn func )
	{
		try { func(); }
		catch( const test_exception_success &e )
		{
			cout << e.what() << endl;
		}
		catch( const test_exception &e )
		{
			cout << e.what() << endl;
			return false;
		}
		catch( ... )
		{
			cout << "Unexpected exception cought" << endl;
			throw;
		}
		return true;
	}
};
