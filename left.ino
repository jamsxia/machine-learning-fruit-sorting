/*
 * @Description: -
 * @Version: -
 * @Author: Fox_benjiaming
 * @Date: 2021-01-08 14:12:35
 * @LastEditors: Fox_benjiaming
 * @LastEditTime: 2021-01-24 11:58:34
 */
#include <SoftwareSerial.h>

#define PIN_MOTOER              5
#define PIN_LIGHT_0             13
#define PIN_LIGHT_1             12
#define PIN_LIGHT_2             11
#define PIN_SERIAL_RIGHT_RX     2    
#define PIN_SERIAL_RIGHT_TX     3    
#define PIN_SERIAL_MIDELE_RX    6    
#define PIN_SERIAL_MIDELE_TX    7    
#define PIN_SERIAL_AI_RX        8    
#define PIN_SERIAL_AI_TX        9    

SoftwareSerial ser_right(PIN_SERIAL_RIGHT_RX, PIN_SERIAL_RIGHT_TX);
SoftwareSerial ser_middle(PIN_SERIAL_MIDELE_RX, PIN_SERIAL_MIDELE_TX);
SoftwareSerial ser_ai(PIN_SERIAL_AI_RX, PIN_SERIAL_AI_TX);

void motor_init(void);
void motor_control(uint8_t run);
void light_init(void);
uint8_t light_check(uint8_t num);

void setup(void) {
    Serial.begin(115200);
    ser_right.begin(115200);
    ser_middle.begin(115200);
    ser_ai.begin(115200);
    motor_init();
    light_init();
}

    // Serial.print(light_check(0));
    // Serial.print(' ');
    // Serial.print(light_check(1));
    // Serial.print(' ');
    // Serial.print(light_check(2));
    // Serial.println("");
    // delay(100);

bool flag_light_2 = true;
bool motor_run = true;
// '0'-bad, '1'-big_good, '2'-small_goot
char apple_good[5] = {1, 1, 0, 0, 0};
char apple_big[5] = {0, 1, 0, 0, 0};
char apple_small[5] = {1, 0, 0, 0, 0};
char flag_bad_apple = 0;
uint8_t light_1_count = 0;
uint8_t light_2_count = 0;
uint8_t i = 0;

