#pragma once

#include <map>
#include <tchar.h>
#include <string>
#include "event.h"



template < typename ContextType >
class action_interface
{
public:
    virtual void exe( ContextType* context ) = 0;
};


template < typename ContextType >
class state_interface
{
    typedef ContextType context_t;
    typedef state_interface state_t;
    typedef action_interface< context_t > action_t;
    typedef std::map< event, state_t* > transition_map;
    typedef std::map< event, action_t* > action_map;
	typedef std::basic_string<TCHAR> tstring;

public:
    virtual void entry(){}
    virtual void exe(){}
    virtual void exit(){}

protected:
    context_t* context;
    state_t* parent;
    tstring name;	//デバッグ用
    transition_map transition;
    action_map action;

protected:
    state_interface( tstring const _name )
        : name( _name )
    {}

public:
    void set_parent( state_t* parent, context_t* context )
    {
        this->parent = parent;
        this->context = context;
    }

    state_interface* get_parent()const
    { return parent; }

public:
    void add_transition( event const& e, state_t* state )
    {
        transition.insert( std::make_pair( e, state ) );
    }

    bool transit( event const& e )
    {
        typename transition_map::iterator it = transition.find( e );
        if( it != transition.end() )
        {
            context->change_state( it->second, this );
            typename action_map::iterator it_action = action.find( e );
            if( it_action != action.end() )
                it_action->second->exe( context );
            return true;
        }
        return false;
    }

public:
    void add_action( event const& e, action_t* act )
    { action.insert( std::make_pair( e, act ) ); }
};

