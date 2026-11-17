#include "dart.h"
#include "characters/character.h"
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node2d.hpp>


Dart::Dart() {
    kill_area = nullptr;
    speed = 390.0;
    direction = godot::Vector2(-1.0, 0.0);
    lifetime = 5.0; // Se destruye tras 5 segundos si no impacta
    elapsed_time = 0.0;
    
    set_process(true);
}

Dart::~Dart() {}

void Dart::_bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("_on_body_entered", "body"), &Dart::_on_body_entered);
    
    godot::ClassDB::bind_method(godot::D_METHOD("set_direction", "dir"), &Dart::set_direction);
    godot::ClassDB::bind_method(godot::D_METHOD("get_direction"), &Dart::get_direction);
    godot::ClassDB::add_property("Dart", godot::PropertyInfo(godot::Variant::VECTOR2, "direction"), "set_direction", "get_direction");
    
    godot::ClassDB::bind_method(godot::D_METHOD("set_speed", "spd"), &Dart::set_speed);
    godot::ClassDB::bind_method(godot::D_METHOD("get_speed"), &Dart::get_speed);
    godot::ClassDB::add_property("Dart", godot::PropertyInfo(godot::Variant::FLOAT, "speed"), "set_speed", "get_speed");
}

void Dart::_ready() {
    Trap::_ready();
    kill_area = godot::Object::cast_to<godot::Area2D>(get_node_or_null("Area2D"));
    if (kill_area) {
        kill_area->connect("body_entered", godot::Callable(this, "_on_body_entered"));
    }
}

void Dart::_process(double delta) {
    if (godot::Engine::get_singleton()->is_editor_hint()) return;
    if (!is_active) return;

    elapsed_time += delta;
    if (elapsed_time >= lifetime) {
        queue_free(); // Autodestrucción por tiempo de vida
        return;
    }

    godot::Vector2 current_pos = get_position();
    current_pos += direction * speed * delta;
    set_position(current_pos);
}

void Dart::trigger_effect() {}

void Dart::_on_body_entered(Node2D *body) {
    if (is_active && body && body->is_in_group("player")) {
        ::Character *character = godot::Object::cast_to<::Character>(body);
        if (character) {
            character->respawn();
        }
        queue_free(); // El dardo desaparece al impactar al jugador
    }
}

void Dart::reset_trap() {
    // Los dardos instanciados se eliminan del mundo al reiniciar la escena
    queue_free();
}

void Dart::set_direction(godot::Vector2 dir) {
    direction = dir.normalized();
}

godot::Vector2 Dart::get_direction() const {
    return direction;
}

void Dart::set_speed(double spd) {
    speed = spd;
}

double Dart::get_speed() const {
    return speed;
}