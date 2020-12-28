#include "simulatedradio.h"

nBlock_SimulatedRadio::nBlock_SimulatedRadio(uint32_t mode, uint32_t payloadLength){
    
    _mode = mode;
    _payload_length = payloadLength;
    
    outputType[0] = OUTPUT_TYPE_ARRAY;
    for (int i=0; i<32; i++) {
        _out_buffer[i] = 0;
        _in_buffer[i] = 0;
    }
}
void nBlock_SimulatedRadio::triggerInput(nBlocks_Message message) {
    if ((_mode == RADIO_MODE_RX_ONLY) && (message.dataType == OUTPUT_TYPE_ARRAY)) {
        char * data_array = (char *)(message.pointerValue);
        for (uint32_t i=0; i<message.dataLength; i++) {
            _out_buffer[i] = data_array[i];
        }
        output[0] = (uint32_t)(&_out_buffer);
        available[0] = message.dataLength;
    }
    
    else if (_mode == RADIO_MODE_TX_ONLY) {
        switch (message.dataType) {
            case OUTPUT_TYPE_INT:
            case OUTPUT_TYPE_FLOAT:
                break;

            case OUTPUT_TYPE_STRING:
                strcpy(_out_buffer, message.stringValue);
                output[0] = (uint32_t)(&_out_buffer);
                available[0] = message.dataLength;
                break;

            case OUTPUT_TYPE_ARRAY:
                char * data_array = (char *)(message.pointerValue);
                for (uint32_t i=0; i<message.dataLength; i++) {
                    _out_buffer[i] = data_array[i];
                }
                output[0] = (uint32_t)(&_out_buffer);
                available[0] = message.dataLength;
                break;
                
        }
    }
}

