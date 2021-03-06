// Copyright (c) 2012-2013 Plenluno All rights reserved.

#include <libnode/trace.h>
#include <libnode/detail/http/agent.h>
#include <libnode/detail/http/incoming_message_list.h>
#include <libnode/detail/http/outgoing_message_list.h>

#include <libj/detail/gc_collect.h>

#include "./gtest_common.h"

int main(int argc, char** argv) {
    LIBNODE_DEBUG_TRACE_ON;

    testing::InitGoogleTest(&argc, argv);
    int r = RUN_ALL_TESTS();

#ifdef LIBNODE_DEBUG
    libj::node::detail::http::freeGlobalAgent();
    libj::node::detail::http::incomingMessageList()->clear();
    libj::node::detail::http::outgoingMessageList()->clear();
#endif

    LIBJ_GC_COLLECT;

    LIBJ_DEBUG_PRINT(
        "remaining objects: %d",
        LIBJ_DEBUG_OBJECT_COUNT);

    LIBNODE_DEBUG_TRACE_OFF;
    return r;
}
