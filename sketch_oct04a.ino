// Author: Douglas R Violante

//Carrega a biblioteca Wire
#include<Wire.h>
 
//Endereco I2C do MPU6050
const int MPU=0x68;

typedef struct
{
  //Variaveis para armazenar valores dos sensores
  float GyroX;
  float GyroY;
  float GyroZ;
  
  float AcelX;
  float AcelY;
  float AcelZ;
  
  float TempMPU;
  
} estrutura_packet;

// Variavel Global
estrutura_packet packet; 


void InicializaMPU6050()
{

  //Inicializa o MPU-6050
  Wire.write(0); 
  Wire.endTransmission(true);
  
}

void lerGiroscopio(estrutura_packet* data)
{  
 

  //Armazena o valor dos sensores nas variaveis correspondentes
  data -> GyroX = Wire.read()<<8|Wire.read(); //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  data -> GyroY = Wire.read()<<8|Wire.read(); //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  data -> GyroZ = Wire.read()<<8|Wire.read(); //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

}

void lerAcelerometro(estrutura_packet* data)
{

 
  
   //Armazena o valor dos sensores nas variaveis correspondentes
  data -> AcelX = Wire.read()<<8|Wire.read(); //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  data -> AcelY = Wire.read()<<8|Wire.read(); //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  data -> AcelZ = Wire.read()<<8|Wire.read(); //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

}

void lerTemperaturaMPU(estrutura_packet* data)
{
  
  data -> TempMPU = (((Wire.read()<<8|Wire.read()) / 340.00) + 36.53); //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
}



void setup()
{
  
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 

      
}


void loop()
{
  
  
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  
  //Solicita os dados do sensor
  Wire.requestFrom(MPU,14,true); 

  lerAcelerometro( &packet );
  lerTemperaturaMPU( &packet );
  lerGiroscopio( &packet );


  Serial.println(packet.GyroX);
  Serial.println(packet.AcelX);
  Serial.println(packet.TempMPU);
  Serial.println("        ");
  
    
  //Aguarda 500 ms e reinicia o processo
  delay(500);
}
