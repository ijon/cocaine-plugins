/*
    Copyright (c) 2011-2012 Andrey Sibiryov <me@kobology.ru>
    Copyright (c) 2011-2012 Other contributors as noted in the AUTHORS file.

    This file is part of Cocaine.

    Cocaine is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    Cocaine is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>. 
*/

#ifndef COCAINE_DEALER_SERVER_EVENT_HPP
#define COCAINE_DEALER_SERVER_EVENT_HPP

#include <cocaine/io.hpp>

#include <cocaine/api/event.hpp>

namespace cocaine { namespace driver {

typedef std::vector<std::string> route_t;

typedef io::channel<
    struct dealer_tag,
    io::policies::unique
> rpc_channel_t;

class dealer_event_t:
    public engine::event_t
{
    public:
        dealer_event_t(const std::string& event,
                       const engine::policy_t& policy,
                       rpc_channel_t& channel,
                       const route_t& route,
                       const std::string& tag);

        virtual
        void
        on_chunk(const void * chunk,
                 size_t size);
        
        virtual
        void
        on_error(error_code code,
                 const std::string& message);
        
        virtual
        void
        on_close();

    private:
        template<class T>
        void
        send(const std::string& route,
             const T& message)
        {
            m_channel.send(route, ZMQ_SNDMORE);
            m_channel.send_message(message);
        }

    private:
        rpc_channel_t& m_channel;        
        
        const route_t m_route;
        const std::string m_tag;
};

}}

#endif