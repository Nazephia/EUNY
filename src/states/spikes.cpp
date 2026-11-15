#include "../traps/spikes.h"
#include "../characters/character.h"
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/area2d.hpp>

Spikes::Spikes() {
    kill_area = nullptr;
}

Spikes::~Spikes() {}

void Spikes::_bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("_on_body_entered", "body"), &Spikes::_on_body_entered);
}

void Spikes::_ready() {
    Trap::_ready();

    kill_area = godot::Object::cast_to<godot::Area2D>(get_node_or_null("Area2D"));
    if (kill_area) {
        kill_area->connect("body_entered", godot::Callable(this, "_on_body_entered"));
    }
}

void Spikes::trigger_effect() {
}

void Spikes::_on_body_entered(Node2D *body) {
    if (is_active && body && body->is_in_group("player")) {
        Character *character = Object::cast_to<Character>(body);
        if (character) {
            character->respawn();
        }
    }
}
