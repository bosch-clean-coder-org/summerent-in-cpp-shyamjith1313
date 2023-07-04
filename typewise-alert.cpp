#include "typewise-alert.h"
#include <stdio.h>
#include <map>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }else if(value > upperLimit) {
    return TOO_HIGH;
  } else {
  return NORMAL;
  }
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  int lowerLimit = 0;
  std::map<CoolingType,int> upperLimits {
    { PASSIVE_COOLING, 35 },
    { HI_ACTIVE_COOLING, 45 },
    { MED_ACTIVE_COOLING, 40 }    
  };
  int upperLimit = upperLimits[coolingType];
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  if(TOO_LOW == breachType){
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
  } else if(TOO_HIGH == breachType) {
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
  } else {
    //Do nothing
  }
}
