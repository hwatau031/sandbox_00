#pragma once

class event
{
private:
    int value;

public:
    event( int value )
        : value( value )
    {}

    bool operator==( event const& e )const
    { return value == e.value; }
    bool operator<( event const& e )const
    { return value < e.value; }
};

