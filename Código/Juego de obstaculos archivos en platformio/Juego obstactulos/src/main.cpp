#include <Arduino.h>


#define DATA_PIN 4 // Pin de datos (DS) 
#define LATCH_PIN 2 // Pin de latch (ST_CP) 
#define CLOCK_PIN 3 // Pin de reloj (SH_CP)  TL 23
#define TL 28
int a[5] = {851, 681, 510, 340, 170}; //voltaje botones
byte b[5] = {16, 8, 4, 2, 1}; //valor botones
//byte bits[8] = {128, 64, 32, 16, 8, 4, 2, 1}; va así 7 a 0 en matriz
int pa=4; //inicio del numero de la columna
int arriba=0; //boton 1
int derecha=0; //boton 2
int abajo=0; //boton 3
int izquierda=0; //boton 4
int reset=0; //boton 5
int fila=7; //inicio fila actual
byte col=16; //inicio valor led bits[4]
int filapass=0; //fila con el valor anterior
byte colpass=1; //inicio valor led con el valor anterior
byte entControl = 0; //numero de control
bool valorImpreso = false; //solo para leer una vez el primer valor de un boton apretado
byte ValorA; //Es el valor anterior despues de que el led avanzara.

 

byte Mwin[8] = { //matriz de win
  B11111111, // Columna 0
  B10000001, // Columna 1
  B10000001, // Columna 2
  B10000001, // Columna 3
  B10000001, // Columna 4
  B10000001, // Columna 5
  B10000001, // Columna 6
  B11111111  // Columna 7
};

byte Mlost[8] = {
  B00000000, // Columna 0
  B10000001, // Columna 1
  B01000010, // Columna 2
  B00100100, // Columna 3
  B00011000, // Columna 4
  B00100100, // Columna 5
  B01000010, // Columna 6
  B10000001 // Columna 7 i
};

byte Minicio[8] = { //matriz de inicio
  B00000000, // Columna 0
  B00000000, // Columna 1
  B00000000, // Columna 2
  B00000000, // Columna 3
  B00000000, // Columna 4
  B00000000, // Columna 5
  B00000000, // Columna 6
  B00000000  // Columna 7
};

byte Mobs[8];  //matriz de obstaculo conforme avance el led
byte MobsO[8]; //matriz de obstaculo original


void actMwin(){ //cuando gane que matriz se va a mostrar
  for(int i=0; i<8; i++){//recorre la matriz almacenando los leds que se van a prender
    digitalWrite(LATCH_PIN , LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, Mwin[i]);
  }
  digitalWrite(LATCH_PIN, HIGH); //Se prende la matriz
    delay(500);
    
}

void actMlost(){ //cuando pierda que matriz se va a mostrar
  for(int i=0; i<8; i++){//recorre la matriz almacenando los leds que se van a prender
    digitalWrite(LATCH_PIN , LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, Mlost[i]);
  }
  digitalWrite(LATCH_PIN, HIGH);//Se prende la matriz
    delay(500);

}


void generarMatrizAleatoria() {
  randomSeed(analogRead(A0)); // Inicializa la semilla del generador de números aleatorios
  byte resultado; // Inicializa el byte
  int posicion; // Genera un número aleatorio entre 0 y 7
  
  for(int i=0; i<=6; i=i+2){
    resultado = 0xFF; //es un byte 11111111
    posicion = random(0, 8); //Genera un número aleatorio entre 0 y 7
    bitWrite(resultado, posicion, 0); //la variable en donde se va a escribir, el bit del numero donde se escribira, el bit que se quiere escribir
    Mobs[i]=resultado; //se almacena el bit generado
  }
    for(int i=1; i<=7; i=i+2){
    resultado = B00000000;
    Mobs[i]=resultado;
  }

  for(int i = 0; i < 8; i++) {
    MobsO[i] = Mobs[i]; //la matriz original almacena la generada para poder mover el led
    }
}

void reinicioC(){ //cuando gane se va a generar otra matriz de obstaculo diferente y se reinician los valores
  for(int i=0; i<8; i++){
    Mobs[i]=MobsO[i];
  }
  fila=7; //inicio fila
  col=16; //inicio valor led bits[4]
  filapass=0; //inicio fila
  colpass=1;
  pa=4;
  
  generarMatrizAleatoria();
}

