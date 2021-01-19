// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

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
    char bytes[120];
};

void setup(void) {
  Serial1.begin(9600);

  mpu.begin();
  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_2000_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  delay(100);
}

void loop() {

  //sensors_event_t a, g, temp;
  //mpu.getEvent(&a, &g, &temp);
  //Serial1.print(temp.temperature);

}

void obtainMeasurement(measurement *meas){
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    meas->accX = a.acceleration.x;
    meas->accY = a.acceleration.y;
    meas->accZ = a.acceleration.z;

    meas->gyrX = g.gyro.x;
    meas->gyrY = g.gyro.y;
    meas->gyrZ = g.gyro.z;
}