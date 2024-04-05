// C++ code
//


//Motor1
#define velm1 6
#define m1a 13
#define m1b 12
#define tmp 5000

//Motor2
#define velm2 5
#define m2a 4
#define m2b 3

//Leitura do Estado do robô
bool movingForward = true;

//Ultrassonic
#define sonarTrigger 9
#define sonarEcho 10

int distance = 0;
int time = 0;


void setup()
{
	//Setup M1
  	pinMode(velm1, OUTPUT);
  	pinMode(m1a, OUTPUT);
  	pinMode(m1b, OUTPUT);
  
  	//SETUP M2
  	pinMode(velm2, OUTPUT);
  	pinMode(m2a, OUTPUT);
  	pinMode(m2b, OUTPUT);
  
  	//SETUP ULTRASSONIC
  	pinMode(sonarTrigger,OUTPUT);
    pinMode(sonarEcho,INPUT);
  	//leitura dos dados
  	Serial.begin(9600);
  
}

void stop(){
//M1 Parado
  analogWrite(velm1,0);
  digitalWrite(m1a,LOW);
  digitalWrite(m1b,LOW);

  
//M2 Parado
  analogWrite(velm2, 0);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, LOW);
}

void moveForward(){
  //M1 move Forward
  analogWrite(velm1,255);
  digitalWrite(m1a,HIGH);
  digitalWrite(m1b,LOW);

  
  //M2 move Foward
  analogWrite(velm2,255);
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);
}


void turnLeft(){
  //M1 move Forward
  analogWrite(velm1,126);
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);
  
  //M2 move Backward
  analogWrite(velm2,126);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, HIGH);
  	
}

void loop()
{
  

	//Leitura Ultrassonica (inicialização)
  	digitalWrite(sonarTrigger,LOW);
  	delay(2);
  
  	//Leitura Ultrassonica (enviar de pulso)
  	digitalWrite(sonarTrigger,HIGH);
  	delay(10);
  	digitalWrite(sonarTrigger,LOW);
  
  	//receber o pulso
  	time = pulseIn(sonarEcho,HIGH);
  	distance = time/58.2;  //calculo velocidade do som
  
  //Inicialização do robô (Alguns segundos parado)
	delay(3000);
    	
  // Estado do robô e tomada de decisão
    if (movingForward) {
        if (distance <= 40) {
            stop();
            movingForward = false;
            delay(1000); 
        } else {
            moveForward();
        }
    } else {
        turnLeft();
        delay(1000); 
        movingForward = true; // Volta a mover para frente 
    }
  
}
