#include <LiquidCrystal.h>   
#include <Keypad.h>
#include <Servo.h>

Servo miServo;
int anguloInicial = 0;  // Ángulo inicial
int anguloFinal = 90;   // Ángulo final
const int buzzer=A2;
int a=0, b=0, c=0, d=0;//Enteros que almacenaran la contraseña
int var=0; //Variable auxiliar para el switch
int C1=1,C2=2,C3=3,C4=4;//La clave
char f='*';  //Caracter para esconder el caracter original
int intentos=0; //Intentos que va a tener el control
int aviso=3; //Aviso para saber cuantos intentos van
const byte filas = 4; //numero de filas.
const byte columnas = 4; //numero de colunas.
char tecla[filas][columnas] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte pinFilas[filas] = {7, 6, 5, 4}; //declaración de pines conectados a filas 
byte pinColumnas[columnas] = {3, 2, 1, 0}; //declaración de pines conectados a filas 

Keypad keypad = Keypad( makeKeymap(tecla), pinFilas, pinColumnas, filas, columnas );
LiquidCrystal lcd(8,9,10,11,12,13); //D7,D6,D4,E,RS
void setup(){
  lcd.begin(16,2); 
  miServo.attach(A5);  // Asignamos el pin A5
  miServo.write(anguloInicial);  //Escribimos un angulo para el servo
  pinMode(A0,OUTPUT); //LED Verde
  pinMode(A1,OUTPUT); //LED Rojo
  
}

void loop() {
char key = keypad.getKey();
  if (key){
   lcd.setCursor(6+var,1);
   lcd.print(key),lcd.setCursor(6+var,1),lcd.print(f);//imprimir el caracter en el lcd
   key=key-48; //convertir char en enteros
   var++; //Incremento auxiliar para almacenar todos los casos en el switch
   switch(var){
    case 1:
    a=key; //almacenar el primer digito para la contraseña
    break;
    case 2:
    b=key; //almacenar el segundo digito para la contraseña 
    break;
    case 3:
    c=key; //almacenar el tercero digito para la contraseña
    break;
    case 4:
    d=key; //almacenar el cuarto digito para la contraseña 
   delay(100);
  if(a==C1 && b==C2 && c==C3 && d==C4){//si a,b,c,d es igual a la clave
    lcd.clear();
    tone(buzzer,500);
    delay(200);
    noTone(buzzer);
    tone(buzzer,600);
    delay(100);
    noTone(buzzer);
    digitalWrite(A1, LOW);
    digitalWrite(A0, HIGH);
    lcd.setCursor(4,0);//Punto de posicion de donde iniciara el mensaje
    lcd.print("Password");
    lcd.setCursor(5,1);
    lcd.print("Correcta");
    miServo.write(anguloFinal);
    delay(2000);
    miServo.write(anguloInicial);
    delay(1000);
    digitalWrite(A0,HIGH);//LED Verde enciende
    delay(2000); // Tiempo de 2 segundos
    lcd.clear();
    digitalWrite(A0,LOW);//LED Verde apaga
    }
  else{
    lcd.clear();//limpia el LCD
    lcd.setCursor(4,0);
    lcd.print("Password");
    lcd.setCursor(4,1);
    lcd.print("Invalida");
    digitalWrite(A1,HIGH); //LED rojo enciende
    delay(1000); 
    lcd.clear();
    digitalWrite(A1,LOW); //Led rojo apaga
    }
//------Si fallas 3 veces-------------------//

  if(a==C1 && b==C2 && c==C3 && d==C4){
      intentos=0;//Si es correcto, la variable intentos no cambia
      aviso=3;//Si la variable aviso es igual a 3
    }
  else{
      intentos ++; // Incrementa en 1 
      aviso --; //Se reduce en 1 hasta llegar 0
      lcd.setCursor(2,0);
      lcd.print("Le restan "); 
      lcd.setCursor(13,0);
      lcd.print(aviso); //imprime el numero de oportunidades restantes
      lcd.setCursor(2,1);
      lcd.print("Oportunidades");
      delay(1000);
      tone(buzzer,600);
      delay(300);
      noTone(buzzer);
      digitalWrite(A1, LOW);
      digitalWrite(A1, HIGH);
       if(aviso==0){
          lcd.clear();
          lcd.setCursor(5,0);
          lcd.print("ALARMA");
          lcd.setCursor(4,1);
          lcd.print("ATIVADA");
        }
      delay(300);lcd.clear();
      }
  while(intentos>=3){ //Cuando llega al maximo tiempo de intentos, suena la alarma
      tone(buzzer,500);
      lcd.setCursor(1,0),lcd.print("Alerta Policia");
      lcd.setCursor(4,1),lcd.print("Intrusos");
      digitalWrite(A1,HIGH); //Enciende el led rojo
      delay(500);
      lcd.clear();
      digitalWrite(A1,LOW);//Apaga el led rojo
      delay(500);
  }
   var=0;
   lcd.clear();
  break;//termina
  }
 }
 if(!key){lcd.setCursor(0,0),lcd.print("Ingresa Password");
      digitalWrite(A1,LOW);   
         }//Mensaje principal
  delay(2);
} 