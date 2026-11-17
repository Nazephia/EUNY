#pragma once

#include "../trap.h"
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/ray_cast2d.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/classes/marker2d.hpp>

class DartLauncher : public Trap {
    GDCLASS(DartLauncher, Trap);

protected:
    static void _bind_methods();

    godot::Ref<godot::PackedScene> dart_scene;
    godot::Marker2D *spawn_marker;
    godot::RayCast2D *target_ray;
    
    double shoot_interval;
    double time_since_last_shot;
    godot::Vector2 shoot_direction;

public:
    DartLauncher();
    ~DartLauncher();

    void _ready() override;
    void _process(double delta) override;

    void trigger_effect() override;
    void reset_trap() override;

    void shoot();

    void set_dart_scene(godot::Ref<godot::PackedScene> scene);
    godot::Ref<godot::PackedScene> get_dart_scene() const;

    void set_shoot_interval(double interval);
    double get_shoot_interval() const;

    void set_shoot_direction(godot::Vector2 dir);
    godot::Vector2 get_shoot_direction() const;
};