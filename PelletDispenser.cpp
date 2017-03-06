// ----------------------------------------------------------------------------
// PelletDispenser.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "PelletDispenser.h"


using namespace pellet_dispenser;

PelletDispenser::PelletDispenser()
{
}

void PelletDispenser::setup()
{
  // Parent Setup
  StageController::setup();

  // Pin Setup

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware

  // Interrupts

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
                              properties_,
                              parameters_,
                              functions_,
                              callbacks_);

  // Properties
  modular_server::Property & steps_per_position_unit_property = modular_server_.property(step_dir_controller::constants::steps_per_position_unit_property_name);
  steps_per_position_unit_property.setDefaultValue(constants::steps_per_position_unit_default);

  modular_server::Property & velocity_max_property = modular_server_.property(step_dir_controller::constants::velocity_max_property_name);
  velocity_max_property.setDefaultValue(constants::velocity_max_default);

  modular_server::Property & velocity_min_property = modular_server_.property(step_dir_controller::constants::velocity_min_property_name);
  velocity_min_property.setDefaultValue(constants::velocity_min_default);

  modular_server::Property & acceleration_max_property = modular_server_.property(step_dir_controller::constants::acceleration_max_property_name);
  acceleration_max_property.setDefaultValue(constants::acceleration_max_default);

  modular_server::Property & home_velocity_property = modular_server_.property(step_dir_controller::constants::home_velocity_property_name);
  home_velocity_property.setDefaultValue(constants::home_velocity_default);

  modular_server::Property & switch_active_polarity_property = modular_server_.property(step_dir_controller::constants::switch_active_polarity_property_name);
  switch_active_polarity_property.setDefaultValue(constants::switch_active_polarity_default);

  modular_server::Property & left_switch_stop_enabled_property = modular_server_.property(step_dir_controller::constants::left_switch_stop_enabled_property_name);
  left_switch_stop_enabled_property.setDefaultValue(constants::left_switch_stop_enabled_default);

  modular_server::Property & current_scale_property = modular_server_.property(stepper_controller::constants::current_scale_property_name);
  current_scale_property.setDefaultValue(constants::current_scale_default);

  modular_server::Property & stage_channel_count_property = modular_server_.property(stage_controller::constants::stage_channel_count_property_name);
  stage_channel_count_property.setDefaultValue(constants::stage_channel_count_default);

  modular_server::Property & stage_position_min_property = modular_server_.property(stage_controller::constants::stage_position_min_property_name);
  stage_position_min_property.setDefaultValue(constants::stage_position_min_default);

  modular_server::Property & stage_position_max_property = modular_server_.property(stage_controller::constants::stage_position_max_property_name);
  stage_position_max_property.setDefaultValue(constants::stage_position_max_default);

  // Parameters
  modular_server::Parameter & stage_positions_parameter = modular_server_.parameter(stage_controller::constants::stage_positions_parameter_name);
  stage_positions_parameter.setUnits(constants::mm_unit);

  // Functions
  modular_server::Function & dispense_pellet_function = modular_server_.createFunction(constants::dispense_pellet_function_name);
  dispense_pellet_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PelletDispenser::dispensePelletHandler));

  modular_server::Function & enable_dispenser_function = modular_server_.createFunction(constants::enable_dispenser_function_name);
  enable_dispenser_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PelletDispenser::enableDispenserHandler));

  modular_server::Function & disable_dispenser_function = modular_server_.createFunction(constants::disable_dispenser_function_name);
  disable_dispenser_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PelletDispenser::disableDispenserHandler));

  // Callbacks
}

void PelletDispenser::dispensePellet()
{
  moveBy(constants::pellet_channel,1);
}

void PelletDispenser::enableDispenser()
{
  restoreCurrent(constants::pellet_channel);
}

void PelletDispenser::disableDispenser()
{
  minimizeCurrent(constants::pellet_channel);
}

// Handlers must be non-blocking (avoid 'delay')
//
// modular_server_.parameter(parameter_name).getValue(value) value type must be either:
// fixed-point number (int, long, etc.)
// floating-point number (float, double)
// bool
// const char *
// ArduinoJson::JsonArray *
// ArduinoJson::JsonObject *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(value) value type must match the property array element default type

void PelletDispenser::dispensePelletHandler()
{
  dispensePellet();
}

void PelletDispenser::enableDispenserHandler()
{
  enableDispenser();
}

void PelletDispenser::disableDispenserHandler()
{
  disableDispenser();
}

