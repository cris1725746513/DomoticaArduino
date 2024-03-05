

#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

#include <Espalexa.h>
#include <WiFiManager.h> 



int pin_cocina = 13;        //1
int pin_master = 12;         //2
int pin_visita = 14;        //3
int pin_sala = 27;         //4
int pin_frente = 26;        //5
int pin_patio = 25;        //6   

int btn_cocina = 23;
int btn_master = 22 ;
int btn_visita = 21;
int btn_sala = 19;
int btn_frente = 18;
int btn_patio = 4;

int last_cocina = 0;
int last_master = 0 ;
int last_visita = 0;
int last_sala = 0;
int last_frente = 0;
int last_patio = 0;



Espalexa alexita;

void FuncionCocina(uint8_t brightness);
void FuncionMaster(uint8_t brightness);
void FuncionVisita(uint8_t brightness);
void FuncionSala(uint8_t brightness);
void FuncionFrente(uint8_t brightness);
void FuncionPatio(uint8_t brightness);

int FuncionCambioFisicoLuces(int ambiente , int luz, int ultimateState, int device);

void setup() {
  Serial.begin(115200);
  WiFiManager wm;
  pinMode(pin_cocina, OUTPUT);
  pinMode(pin_master, OUTPUT);
  pinMode(pin_visita, OUTPUT);
  pinMode(pin_sala, OUTPUT);
  pinMode(pin_frente, OUTPUT);
  pinMode(pin_patio, OUTPUT);

  pinMode(btn_cocina, INPUT_PULLDOWN);
  pinMode(btn_master, INPUT_PULLDOWN);
  pinMode(btn_visita, INPUT_PULLDOWN);
  pinMode(btn_sala, INPUT_PULLDOWN);
  pinMode(btn_frente, INPUT_PULLDOWN);
  pinMode(btn_patio, INPUT_PULLDOWN);
  
   bool res;
     res = wm.autoConnect(); // auto generated AP name from chipid
    if(!res) {
        Serial.println("Failed to connect");
    } 
    else { 
        Serial.println("connected...yeey :)");
          Serial.print("IP address: ");
          Serial.println(WiFi.localIP());
          alexita.addDevice("cocina", FuncionCocina);
          alexita.addDevice("master", FuncionMaster);
          alexita.addDevice("visita", FuncionVisita);
          alexita.addDevice("Sala", FuncionSala);
          alexita.addDevice("frente", FuncionFrente);
  alexita.addDevice("patio", FuncionPatio);
  alexita.begin();
    }
  
}

void loop() {
  alexita.loop();
  delay(1);
    
  last_cocina = FuncionCambioFisicoLuces(btn_cocina ,pin_cocina, last_cocina , 0);
  last_master = FuncionCambioFisicoLuces(btn_master ,pin_master, last_master , 1);
  last_visita = FuncionCambioFisicoLuces(btn_visita ,pin_visita, last_visita , 2);
  last_sala = FuncionCambioFisicoLuces(btn_sala ,pin_sala, last_sala , 3);
  last_frente = FuncionCambioFisicoLuces(btn_frente ,pin_frente, last_frente , 4);
  last_patio = FuncionCambioFisicoLuces(btn_patio ,pin_patio, last_patio , 5);
    
}


 
void FuncionCocina(uint8_t brightness){
   if (brightness) {digitalWrite(pin_cocina, 1);}
  else { digitalWrite(pin_cocina, 0); }}

  
void FuncionMaster(uint8_t brightness){
  if (brightness) { digitalWrite(pin_master, 1);}
  else {digitalWrite(pin_master, 0); }}
  
void FuncionVisita(uint8_t brightness){
  if (brightness) {digitalWrite(pin_visita, 1);}
  else {digitalWrite(pin_visita, 0);}}
 
void FuncionSala(uint8_t brightness){
  if (brightness) {digitalWrite(pin_sala, 1);} 
  else {digitalWrite(pin_sala, 0);}}
    
void FuncionFrente(uint8_t brightness){
  if (brightness) { digitalWrite(pin_frente, 1); }
  else {digitalWrite(pin_frente, 0);}}
  
void FuncionPatio(uint8_t brightness){
  if (brightness) {digitalWrite(pin_patio, 1);}
  else {digitalWrite(pin_patio, 0); }}

int FuncionCambioFisicoLuces(int ambiente , int luz, int ultimateState, int device){
    if(digitalRead(ambiente) != ultimateState){
        EspalexaDevice* foco = alexita.getDevice(device);
        int Nivel = foco->getValue();
        int valor = Nivel > 0 ? 1 : 0;
            if(valor == 1){
                  digitalWrite(luz, LOW);
                  foco->setPercent(0);
                  delay(300);
                  return 0;
              }else {
                  digitalWrite(luz, HIGH);
                  foco->setPercent(255);
                  delay(300);
                  return 1;
                }
      }else {
        return ultimateState;
      }
}
