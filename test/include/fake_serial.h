#ifndef FAKE_SERIAL_H
#define FAKE_SERIAL_H
#include <iostream>

class SerialPort {
public:
	void begin(int baudrate){};
	void printf(const char *fmt, ...){};
	void println(const char *str){
		std::cout << str << std::endl;
	};
	void println(String str){
		std::cout << str << std::endl;
	};
	void flush(){};
	uint8_t read(){};
	void write(uint8_t byte){};
	bool available(){ return true;};
};

typedef SerialPort& USARTSerial;

extern SerialPort Serial;
extern SerialPort Serial1;

#endif // FAKE_SERIAL_H
