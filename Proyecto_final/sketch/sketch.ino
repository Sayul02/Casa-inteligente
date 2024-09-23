#include "DataLogger.h"

void setup() {
  Serial.begin(115200);
  SENSORES.sensores_init();
  ACTUADORES.actuadores_init();
  INFORMACION.setup_WiFi();
  INFORMACION.set_MQTT_server();
  INFORMACION.set_MQTT_callback();
  MSD.MicroSD_init();
  Myrtc.RTC_init();
  Myrfid.rfid_init();
}

void loop() {
  Tareas.actualizar_tareas();
  Tareas.tarea_SENSORES();
  Tareas.tarea_actuadores();
  Tareas.tarea_LCD();
  Tareas.tarea_MSD();
  Myrtc.show_time();
  Myrfid.verificar_tarjeta_presente();
}

