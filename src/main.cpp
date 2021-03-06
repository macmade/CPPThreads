/*******************************************************************************
 * Copyright (c) 2012, Jean-David Gadina - www.xs-labs.com
 * Distributed under the Boost Software License, Version 1.0.
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************/

/* $Id$ */

/*!
 * @file            main.cpp
 * @author          Jean-David Gadina - www.xs-labs.com
 * @copyright       (c) 2012, XSLabs
 */

#include <iostream>
#include <unistd.h>
#include "Object.h"
#include "Thread.h"
#include "Lock.h"

class Foo: public EOS::Object
{
    public:
    
        Foo( void );
        void test( EOS::Thread * thread );
        
    protected:
        
        EOS::Lock _lock;
};

Foo::Foo( void )
{}

void Foo::test( EOS::Thread * thread )
{
    std::vector< void * >           args;
    std::vector< void * >::iterator i;
    
    _lock.lock();
    
    std::cout << "OK from thread..." << std::endl << "This: " << this << std::endl;
    
    args = thread->arguments();
    
    for( i = args.begin(); i != args.end(); ++i )
    {
        std::cout << *( i ) << std::endl;
    }
    
    _lock.unlock();
}

int main( void )
{
    Foo                   f;
    std::vector< void * > args;
    
    args.push_back( &f );
    
    DetachThread( Foo::test, &f );
    DetachThread( Foo::test, &f, args );
    
    sleep( 1 );
    
    return 0;
}
