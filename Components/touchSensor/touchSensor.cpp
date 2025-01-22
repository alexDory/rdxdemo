#include "Components/touchSensor/touchSensor.hpp"
#include "Fw/Types/BasicTypes.hpp"
#include "FpConfig.hpp"

#define TOUCH_SENSOR_GPIO 4
#define LED_GPIO 25
#define TOUCH_THRESHOLD 400

namespace Components {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

touchSensor::touchSensor(const char* compName): 
    touchSensorComponentBase(compName), 
    m_state(Fw::On::OFF),
    m_count(0)  {}

touchSensor::~touchSensor() {}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void touchSensor::schedIn_handler(NATIVE_INT_TYPE portNum, NATIVE_UINT_TYPE context) 
{
    Fw::On touchState = this->m_state;
    if (this->isConnected_gpioReadTouch_OutputPort(TOUCH_SENSOR_GPIO)) 
    {
        Fw::Logic logicState = (Fw::On::ON == touchState) ? Fw::Logic::HIGH : Fw::Logic::LOW;
        this->gpioReadTouch_out(TOUCH_SENSOR_GPIO, logicState);

        if (touchState == Fw::On::ON)
        {
            this->gpioSetLed_out(LED_GPIO, Fw::Logic::HIGH);
            this->log_ACTIVITY_HI_touchSensorStateEvent(Fw::On::ON);
            this->m_count++;
            this->tlmWrite_count(this->m_count, this->getTime());
        }else
        {
            this->gpioSetLed_out(LED_GPIO, Fw::Logic::LOW);
            this->log_ACTIVITY_HI_touchSensorStateEvent(touchState);
        }

        this->m_state = touchState;
    }
}

// ----------------------------------------------------------------------
// Command handler implementations
// ----------------------------------------------------------------------

void touchSensor::initialize_cmdHandler(FwOpcodeType opCode, U32 cmdSeq)
{
    this->m_state = Fw::On::OFF;
    this->m_count = 0;
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

void touchSensor::resetStats_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) 
{
    this->tlmWrite_count(0, Fw::Time::zero(TB_NONE));
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

} // namespace Components
