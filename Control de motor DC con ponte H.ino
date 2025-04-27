/* 
//O obxectivo deste práctica é deseñar o funcionamento dunha ponte 
//H usando catro relés SPDT, utilizaremos un motor DC de 24V que será controlado
//con un arduino.
//Un pulsador controlará os estados do motor,son os seguintes:
//(a) xira en sentido dereito (antihorario), 
//(b) frea inmediatamente, 
//(c) xira en sentido inverso (horario), 
//(d) frea inmediatamente. 
//Haberá un estado máis, de inicio ou estado -1, chamado"freado" 
//O sistema pasa a este estado tras 15s de paro inmediato e
//retornando ao estado (a).
//AUTORA:DOLORES PATIÑO
//DATA:ABRIL 2025
*/

//Declaración de entradas dos pins de E/S
#define pulsador 7
#define S1 11
#define S2 10
#define S3 9
#define S4 8

//Declaración de variables globais
bool PULS = false;

int estado = -1;      

int contador = 0;
void setup(){
    
  pinMode(pulsador, INPUT); 
  pinMode(S1, OUTPUT);         
  pinMode(S2, OUTPUT);           
  pinMode(S3, OUTPUT);
  pinMode(S4, OUTPUT); 
  Serial.begin(9600);			
}

    
  void XiraDereita() {
    
    digitalWrite(S1, HIGH);      //PULSADOR ENCENDIDO
    digitalWrite(S4, HIGH);      //PULSADOR ENCENDIDO
    digitalWrite(S3,LOW);        //PULSADOR APAGADO
    digitalWrite(S2,LOW);        //PULSADOR APAGADO
}
void XiraEsquera() {
    
    digitalWrite(S3, HIGH);      //PULSADOR ENCENDIDO
    digitalWrite(S2, HIGH);      //PULSADOR ENCENDIDO
    digitalWrite(S1,LOW);        //PULSADOR APAGADO
    digitalWrite(S4,LOW);        //PULSADOR APAGADO
}
void ParoInmediato() {
     
    digitalWrite(S1, HIGH);      //PULSADOR ENCENDIDO
    digitalWrite(S2, HIGH);      //PULSADOR ENCENDIDO
    digitalWrite(S3, LOW);       //PULSADOR APADAGADO
    digitalWrite(S4, LOW);       //PULSADOR APAGADO
    contador = 0;               
}
 void loop(){
  
  PULS = digitalRead(pulsador);    
 
  if ( PULS == true ){          
    
    
    if (estado == -1) {      //ESTADO 0
      
      estado = 0;
      
    } else { 
    
      estado = (estado +1) % 4;    // Ciclo 0 -> 1 -> 2 -> 3
    

    }
    
   while(digitalRead(pulsador)){ 
     delay(15);                     //ÚNICA LECTURA
      							    
							  
    }
  switch (estado){       //ESTADO DOS VALORES
      
    case 0:
    	XiraDereita ();          //XIRA HORARIO.
      	break;
    case 1:
        ParoInmediato();		 //ESTADO PARO INMEDIATO.
      	break;
    case 2:
      XiraEsquera ();          //XIRA ANTIHORARIO.
    	break;
    case 3:
      ParoInmediato();		 //ESTADO PARO INMEDIATO.
   	 	break;  
  }
  }
  
  
  if (estado == 0 || estado == 2) {
   
  contador ++;
    
  }
  
    if (contador == 150){
      
    ParoInmediato();          // Freado por inercia
      
    contador = 0;           // Reiniciamos Contador  
   
      estado = -1;            // Volvemos ó estado de Inicio
  
  }
   
Serial.print("Estado: ");
  Serial.print(estado);
  Serial.print(" | Tempo de paro: ");
  Serial.println(contador);
}
