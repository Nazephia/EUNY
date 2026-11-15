#pragma once

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/input.hpp>



class Character : public godot::CharacterBody2D {
	GDCLASS(Character, godot::CharacterBody2D)

	private:
	double speed;
	double jump_velocity;
	double gravity;

	protected:
	static void _bind_methods();

	public:
	Character();
	~Character();

	// Movimiento
	virtual void _physics_process(double delta) override;

	// Metodos Get y Set para las variables privadas
	double get_speed() const;
	void set_speed(double p_speed);
	double get_jump_velocity() const;
	void set_jump_velocity(double p_jump_velocity);
	double get_gravity() const;
	
};
