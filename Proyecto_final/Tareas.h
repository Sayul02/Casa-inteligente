#ifndef Tareas_h
#define Tareas_h
/*****************************************************************************************
*      DESCRIPCIÓN DE LA LIBRERÍA: El objetivo de esta librería es generar tiempos de    *
*       espera de ejecución sin la implementación de la función "delay()".               *
******************************************************************************************/
#define TIEMPO_RTC 1000
#define TIEMPO_MSD 10000
#define TIEMPO_LCD 2000
#define TIEMPO_SENSORES 200
#define TIEMPO_ACTUADORES 100
long lastMsg = 0;

class millis_tasks {

  public:
    uint64_t  
             tiempo_actual = 0,      // Contador de tiempo que tendrá múltiplos de TIEMPO.
             tiempo_anterior_RTC = 0,
             tiempo_anterior_MSD = 0,
             tiempo_anterior_LCD = 0,
             tiempo_anterior_SENSORES = 0,
             tiempo_anterior_actuadores = 0;
    
  public:
    void actualizar_tareas (void );  // Función que actualiza el conteo obtenido de la función "millis()".
    // void tarea_RTC ( void );
    void tarea_MSD ( void );
    void tarea_LCD ( void );
    void tarea_SENSORES ( void );
    void tarea_actuadores(void);
 
};


// void millis_tasks :: tarea_RTC ( void ) {
//   if ( ( tiempo_actual - tiempo_anterior_RTC ) >= TIEMPO_RTC ){

//      Serial.println ( "2.- Ejecutando tarea 2" );
//      tiempo_anterior_RTC = tiempo_actual;

//   }
 
// }

 void millis_tasks :: tarea_MSD ( void ) {
   if ( ( tiempo_actual - tiempo_anterior_MSD ) >= TIEMPO_MSD ){
     Serial.println(F("Ejecutando tarea MSD"));
     Myrfid.verificar_tarjeta_presente();
     MSD.ReadFile();
    tiempo_anterior_MSD = tiempo_actual;
   }
 
 }

 void millis_tasks :: tarea_LCD ( void ) {
   if ( ( tiempo_actual - tiempo_anterior_LCD ) >= TIEMPO_LCD ){
      int temperatura = SENSORES.dht_temperatura();
      int humedad = SENSORES.dht_humedad();
      ACTUADORES.show_LCD("Temperatura=" + String(temperatura) + "c", "Humedad = " + String(humedad) + "%");
      tiempo_anterior_LCD = tiempo_actual;
   }
 }

void millis_tasks :: tarea_SENSORES ( void ) {
  if ( ( tiempo_actual - tiempo_anterior_SENSORES ) >= TIEMPO_SENSORES ){
    Myrtc.get_time();
    int temperatura = SENSORES.dht_temperatura();
    int humedad = SENSORES.dht_humedad();
    int pir_patio = SENSORES.pir_read(PIN_PIR_PATIO);
    int pir_calle = SENSORES.pir_read(PIN_PIR_CALLE);
    String fecha = Myrtc.format_date();
    
    String json = Json.FAC_Json(String(temperatura), String(humedad), String(pir_patio), String(pir_calle), fecha);
    
    INFORMACION.reconnect_MQTT();
    long now = millis();
    if (now - lastMsg > 5000) {
      lastMsg = now;
      INFORMACION.publish_MQTT(json);
  } 
    tiempo_anterior_SENSORES = tiempo_actual;
  }
}

void millis_tasks :: tarea_actuadores ( void ) {
  if ( ( tiempo_actual - tiempo_anterior_actuadores ) >= TIEMPO_ACTUADORES ){
    ACTUADORES.encender_luces();
    tiempo_anterior_actuadores = tiempo_actual;
  }
}


/*~~~~~~~~~~~~~~~~~~~~~~~~ actualizar_tareas - Función que actualiza el contador de "millis()" ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_tasks :: actualizar_tareas ( void ) {

  tiempo_actual = millis( );

}

#endif