#ifndef __NB_SIMULATEDRADIO
#define __NB_SIMULATEDRADIO

#include "nworkbench.h"

#define RADIO_MODE_TX_ONLY 0
#define RADIO_MODE_RX_ONLY 1
#define RADIO_MODE_BIDIR   2

class nBlock_SimulatedRadio: public nBlockSimpleNode<1> {
public:
    nBlock_SimulatedRadio(
        uint32_t mode,
        uint32_t payloadLength
    );
    void triggerInput(nBlocks_Message message);
private:
    uint32_t _mode;
    uint32_t _payload_length;
    char _out_buffer[64];
    char _in_buffer[64];
};

#endif
