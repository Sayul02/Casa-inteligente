#ifndef Sensores_h
#define Sensores_h


#define PIN_PIR_CALLE 13
#define PIN_PIR_PATIO 4


class Sensores{
  public:
    void sensores_init(void);
    bool pir_read(int);
    int dht_humedad(void);
    int dht_temperatura(void);
};


void Sensores::sensores_init(void){
   pinMode(PIN_PIR_CALLE, INPUT);
   pinMode(PIN_PIR_PATIO, INPUT);
   dht.begin();
}

bool Sensores::pir_read(int pin_pir){
  return digitalRead(pin_pir);
}

int Sensores::dht_humedad(void){
  return dht.readHumidity();
}

int Sensores::dht_temperatura(void){
  return dht.readTemperature();
}


#endif 