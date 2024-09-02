#include <Wire.h>

#define MPU6050_ADDR          0x68  
#define PWR_MGMT_1            0x6B  
#define GYRO_XOUT_H           0x43  

void setup() {
  Serial.begin(9600);
  Wire.begin();

  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(PWR_MGMT_1);
  Wire.write(0);
  Wire.endTransmission();
}

void loop() {
  int gyroyaw = readGyroYaw();
  float yawRate = gyroyaw / 131.0;
  
  static float yaw = 0;
  yaw += yawRate * 0.01;
  
  Serial.print("Yaw: ");
  Serial.println(yaw);
  
  delay(25); 
}

int readGyroYaw() {
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(GYRO_XOUT_H + 4);
  Wire.endTransmission(false);
  
  Wire.requestFrom(MPU6050_ADDR, 2, true);
  int16_t gyroYaw = Wire.read() << 8 | Wire.read();
  
  return gyroYaw;
}