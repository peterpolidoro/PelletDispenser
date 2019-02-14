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
#include <HBridgeController.h>
#include <OpticalSwitchInterface.h>
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
  StageController::PositionArray getBasePosition();
  StageController::PositionArray getDeliverPosition();
  StageController::PositionArray getDispensePosition();
  StageController::PositionArray getCleanPosition();
  long getBuzzPeriod();
  long getBuzzOnDuration();
  long getBuzzCount();
  long getToneDelay();
  long getToneFrequency();
  long getToneDuration();
  long getToneVolume();
  long getDispenseDelay();
  long getReturnDelay();
  long getCleanDuration();

  void moveStageToBasePosition();
  void moveStageToDeliverPosition();
  void moveStageToDispensePosition();
  void moveStageToCleanPosition();
  void buzz();
  void setWaitToPlayToneState();
  void waitToPlayTone();
  void setPlayToneState();
  void playTone();
  void waitToDispense();
  void setMoveToDispenseState();
  void waitToReturn();
  void setMoveToCleanState();
  void waitAtClean();
  void setMoveToBaseStopState();

  void deliver();
  void abort();

private:
  modular_server::Property properties_[pellet_dispenser::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[pellet_dispenser::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[pellet_dispenser::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[pellet_dispenser::constants::CALLBACK_COUNT_MAX];

  pellet_dispenser::constants::AssayStatus assay_status_;
  EventController<pellet_dispenser::constants::EVENT_COUNT_MAX> event_controller_;

  ModularClient * h_bridge_controller_ptr_;
  ModularClient * optical_switch_interface_ptr_;
  ModularClient * audio_controller_ptr_;

  // Handlers
  void setClientPropertyValuesHandler();
  void getAssayStatusHandler();
  void moveStageToBasePositionHandler();
  void moveStageToDeliverPositionHandler();
  void moveStageToDispensePositionHandler();
  void moveStageToCleanPositionHandler();
  void playToneHandler(int arg);
  void waitToDispenseHandler(int arg);
  void moveToDispenseHandler(int arg);
  void waitToPlayToneHandler(int arg);
  void moveToCleanHandler(int arg);
  void moveToBaseStopHandler(int arg);
  void deliverHandler(modular_server::Pin * pin_ptr);
  void abortHandler(modular_server::Pin * pin_ptr);

};

#endif
