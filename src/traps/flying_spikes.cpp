#include "flying_spikes.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

FlyingSpikes::FlyingSpikes() {
    direction_ray = nullptr;
    direction_marker = nullptr;
    direction = godot::Vector2(-1.0, 0.0);
    destination = godot::Vector2();
    speed = 400.0;
    launched = false;
    reached_destination = false;
    set_process(true);
}

FlyingSpikes::~FlyingSpikes() {}

void FlyingSpikes::_bind_methods() {}

void FlyingSpikes::_ready() {
    Spikes::_ready();
    if (godot::Engine::get_singleton()->is_editor_hint()) {
        return;
    }

    direction_ray = godot::Object::cast_to<godot::RayCast2D>(get_node_or_null("RayCast2D"));
    direction_marker = godot::Object::cast_to<godot::Marker2D>(get_node_or_null("Marker2D"));
    if (!direction_ray) {
        godot::UtilityFunctions::push_error("FlyingSpikes requires a RayCast2D child named RayCast2D.");
    }
    if (!direction_marker) {
        godot::UtilityFunctions::push_error("FlyingSpikes requires a Marker2D child named Marker2D.");
    }
}

void FlyingSpikes::_process(double delta) {
    if (godot::Engine::get_singleton()->is_editor_hint() || !is_active) {
        return;
    }

    if (!launched) {
        if (!direction_ray || !direction_marker) {
            return;
        }

        direction_ray->force_raycast_update();
        godot::Node *target = godot::Object::cast_to<godot::Node>(direction_ray->get_collider());
        if (!target || !target->is_in_group("player")) {
            return;
        }

        godot::Vector2 marker_direction = direction_marker->get_global_position() - get_global_position();
        if (marker_direction.is_zero_approx()) {
            godot::UtilityFunctions::push_error("FlyingSpikes Marker2D must be offset from the trap to set a flight direction.");
            return;
        }

        direction = marker_direction.normalized();
        destination = direction_marker->get_global_position();
        launched = true;
    }

    if (reached_destination) {
        return;
    }

    godot::Vector2 position = get_global_position();
    double distance_remaining = position.distance_to(destination);
    double distance_this_frame = speed * delta;
    if (distance_remaining <= distance_this_frame) {
        set_global_position(destination);
        reached_destination = true;
        return;
    }

    set_global_position(position + direction * distance_this_frame);
}

void FlyingSpikes::reset_trap() {
    Spikes::reset_trap();
    launched = false;
    reached_destination = false;
}

void FlyingSpikes::_on_body_entered(godot::Node2D *body) {
    Spikes::_on_body_entered(body);
    if (body && body->is_in_group("player")) {
        reset_trap();
    }
}
