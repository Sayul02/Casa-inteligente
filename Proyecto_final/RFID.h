#ifndef RFID_h
#define RFID_h

#include <SPI.h>
#include <MFRC522.h>
#include <ESP32Servo.h>

#define SS_PIN 13
#define RST_PIN 21

class rfid {
  private:
    MFRC522 mfrc522;
    Servo miServo;

  public:
    bool tarjetaAutorizada = false;
    unsigned long tiempoUltimaLectura = 0;
    const unsigned long tiempoEspera = 5000;
    // Define dos conjuntos de códigos autorizados
    byte uidAutorizado1[4] = {0x01, 0x63, 0x30, 0x1D};
    byte uidAutorizado2[4] = {0xA3, 0xF8, 0x8C, 0xAC};

    rfid() : mfrc522(SS_PIN, RST_PIN) {}

    void rfid_init();
    void verificar_tarjeta_presente();
    bool verificar_tarjeta_autorizada(byte *uid, byte bufferSize);
    void mover_servo(int angulo);
    void imprimir_uid(byte *buffer, byte bufferSize);
    String obtener_uid(byte *buffer, byte bufferSize);
};

void rfid::rfid_init() {
  SPI.begin();         // Iniciar la comunicación SPI
  mfrc522.PCD_Init();  // Iniciar el lector RFID
}

void rfid::verificar_tarjeta_presente() {
  // Verificar si hay una tarjeta presente
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Mostrar el número de identificación de la tarjeta
    Serial.print("Número de identificación de la tarjeta: ");
    imprimir_uid(mfrc522.uid.uidByte, mfrc522.uid.size);
    Serial.println();

    // Verificar si la tarjeta es autorizada
    if (verificar_tarjeta_autorizada(mfrc522.uid.uidByte, mfrc522.uid.size)) {
      tarjetaAutorizada = true;
      tiempoUltimaLectura = millis();  // Actualizar el tiempo de la última lectura
      mover_servo(0);  // Mover el servo a 0 grados (puede cambiar según tu configuración)
      Myrtc.get_time();
      String uid = obtener_uid(mfrc522.uid.uidByte, mfrc522.uid.size);
      String json = Json.Acceso_Json(Myrtc.format_date(), Myrtc.format_time(), uid);
      MSD.SaveFile (json);
    }

    delay(1000);  // Esperar un segundo antes de leer la próxima tarjeta
  }

  // Verificar si ha pasado el tiempo de espera y revertir el estado del servo
  if (tarjetaAutorizada && (millis() - tiempoUltimaLectura >= tiempoEspera)) {
    tarjetaAutorizada = false;
    mover_servo(75);  // Volver el servo a la posición original (75 grados)
  }
}

bool rfid::verificar_tarjeta_autorizada(byte *uid, byte bufferSize) {
  // Comparar el UID de la tarjeta con los dos conjuntos de UID autorizados
  return (memcmp(uid, uidAutorizado1, sizeof(uidAutorizado1)) == 0 || memcmp(uid, uidAutorizado2, sizeof(uidAutorizado2)) == 0);
}

void rfid::mover_servo(int angulo) {
  miServo.write(angulo);  // Mover el servo al ángulo especificado
  delay(500);  // Pequeño retardo para asegurar que el servo tenga tiempo de moverse
}

void rfid::imprimir_uid(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

String rfid::obtener_uid(byte *buffer, byte bufferSize) {
  String uid = ""; // Inicializar una cadena vacía para guardar el UID
  
  // Iterar sobre el buffer que contiene el UID
  for (byte i = 0; i < bufferSize; i++) {
    // Convertir cada byte en su representación hexadecimal y agregarlo a la cadena
    uid += String(buffer[i], HEX);
  }
  
  return uid; // Devolver la cadena que contiene el UID
}

#endif
