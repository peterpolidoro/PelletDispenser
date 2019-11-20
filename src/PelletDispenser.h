// ----------------------------------------------------------------------------
// PelletDispenser.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef PELLET_DISPENSER_H
#define PELLET_DISPENSER_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

#include <EventController.h>

#include <ModularClient.h>
#include <AudioController.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>
#include <StepDirController.h>
#include <StepperController.h>
#include <StageController.h>

#include "PelletDispenser/Constants.h"


class PelletDispenser : public StageController
{
public:
  PelletDispenser();
  virtual void setup();
  virtual void update();

  pellet_dispenser::constants::AssayStatus getAssayStatus();
  StageController::PositionArray getNextDeliverPosition();
  StageController::PositionArray getDispensePosition();
  StageController::PositionArray getShakePosition();
  long getPositionToneFrequency();
  long getPositionToneVolume();
  long getPositionToneDelay();
  long getPositionToneDuration();
  long getDispenseDelay();
  long getReturnDelay();
  long getShakeDuration();

  void moveStageToNextDeliverPosition();
  void moveStageToDispensePosition();
  void moveStageToShakePosition();
  void playPositionTone();
  void setWaitToDispenseState();
  void waitToDispense();
  void setMoveToDispenseState();
  void waitToReturn();
  void setMoveToShakeState();
  void waitAtShake();
  void setMoveToNextDeliverState();

  void startAssay();
  void dispense();
  void abort();

private:
  modular_server::Property properties_[pellet_dispenser::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[pellet_dispenser::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[pellet_dispenser::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[pellet_dispenser::constants::CALLBACK_COUNT_MAX];

  pellet_dispenser::constants::AssayStatus assay_status_;
  EventController<pellet_dispenser::constants::EVENT_COUNT_MAX> event_controller_;

  ModularClient * audio_controller_ptr_;

  StageController::PositionArray deliver_position_;

  // Handlers
  void setClientPropertyValuesHandler();
  void getAssayStatusHandler();
  void playPositionToneHandler();
  void waitToDispenseHandler(int arg);
  void moveToDispenseHandler(int arg);
  void moveToShakeHandler(int arg);
  void moveToNextDeliverHandler(int arg);
  void startAssayHandler(modular_server::Pin * pin_ptr);
  void dispenseHandler(modular_server::Pin * pin_ptr);
  void abortHandler(modular_server::Pin * pin_ptr);

};

#endif
