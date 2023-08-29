
// #include <iostream>
// #include <drivers.h>
// #include <Debug.h>
// #include "pico/stdlib.h"

// int main(int argc, char const *argv[])
// {
//     pico::Drivers *drivers = new pico::Drivers();
//     // pico::Drivers *drivers = pico::Drivers::getDrivers();

//     stdio_init_all();
//     gpio_init(25);
//     gpio_set_dir(25, GPIO_OUT);

//     drivers->remote.initialize();
//     while (1)
//     {
//         // Turn On LED
//         gpio_put(25, 1); // Set pin 25 to high
//         printf("LED on!\n");
//         sleep_ms(250);
//         // Turn Off LED
//         gpio_put(25, 0); // Set pin 25 to high.
//         printf("LED off!\n");
//         sleep_ms(250);
//         // try
//         // {
//         //     throw std::invalid_argument("received negative value");
//         // }
//         // catch (const std::invalid_argument &e)
//         // {
//         //     std::cout << "throw" << std::endl;
//         // }

//         // ====
//         std::cout << "." << std::endl;
//         drivers->remote.read(); // Reading the remote before we check if it is connected yet or not.
//         if (drivers->remote.isConnected())
//         {
//             std::cout << "remote: " << drivers->remote.getChannel(pico::communication::serial::Remote::Channel::LEFT_HORIZONTAL) << std::endl;
//         }
//         tight_loop_contents();
//     }
// }

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
extern "C"
{
#include "rm_pico_dev/lib/can2040/src/can2040.h"
}
#include "RP2040.h"

typedef struct can2040_msg CANMsg;
static struct can2040 cbus;


static void
can2040_cb(struct can2040 *cd, uint32_t notify, struct can2040_msg *msg)
{
}

static void
PIOx_IRQHandler(void)
{
    can2040_pio_irq_handler(&cbus);
}

const char *pilk = "pilk";
void canbus_setup(void)
{
    uint32_t pio_num = 0;
    uint32_t sys_clock = 125000000, bitrate = 1000000;
    uint32_t gpio_rx = 4, gpio_tx = 5;

    // Setup canbus
    can2040_setup(&cbus, pio_num);
    can2040_callback_config(&cbus, can2040_cb);

    // Enable irqs
    irq_set_exclusive_handler(PIO0_IRQ_0_IRQn, PIOx_IRQHandler);
    NVIC_SetPriority(PIO0_IRQ_0_IRQn, 1);
    NVIC_EnableIRQ(PIO0_IRQ_0_IRQn);

    // Start canbus
    can2040_start(&cbus, sys_clock, bitrate, gpio_rx, gpio_tx);
}

void setup_msg(uint32_t id)
{
    CANMsg msg = {0};
    msg.dlc = 8;
    msg.id = id; // 0x204;
    // clear buffer
    msg.data[0] = 0x00;
    msg.data[1] = 0xef;
    msg.data[2] = 0x00;
    msg.data[3] = 0xef;
    msg.data[4] = 0x00;
    msg.data[5] = 0xef;
    msg.data[6] = 0x00;
    msg.data[7] = 0xef;

    // for (int i = 0; i < 5; i++)
    // {
    //     msg.data[i] = (int)*(pilk + i);
    //     printf("%x,",msg.data[i]);
    // }
    // puts("");
    int res = can2040_transmit(&cbus, &msg);
    printf("Sending! PILK returned: %d\n", res);
}

int main()
{
    stdio_init_all();
    canbus_setup();

    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true)
    {
        // setup_msg(0x208);
        // setup_msg(0x207);
        // setup_msg(0x206);
        // setup_msg(0x205);
        // setup_msg(0x204);
        // setup_msg(0x203);
        // setup_msg(0x202);
        // setup_msg(0x201);
        setup_msg(0x200);

        // printf("LED ON!\n");
        // gpio_put(LED_PIN, 1);
        // sleep_ms(250);
        // // printf("LED OFF!\n");
        // gpio_put(LED_PIN, 0);
        // sleep_ms(250);
        tight_loop_contents();
    }

    return 0;
}
