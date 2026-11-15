#include "death_zone.h"
#include "../characters/character.h"

DeathZone::DeathZone() {}
DeathZone::~DeathZone() {}

void DeathZone::_bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("_on_body_entered", "body"), &DeathZone::_on_body_entered);
}

void DeathZone::_ready() {
    connect("body_entered", godot::Callable(this, "_on_body_entered"));
}

void DeathZone::_on_body_entered(Node2D *body) {
    if (body && body->is_in_group("player")) {
        Character *character = Object::cast_to<Character>(body);
        if (character) {
            character->respawn();
        }
    }
}