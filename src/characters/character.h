#pragma once

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>

class StateMachine;

class Character : public godot::CharacterBody2D {
	GDCLASS(Character, godot::CharacterBody2D)

	private:
	double speed;
	double jump_velocity;
	double gravity;
	godot::AnimatedSprite2D *animated_sprite;
	StateMachine *state_machine;
	godot::Vector2 spawn_position;

	protected:
	static void _bind_methods();

	public:
	Character();
	~Character();

	// Movimiento
	virtual void _physics_process(double delta) override;
	virtual void _ready() override;
	void respawn();

	// Metodos Get y Set para las variables privadas
	double get_speed() const;
	void set_speed(double p_speed);
	double get_jump_velocity() const;
	void set_jump_velocity(double p_jump_velocity);
	double get_gravity() const;
	StateMachine *get_state_machine() const;
	godot::AnimatedSprite2D *get_animated_sprite() const;
	
};
