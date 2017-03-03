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
  StepperController::setup();

  // Variable Setup
  stage_homed_ = false;

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

  // Parameters
  modular_server::Parameter & stage_positions_parameter = modular_server_.createParameter(constants::stage_positions_parameter_name);
  stage_positions_parameter.setRange(constants::stage_position_min,constants::stage_position_max);
  stage_positions_parameter.setArrayLengthRange(constants::STAGE_CHANNEL_COUNT,constants::STAGE_CHANNEL_COUNT);
  stage_positions_parameter.setUnits(constants::mm_unit);

  // Functions
  modular_server::Function & dispense_pellet_function = modular_server_.createFunction(constants::dispense_pellet_function_name);
  dispense_pellet_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PelletDispenser::dispensePelletHandler));

  modular_server::Function & enable_dispenser_function = modular_server_.createFunction(constants::enable_dispenser_function_name);
  enable_dispenser_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PelletDispenser::enableDispenserHandler));

  modular_server::Function & disable_dispenser_function = modular_server_.createFunction(constants::disable_dispenser_function_name);
  disable_dispenser_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PelletDispenser::disableDispenserHandler));

  modular_server::Function & home_stage_function = modular_server_.createFunction(constants::home_stage_function_name);
  home_stage_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PelletDispenser::homeStageHandler));
  home_stage_function.setReturnTypeBool();

  modular_server::Function & stage_homing_function = modular_server_.createFunction(constants::stage_homing_function_name);
  stage_homing_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PelletDispenser::stageHomingHandler));
  stage_homing_function.setReturnTypeBool();
  stage_homing_function.setReturnTypeBool();

  modular_server::Function & stage_homed_function = modular_server_.createFunction(constants::stage_homed_function_name);
  stage_homed_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PelletDispenser::stageHomedHandler));
  stage_homed_function.setReturnTypeBool();

  modular_server::Function & move_stage_to_function = modular_server_.createFunction(constants::move_stage_to_function_name);
  move_stage_to_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PelletDispenser::moveStageToHandler));
  move_stage_to_function.addParameter(stage_positions_parameter);

  modular_server::Function & get_stage_positions_function = modular_server_.createFunction(constants::get_stage_positions_function_name);
  get_stage_positions_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&PelletDispenser::getStagePositionsHandler));
  get_stage_positions_function.setReturnTypeArray();

  // Callbacks
}

void PelletDispenser::update()
{
  // Parent Update
  StepperController::update();

  if (stage_homing_)
  {
    bool stage_homing = false;
    bool stage_homed = true;
    for (size_t channel_i=0; channel_i<constants::STAGE_CHANNEL_COUNT; ++channel_i)
    {
      size_t channel = constants::stage_channels[channel_i];
      if (!homed(channel))
      {
        stage_homing = true;
        stage_homed = false;
      }
    }
    stage_homing_ = stage_homing;
    stage_homed_ = stage_homed;
  }
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

bool PelletDispenser::homeStage()
{
  reinitialize();

  bool stage_homing = false;
  bool stage_homed = true;
  for (size_t channel_i=0; channel_i<constants::STAGE_CHANNEL_COUNT; ++channel_i)
  {
    size_t channel = constants::stage_channels[channel_i];
    bool homing = home(channel);
    if (homing)
    {
      stage_homing = true;
      stage_homed = false;
    }
  }
  stage_homing_ = stage_homing;
  stage_homed_ = stage_homed;
  return stage_homing;
}

bool PelletDispenser::stageHoming()
{
  return stage_homing_;
}

bool PelletDispenser::stageHomed()
{
  return stage_homed_;
}

void PelletDispenser::moveStageTo(Array<double,pellet_dispenser::constants::STAGE_CHANNEL_COUNT> stage_positions)
{
  if (stage_homed_)
  {
    for (size_t channel_i=0; channel_i<constants::STAGE_CHANNEL_COUNT; ++channel_i)
    {
      moveTo(constants::stage_channels[channel_i],stage_positions[channel_i]);
    }
  }
}

Array<double,pellet_dispenser::constants::STAGE_CHANNEL_COUNT> PelletDispenser::getStagePositions()
{
  Array<double,pellet_dispenser::constants::STAGE_CHANNEL_COUNT> stage_positions;
  for (size_t channel_i=0; channel_i<constants::STAGE_CHANNEL_COUNT; ++channel_i)
  {
    stage_positions.push_back(getPosition(constants::stage_channels[channel_i]));
  }
  return stage_positions;
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

void PelletDispenser::homeStageHandler()
{
  bool homing = homeStage();
  modular_server_.response().returnResult(homing);
}

void PelletDispenser::stageHomingHandler()
{
  bool homing = stageHoming();
  modular_server_.response().returnResult(homing);
}

void PelletDispenser::stageHomedHandler()
{
  bool homed = stageHomed();
  modular_server_.response().returnResult(homed);
}

void PelletDispenser::moveStageToHandler()
{
  ArduinoJson::JsonArray * stage_positions_array_ptr;
  modular_server_.parameter(constants::stage_positions_parameter_name).getValue(stage_positions_array_ptr);

  Array<double,pellet_dispenser::constants::STAGE_CHANNEL_COUNT> stage_positions;

  size_t channel_i = 0;
  for (ArduinoJson::JsonArray::iterator stage_positions_it=stage_positions_array_ptr->begin();
       stage_positions_it != stage_positions_array_ptr->end();
       ++stage_positions_it)
  {
    if (channel_i < constants::STAGE_CHANNEL_COUNT)
    {
      double position = *stage_positions_it;
      stage_positions.push_back(position);
      ++channel_i;
    }
  }
  moveStageTo(stage_positions);
}

void PelletDispenser::getStagePositionsHandler()
{
  Array<double,pellet_dispenser::constants::STAGE_CHANNEL_COUNT> stage_positions = getStagePositions();
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  for (size_t channel_i=0; channel_i<constants::STAGE_CHANNEL_COUNT; ++channel_i)
  {
    modular_server_.response().write(stage_positions[channel_i]);
  }
  modular_server_.response().endArray();
}

