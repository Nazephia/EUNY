#pragma once
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/core/class_db.hpp>

class Trap : public godot::Node2D {
    GDCLASS(Trap, Node2D);

    protected:
    static void _bind_methods();
    bool is_active;
    godot::Transform2D initial_transform;

    public:
    Trap();
    virtual ~Trap();

    void _ready() override;
    virtual void trigger_effect() = 0;
    virtual void reset_trap();

    // Getters y Setters
    void set_is_active(bool p_active);
    bool get_is_active() const;

};
