#include <Wire.h> // I2C

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(0x68); // I2C address of the MPU-6050
  Wire.write(0x6B); // 0x6B | PWR_MGMT_1 --> MPU-6050 Register Map
  Wire.write(0);  // set to zero(wakes up the MPU 6050)
  Wire.endTransmission(true);
}

void loop() {
  int16_t acc_rawX, acc_rawY, acc_rawZ;
  int h, m, s;
  int previous_valueX, previous_valueY, previous_valueZ;
  int now_valueX, now_valueY, now_valueZ;
  
  Wire.beginTransmission(0x68);
  Wire.write(0x3B); // starting with register 0x3B | ACCEL_XOUT_H --> MPU-6050 Register Map
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 6, true);  // request a total of 6 registers

  acc_rawX = Wire.read()<<8|Wire.read(); // 0x3B | 59 | ACCEL_XOUT_H and 0x3C | 60 | ACCEL_XOUT_L
  acc_rawY = Wire.read()<<8|Wire.read(); // 0x3D | 61 | ACCEL_YOUT_H and 0x3E | 62 | ACCEL_YOUT_L
  acc_rawZ = Wire.read()<<8|Wire.read(); // 0x3F | 63 | ACCEL_ZOUT_H and 0x40 | 64 | ACCEL_ZOUT_L

  Wire.beginTransmission(0x68);
  Wire.write(0x43); // starting with register 0x43 | GYRO_XOUT_H --> MPU-6050 Register Map
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 6, true);

  do{
    Serial.print("|||||||||||| \n");
    Serial.print("|");
    Serial.print(" : ");
    Serial.print("|");
    Serial.print(" : ");
    Serial.print("g");
    Serial.print("\n");

    //  previous value
    if(acc_rawX > 0){
      previous_valueX = 1;
    }
    else{
      previous_valueX = -1;
    }
        if(acc_rawY > 0){
      previous_valueY = 1;
    }
    else{
      previous_valueY = -1;
    }    
    if(acc_rawZ > 0){
      previous_valueZ = 1;
    }
    else{
      previous_valueZ = -1;
    }
    Serial.print("Phase1");

    delay(5000);
    
    //  now value
    if(acc_rawX > 0){
      now_valueX = 1;
    }
    else{
      now_valueX = -1;
    }
    if(acc_rawY > 0){
      now_valueY = 1;
    }
    else{
      now_valueY = -1;
    }
        if(acc_rawZ > 0){
      now_valueZ = 1;
    }
    else{
      now_valueZ = -1;
    }
    Serial.print("Phase2");
  }while(previous_valueX != now_valueX && previous_valueY != now_valueY && previous_valueZ != now_valueZ);



  // in X positive Richtung
  if(acc_rawX > 14000){
  h = 0, m = 0, s = 10;
  countdown(h, m, s);
  }

  // in X negative Richtung
  if(acc_rawX < -14000){
  h = 0, m = 0, s = 15;
  countdown(h, m, s);
  }

  //  in Y positive Richtung
  if(acc_rawY > 14000){
  h = 0, m = 0, s = 20;
  countdown(h, m, s);
  }

  //  in Y negative Richting
  if(acc_rawY < -14000){
  h = 0, m = 0, s = 25;
  countdown(h, m, s);
  }

  // in Z positive Richtung
  if(acc_rawZ > 14000){
  h = 0, m = 0, s = 30;
  countdown(h, m, s);
  }

  //  in Z negative Richtung
  if(acc_rawZ < -14000){
  h = 0, m = 0, s = 35;
  countdown(h, m, s);
  }
  
  else{
  Serial.print("bljaaaaaaaaaaaa");
  }
  // put your main code here, to run repeatedly:
  print_raw_value(acc_rawX, acc_rawY, acc_rawZ);
}

void print_raw_value(int16_t acc_rawX, int16_t acc_rawY, int16_t acc_rawZ){
  Serial.print(acc_rawX);
  Serial.print("\t");
  Serial.print(acc_rawY);
  Serial.print("\t");
  Serial.print(acc_rawZ);
  Serial.print("\t");
  Serial.print("\n");
}

void countdown(int h, int m, int s){
  for(int hour = h; hour >= 0; hour--){
    for(int minute = m; minute >= 0; minute--){
      if(minute == 0 && h > 0){
        m = 59;
      }
      for(int sec = s; sec >= 0; sec--){
        if(sec == 0){
          s = 59;
        }
      delay(1000);
      Serial.print(hour);
      Serial.print(" : ");
      Serial.print(minute);
      Serial.print(" : ");
      Serial.print(sec);
      Serial.print("\n");
      }
    }
  }
}
