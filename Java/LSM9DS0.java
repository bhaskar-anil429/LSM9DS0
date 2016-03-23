// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// LSM9DS0
// This code is designed to work with the LSM9DS0_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Accelorometer?sku=LSM9DS0_I2CS#tabs-0-product_tabset-2

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class LSM9DS0
{
	public static void main(String args[]) throws Exception
	{
		// Create I2CBus
		I2CBus bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, LSM9DSO GYRO I2C address is 0x6A(106)
		I2CDevice device_gyro = bus.getDevice(0x6A);

		// Select control register1
		// X, Y and Z axis enabled, power on mode, data rate o/p 95 Hz
		device_gyro.write(0x20, (byte)0x0F);
		// Select control register4
		// Full scale 2000 dps, continuous update
		device_gyro.write(0x23, (byte)0x30);
		Thread.sleep(300);

		// Read 6 bytes of data
		// xGyro lsb, xGyro msb, yGyro lsb, yGyro msb, zGyro lsb, zGyro msb
		byte[] data = new byte[6];
		data[0] = (byte)device_gyro.read(0x28);
		data[1] = (byte)device_gyro.read(0x29);
		data[2] = (byte)device_gyro.read(0x2A);
		data[3] = (byte)device_gyro.read(0x2B);
		data[4] = (byte)device_gyro.read(0x2C);
		data[5] = (byte)device_gyro.read(0x2D);

		// Convert the data
		int xGyro = ((data[1] & 0xFF) * 256 + (data[0] & 0xFF)) ;
		if(xGyro > 32767)
		{
			xGyro -= 65536;

		int yGyro = ((data[3] & 0xFF) * 256 + (data[2] & 0xFF)) ;
		if(yGyro > 32767)
		{
			yGyro -= 65536;

		int zGyro = ((data[5] & 0xFF) * 256 + (data[4] & 0xFF)) ;
		if(zGyro > 32767)
		{
			zGyro -= 65536;
		}

		// Get I2C device, LSM9DSO ACCELERO MAGNETO I2C address is 0x1E(30)
		I2CDevice device_acc_mag = bus.getDevice(0x1E);

		// Select control register1
		// X, Y and Z axis enabled, power on mode, accelero data rate o/p 100 Hz 
		device_acc_mag.write(0x20, (byte)0x67);
		// Select control register2
		// Full scale selection, +/- 16g
		device_acc_mag.write(0x21, (byte)0x20);
		// Select control register5
		// Magnetic high resolution, o/p data rate 50 Hz
		device_acc_mag.write(0x24, (byte)0x70);
		// Select control register6
		// Magnetic full scale selection, +/- 12 gauss
		device_acc_mag.write(0x25, (byte)0x60);
		// Select control register7
		// Normal mode, magnetic continuous conversion mode
		device_acc_mag.write(0x26, (byte)0x00);
		Thread.sleep(300);

		// Read 6 bytes of data
		// xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
		data[0] = (byte)device_acc_mag.read(0x28);
		data[1] = (byte)device_acc_mag.read(0x29);
		data[2] = (byte)device_acc_mag.read(0x2A);
		data[3] = (byte)device_acc_mag.read(0x2B);
		data[4] = (byte)device_acc_mag.read(0x2C);
		data[5] = (byte)device_acc_mag.read(0x2D);

		// Convert the data
		int xAccl = ((data[1] & 0xFF) * 256 + (data[0] & 0xFF)) ;
		if(xAccl > 32767)
		{
			xAccl -= 65536;
		}	

		int yAccl = ((data[3] & 0xFF) * 256 + (data[2] & 0xFF)) ;
		if(yAccl > 32767)
		{
			yAccl -= 65536;
		}

		int zAccl = ((data[5] & 0xFF) * 256 + (data[4] & 0xFF)) ;
		if(zAccl > 32767)
		{
			zAccl -= 65536;
		}

		// Read 6 bytes of data
		// xMag lsb, xMag msb, yMag lsb, yMag msb, zMag lsb, zMag msb
		data[0] = (byte)device_acc_mag.read(0x08);
		data[1] = (byte)device_acc_mag.read(0x09);
		data[2] = (byte)device_acc_mag.read(0x0A);
		data[3] = (byte)device_acc_mag.read(0x0B);
		data[4] = (byte)device_acc_mag.read(0x0C);
		data[5] = (byte)device_acc_mag.read(0x0D);

		int xMag = ((data[1] & 0xFF) * 256 + (data[0] & 0xFF));
		if(xMag > 32767)
		{
			xMag -= 65536;
		}	

		int yMag = ((data[3] & 0xFF) * 256 + (data[2] & 0xFF)) ;
		if(yMag > 32767)
		{
			yMag -= 65536;
		}

		int zMag = ((data[5] & 0xFF) * 256 + (data[4] & 0xFF)) ;
		if(zMag > 32767)
		{
			zMag -= 65536;
		}

		// Output data to screen
		System.out.printf("X-axis Of Rotation : %d %n", xGyro);
		System.out.printf("Y-axis Of Rotation : %d %n", yGyro);
		System.out.printf("Z-axis Of Rotation : %d %n", zGyro);
		System.out.printf("Acceleration in X-Axis : %d %n", xAccl);
		System.out.printf("Acceleration in Y-Axis : %d %n", yAccl);
		System.out.printf("Acceleration in Z-Axis : %d %n", zAccl);
		System.out.printf("Magnetic field in X-Axis : %d %n", xMag);
		System.out.printf("Magnetic field in Y-Axis : %d %n", yMag);
		System.out.printf("Magnetic field in Z-Axis : %d %n", zMag);
	}
}
