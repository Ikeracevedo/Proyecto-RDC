/*
  Simulador de nodo IoT agrícola con ESP32
  Envía datos falsos por Serial en formato JSON cada 2 segundos.
*/

#include <Arduino.h>

#ifndef LED_BUILTIN
#define LED_BUILTIN 2  // LED del ESP32 (puede variar según la placa)
#endif

const char* NODE_ID = "nodeA";   // cambia a nodeB, nodeC, etc.
const unsigned long SEND_INTERVAL = 2000; // cada 2 segundos

// Función para generar ruido suave (simulación tipo “sensor real”)
float smoothNoise(float base, float amplitude, float period_ms) {
  float t = (millis() % (unsigned long)period_ms) / period_ms;
  float x = t * 2.0f * PI;
  return base + amplitude * sin(x);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println(F("{\"event\":\"boot\",\"msg\":\"ESP32 iniciado y simulando datos\"}"));
}

void loop() {
  static unsigned long last = 0;
  unsigned long now = millis();

  if (now - last >= SEND_INTERVAL) {
    last = now;

    // Variables simuladas
    float tempC = smoothNoise(24.0, 2.5, 11000.0);      // temperatura ambiente
    float humRel = smoothNoise(60.0, 10.0, 15000.0);    // humedad relativa
    int lux = 400 + (now / 100) % 600;                  // luminosidad simulada
    int co2ppm = 420 + (now / 250) % 600;               // CO₂ simulado
    float ph = smoothNoise(6.5, 0.3, 20000.0);          // pH simulado
    unsigned long ts = millis();

    // Formato JSON
    char buffer[256];
    snprintf(buffer, sizeof(buffer),
      "{\"node\":\"%s\",\"ts_ms\":%lu,"
      "\"temp_c\":%.2f,\"hum_rel\":%.1f,"
      "\"lux\":%d,\"co2_ppm\":%d,\"ph\":%.2f}",
      NODE_ID, ts, tempC, humRel, lux, co2ppm, ph);

    // Enviar por Serial
    Serial.println(buffer);

    // Parpadeo del LED para indicar envío
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
  }

  delay(5); // estabilidad del loop
}
