/*
 * Copyright 2012-2013 BrewPi/Elco Jacobs.
 *
 * This file is part of BrewPi.
 * 
 * BrewPi is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * BrewPi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with BrewPi.  If not, see <http://www.gnu.org/licenses/>.
 */ 

#pragma once

#include "Brewpi.h"
#include "TemperatureFormats.h"
#include "Platform.h"
#include "TempSensor.h"
#include "Actuator.h"
#include "Sensor.h"
#include "EepromTypes.h"
#include "ActuatorAutoOff.h"
#include "ActuatorOnOff.h"
#include "ActuatorPwm.h"
#include "ModeControl.h"
#include "Ticks.h"

// These two structs are stored in and loaded from EEPROM
struct ControlSettings{
	control_mode_t mode;
	temperature beerSetting;
	temperature fridgeSetting;
	temperature heatEstimator; // updated automatically by self learning algorithm
	temperature coolEstimator; // updated automatically by self learning algorithm
};

struct ControlVariables{
	temperature beerDiff;
	long_temperature diffIntegral; // also uses 9 fraction bits, but more integer bits to prevent overflow
	temperature beerSlope;
	temperature p;
	temperature i;
	temperature d;
};

struct ControlConstants{
	char tempFormat;
	temperature tempSettingMin;
	temperature tempSettingMax;	
	temperature Kp;
	temperature Ki;
	temperature Kd;
	temperature idleRangeHigh;
	temperature idleRangeLow;
	// for the filter coefficients the b value is stored. a is calculated from b.
	uint8_t fridgeFastFilter;	// for display, logging and on-off control
	uint8_t fridgeSlowFilter;	// for peak detection
	uint8_t fridgeSlopeFilter;	// not used in current control algorithm
	uint8_t beerFastFilter;	// for display and logging
	uint8_t beerSlowFilter;	// for on/off control algorithm
	uint8_t beerSlopeFilter;	// for PID calculation
	uint8_t lightAsHeater;		// use the light to heat rather than the configured heater device
	uint8_t rotaryHalfSteps; // define whether to use full or half steps for the rotary encoder
	temperature pidMax;
    uint16_t heatPwmPeriod;
    uint16_t coolPwmPeriod;
    uint16_t minCoolTime;
    uint16_t minCoolIdleTime;
	fixed7_9 fridgePwmKpHeat;
	fixed7_9 fridgePwmKiHeat;
	fixed7_9 fridgePwmKdHeat;
	fixed7_9 fridgePwmKpCool;
    fixed7_9 fridgePwmKiCool;
    fixed7_9 fridgePwmKdCool;
    fixed7_9 beerPwmKpHeat;
    fixed7_9 beerPwmKiHeat;
    fixed7_9 beerPwmKdHeat;

};

#define EEPROM_TC_SETTINGS_BASE_ADDRESS 0
#define EEPROM_CONTROL_SETTINGS_ADDRESS (EEPROM_TC_SETTINGS_BASE_ADDRESS+sizeof(uint8_t))
#define EEPROM_CONTROL_CONSTANTS_ADDRESS (EEPROM_CONTROL_SETTINGS_ADDRESS+sizeof(ControlSettings))

enum states{
	IDLE,						// 0
	STATE_OFF,					// 1
	DOOR_OPEN,					// 2 used by the Display only
	HEATING,					// 3
	COOLING,					// 4
	NUM_STATES                  // 5
};

#define TC_STATE_MASK 0x7;	// 3 bits

#if TEMP_CONTROL_STATIC
#define TEMP_CONTROL_METHOD static
#define TEMP_CONTROL_FIELD static
#else
#define TEMP_CONTROL_METHOD 
#define TEMP_CONTROL_FIELD
#endif

// Making all functions and variables static reduces code size.
// There will only be one TempControl object, so it makes sense that they are static.

/*
 * MDM: To support multi-chamber, I could have made TempControl non-static, and had a reference to
 * the current instance. But this means each lookup of a field must be done indirectly, which adds to the code size.
 * Instead, we swap in/out the sensors and control data so that the bulk of the code can work against compile-time resolvable
 * memory references. While the design goes against the grain of typical OO practices, the reduction in code size make it worth it.
 */

class TempControl{
	public:
	
	TempControl();
	~TempControl(){};
	
	TEMP_CONTROL_METHOD void init(void);

