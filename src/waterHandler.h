/**
 * @file swaterHandler.h
 *
 * @brief Handler for digital water switch
 */

uint8_t currStateWaterSwitch;
    #define FEATURE_STROKE  1                     // 0 = deactivated, 1 = activated
    //#define STROKETIME  700    // Time Stroke ms
    //#define PAUSETIME   5     // Time pause ms
    bool pumpState;
    double Q = 0;
    double P = 0;
    double flow_Forecast = 0;
    unsigned long lastTime=0;
    unsigned long timepassed = 0;
    unsigned int lastflow = 0;
    #define HEATPOWER   1300     // Heizleistung in Watt

void flowForecast() {
//Pins für Flow Sensor auf VCC und GND setzen
highpower3Relay.on();
lowpowerRelay.off();

timepassed = millis() - lastTime;

//alle 100ms berechnen
if (timepassed >= 500){
    //Forecast Rechnung, basierend auf dem letzten Flow
    // Q=mcΔT

    Q = flow*0.408 * 4.18 * (setpoint-23);

    //P = Q/t​
    P = Q / timepassed * 1000;

    //flow_Forecast = P / HEATPOWER

    flow_Forecast = P / HEATPOWER * 100;
    lastTime =  millis();
    if(lastflow != flow){
        LOGF(INFO, "Gesamtflow %i",flow);
        LOGF(INFO, "Timepassed %i",timepassed);
        LOGF(INFO, "Forecast %f",flow_Forecast);
        LOGF(INFO, "P %f",P);
        LOGF(INFO, "Q %f",Q);
        lastflow = flow;
    }
    flow = 0;
    //189 alter flow
    //53,44g
    //320 neuer flow
    // 320-189 = 131 steps
    // 53,44/131 = 0,408 gram/step
}
}

void checkWaterSwitch() {

waterbuttonRelay.on();
button1Relay.on();
button2Relay.on();
highpower1Relay.on();
highpower2Relay.on();

    if (FEATURE_WATERSWITCH && machineState != kBrew ) { //&& machineState != kSteam
        uint8_t waterSwitchReading = waterSwitch->isPressed();


        if (WATERSWITCH_TYPE == Switch::TOGGLE) {
            // Set steamON to 1 when src/waterHandler.h waterswitch is HIGH
            if (waterSwitchReading == HIGH) {
                waterON = 1;
                if (machineState == kSteam){
                    pumpstrokes = true;
                }
                else {
                    pumpstrokes = false;
                    pumpRelay.on();
                }
                
            }
            else
            {
                pumpRelay.off();
                pumpstrokes = false;
            }

            /*/ if activated via web interface then steamFirstON == 1, prevent override
            if (waterSwitchReading == LOW && !waterFirstON) {
                waterON = 0;
                pumpRelay.off();
            }
            */

        }
        else if (WATERSWITCH_TYPE == Switch::MOMENTARY) {
            if (waterSwitchReading != currStateWaterSwitch) {
                currStateWaterSwitch = waterSwitchReading;

                // only toggle heating power if the new button state is HIGH
                if (currStateWaterSwitch == HIGH) {
                    if (waterON == 0) {
                        waterON = 1;
                        pumpRelay.on();                       
                    }
                    else {
                        waterON = 0;
                        pumpRelay.off();
                    }
                }
            }
        }
    }
}

