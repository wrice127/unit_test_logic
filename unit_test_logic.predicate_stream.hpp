template< typename... >
struct storage;

template< typename Type >
struct storage< Type >
{
	Type value;
	storage( Type v ) : value( v )
	{}
};

template< typename Type, typename... Rest >
struct storage< Type, Rest... > : storage< Rest... >
{
	Type value;
	storage( Type v, Rest... r )
		: storage< Rest... >( r... ), value( v )
	{}
};

template< typename... Args >
class predicate_stream
{
	const bool out_;
	const string msg_;
	const storage< Args... > args_;
public:
	predicate_stream( bool out, string msg, Args&&... args )
		: out_( out ), msg_( msg ), args_( args... )
	{}
	bool out() const { return out_; }
};
