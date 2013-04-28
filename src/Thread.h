/*******************************************************************************
 * Copyright (c) 2012, Jean-David Gadina <macmade@eosgarden.com>
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
 * @header          Thread.h
 * @author          Jean-David Gadina <macmade@eosgarden.com>
 * @copyright       (c) 2012, eosgarden
 */

#ifndef __EOS_THREAD_H__
#define __EOS_THREAD_H__

#include <string>
#include <vector>

#define DetachThread( __func__, ... ) EOS::Thread::detach( ( EOS::Thread::EntryPoint )&__func__, __VA_ARGS__ );

namespace EOS
{
    class Object;
    
    class Thread
    {
        public:
            
            typedef void ( Object::* EntryPoint )( Thread * thread );
            
            static bool detach( EntryPoint func, void * target );
            static bool detach( EntryPoint func, void * target, std::vector< void * > & arguments );
            
            unsigned int threadID( void ) const;
            const std::string & name( void ) const;
            void name( const std::string & name );
            const std::vector< void * > & arguments( void ) const;
            
        protected:
            
            Thread( void );
            ~Thread( void );
            
            static bool _detach( EntryPoint func, void * target, Thread * thread );
            
            void _threadID( unsigned int threadID );
            void _arguments( const std::vector< void * > & arguments );
            
            unsigned int _id;
            std::string _name;
            std::vector< void * > _args;
    };
}

#endif /* __EOS_THREAD_H__ */
