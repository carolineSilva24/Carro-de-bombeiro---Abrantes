#include <SoftwareSerial.h> // Permite a comunicação serial em outros pinos, além do padrão
#include <AFMotor.h> // Controla os motores DC usando a AdaFruit Motor Shield
#include <Servo.h>

int RELAY1 = A0; // Pino para o relé da bomba
int state1 = 0;  // Estado da bomba

// Definição dos motores
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

// definição do motor Servo
Servo meuServo;

// Variavel que armazena os comandos recebidos pelo controle
char bt = 'S';

// Velocidade dos motores para 150
void setup()
{
  Serial.begin(9600);
  motor1.setSpeed(150);
  motor2.setSpeed(150);
  motor3.setSpeed(150);
  motor4.setSpeed(150);
  
  pinMode(RELAY1, OUTPUT);
  
  digitalWrite(RELAY1, HIGH); // Iniciar com a bomba desligada (lógica invertida)
  
  // conectamos o servo motor no pino 10
  meuServo.attach(10);
  // Sua posição inicial é 0
  meuServo.write(0);
  // Função para garantir que os motores fiquem parados no inicio
  Stop();
}

void loop() {
  // Le os comandos enviados pelo Bluetooth
  bt = Serial.read();

  // Mapeamento de botões
  if (bt == 'F') forward();
  if (bt == 'B') backward();
  if (bt == 'L') left();
  if (bt == 'R') right();
  if (bt == 'W') Stop();
  
  if (bt == 'M') pump_ON();
  if (bt == 'm') pump_OFF();
}

// Função para ligar a bomba
void pump_ON() {
  if (state1 == 0 && bt == 'M') {
    digitalWrite(RELAY1, LOW); // Liga a bomba d'água (lógica invertida)
    state1 = 1;
    bt = 0;
  }
}

// Função para desligar a bomba
void pump_OFF() {
  if (state1 == 1 && bt == 'm') {
    digitalWrite(RELAY1, HIGH); // Desliga a bomba d'água (lógica invertida)
    state1 = 0;
    bt = 0;
  }
}

// Função para mover o carro para frente
void forward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

// Função para mover o carro para tras
void backward() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

// Função para mover o carro para a esquerda
void left() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

// Função para mover o carro para a direita
void right() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

// Função para para o carro
void Stop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

