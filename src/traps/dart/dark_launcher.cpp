#include "dart_launcher.h"
#include "dart.h"
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

DartLauncher::DartLauncher() {
    spawn_marker = nullptr;
    target_ray = nullptr;
    shoot_interval = 2.0; // Dispara cada 2 segundos por defecto
    time_since_last_shot = 0.0;
    shoot_direction = godot::Vector2(-1.0, 0.0);
    
    set_process(true);
}

DartLauncher::~DartLauncher() {}

void DartLauncher::_bind_methods() {
    godot::ClassDB::bind_method(godot::D_METHOD("set_dart_scene", "scene"), &DartLauncher::set_dart_scene);
    godot::ClassDB::bind_method(godot::D_METHOD("get_dart_scene"), &DartLauncher::get_dart_scene);
    godot::ClassDB::add_property("DartLauncher", godot::PropertyInfo(godot::Variant::OBJECT, "dart_scene", godot::PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_dart_scene", "get_dart_scene");

    godot::ClassDB::bind_method(godot::D_METHOD("set_shoot_interval", "interval"), &DartLauncher::set_shoot_interval);
    godot::ClassDB::bind_method(godot::D_METHOD("get_shoot_interval"), &DartLauncher::get_shoot_interval);
    godot::ClassDB::add_property("DartLauncher", godot::PropertyInfo(godot::Variant::FLOAT, "shoot_interval"), "set_shoot_interval", "get_shoot_interval");

    godot::ClassDB::bind_method(godot::D_METHOD("set_shoot_direction", "dir"), &DartLauncher::set_shoot_direction);
    godot::ClassDB::bind_method(godot::D_METHOD("get_shoot_direction"), &DartLauncher::get_shoot_direction);
    godot::ClassDB::add_property("DartLauncher", godot::PropertyInfo(godot::Variant::VECTOR2, "shoot_direction"), "set_shoot_direction", "get_shoot_direction");
}

void DartLauncher::_ready() {
    Trap::_ready();
    if (godot::Engine::get_singleton()->is_editor_hint()) {
        return;
    }

    spawn_marker = godot::Object::cast_to<godot::Marker2D>(get_node_or_null("Marker2D"));
    target_ray = godot::Object::cast_to<godot::RayCast2D>(get_node_or_null("RayCast2D"));
    if (target_ray) {
        target_ray->set_target_position(shoot_direction * 1000.0);
    }
}

void DartLauncher::_process(double delta) {
    if (!is_active || godot::Engine::get_singleton()->is_editor_hint()) return;

    time_since_last_shot += delta;
    if (time_since_last_shot >= shoot_interval) {
        time_since_last_shot = 0.0;
        shoot();
    }
}

void DartLauncher::shoot() {
    if (dart_scene.is_null()) return;
    if (!target_ray) return;

    target_ray->force_raycast_update();
    godot::Node *target = godot::Object::cast_to<godot::Node>(target_ray->get_collider());
    if (!target || !target->is_in_group("player")) return;

    godot::Node *instantiated_node = dart_scene->instantiate();
    Dart *dart = godot::Object::cast_to<Dart>(instantiated_node);
    if (!dart) {
        memdelete(instantiated_node);
        return;
    }

    godot::Vector2 ray_direction =
        (target_ray->to_global(target_ray->get_target_position()) - target_ray->get_global_position()).normalized();
    dart->set_direction(ray_direction);

    // Obtener la posición global de salida (desde el Marker2D o el centro del dispensador)
    godot::Vector2 spawn_pos = spawn_marker ? spawn_marker->get_global_position() : get_global_position();
    dart->set_global_position(spawn_pos);

    // Añadir el dardo a la escena principal (fuera del árbol del dispensador para que no se mueva con él)
    godot::Node *tree_root = get_tree()->get_current_scene();
    if (tree_root) {
        tree_root->add_child(dart);
    }
}

void DartLauncher::trigger_effect() {
    shoot();
}

void DartLauncher::reset_trap() {
    Trap::reset_trap();
    time_since_last_shot = 0.0;
}

void DartLauncher::set_dart_scene(godot::Ref<godot::PackedScene> scene) {
    dart_scene = scene;
}

godot::Ref<godot::PackedScene> DartLauncher::get_dart_scene() const {
    return dart_scene;
}

void DartLauncher::set_shoot_interval(double interval) {
    shoot_interval = interval;
}

double DartLauncher::get_shoot_interval() const {
    return shoot_interval;
}

void DartLauncher::set_shoot_direction(godot::Vector2 dir) {
    shoot_direction = dir.normalized();
    if (target_ray) {
        target_ray->set_target_position(shoot_direction * 1000.0);
    }
}

godot::Vector2 DartLauncher::get_shoot_direction() const {
    return shoot_direction;
}