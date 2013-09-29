#pragma once
#include <core/framework/IPlatform.h>

class SDLPlatformBase : public IPlatform
{
protected:
    SDLPlatformBase();
    virtual ~SDLPlatformBase();
    
public:
    virtual std::string get_window_title() override;
    virtual void set_window_title(std::string title) override;
    virtual milliseconds get_ticks() override;
    virtual void sleep_ticks(milliseconds) override;
    virtual void quit() override;
};