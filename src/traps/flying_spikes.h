#pragma once

#include "spikes.h"
#include <godot_cpp/classes/marker2d.hpp>
#include <godot_cpp/classes/ray_cast2d.hpp>
#include <godot_cpp/variant/vector2.hpp>

class FlyingSpikes : public Spikes {
    GDCLASS(FlyingSpikes, Spikes);

protected:
    static void _bind_methods();

    godot::RayCast2D *direction_ray;
    godot::Marker2D *direction_marker;
    godot::Vector2 direction;
    godot::Vector2 destination;
    double speed;
    bool launched;
    bool reached_destination;

public:
    FlyingSpikes();
    ~FlyingSpikes();

    void _ready() override;
    void _process(double delta) override;
    void reset_trap() override;
    void _on_body_entered(godot::Node2D *body) override;
};
