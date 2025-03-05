#include <unistd.h>
#include "serialPort/SerialPort.h"
#include "unitreeMotor/unitreeMotor.h"


int main() {

  SerialPort  serial("/dev/ttyUSB0");
  MotorCmd    cmd;
  MotorData   data;

  while(true) 
  {
    cmd.motorType = MotorType::A1;
    data.motorType = MotorType::A1;
    cmd.mode  = queryMotorMode(MotorType::A1,MotorMode::FOC);
    cmd.id    = 0;
    cmd.kp    = 0.0;
    cmd.kd    = 2;
    cmd.q     = 0.0;
    cmd.dq    = -0.628*queryGearRatio(MotorType::A1)*5;
    cmd.tau   = 0.0;
    serial.sendRecv(&cmd,&data);

    std::cout <<  std::endl;
    std::cout <<  "motor.q: "    << data.q    <<  std::endl;
    std::cout <<  "motor.temp: "   << data.temp   <<  std::endl;
    std::cout <<  "motor.W: "      << data.dq      <<  std::endl;
    std::cout <<  "motor.merror: " << data.merror <<  std::endl;
    std::cout <<  std::endl;

    usleep(200);
  }

}
