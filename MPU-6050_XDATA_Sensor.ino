#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
byte status = 200;

typedef struct measurement {
    float accX;
    float accY;
    float accZ;
    float gyrX;
    float gyrY;
    float gyrZ;
};

typedef union measurementContainer {
    struct measurement meas[5];
    byte bytes[120];
};

void setup(void) {

    Serial1.begin(9600);

    if (mpu.begin()) {
        status = 100;
    }
    mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
    mpu.setGyroRange(MPU6050_RANGE_2000_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

    delay(100);
}

measurementContainer container;
measurement meas;
unsigned long counter = 0;
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
bool stateActivated[] = {false, false, false, false, false};

void loop() {
    currentMillis = millis();
    counter = currentMillis - previousMillis;

    if ((counter <= 200 || counter > 1000) && !stateActivated[0]) {
        previousMillis = currentMillis;
        stateActivated[4] = false;
        stateActivated[0] = true;

        obtainMeasurement(&meas);
        container.meas[0] = meas;
        //Serial1.println("1st Measurement");
    }

    if (counter > 200 && counter <= 400 && !stateActivated[1]) {
        stateActivated[0] = false;
        stateActivated[1] = true;

        obtainMeasurement(&meas);
        container.meas[1] = meas;
        //Serial1.println("2nd Measurement");
    }

    if (counter > 400 && counter <= 600 && !stateActivated[2]) {
        stateActivated[1] = false;
        stateActivated[2] = true;

        obtainMeasurement(&meas);
        container.meas[2] = meas;
        //Serial1.println("3rd Measurement");
    }

    if (counter > 600 && counter <= 800 && !stateActivated[3]) {
        stateActivated[2] = false;
        stateActivated[3] = true;

        obtainMeasurement(&meas);
        container.meas[3] = meas;
        //Serial1.println("4th Measurement");
    }

    if (counter > 800 && counter <= 1000 && !stateActivated[4]) {
        stateActivated[3] = false;
        stateActivated[4] = true;
        obtainMeasurement(&meas);
        container.meas[4] = meas;

        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);

        //Serial1.println("5th Measurement and firing XDATA");
        Serial1.print("xdata=4201");
        Serial1.print("S=");
        Serial1.print(status);
        Serial1.print("T=");
        if (temp.temperature => 10.0 || temp.temperature <= -10.0) Serial1.print("0");
        if (temp.temperature > 0.0) Serial1.print("0");
        Serial1.print(temp.temperature, 2);
        Serial1.print("D=");
        Serial1.write(container.bytes, 120);
        Serial1.println("");
    }
}

void obtainMeasurement(measurement *meas) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    meas->accX = a.acceleration.x;
    meas->accY = a.acceleration.y;
    meas->accZ = a.acceleration.z;

    meas->gyrX = g.gyro.x;
    meas->gyrY = g.gyro.y;
    meas->gyrZ = g.gyro.z;
}