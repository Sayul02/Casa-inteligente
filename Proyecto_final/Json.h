#ifndef Json_h
#define Json_h

class JsonClass{
  public: 
  String FAC_Json (String, String, String, String, String);
  String Acceso_Json(String, String, String);
};

String JsonClass::FAC_Json(String msg1, String msg2, String msg3, String msg4, String msg5){
  String temp = "";
  DynamicJsonDocument JSON ( 1024 );         /* Objeto donde se alamcenará el JSON */
  JSON [ "DHT" ]["temperatura"] = msg1;  
  JSON["DHT"]["humedad"] = msg2;         /* Almacena números enteros o flotantes */         
  JSON [ "PIR_PATIO" ] = msg3;
  JSON [ "PIR_CALLE" ] = msg4; 
  JSON["FECHA"] = msg5; 
  serializeJsonPretty( JSON, temp); 
  return temp;
}

String JsonClass::Acceso_Json(String msg1, String msg2, String msg3){
  String temp = "";
  DynamicJsonDocument JSON ( 1024 );         /* Objeto donde se alamcenará el JSON */
  JSON [ "FECHA" ]["fecha"] = msg1;  
  JSON["FECHA"]["hora"] = msg2;         /* Almacena números enteros o flotantes */         
  JSON [ "ID" ] = msg3;
  serializeJsonPretty( JSON, temp); 
  return temp;
}
#endif