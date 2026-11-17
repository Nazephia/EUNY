#include "register_types.h"

#include <godot_cpp/godot.hpp>

#include "characters/character.h"
#include "traps/trap.h"
#include "traps/proximity/proximity_trap.h"
#include "traps/proximity/fallling_floor/falling_floor.h"
#include "traps/death_zone.h"
#include "traps/spikes.h"
#include "traps/flying_spikes.h"
#include "traps/dart/dart.h"
#include "traps/dart/dart_launcher.h"


using namespace godot;

void initialize_euny_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	GDREGISTER_CLASS(Character);
	GDREGISTER_ABSTRACT_CLASS(Trap);
	GDREGISTER_CLASS(ProximityTrap);
	GDREGISTER_CLASS(FallingFloor);

	GDREGISTER_CLASS(DeathZone);
	GDREGISTER_CLASS(Spikes);
	GDREGISTER_CLASS(FlyingSpikes);
	GDREGISTER_CLASS(Dart);
	GDREGISTER_CLASS(DartLauncher);
}

void uninitialize_euny_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {
GDExtensionBool GDE_EXPORT euny_library_init(
		GDExtensionInterfaceGetProcAddress p_get_proc_address,
		GDExtensionClassLibraryPtr p_library,
		GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(initialize_euny_module);
	init_obj.register_terminator(uninitialize_euny_module);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}
