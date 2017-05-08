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

  modular_server::Property & switch_active_polarity_property = modular_server_.property(step_dir_controller::constants::switch_active_polarity_property_name);
  switch_active_polarity_property.setDefaultValue(constants::switch_active_polarity_default);

  modular_server::Property & left_switch_stop_enabled_property = modular_server_.property(step_dir_controller::constants::left_switch_stop_enabled_property_name);
  left_switch_stop_enabled_property.setDefaultValue(constants::left_switch_stop_enabled_default);

  modular_server::Property & right_switches_enabled_property = modular_server_.property(step_dir_controller::constants::right_switches_enabled_property_name);
  right_switches_enabled_property.setDefaultValue(constants::right_switches_enabled_default);

  modular_server::Property & right_switch_stop_enabled_property = modular_server_.property(step_dir_controller::constants::right_switch_stop_enabled_property_name);
  right_switch_stop_enabled_property.setDefaultValue(constants::right_switch_stop_enabled_default);

  modular_server::Property & home_velocity_property = modular_server_.property(step_dir_controller::constants::home_velocity_property_name);
  home_velocity_property.setDefaultValue(constants::home_velocity_default);

  modular_server::Property & current_scale_property = modular_server_.property(stepper_controller::constants::current_scale_property_name);
  current_scale_property.setDefaultValue(constants::current_scale_default);

  modular_server::Property & stage_channel_count_property = modular_server_.property(stage_controller::constants::stage_channel_count_property_name);
  stage_channel_count_property.setDefaultValue(constants::stage_channel_count_default);
  stage_channel_count_property.setRange(constants::stage_channel_count_min,constants::stage_channel_count_max);

  modular_server::Property & stage_position_min_property = modular_server_.property(stage_controller::constants::stage_position_min_property_name);
  stage_position_min_property.setDefaultValue(constants::stage_position_min_default);
  stage_position_min_property.setRange(constants::stage_position_min_default,constants::stage_position_max_default);

  modular_server::Property & stage_position_max_property = modular_server_.property(stage_controller::constants::stage_position_max_property_name);
  stage_position_max_property.setDefaultValue(constants::stage_position_max_default);
  stage_position_max_property.setRange(constants::stage_position_min_default,constants::stage_position_max_default);

  modular_server::Property & base_position_property = modular_server_.createProperty(constants::base_position_property_name,constants::base_position_default);
  base_position_property.setRange(constants::stage_position_min_default,constants::stage_position_max_default);

  modular_server::Property & deliver_position_property = modular_server_.createProperty(constants::deliver_position_property_name,constants::deliver_position_default);
  deliver_position_property.setRange(constants::stage_position_min_default,constants::stage_position_max_default);

  // Parameters
  modular_server::Parameter & stage_positions_parameter = modular_server_.parameter(stage_controller::constants::stage_positions_parameter_name);
  stage_positions_parameter.setUnits(constants::mm_unit);

  // Functions
  modular_server::Function & home_rig_function = modular_server_.createFunction(constants::home_rig_function_name);
  home_rig_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PelletDispenser::homeRigHandler));
  home_rig_function.setReturnTypeBool();

  // modular_server::Function & dispense_pellet_function = modular_server_.createFunction(constants::dispense_pellet_function_name);
  // dispense_pellet_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PelletDispenser::dispensePelletHandler));

  // modular_server::Function & enable_dispenser_function = modular_server_.createFunction(constants::enable_dispenser_function_name);
  // enable_dispenser_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PelletDispenser::enableDispenserHandler));

  // modular_server::Function & disable_dispenser_function = modular_server_.createFunction(constants::disable_dispenser_function_name);
  // disable_dispenser_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PelletDispenser::disableDispenserHandler));

  // Callbacks
  modular_server::Callback & deliver_callback = modular_server_.createCallback(constants::deliver_callback_name);
  deliver_callback.attachFunctor(makeFunctor((Functor1<modular_server::Interrupt *> *)0,*this,&PelletDispenser::deliverHandler));
  deliver_callback.attachTo(modular_device_base::constants::bnc_a_interrupt_name,modular_server::interrupt::mode_falling);

  modular_server::Callback & abort_callback = modular_server_.createCallback(constants::abort_callback_name);
  abort_callback.attachFunctor(makeFunctor((Functor1<modular_server::Interrupt *> *)0,*this,&PelletDispenser::abortHandler));
  abort_callback.attachTo(modular_device_base::constants::bnc_b_interrupt_name,modular_server::interrupt::mode_falling);

  // Clients
  // audio_controller_.setStream(Serial1);
}

bool PelletDispenser::homeRig()
{
  bool stage_homing = homeStage();
  bool dispenser_homing = home(constants::dispenser_channel);
  return (stage_homing || dispenser_homing);
}

// void PelletDispenser::dispensePellet()
// {
//   // audio_controller_.callServerMethod(audio_controller::constants::play_tone_function_name,
//   //                                    5000,
//   //                                    audio_controller::constants::speaker_all);
//   // moveBy(constants::pellet_channel,1);
// }

// void PelletDispenser::enableDispenser()
// {
//   restoreCurrent(constants::pellet_channel);
// }

// void PelletDispenser::disableDispenser()
// {
//   minimizeCurrent(constants::pellet_channel);
// }

void PelletDispenser::deliver()
{
  Serial << "deliver!\n";
}

void PelletDispenser::abort()
{
  Serial << "abort!\n";
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
// modular_server_.property(property_name).getElementValue(element_index,value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(element_index,value) value type must match the property array element default type

void PelletDispenser::homeRigHandler()
{
  bool rig_homing = homeRig();
  modular_server_.response().returnResult(rig_homing);
}

// void PelletDispenser::dispensePelletHandler()
// {
//   dispensePellet();
// }

// void PelletDispenser::enableDispenserHandler()
// {
//   enableDispenser();
// }

// void PelletDispenser::disableDispenserHandler()
// {
//   disableDispenser();
// }

void PelletDispenser::deliverHandler(modular_server::Interrupt * interrupt_ptr)
{
  deliver();
}

void PelletDispenser::abortHandler(modular_server::Interrupt * interrupt_ptr)
{
  abort();
}

