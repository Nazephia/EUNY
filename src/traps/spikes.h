#pragma once

#include "trap.h"
#include <godot_cpp/classes/area2d.hpp>

class Spikes : public Trap {
    GDCLASS(Spikes, Trap);

protected:
    static void _bind_methods();
    
    godot::Area2D *kill_area;

public:
    Spikes();
    ~Spikes();

    void _ready() override;
    
    void trigger_effect() override; 
    virtual void _on_body_entered(Node2D *body);
};