// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// LSM9DSO
// This code is designed to work with the TCS3414_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Color?sku=LSM9DSO_I2CS#tabs-0-product_tabset-2

#include <application.h>
#include <spark_wiring_i2c.h>

// LSM9DSO Gyro I2C address is 6A(106)
#define Addr_Gyro 0x6A
// LSM9DSO Accl I2C address is 1E(30)
#define Addr_Accl 0x1E

int xAccl = 0, yAccl =  0, zAccl = 0, xGyro = 0, yGyro = 0, zGyro = 0, xMag = 0, yMag = 0, zMag = 0;
void setup() 
{
    // Set variable
    Particle.variable("i2cdevice", "LSM9DS0");
    Particle.variable("xAccl", xAccl);
    Particle.variable("yAccl", yAccl);
    Particle.variable("zAccl", zAccl);
    Particle.variable("xGyro", xGyro);
    Particle.variable("yGyro", yGyro);
    Particle.variable("zGyro", zGyro);
    Particle.variable("xMag", xMag);
    Particle.variable("yMag", yMag);
    Particle.variable("zMag", zMag);
    
    // Initialise I2C communication as MASTER
    Wire.begin();
    // Initialise Serial Communication, set baud rate = 9600
    Serial.begin(9600);
    
    // Start I2C Transmission
    Wire.beginTransmission(Addr_Gyro);
    // Select control register 1
    Wire.write(0x20);
    // Data rate = 95Hz, X, Y, Z-Axis enabled, power on  
    Wire.write(0x0F);
    // Stop I2C Transmission
    Wire.endTransmission();
    
    // Start I2C Transmission
    Wire.beginTransmission(Addr_Gyro);
    // Select control register 4
    Wire.write(0x23);
    // Full-scale 2000 dps, continuous update
    Wire.write(0x30);
    // Stop I2C Transmission
    Wire.endTransmission();
    
    // Start I2C Transmission
    Wire.beginTransmission(Addr_Accl);
    // Select control register 1
    Wire.write(0x20);
    // Acceleration data rate = 100Hz, X, Y, Z-Axis enabled, power on
    Wire.write(0x67);
    // Stop I2C Transmission on the device
    Wire.endTransmission();
    
    // Start I2C Transmission
    Wire.beginTransmission(Addr_Accl);
    // Select control register 2
    Wire.write(0x21);
    // Full scale selection +/- 16g
    Wire.write(0x20);
    // Stop I2C Transmission
    Wire.endTransmission();
    
    // Start I2C Transmission
    Wire.beginTransmission(Addr_Accl);
    // Select control register 5
    Wire.write(0x24);
    // Magnetic high resolution, output data rate = 50Hz
    Wire.write(0x70);
    // Stop I2C Transmission
    Wire.endTransmission();
    
    // Start I2C Transmission
    Wire.beginTransmission(Addr_Accl);
    // Select control register 6
    Wire.write(0x25);
    // Magnetic full-scale +/- 12 gauss
    Wire.write(0x60);
    // Stop I2C Transmission
    Wire.endTransmission();
    
    // Start I2C Transmission
    Wire.beginTransmission(Addr_Accl);
    // Select control register 7
    Wire.write(0x26);
    // Normal mode, magnetic continuous conversion mode
    Wire.write(0x00);
    // Stop I2C Transmission
    Wire.endTransmission();
    delay(300);
}

void loop()
{
    unsigned int data[6];
    
    for(int i = 0; i < 6; i++)
    {
        // Start I2C Transmission
        Wire.beginTransmission(Addr_Gyro);
        // Select data register
        Wire.write((40+i));
        // Stop I2C Transmission
        Wire.endTransmission();
        
        // Request 1 byte of data
        Wire.requestFrom(Addr_Gyro, 1);
     
        // Read 6 bytes of data
        // xGyro lsb, xGyro msb, yGyro lsb, yGyro msb, zGyro lsb, zGyro msb
        if(Wire.available() == 1)
        {
            data[i] = Wire.read();
        }
    }
    
    // Convert the data
    xGyro = ((data[1] * 256) + data[0]);
    if (xGyro > 32767)
    {
        xGyro -= 65536;
    }
    yGyro = ((data[3] * 256) + data[2]);
    if (yGyro > 32767)
    {
        yGyro -= 65536;
    }
    zGyro = ((data[5] * 256) + data[4]);
    if (zGyro > 32767)
    {
        zGyro -= 65536;
    }

    for(int i = 0; i < 6; i++)
    {
        // Start I2C Transmission
        Wire.beginTransmission(Addr_Accl);
        // Select data register
        Wire.write((40+i));
        // Stop I2C Transmission
        Wire.endTransmission();
        
        // Request 1 byte of data
        Wire.requestFrom(Addr_Accl,1);
        
        // Read 6 bytes of data
        // xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
        if(Wire.available() == 1)
        {
            data[i] = Wire.read();
        }
    }
    
    // Convert the data
    xAccl = ((data[1] * 256) + data[0]);
    if(xAccl > 32767)
    {
      xAccl -= 65536;
    }
  
    yAccl = ((data[3] * 256) + data[2]);
    if(yAccl > 32767)
    {
      yAccl -= 65536;
    }
    
    zAccl = ((data[5] * 256) + data[4]);
    if(zAccl > 32767)
    {
      zAccl -= 65536;
    }
    
    for(int i = 0; i < 6; i++)
    {
        // Start I2C Transmission
        Wire.beginTransmission(Addr_Accl);
        // Select data register
        Wire.write((8 + i));
        // Stop I2C Transmission
        Wire.endTransmission();
        
        // Request 1 byte of data
        Wire.requestFrom(Addr_Accl, 1);
        
        // Read 6 bytes of data
        // xMag lsb, xMag msb, yMag lsb, yMag msb
        // zMag lsb, zMag msb
        if(Wire.available() == 1)
        {
            data[i] = Wire.read();
        }
    }
    
    // Convert the data
    xMag = ((data[1] * 256) + data[0]);
    if(xMag > 32767)
    {
      xMag -= 65536;
    }
    yMag = ((data[3] * 256) + data[2]);
    if(yMag > 32767)
    {
      yMag -= 65536;
    }
    zMag = ((data[5] * 256) + data[4]);
    if(zMag > 32767)
    {
      zMag -= 65536;
    }
    
    // Output data to dashboard
    Particle.publish("X-Axis of rotation : ", String(xGyro));
    Particle.publish("Y-Axis of rotation : ", String(yGyro));
    Particle.publish("Z-Axis of rotation : ", String(zGyro));
    delay(1000);
    Particle.publish("Acceleration in X-Axis : ", String(xAccl));
    Particle.publish("Acceleration in Y-Axis : ", String(yAccl));
    Particle.publish("Acceleration in Z-Axis : ", String(zAccl));
    delay(1000);
    Particle.publish("Magnetic field in X-Axis : ", String(xMag));
    Particle.publish("Magnetic field in Y-Axis : ", String(yMag));
    Particle.publish("Magnetic filed in Z-Axis : ", String(zMag));
    delay(1000);
}
