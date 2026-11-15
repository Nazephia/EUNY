#include "trap.h"

Trap::Trap() {
    is_active = true;
}

Trap::~Trap() {}

void Trap::_bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("set_is_active", "active"), &Trap::set_is_active);
    godot::ClassDB::bind_method(godot::D_METHOD("get_is_active"), &Trap::get_is_active);
    ADD_PROPERTY(godot::PropertyInfo(godot::Variant::BOOL, "is_active"), "set_is_active", "get_is_active");
}

void Trap::_ready() {
    
    initial_transform = get_global_transform();
}

void Trap::reset_trap() {
    is_active = true;
    set_global_transform(initial_transform);
    
}

void Trap::set_is_active(bool p_active) {
    is_active = p_active;
}

bool Trap::get_is_active() const {
    return is_active;
}
