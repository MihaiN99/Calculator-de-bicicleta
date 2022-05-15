// Necula Mihai
// Giurgea George
//332AB

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

Adafruit_MPU6050 mpu;
long t,t1;
double delta,distanta=0,viteza;
double err;
int N=1000;
float v;
double val;
void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10);

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
    ;
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);
  double acc;
  for(int i=0;i<N;i++)
  {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    acc+=a.acceleration.x;
    
    }
    
  err=acc/N;
  lcd.init();
  lcd.clear();
  lcd.backlight();
}

void loop() {


  t=millis();
  
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x-err);
  val=a.acceleration.x-err;
  Serial.println(" m/s^2");
  
  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");
  

  Serial.println("");
  t1=millis();
  delta=t1-t;
  
  viteza=delta*val;
  
  distanta+=viteza*delta;
  v=double(viteza/1000);
  if(viteza<0) viteza=0;
  if(distanta<0) distanta=0;
  Serial.print(distanta);
  
  lcd.setCursor(0, 0);
  lcd.print("V:");
  lcd.print(v,2);
  lcd.print(" a:");
  lcd.print(val,2);
  
  lcd.setCursor(0,1 );
  lcd.print("D:");
  lcd.print(distanta/1000);
  lcd.print(" T:");
  lcd.print(temp.temperature);
  
  /*Serial.println();
  Serial.print("viteza ");
  Serial.print(viteza/1000);
  Serial.print("m/s");
  Serial.println();
  
  Serial.print("distanta :");
  Serial.print(distanta/1000);
  Serial.print("m");
  Serial.println();*/
  
  
  delay(300);
}
