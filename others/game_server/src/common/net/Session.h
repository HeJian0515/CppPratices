#ifndef SESSION_H
#define SESSION_H

#pragma once

#include <memory>

namespace HGS {
    class Session : public std::enable_shared_from_this<Session>{
    public:
        explicit Session();

        virtual ~Session();
    };

}

#endif //SESSION_H
