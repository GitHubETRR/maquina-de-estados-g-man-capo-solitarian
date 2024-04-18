#define PIN_LED 1
#define PIN_SWITCH 2
#define PRESS_SWITCH 3
#define RELEASE_SWITCH 4
#define TIEMPO_MINIMO 40
#define PUSH 0

void debounceFSM_init();    
void debounceFSM_update();  
void buttonPressed();     
void buttonReleased();    
bool botonPresionado(int boton);

typedef enum{
  BUTTON_UP,
  BUTTON_FALLING,
  BUTTON_DOWN,
  BUTTON_RAISING,
} debounceState_t;

debounceState_t estado;

unsigned long time = 0;

void setup(){
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_SWITCH, INPUT);
  debounceFSM_init();
  time = millis();
}

void loop() {
  debounceFSM_update();
}

void debounceFSM_init(){
  digitalWrite(PIN_LED, 0);
  if(botonPresionado(PIN_SWITCH))estado=BUTTON_DOWN;
  else estado=BUTTON_UP;
 
}

void debounceFSM_update(){
 

  switch (estado){
    case BUTTON_UP:
        if (botonPresionado(PIN_SWITCH))estado=BUTTON_FALLING;
        break;
        
    case BUTTON_FALLING:
        if(millis()-time>=TIEMPO_MINIMO){
          if (botonPresionado(PIN_SWITCH)){
            buttonPressed();
            estado = BUTTON_DOWN;  
          }
          else estado = BUTTON_UP;          
          time=millis();
        }
        break;
        
    case BUTTON_DOWN:
        if (!botonPresionado(PIN_SWITCH))estado=BUTTON_RAISING;
        break;
        
    case BUTTON_RAISING:
        if(millis()-time>=TIEMPO_MINIMO){
          if (!botonPresionado(PIN_SWITCH)){
            buttonReleased();
            estado = BUTTON_UP;  
          }
          else estado = BUTTON_DOWN;          
          time=millis();
        }
        break;
    
    default:
        debounceFSM_init();
        break;
  }
}

void buttonPressed(){
    digitalWrite(PRESS_SWITCH,!digitalRead(PRESS_SWITCH));
}

void buttonReleased(){
    digitalWrite(RELEASE_SWITCH,!digitalRead(RELEASE_SWITCH));
}

bool botonPresionado(int boton){
  if (digitalRead(boton) == PUSH)return (true);
  return (false);
}
