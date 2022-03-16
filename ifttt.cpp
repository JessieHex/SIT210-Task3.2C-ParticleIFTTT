#include <BH1750.h>

#define PRINT 1

BH1750 sensor(0x23, Wire);
float prev_light_level = 0;

void setup()
{
  Serial.begin(9600);
  sensor.begin();
  sensor.set_sensor_mode(BH1750::forced_mode_high_res2);
}

void loop()
{
  sensor.make_forced_measurement();

  float cur_light_level = sensor.get_light_level();
  if (prev_light_level < 1000 and cur_light_level > 1000)
    Particle.publish("sunlight", "on", PRIVATE);
  if (prev_light_level > 1000 and cur_light_level < 1000)
    Particle.publish("sunlight", "off", PRIVATE);
  
  // print to serial for debugging
  if (PRINT)
  {
      time_t t = Time.now();
      Time.zone(11);
      Serial.print(Time.timeStr(t));
      Serial.println(String::format(" previous: %f, current: %f", prev_light_level, cur_light_level));
  }
  
  prev_light_level = cur_light_level; // update prev light level

  delay(30000);               // Wait for 30 seconds

}
