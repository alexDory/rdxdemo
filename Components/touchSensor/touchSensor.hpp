#ifndef TOUCHSENSOR_HPP
#define TOUCHSENSOR_HPP

#include "Components/touchSensor/touchSensorComponentAc.hpp"

namespace Components {

class touchSensor : public touchSensorComponentBase {
  public:

    // ----------------------------------------------------------------------
    // Constructor and destructor
    // ----------------------------------------------------------------------

    /**
     * @brief Construct a new touchSensor object
     * 
     * @param compName The component name
     */
    touchSensor(const char* compName);

    /**
     * @brief Destroy the touchSensor object
     * 
     */
    ~touchSensor();

    // ----------------------------------------------------------------------
    // Overridden command handlers
    // ----------------------------------------------------------------------

    /** 
     * @brief Handler for the resetStats command
     * @param opCode The opcode
     * @param cmdSeq The command sequence number  
     **/
    void resetStats_cmdHandler(FwOpcodeType opCode, U32 cmdSeq);

    /** 
     * @brief Handler for the initialize command
     * @param opCode The opcode
     * @param cmdSeq The command sequence number  
     **/
    void initialize_cmdHandler(FwOpcodeType opCode, U32 cmdSeq);

  private:

    // ----------------------------------------------------------------------
    // Ports setup
    // ----------------------------------------------------------------------

    /** 
     * 
     * @brief Handler for the schedIn input port
     * @param portNum The port number
     * @param context The call order
     * @note This function is called by the schedIn input port
     *  
     * **/
    void schedIn_handler(NATIVE_INT_TYPE portNum, NATIVE_UINT_TYPE context);

    // ----------------------------------------------------------------------
    // Member variables to hold GPIO states and count
    // ---------------------------------------------------------------------- 

    Fw::On m_state; 
    U64 m_count;

  };
} // namespace Components

#endif
