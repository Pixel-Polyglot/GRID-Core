#pragma once

class Widget {
public:
    virtual ~Widget() {};
    virtual void render() = 0;
};