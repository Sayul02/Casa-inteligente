#ifndef Actuadores_h
#define Actuadores_h

#define PIN_LED_CALLE 12
#define PIN_LED_PATIO 5
#define PIN_LED_COCINA 15
#define PIN_LED_SALA 25
#define PIN_LED_BANIO 14
#define PIN_LED_PASILLO 16
#define PIN_SERVO_COCHERA 26
#define PIN_VENTILADOR 33
int pos = 0;

class Actuadores {
  public:
    void actuadores_init(void);
    void encender_luces(void);
    void control_luces(String);
    void show_LCD (String, String);
};

void Actuadores::actuadores_init(void) {
  pinMode(PIN_LED_CALLE, OUTPUT);
  pinMode(PIN_LED_PATIO, OUTPUT);
  pinMode(PIN_LED_COCINA, OUTPUT);
  pinMode(PIN_LED_SALA, OUTPUT);
  pinMode(PIN_LED_BANIO, OUTPUT);
  pinMode(PIN_LED_PASILLO, OUTPUT);
  servoCochera.attach(PIN_SERVO_COCHERA);
  pinMode(PIN_VENTILADOR, OUTPUT);
  lcd.init();
  lcd.backlight();
}

void Actuadores::encender_luces(void) {
  if (SENSORES.pir_read(PIN_PIR_CALLE) == 1) {
    digitalWrite(PIN_LED_CALLE, HIGH);
  }
  else {
    digitalWrite(PIN_LED_CALLE, LOW);
  }

  if (SENSORES.pir_read(PIN_PIR_PATIO) == 1) {
    digitalWrite(PIN_LED_PATIO, HIGH);
  }
  else {
    digitalWrite(PIN_LED_PATIO, LOW);
  }
}

void Actuadores::control_luces(String mensaje) {
  if ( mensaje == "luzSala encender") {
    digitalWrite(PIN_LED_SALA, HIGH);
  }
  else if ( mensaje == "luzSala apagar") {
    digitalWrite(PIN_LED_SALA, LOW);
  }

  if ( mensaje == "luzPasillo encender") {
    digitalWrite(PIN_LED_PASILLO, HIGH);
  }
  else if ( mensaje == "luzPasillo apagar") {
    digitalWrite(PIN_LED_PASILLO, LOW);
  }

  if ( mensaje == "luzCocina encender") {
    digitalWrite(PIN_LED_COCINA, HIGH);
  }
  else if ( mensaje == "luzCocina apagar") {
    digitalWrite(PIN_LED_COCINA, LOW);
  }

  if ( mensaje == "luzBanio encender") {
    digitalWrite(PIN_LED_BANIO, HIGH);
  }
  else if ( mensaje == "luzBanio apagar") {
    digitalWrite(PIN_LED_BANIO, LOW);
  }

  if ( mensaje == "puerta_cochera encender") {
    for (pos = 5; pos <= 180; pos += 1) {
      servoCochera.write(pos);    // llamar al servo para poner en la posicion 'pos'
      delay(15);             
    }
  }
  else if ( mensaje == "puerta_cochera apagar") {
    for (pos = 180; pos >= 5; pos -= 1) {
      servoCochera.write(pos);    // tell servo to go to position in variable 'pos'
      delay(15);             
    }
  }

  if ( mensaje == "ventilador encender") {
    digitalWrite(PIN_VENTILADOR, HIGH);
  }
  else if ( mensaje == "ventilador apagar") {
    digitalWrite(PIN_VENTILADOR, LOW);
  }


}

void Actuadores::show_LCD(String msg1, String msg2) {
  lcd.clear();
  lcd.setCursor (0, 0);
  lcd.print(msg1);
  lcd.setCursor(0, 1);
  lcd.print(msg2);
}

#endif