void loop(void) {
    // light_0 on
    if (light_check(0) == true)
    {
        delay(100);
        if (light_check(0) == true)
        {
            while (light_check(0) == true)
            {
                motor_control(true);
            }
            delay(200);
            motor_control(false);
        back_0:
            ser_right.write("1");
            ser_right.listen();
            i = 0;
            while (ser_right.available() == 0 && i < 50)
            {
                delay(100);
                i++;
            }
            if (i == 50)
                goto back_0;
            ser_right.read();
            motor_control(true);
        }
    }
    // light_1 on
    if (light_check(1) == true)
    {
        delay(100);
        if (light_check(1) == true)
        {
            motor_control(false);
        back_1:
            ser_ai.write("1");
            ser_ai.listen();
            i = 0;
            while (ser_ai.available() == 0 && i < 50)
            {
                delay(100);
                i++;
            }
            if (i == 50)
                goto back_1;
            ser_ai.read();
            // flag_bad_apple = ser_ai.read();
            // if (flag_bad_apple == '0')
            // {
            //     apple_good[light_1_count] = 1;
            // }
            // else
            // {
            //     apple_good[light_1_count] = 0;
            // }
            motor_control(true);
            if ((light_1_count > 0) && (apple_small[light_1_count-1] == 1) && (apple_good[light_1_count-1] == 1))
            // if ((light_1_count > 0) && (apple_small[light_1_count-1] == 1))
            {
                Serial.print("small down\r\n");
                motor_control(false);
            back_2:
                switch (light_1_count-1)
                {
                case 0:
                    ser_middle.write("0");
                    break;
                case 1:
                    ser_middle.write("1");
                    break;
                case 2:
                    ser_middle.write("2");
                    break;
                case 3:
                    ser_middle.write("3");
                    break;
                case 4:
                    ser_middle.write("4");
                    break;
                default:
                    break;
                }
                // ser_ai.write("small down\r\n");
                ser_middle.listen();
                i = 0;
                while (ser_middle.available() == 0 && i < 50)
                {
                    i++;
                    delay(100);
                }
                if (i == 50)
                    goto back_2;
                ser_middle.read();
                Serial.print("small up\r\n");
                // ser_ai.write("small up\r\n");
                motor_control(true);
            }
            while (light_check(1) == true)
            {
                motor_control(true);
            }
            motor_control(true);
            if ((light_1_count > 1) && (apple_big[light_1_count-2] == 1) && (apple_good[light_1_count-2] == 1))
            // if ((light_1_count > 1) && (apple_big[light_1_count-2] == 1))
            {
                delay(500);
                motor_control(false);
                Serial.print("big down\r\n");
            back_3:
                switch (light_1_count-2)
                {
                case 0:
                    ser_middle.write("0");
                    break;
                case 1:
                    ser_middle.write("1");
                    break;
                case 2:
                    ser_middle.write("2");
                    break;
                case 3:
                    ser_middle.write("3");
                    break;
                case 4:
                    ser_middle.write("4");
                    break;
                default:
                    break;
                }
                // ser_ai.write("big down\r\n");
                ser_middle.listen();
                i = 0;
                while (ser_middle.available() == 0 && i < 50)
                {
                    i++;
                    delay(100);
                }
                if (i == 50)
                    goto back_3;
                ser_middle.read();
                Serial.print("big up\r\n");
                // ser_ai.write("big up\r\n");
                motor_control(true);
            }
            light_1_count++;
            Serial.println(light_1_count);
        }
    }
    if ((light_check(2) == true) && (flag_light_2 == false))
    {
        delay(100);
        if (light_check(2) == true)
        {
            flag_light_2 = true;
            light_2_count++;
            // ser_ai.write("get end\r\n");
            Serial.print("get end\r\n");
        }
    }
    if ((light_check(2) == false) && (flag_light_2 == true))
    {
        delay(100);
        if (light_check(2) == false)
        {
            flag_light_2 = false;
        }
    }
    if (light_2_count >= 5)
    {
        motor_control(false);
    }
}

/**
 * @brief: Initializes port and status related to motor 
 * @param None
 * @return None
 */
void motor_init(void) {
    pinMode(PIN_MOTOER, OUTPUT);
    motor_control(true);
}

/**
 * @brief:Control motor 
 * @param {uint8_t} run: 0->stop, not 0->run
 * @return {void}
 */
void motor_control(uint8_t run) {
    if (run == false) {
        analogWrite(PIN_MOTOER, 255);
    }
    else {
        analogWrite(PIN_MOTOER, 128);
    }
}

/**
 * @brief: Initializes port of light 
 * @param None
 * @return None
 */
void light_init(void) {
    pinMode(PIN_LIGHT_0, INPUT);
    pinMode(PIN_LIGHT_1, INPUT);
    pinMode(PIN_LIGHT_2, INPUT);
}

/**
 * @brief: Check light output
 * @param None
 * @return {uint8_t} 0->not checked, 1->checked
 */
uint8_t light_check(uint8_t num) {
    uint8_t pin;

    switch (num)
    {
    case 0:
        pin = PIN_LIGHT_0;
        break;
    case 1:
        pin = PIN_LIGHT_1;
        break;
    case 2:
        pin = PIN_LIGHT_2;
        break;
    default:
        break;
    }
    if (pin == PIN_LIGHT_0)
    {
        if (digitalRead(pin) == HIGH) {
            return false;
        }
        else if (digitalRead(pin) == LOW) {
            return true;
        }
    }
    else
    {
        if (digitalRead(pin) == HIGH) {
            return true;
        }
        else if (digitalRead(pin) == LOW) {
            return false;
        }
    }
}
