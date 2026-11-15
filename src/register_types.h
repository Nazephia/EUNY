#pragma once

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_euny_module(ModuleInitializationLevel p_level);
void uninitialize_euny_module(ModuleInitializationLevel p_level);

extern "C" {
GDExtensionBool GDE_EXPORT euny_library_init(
        GDExtensionInterfaceGetProcAddress p_get_proc_address,
        const GDExtensionClassLibraryPtr p_library,
        GDExtensionInitialization *r_initialization);
}
