/*
 * @Description: -
 * @Version: -
 * @Author: Fox_benjiaming
 * @Date: 2021-01-08 16:37:32
 * @LastEditors: Fox_benjiaming
 * @LastEditTime: 2021-01-23 11:34:38
 */
#include <Servo.h>

#define PIN_SERVO_0     12
#define PIN_SERVO_1     11
#define PIN_SERVO_2     10
#define PIN_SERVO_3     9
#define PIN_SERVO_4     8

#define PIN_WEIGHT_DAT_0    7
#define PIN_WEIGHT_DAT_1    6
#define PIN_WEIGHT_DAT_2    5
#define PIN_WEIGHT_DAT_3    4
#define PIN_WEIGHT_DAT_4    3
#define PIN_WEIGHT_SCK      2

#define SERVO_ANGLE_0_UP        102
#define SERVO_ANGLE_0_DOWN      150
#define SERVO_ANGLE_1_UP        98
#define SERVO_ANGLE_1_DOWN      150
#define SERVO_ANGLE_2_UP        102
#define SERVO_ANGLE_2_DOWN      150
#define SERVO_ANGLE_3_UP        100
#define SERVO_ANGLE_3_DOWN      150
#define SERVO_ANGLE_4_UP        100
#define SERVO_ANGLE_4_DOWN      150

Servo servo_0, servo_1, servo_2, servo_3, servo_4;

void servo_init(void);
uint8_t weight_init(void);
uint32_t get_weights(uint8_t num);

void setup(void) {
    Serial.begin(115200);
    servo_init();
    weight_init();
    // servo_test();
}

char rec;

void loop(void) {
    while (Serial.available() > 0) {
        rec = Serial.read();
        if (rec >= '0' && rec <= '4') {
            servo_control(rec-'0', 0);
            delay(2000);
            servo_control(rec-'0', 1);
            delay(1000);
            Serial.write("1");
        }
    }
}

/**
 * @brief Initialize 4 servos and set position with 90 degrees
 * @param None
 * @return None
 */
void servo_init(void) {
    servo_0.attach(PIN_SERVO_0);
    servo_1.attach(PIN_SERVO_1);
    servo_2.attach(PIN_SERVO_2);
    servo_3.attach(PIN_SERVO_3);
    servo_4.attach(PIN_SERVO_4);
    servo_0.write(SERVO_ANGLE_0_UP);
    servo_1.write(SERVO_ANGLE_1_UP);
    servo_2.write(SERVO_ANGLE_2_UP);
    servo_3.write(SERVO_ANGLE_3_UP);
    servo_4.write(SERVO_ANGLE_4_UP);
}

void servo_control(uint8_t num, uint8_t up) {
    Servo servo_tmp;
    uint8_t up_value, down_value;

    switch (num)
    {
    case 0:
        servo_tmp = servo_0;
        up_value = SERVO_ANGLE_0_UP;
        down_value = SERVO_ANGLE_0_DOWN;
        break;
    case 1:
        servo_tmp = servo_1;
        up_value = SERVO_ANGLE_1_UP;
        down_value = SERVO_ANGLE_1_DOWN;
        break;
    case 2:
        servo_tmp = servo_2;
        up_value = SERVO_ANGLE_2_UP;
        down_value = SERVO_ANGLE_2_DOWN;
        break;
    case 3:
        servo_tmp = servo_3;
        up_value = SERVO_ANGLE_3_UP;
        down_value = SERVO_ANGLE_3_DOWN;
        break;
    case 4:
        servo_tmp = servo_4;
        up_value = SERVO_ANGLE_4_UP;
        down_value = SERVO_ANGLE_4_DOWN;
        break;
    default:
        break;
    }
    servo_tmp.write((up == 0) ? down_value : up_value);
}

uint8_t weight_init(void) {
    pinMode(PIN_WEIGHT_SCK, OUTPUT);
    pinMode(PIN_WEIGHT_DAT_0, INPUT);
    pinMode(PIN_WEIGHT_DAT_1, INPUT);
    pinMode(PIN_WEIGHT_DAT_2, INPUT);
    pinMode(PIN_WEIGHT_DAT_3, INPUT);
    pinMode(PIN_WEIGHT_DAT_4, INPUT);
    digitalWrite(PIN_WEIGHT_SCK, HIGH);
}

uint32_t get_weights(uint8_t num) {
    uint32_t count = 0;
    uint8_t i = 0;
    uint8_t pin = 0;

    switch (num)
    {
    case 0:
        pin = PIN_WEIGHT_DAT_0;
        break;
    case 1:
        pin = PIN_WEIGHT_DAT_1;
        break;
    case 2:
        pin = PIN_WEIGHT_DAT_2;
        break;
    case 3:
        pin = PIN_WEIGHT_DAT_3;
        break;
    case 4:
        pin = PIN_WEIGHT_DAT_4;
        break;
    default:
        break;
    }

    digitalWrite(PIN_WEIGHT_SCK, LOW);
    delayMicroseconds(10);
    while (digitalRead(pin) == HIGH);
    for (i = 0; i < 24; i++)
    {
        digitalWrite(PIN_WEIGHT_SCK, HIGH);
        count = count << 1;
        delayMicroseconds(10);
        digitalWrite(PIN_WEIGHT_SCK, LOW);
        if (digitalRead(pin) == HIGH)
            count++;
        delayMicroseconds(10);
    }
    digitalWrite(PIN_WEIGHT_SCK, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_WEIGHT_SCK, LOW);
    delayMicroseconds(10);
    digitalWrite(PIN_WEIGHT_SCK, HIGH);
    count = count ^ 0x800000;

    return count;
}

void servo_test(void)
{
    delay(2000);
    servo_control(0, 0);
    delay(2000);
    servo_control(0, 1);
    delay(2000);
    servo_control(1, 0);
    delay(2000);
    servo_control(1, 1);
    delay(2000);
    servo_control(2, 0);
    delay(2000);
    servo_control(2, 1);
    delay(2000);
    servo_control(3, 0);
    delay(2000);
    servo_control(3, 1);
    delay(2000);
    servo_control(4, 0);
    delay(2000);
    servo_control(4, 1);
    delay(2000);
}