	TEMP_CONTROL_METHOD void updateTemperatures(void);
	TEMP_CONTROL_METHOD void updatePID(void);
	TEMP_CONTROL_METHOD void updateState(void);
	TEMP_CONTROL_METHOD void updateOutputs(void);
	TEMP_CONTROL_METHOD void updatePwm(void);
	
	TEMP_CONTROL_METHOD void loadSettings(eptr_t offset);
	TEMP_CONTROL_METHOD void storeSettings(eptr_t offset);
	TEMP_CONTROL_METHOD void loadDefaultSettings(void);
	
	TEMP_CONTROL_METHOD void loadConstants(eptr_t offset);
	TEMP_CONTROL_METHOD void storeConstants(eptr_t offset);
	TEMP_CONTROL_METHOD void loadDefaultConstants(void);
	
	//TEMP_CONTROL_METHOD void loadSettingsAndConstants(void);
		
	TEMP_CONTROL_METHOD tcduration_t timeSinceCooling(void);
 	TEMP_CONTROL_METHOD tcduration_t timeSinceHeating(void);
  	TEMP_CONTROL_METHOD tcduration_t timeSinceIdle(void);
	  
	TEMP_CONTROL_METHOD temperature getBeerTemp(void);
	TEMP_CONTROL_METHOD temperature getBeerSetting(void);
	TEMP_CONTROL_METHOD void setBeerTemp(temperature newTemp);
	
	TEMP_CONTROL_METHOD temperature getFridgeTemp(void);
	TEMP_CONTROL_METHOD temperature getFridgeSetting(void);
	TEMP_CONTROL_METHOD void setFridgeTemp(temperature newTemp);
	
	TEMP_CONTROL_METHOD temperature getRoomTemp(void) {
		return ambientSensor->read();
	}
		
	TEMP_CONTROL_METHOD void setMode(control_mode_t newMode, bool force=false);
	TEMP_CONTROL_METHOD control_mode_t getMode(void) {
		return cs.mode;
	}

	TEMP_CONTROL_METHOD states getState(void){
		return state;
	}
	
	TEMP_CONTROL_METHOD bool stateIsCooling(void);
	TEMP_CONTROL_METHOD bool stateIsHeating(void);
	TEMP_CONTROL_METHOD bool modeIsBeer(void){
		return (cs.mode == MODE_BEER_CONSTANT || cs.mode == MODE_BEER_PROFILE);
	}
		
	TEMP_CONTROL_METHOD void initFilters();
	
	TEMP_CONTROL_METHOD bool isDoorOpen() { return doorOpen; }
	
	TEMP_CONTROL_METHOD unsigned char getDisplayState() {
		return isDoorOpen() ? DOOR_OPEN : getState();
	}

	public:
	TEMP_CONTROL_FIELD TempSensor* beerSensor;
	TEMP_CONTROL_FIELD TempSensor* fridgeSensor;
	TEMP_CONTROL_FIELD BasicTempSensor* ambientSensor;
	TEMP_CONTROL_FIELD ActuatorOnOff* chamberCoolerLimiter;
	TEMP_CONTROL_FIELD ActuatorPwm* chamberHeater;
	TEMP_CONTROL_FIELD ActuatorPwm* beerHeater;
	TEMP_CONTROL_FIELD ActuatorPwm* chamberCooler;
	TEMP_CONTROL_FIELD Actuator* light;
	TEMP_CONTROL_FIELD Actuator* fan;
	TEMP_CONTROL_FIELD AutoOffActuator cameraLight;
	TEMP_CONTROL_FIELD Sensor<bool>* door;
	
	// Control parameters
	TEMP_CONTROL_FIELD ControlConstants cc;
	TEMP_CONTROL_FIELD ControlSettings cs;
	TEMP_CONTROL_FIELD ControlVariables cv;

	private:
	// keep track of beer setting stored in EEPROM
	TEMP_CONTROL_FIELD temperature storedBeerSetting;

	// Timers
	TEMP_CONTROL_FIELD tcduration_t lastIdleTime;
	TEMP_CONTROL_FIELD tcduration_t lastHeatTime;
	TEMP_CONTROL_FIELD tcduration_t lastCoolTime;
	
	// State variables
	TEMP_CONTROL_FIELD states state;
	TEMP_CONTROL_FIELD bool doorOpen;

	friend class TempControlState;
};
	
extern TempControl tempControl;
