# TIK-boron (which really needs a new name)
This repository contains firmware that creates a general architecture for:
- connecting a reference instrument to a Particle device
- adding metadata such as time or geo-location to a data packet
- publishing the data to the cloud
- writing the data to an SD card
- logging errors to the cloud and SD card

# The Architecture
![](media/data_flow_diagram.png)

# Adding Instrument
The current firmware was being tested on a Teledyne T400 instrument which uses Modbus RTC over RS232 (Serial).

## Adding Instrument Using Modbus
To configure the firmware to work with a Modbus instrument:
1. Update T400_register.h (TODO: rename this file) with the appropriate input registers and discrete input registers.
2. Adjust the read rate in TIK_V0.ino (TODO: move to a separate config header file).
3. Adjust the baud_rate for ModbusMaster in TIK_V0.ino. __Note: The max baud rate for ModbusMaster on Argon is 57600. 115200 results in an invalid Modbus transaction.__

## Adding Other Instrument
To configure the firmware to work with a different protocol:
1. Modify the RawPacket class by adding the fields that you need.
2. Extend the InstrumentReaderInterface class. Your class must contain a Read() function that returns a PacketWithStatus with a RawPacket.
3. Extend the InstrumentDataFormatterInterface class. Your class must contain a Format() function that transforms a RawPacket into a DataPacket.
4. Update the __reader__ and __data_formatter__ unique_ptr in the main .ino file to initialize as members of your new classes.

# Adding Writers (Output methods)
The current firmware has a Serial Writer which simply prints the packet or error to the serial monitor and a CloudWriter which hasn't been tested on a device, but was mocked and unittested (please update if necessary). There is also a sketch for an SD Writer without an implementation.

## Adding Writer to the Main Program
To add a writer to the program:
1. In the main .ino file, initialize a unique_ptr to the desired reader.
2. You may need to pass an Options struct to the Writer. For example, for a Cloud Writer, set the batch number to 5 so it sends the data 5 packets at a time. For an Error Writer, set the batch number to 1 so it writes the data as soon as it receives it.
3. In setup(), call `outputter.AddWriter(std::move(your_writer_unique_ptr));`
4. If you want to configure the writer as an error writer, call `outputter.AddErrorWriter(std::move(your_writer_unique_ptr));``

## Adding Custom Writer
To add a custom writer:
1. Extend the WriterInterface class. It should contain a AddDataPacket class.
2. Add the writer to the main program (steps above).

# To Run Tests
From the test/ folder, run the command:
```
$ make TEST=true && ./build/allTests
```

# To Run a Local build
The test/run/ folder contains an example sketch modified to compile locally (there are a few Particle defined functions I wasn't able to mock).
From the test/ folder, run the command:
```
$ make && ./build/main
```
Be careful leaving <iostream> and std::cout calls from the local build in files which particle compiles.
You will get a very long error that looks like this:
```
/usr/local/gcc-arm-embedded/bin/../lib/gcc/arm-none-eabi/4.9.3/../../../../arm-none-eabi/lib/armv7-m/libg_nano.a(lib_a-readr.o): In function `_read_r':
readr.c:(.text._read_r+0x10): undefined reference to `_read'
collect2: error: ld returned 1 exit status
../../../build/module.mk:222: recipe for target 'target/workspace.elf' failed
make[1]: Leaving directory '/firmware/modules/photon/user-part'
make[1]: *** [target/workspace.elf] Error 1
../build/recurse.mk:11: recipe for target 'modules/photon/user-part' failed
make: *** [modules/photon/user-part] Error 2
```
See (rickkas7's answer)[https://community.particle.io/t/solved-problems-using-libraries-implemented-in-cpp/40038/4] for more information.