void actMatriz(int fila, byte col){ //actualizar posición del led
   
  for(int i=0; i<8; i++){ //Se va a recorer la matriz dependiendo de como se vaya a mover el led
    if(fila == i){ //si la fila act es igual a i que es el numero de fila
       Minicio[i]=col; //la matriz en 0 se iguala al valor de la columna
      if(filapass == fila && colpass == col){ //si la fila de la posicion pasada es igual a la actual 
        // y si el valor de la columna actual es igual al de la pasada significa que 
        //filas iguales y columnas iguales, no se movio el led
        Mobs[i]=ValorA; //Se almacena el valor actual de la matriz
        }else{//fila y columna actual son diferentes
          if(Minicio[i] & Mobs[i]){ //Se compara bit por bit
            //Minicio almacena solo la posicion del led contra Mobs de los obstaculos si la posicion de led (1) resulta que en su posicion de obstaculos tambien es 1 entonces
            //ya perdio por que significa que choco con un obstaculo, se imprime la M de lost y se reinicia el juego
            
            actMlost();
            reinicioC();
          }else{ //si ningun bit es igual se combina la pisicion del led con la de los obscatulos
            Mobs[i] |= Minicio[i];            
            ValorA=Mobs[i]; //El valor actual se actualiza pues avanzo el led
            
          }
        }
        digitalWrite(LATCH_PIN , LOW);
        shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, Mobs[i]);
       }else{// si fila y i no son iguales es decir que es el resto de la matriz
        Minicio[i]=0; //sigue en 0
        Mobs[filapass]=MobsO[filapass]; //Mobs actualiza los valores pasados con fila del Mobs original
        digitalWrite(LATCH_PIN , LOW);
        shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, Mobs[i]); 
        }
    }
  digitalWrite(LATCH_PIN, HIGH);
    delay(200);  //Se actualiza
}



void setup() {
  // put your setup code here, to run once:
  pinMode(DATA_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
  generarMatrizAleatoria();//Se genera la matriz aleatori7a
}

void loop() {
  // put your main code here, to run repeatedly:
  int valor = 0;
  int linf = 0;
  int lsup = 0;
  int i=0;
 
   
  actMatriz(fila, col); //se actualiza la posición actual
   filapass = fila; //Se almacena como posicion pasada
  colpass = col; //Se almacena como posicion pasada
  

  
  valor = analogRead(A1); //Se lee el pin de los botones
  //Serial.println(valor);
   
  if(valor >0 && !valorImpreso){ //Si ya se leyo debe de ser false valor impreso
    valorImpreso=true; //como ya lo leyo se cambia a true
 
    for ( i = 0; i < 5; i++){ //Se recorre el valor del A1 para determinar que control es
      linf = a[i] - TL;
      lsup = a[i] + TL;
      if(valor >= linf && valor <= lsup){
        
        entControl = b[i]; 
        if(entControl == 16){
          arriba=1;//de acuerdo al valor se determina si es arriba, abajo, dere o izq o reset
          
          }else{//arr
            if(entControl == 8){
              derecha=1;
              
              }else{//de
                if(entControl == 4){
                  abajo=1;
                  
                  }else{//ab
                    if(entControl == 2){
                      izquierda=1;
                      
                      }else{
                        if(entControl == 1){
                          reset=1;
                          
                      }
                      }
                  }//iz
              }
           } // IF END BOTONES
      }
    } // FOR END
 
    if(arriba == 1){ //Se leen los valores
      if(fila > 0){//si la fila es mayor de 0 y fue arriba se disminuye
        fila--;
        
      }else{
        
       }
       if(fila == 0){//si es igual a 0 entonces ya llego a la meta 
           actMwin();
           reinicioC();
           }
       arriba = 0; //se inicia en 0 de nuevo
       valorImpreso = false; //valor impreso sera false para leer el sig movimiento

       }else{
        if(derecha == 1){
          if(col < 129 && col > 1){ //si la col es menor 129 y si es mayor a 1
            col = col >> 1; //Se disminuye el valor de columna
            pa--;
            }else{
              if(col == 1){//si col es igual a 1 entonces sera 1 para que no desaparesca de la matriz
                //De esta forma queda definido el margen ene l que entra el led
                  col = 1;
                }
            }
            derecha = 0; 
            valorImpreso = false;
            

         }else{
          if(izquierda == 1){ 
            if(col > 0 && pa < 7){//si la col es menor 0 y si pa <7 entonces pa aumentara
              pa++;
               col= 1 << pa; //Esto para almacenar el valor de la col de acuerdo a su posicion 1 << 5 = 32
               }else{
                 pa= 7; //pa sera 7 para poder respetar los limites de la matriz
                }
                izquierda = 0;
                valorImpreso = false;
                
                }else{
                  if(abajo == 1){
                    if(fila < 7){ //si la fila es menor que 7 se aumenta fila
                      fila ++;
                      }else{
                        fila = 7; //sino fila sera 7 para respetar los limites de la matriz
                        }
                        abajo = 0;
                        valorImpreso = false;
                        
                  }else{
                    if(reset==1){
                      
                      reinicioC();
                      valorImpreso = false;
                      
                      reset = 0;
                    }
                }
         }
         }
      } //IFS END
      valorImpreso = false;
  }
   
} //LOOP