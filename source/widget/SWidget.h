#pragma once

#include <list>

class SWidget {
public:
    SWidget() = default;
    virtual ~SWidget() = default;

    virtual void handleChildEvent(SWidget* child) = 0;
    virtual void sendParentEvent() = 0;
protected:
    SWidget* parent_ = nullptr;
};
