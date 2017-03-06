// ----------------------------------------------------------------------------
// PelletDispenser.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef PELLET_DISPENSER_H
#define PELLET_DISPENSER_H
#include "Flash.h"
#include <EEPROM.h>
#include "Streaming.h"
#include "ArduinoJson.h"
#include "JsonSanitizer.h"
#include "JsonStream.h"
#include "Array.h"
#include "Vector.h"
#include "MemoryFree.h"
#include "ConstantVariable.h"
#include "SavedVariable.h"
#include "Functor.h"
#include "IndexedContainer.h"
#include "FunctorCallbacks.h"

#include "SPI.h"
#include "TMC429.h"
#include "TMC26X.h"

#include "ModularServer.h"
#include "ModularDeviceBase.h"
#include "StepDirController.h"
#include "StepperController.h"

#include "utility/Constants.h"


class PelletDispenser : public StepperController
{
public:
  PelletDispenser();
  virtual void setup();
  virtual void update();

  void dispensePellet();
  void enableDispenser();
  void disableDispenser();

  bool homeStage();
  bool stageHoming();
  bool stageHomed();

  bool moveStageTo(Array<double,pellet_dispenser::constants::STAGE_CHANNEL_COUNT> stage_positions);
  Array<double,pellet_dispenser::constants::STAGE_CHANNEL_COUNT> getStagePositions();

private:
  modular_server::Property properties_[pellet_dispenser::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[pellet_dispenser::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[pellet_dispenser::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[pellet_dispenser::constants::CALLBACK_COUNT_MAX];

  bool stage_homing_;
  bool stage_homed_;

  // Handlers
  void dispensePelletHandler();
  void enableDispenserHandler();
  void disableDispenserHandler();
  void homeStageHandler();
  void stageHomingHandler();
  void stageHomedHandler();
  void moveStageToHandler();
  void getStagePositionsHandler();

};

#endif
