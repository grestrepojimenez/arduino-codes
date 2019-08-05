
/* Algoritmo para control de Nivel, Temperatura y Humedad para el problema planteado */

float nivel=0, temp=0, humedad=0; //Variables para valores sensados
float  sensorTemp=1; // Definicion de lectura de sensores en puertos analogos (Variables auxiliares)
int resistencia=6, compuerta=5, deshumidificador=4 , ledNivel=7 , ledTempBaja=9 , ledTempAlta=10 , ledHumedad=11; // Definicion de pines para salidas (LEDS, Compuertas, Resistencia) (Variables auxiliares)
float medida=0;


/* Medir con sensor DHT11 */
#include <DHT.h> //Librerias para usar DHT11
#include <DHT_U.h> //Librerias para usar DHT11




// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 6
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11
// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  pinMode(ledNivel, OUTPUT);
  pinMode(ledTempBaja, OUTPUT);
  pinMode(ledTempAlta, OUTPUT);
  pinMode(ledHumedad, OUTPUT);
  pinMode(resistencia, OUTPUT);
  pinMode(compuerta, OUTPUT);
  pinMode(deshumidificador, OUTPUT);



   
   dht.begin();
   
  Serial1.begin(9600);
}

void loop() {
  nivel= medirNivel();
  temp = leerTemperatura();
  humedad= leerHumedad();
  mostrarEnPantalla(nivel, temp, humedad);
}

int medirNivel(){

  float distancia = ultrasoundRead(J6);

    if(distancia < 50){
       digitalWrite(ledNivel, HIGH);  //Encender LED indicador de alto nivel
      
       digitalWrite(compuerta, LOW);  //Cerrar compuerta de entrada de arroz
      }
      else{
        digitalWrite(ledNivel, LOW);   //Apagar LED indicador de alto nivel
        digitalWrite(compuerta, HIGH);  // Abrir compuerta de entrada de arroz
      }

    return distancia;
  }

int leerTemperatura(){

     int valorMedido = analogRead(sensorTemp); // lectura de sensor
     float millivoltios = (valorMedido / 1023.0) * 5000; //conversion a milivoltios
     float gradosCelsius = millivoltios / 10;  // conversion a grados centigrados
      
        float medida = gradosCelsius ;  
    

     if(medida <= 70){
       digitalWrite(ledTempBaja, HIGH);  //Encender LED indicador de baja temperatura
       digitalWrite(resistencia, HIGH);  //Encender Resistencia para calentar
      }
      else if (medida >= 80){
        digitalWrite(ledTempAlta, HIGH);   //Encender LED indicador de alta temperatura
         digitalWrite(resistencia, LOW);  //Apagar Resistencia para calentar
      }
      else{  // Si no se da ninguna de las conficiones anteriores apaga los leds indicadores 
        digitalWrite(ledTempAlta, LOW);
        digitalWrite(ledTempBaja, LOW); 
        digitalWrite(resistencia, LOW);  //Apagar Resistencia
      }


    return medida;
  }

    
int leerHumedad(){
  
    medida= dht.readHumidity(); // Leemos la humedad relativa

     if(medida >= 60){
       digitalWrite(ledHumedad, HIGH);  //Encender LED indicador de alta humedad
       digitalWrite(deshumidificador, HIGH);  //Encender deshumidificador
      }
      else{
        digitalWrite(ledNivel, LOW);   //Apagar LED indicador de alto nivel
        digitalWrite(deshumidificador, LOW);  //Apagar deshumidificador
      }


    return medida;
  }

  void mostrarEnPantalla(int nivel, int temp, int humedad){
    
  /*  Serial.print("Alerta por alto nivel: ");
    Serial.print(nivel);
    Serial.print(" La temperatura actual es: ");
    Serial.print(temp);
    Serial.print(" La humedad actual es: ");
    Serial.println(humedad); */


     Serial1.print(nivel);

  Serial1.print("|");
  Serial1.print(temp);

  Serial1.print("|");
  Serial1.print(humedad);
  Serial1.println("|");
  delay(400);
  
  
   
  }


