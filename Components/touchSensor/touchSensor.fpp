module Components {
    @ Capacitive touch sensor. Sends events when activated, blinks an LED, and logs state.
    active component touchSensor {

        ###########################################################################
        # Telemetry Definitions                                                  #
        ###########################################################################
        @ Sensor trigger telemetry counter
        telemetry count: U64 

        ###########################################################################
        # Event Definitions                                                      #
        ###########################################################################
        @ Event for touch sensor state change
        event touchSensorStateEvent(m_currentState: Fw.On) severity activity high id 0 format "Touch sensor state switched: {}"

        ###########################################################################
        # Command Definitions                                                    #
        ###########################################################################
        @ Async command to initialize the sensor
        async command initialize() opcode 0

        @ Command to reset statistics
        sync command resetStats() opcode 1

        ###########################################################################
        # Port Definitions                                                       #
        ###########################################################################

        @ Port to Schedule the touchSensor component tasks
        sync input port schedIn: Svc.Sched

        @ Port to request the current state of the sensor
        output port gpioReadTouch: Drv.GpioRead

        @ Port to control the internal LED
        output port gpioSetLed: Drv.GpioWrite

        ###########################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, Parameters #
        ###########################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Port for sending command registrations
        command reg port cmdRegOut

        @ Port for receiving commands
        command recv port cmdIn

        @ Port for sending command responses
        command resp port cmdResponseOut

        @ Port for sending textual representation of events
        text event port logTextOut

        @ Port for sending events to downlink
        event port logOut

        @ Port for sending telemetry channels to downlink
        telemetry port tlmOut

        @ Port to return the value of a parameter
        param get port prmGetOut

        @ Port to set the value of a parameter
        param set port prmSetOut
    }
}
