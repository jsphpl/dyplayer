#include "DYPlayer.h"
#include "hardware/uart.h"

namespace DY {

class Player : public DYPlayer {
public:
    Player(uart_inst_t *instance, uint8_t txPin, uint8_t rxPin) :
        instance(instance), txPin(txPin), rxPin(rxPin){};
    void begin();
    void serialWrite(uint8_t *buffer, uint8_t len);
    bool serialRead(uint8_t *buffer, uint8_t len);

private:
    uart_inst_t *instance;
    uint8_t txPin;
    uint8_t rxPin;
};

} // namespace DY
