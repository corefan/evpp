#pragma once

#include <map>
#include <vector>
#include <mutex>

#include "evpp/inner_pre.h"
#include "evpp/duration.h"
#include "evpp/event_loop.h"

namespace evpp {
    namespace httpc {
        class Conn;
        typedef std::shared_ptr<Conn> ConnPtr;
        class EVPP_EXPORT ConnPool {
        public:
            ConnPool(const std::string& host, int port, Duration timeout, size_t max_pool_size = 1024);

            ConnPtr Get(EventLoop* loop);
            void Put(const ConnPtr& c);

            const std::string& host() const { return host_; }
            int port() const { return port_; }
            Duration timeout() const { return timeout_; }
        private:
            std::string host_;
            int port_;
            Duration timeout_;
            size_t max_pool_size_; // The max size of the pool per EventLoop

            std::mutex mutex_; // The guard of pools_
            std::map<EventLoop*, std::vector<ConnPtr> > pools_; // TODO make sure Conn release in EventLoop
        };
    } // httpc
} // evpp