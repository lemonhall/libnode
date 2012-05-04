// Copyright (c) 2012 Plenluno All rights reserved.

#include "libnode/event_emitter.h"
#include "libj/array_list.h"
#include "libj/null.h"

namespace libj {
namespace node {
namespace events {

class EventEmitterImpl : public EventEmitter {
 public:
    void on(Type<String>::Cptr event, Type<JsFunction>::Ptr listener) {
        addListener(event, listener);
    }
    
    void addListener(Type<String>::Cptr event, Type<JsFunction>::Ptr listener) {
        Type<JsArray>::Ptr a;
        Value v = listeners_->get(event);
        if (v.instanceOf(Type<Null>::id())) {
            a = JsArray::create();
            listeners_->put(event, a);
        } else {
            toPtr<JsArray>(v, &a);
        }
        a->add(listener);
    }
    
    void removeListener(Type<String>::Cptr event, Type<JsFunction>::Cptr listener) {
        // TODO: implement
    }
    
    void removeAllListeners() {
        listeners_->clear();
    }
    
    void removeAllListeners(Type<String>::Cptr event) {
        Value v = listeners_->get(event);
        if (!v.instanceOf(Type<Null>::id())) {
            Type<JsArray>::Ptr a;
            toPtr<JsArray>(v, &a);
            a->clear();
        }
    }
    
    void emit(Type<String>::Cptr event, Type<JsArray>::Cptr args) {
        Value v = listeners_->get(event);
        if (!v.instanceOf(Type<Null>::id())) {
            Type<JsArray>::Ptr a;
            toPtr<JsArray>(v, &a);
            Size n = a->size();
            for (Size i = 0; i < n; i++) {
                Value v = a->get(i);
                Type<JsFunction>::Ptr f;
                toPtr<JsFunction>(v, &f);
                (*f)(args);
            }
        }
    }
    
    Value listeners(Type<String>::Cptr event) {
        return listeners_->get(event);
    }

    Type<String>::Cptr toString() const {
           return listeners_->toString();
    }

    static Ptr create() {
        Ptr p(new EventEmitterImpl());
        return p;
    }

 private:
     Type<JsObject>::Ptr listeners_;
    
    EventEmitterImpl()
        : listeners_(JsObject::create()) {}
    
    LIBNODE_JS_OBJECT_IMPL(listeners_);
};

Type<EventEmitter>::Ptr EventEmitter::create() {
    return EventEmitterImpl::create();
}

}  // namespace events
}  // namespace node
}  // namespace libj
