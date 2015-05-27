template< typename Type >
struct value_range
{
	const Type value_low;
	const Type value_high;
	value_range( Type l, Type h )
		: value_low( l ), value_high( h )
	{}
};


template< typename Type >
struct value_error
{
	const Type error;
	value_error( Type e )
		: error( e )
	{}
};
