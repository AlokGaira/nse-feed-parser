//
// Created by alok on 26/11/18.
//

#ifndef LEARN_REDIS_H
#define LEARN_REDIS_H

#include "iostream"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "../third_party/hiredis/hiredis.h"
#include "../third_party/hiredis/read.h"

#include <boost/log/trivial.hpp>

#define CHECK(X) if ( !X || X->type == REDIS_REPLY_ERROR ) { printf("Error\n"); exit(-1); }


struct Redis_Data {
    std::string key;
    std::string value;
};

class Redis {
    /* Put event loop in the global scope, so it can be explicitly stopped */
    redisContext *redis_context;
    redisReply *redis_reply;
    std::string hostname;
    unsigned port;

    struct timeval timeout = {1, 500000}; // 1.5 seconds
public:
    Redis(const std::string hostname, unsigned int port) : hostname(hostname), port(port) {
        connect();
    }

private:

    void connect() {
        redis_context = redisConnectWithTimeout(hostname.c_str(), port, timeout);
        if (redis_context == NULL || redis_context->err) {
            if (redis_context) {
                BOOST_LOG_TRIVIAL(error) << "Connection error: " << redis_context->errstr << std::endl;
                redisFree(redis_context);
            } else {
                BOOST_LOG_TRIVIAL(error) << "Connection error: can't allocate redis context" << std::endl;
            }
            exit(1);
        }

    }

    void handle_error() {
        BOOST_LOG_TRIVIAL(error) << "Connection error: " << redis_context->errstr << std::endl;
        BOOST_LOG_TRIVIAL(error) << "Trying To Reconnect" << std::endl;
        connect();
    }

    void set(std::string *key, std::string *value) {
        redis_reply = (redisReply *) redisCommand(redis_context, "SET %s %s", "foo", "hello world");
        if (!redis_reply) {
            handle_error();
        }
        printf("SET: %s\n", redis_reply->str);
        freeReplyObject(redis_reply);
    }

    void m_set(std::vector<std::string> key_value) {
        std::string cmd = "MSET ";
        for (auto it = key_value.cbegin(); it != key_value.cend(); ++it) {
            cmd.append("%b ");
        }
        redis_reply = (redisReply *) redisCommand(redis_context, cmd.c_str(), key_value);
        if (!redis_reply) {
            handle_error();
        }
    }

    /**
     * https://gist.github.com/dspezia/1893378
     */
    void r_push(std::vector<std::string> key_value) {
        redisReply *redis_reply;
        unsigned int count = 0;

        for (auto it = key_value.cbegin(); it != key_value.cend();) {
            int cmd = 0;
            redisAppendCommand(redis_context, "RPUSH %d %d", *it++, *it++);
            ++count;
        }

        while (count-- > 0) {
            int r = redisGetReply(redis_context, (void **) &redis_reply);
            if (r == REDIS_ERR) {
                printf("Error\n");
                exit(-1);
            }
            CHECK(redis_reply);
            freeReplyObject(redis_reply);
        }
    }
};


#endif //LEARN_REDIS_H
