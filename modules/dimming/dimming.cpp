// dimming.cpp

#include "dimming.h"
#include "mbed.h"
#include "pc_serial.h"

#define CANTIDAD_LUCES_PWM 2

// Definir pines para los LEDs
DigitalOut lucesPwm[] = {(D5),(D6)};

static int onTime[CANTIDAD_LUCES_PWM];
static int offTime[CANTIDAD_LUCES_PWM];

Ticker tickerDimming;

static int tickRateMSDimming = 1;
static int tickCounter[CANTIDAD_LUCES_PWM];

static float periodSFloat[CANTIDAD_LUCES_PWM];

// Variables para el brillo final del modo Dimming
float brightness[2] = {1.0, 1.0};  

// Flags de modo Dimming
bool dimmingModeActive[2] = {false, false};

// Flags de modo OnOff
bool onModeActive[2] = {false, false};

AnalogIn potentiometer(A0);

static void setPeriod( size_t light, float period );
static void tickerCallbackDimming( );

float leerPotenciometro() {
    return potentiometer.read();
}

void setDutyCycle( lucesPwm_t luz, float dutyCycle )
{
    onTime[luz] = int ( ( periodSFloat[luz] * dutyCycle ) * 1000 );
    offTime[luz] = int ( periodSFloat[luz] * 1000) - onTime[luz];
}

static void setPeriod( lucesPwm_t luz, float period )
{
    periodSFloat[luz] = period;
}

void dimmingInit()
{
    
    tickerDimming.attach( tickerCallbackDimming, 
                              ( (float) tickRateMSDimming) / 1000.0 );

    setPeriod( LUZ_INTERIOR, 0.01f );
    setPeriod( LUZ_GUARDABARRO , 0.01f );

    setDutyCycle( LUZ_INTERIOR, 0.0f );
    setDutyCycle( LUZ_GUARDABARRO, 0.0f );
}

void setDimmingMode(lucesPwm_t ledIndex, bool mode) {
    dimmingModeActive[ledIndex] = mode;
}

bool getDimmingMode(lucesPwm_t ledIndex) {
    return dimmingModeActive[ledIndex];
}

void setOnMode(lucesPwm_t ledIndex, bool mode) {
    onModeActive[ledIndex] = mode;
}

bool getOnMode(lucesPwm_t ledIndex) {
    return onModeActive[ledIndex];
}

void dimmingUpdate() {
    float dutyCycle = leerPotenciometro();

    if(onModeActive[LUZ_INTERIOR]){
        if (dimmingModeActive[LUZ_INTERIOR]) {
        
        pcSerialComStringWrite("LED1 en modo dimming\n");
        
        setDutyCycle( LUZ_INTERIOR, dutyCycle );
        brightness[LUZ_INTERIOR] = dutyCycle;
        }else 
        setDutyCycle( LUZ_INTERIOR, brightness[LUZ_INTERIOR] );
    }else
        setDutyCycle( LUZ_INTERIOR, 0.0f );
    
    
    if(onModeActive[LUZ_GUARDABARRO]){
        if (dimmingModeActive[LUZ_GUARDABARRO]) {
        pcSerialComStringWrite("LED2 en modo dimming\n");
        setDutyCycle( LUZ_GUARDABARRO, dutyCycle );
        brightness[LUZ_GUARDABARRO] = dutyCycle;
        } else
            setDutyCycle( LUZ_GUARDABARRO, brightness[LUZ_GUARDABARRO] );  // Mantener el brillo final si no está en modo Dimming
    }else
        setDutyCycle( LUZ_GUARDABARRO, 0.0f );
    
}

static void tickerCallbackDimming( )
{
    int i;

    for (i = 0 ; i < CANTIDAD_LUCES_PWM ; i++) {
        tickCounter[i]++;
        if ( lucesPwm[i].read() == 1 ) {
            if( tickCounter[i] > onTime[i] ) {
                tickCounter[i] = 1;
                if ( offTime[i] ) lucesPwm[i] = 0;
                
            }
        } else {
            if( tickCounter[i] > offTime[i] ) { 
                tickCounter[i] = 1;
                if ( onTime[i] ) lucesPwm[i] = 1;
            }
        }
    }
}