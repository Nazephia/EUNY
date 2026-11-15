#include "character.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/class_db.hpp>
#include "../states/state_machine.h"
#include "../states/states_character/idle_state.h"
#include "../states/states_character/walk_state.h"
#include "../states/states_character/jump_state.h"

Character::Character(){
	speed = 300.0;
	jump_velocity = -400.0;
	gravity = godot::ProjectSettings::get_singleton()->get_setting("physics/2d/default_gravity");
	animated_sprite = nullptr;
	state_machine = new StateMachine(this);
}

Character::~Character(){
	delete state_machine;
}

void Character::_ready(){
	animated_sprite = get_node<godot::AnimatedSprite2D>("AnimatedSprite2D");
	state_machine->add_state("idle", new IdleState());
	state_machine->add_state("walk", new WalkState());
	state_machine->add_state("jump", new JumpState());
	state_machine->change_state("idle");
}


void Character::_bind_methods() {
	// _physics_process es un callback virtual del motor (Node).
	// No hace falta (ni se debe) hacer ClassDB::bind_method para él.
	// Aquí se vinculan los métodos propios que quieras exponer a GDScript.
	godot::ClassDB::bind_method(godot::D_METHOD("set_speed", "speed"), &Character::set_speed);
	godot::ClassDB::bind_method(godot::D_METHOD("get_speed"), &Character::get_speed);
	ADD_PROPERTY(godot::PropertyInfo(godot::Variant::FLOAT, "speed"), "set_speed", "get_speed");

	godot::ClassDB::bind_method(godot::D_METHOD("set_jump_velocity", "jump_velocity"), &Character::set_jump_velocity);
    godot::ClassDB::bind_method(godot::D_METHOD("get_jump_velocity"), &Character::get_jump_velocity);
	ADD_PROPERTY(godot::PropertyInfo(godot::Variant::FLOAT, "jump_velocity"), "set_jump_velocity", "get_jump_velocity");
}


void Character::_physics_process(double delta) {
	if (godot::Engine::get_singleton()->is_editor_hint()) {
		return;
	}

	godot::Vector2 velocity = get_velocity();
	if(!is_on_floor()){
		velocity.y += gravity * delta;
	}
	set_velocity(velocity);
	state_machine->update(delta);
	state_machine->physics_update(delta);
	move_and_slide();
}

// Metodos Get y Set para las variables privadas
double Character::get_speed() const { return speed; }
void Character::set_speed(double p_speed) { speed = p_speed; }	

double Character::get_jump_velocity() const { return jump_velocity; }	
void Character::set_jump_velocity(double p_jump_velocity) { jump_velocity = p_jump_velocity; }

double Character::get_gravity() const { return gravity; }
StateMachine *Character::get_state_machine() const { return state_machine; }
godot::AnimatedSprite2D *Character::get_animated_sprite() const { return animated_sprite; }