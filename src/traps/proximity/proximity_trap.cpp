#include "proximity_trap.h"
#include <godot_cpp/variant/utility_functions.hpp>


ProximityTrap::ProximityTrap() {
    detection_area = nullptr;
    activation_delay = 0.0;
}

ProximityTrap::~ProximityTrap() {}

void ProximityTrap::_bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("_on_body_entered", "body"), &ProximityTrap::_on_body_entered);

    godot::ClassDB::bind_method(godot::D_METHOD("set_activation_delay", "delay"), &ProximityTrap::set_activation_delay);
    godot::ClassDB::bind_method(godot::D_METHOD("get_activation_delay"), &ProximityTrap::get_activation_delay);
    ADD_PROPERTY(godot::PropertyInfo(godot::Variant::FLOAT, "activation_delay"), "set_activation_delay", "get_activation_delay");
}

void ProximityTrap::_ready() {
    Trap::_ready(); // Llama al _ready() de la clase padre

    detection_area = godot::Object::cast_to<godot::Area2D>(get_node_or_null("Area2D"));
    if (detection_area) {
        detection_area->connect("body_entered", godot::Callable(this, "_on_body_entered"));
    }
}

void ProximityTrap::_on_body_entered(godot::Node2D *body) {
    if (is_active && body && body->is_in_group("player")) {
        trigger_effect();
    }
}

void ProximityTrap::trigger_effect() {
    // Las clases hijas (como FallingFloor) sobrescribirán esto
    godot::UtilityFunctions::print("ProximityTrap activada por el jugador.");
}

void ProximityTrap::reset_trap() {
    Trap::reset_trap();
    // Lógica extra de reseteo si es necesaria
}

void ProximityTrap::set_activation_delay(double p_delay) {
    activation_delay = p_delay;
}

double ProximityTrap::get_activation_delay() const {
    return activation_delay;
}