#include <htu21d.h>

htu21d m_htu21d;

void setup() {
  htu21_battery_status battery_status;
  htu21_status status;

  Serial.begin(9600);

  Serial.println("==== TE Connectivity ====");
  Serial.println("======== HTU21D =========");
  Serial.println("======== Measure =========");

  // WeatherShield MUX control pins
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  // MUX select HTU21D
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);

  m_htu21d.begin();
  status = m_htu21d.get_battery_status(&battery_status);
  Serial.println(battery_status == htu21_battery_ok ? "Battery OK"
                                                    : "Battery LOW");

  m_htu21d.set_i2c_master_mode(htu21_i2c_hold);
}

void loop() {
  htu21_status status;
  float temperature;
  float humidity;
  boolean connected;

  connected = m_htu21d.is_connected();
  if (connected) {
    Serial.println(connected ? "Sensor Connected" : "Sensor Disconnected");

    status = m_htu21d.read_temperature_and_relative_humidity(&temperature,
                                                             &humidity);

    Serial.print("---Temperature = ");
    Serial.print(temperature, 1);
    // Serial.print((char)176);
    Serial.println("C");

    Serial.print("---Humidity = ");
    Serial.print(humidity, 1);
    Serial.println("%RH");
  } else {
    Serial.println(connected ? "Sensor Connected" : "Sensor Disconnected");
  }

  delay(1000);
}
