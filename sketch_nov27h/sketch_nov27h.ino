#include <PS2X_lib.h>
#include <Servo.h>

Servo servo;
PS2X ps2x; // funcion de libreria para agregar/habilitar el joystick para usarlo //

int error=0;   // variables para el joystick //
byte vibrate=0;

int ledv=2;
int leda=3;
int ledr=4;
int buzzer=5;
int lx;
int dir1=A5;
int dir2=A4;

void setup() {
  // put your setup code here, to run once:
 Serial.begin (9600);
 // declarar (clock, comand, attention, data) estos son los pines del mando, nosotros debemos poner en que pines los pusimos en el arduino //
 error=ps2x.config_gamepad (10,12,11,13,false,false); // ahora debemos decirle al arduino si vamos a usar el sensor de presion
 // de tecla y la vibracion, como en este caso no los vamos a usar, ponemos false en ambos //
 // error nos va a servir para indicarnos si detecto o no el joystick //
  if ( error==0 ){
    Serial.println ("Se detecto el mando");
  }
  else {
    Serial.println ("Error, no se detecto ningun mando");
  }

  pinMode (ledv , OUTPUT);
  pinMode (leda , OUTPUT);
  pinMode (ledr, OUTPUT)
  pinMode (buzzer, OUTPUT);
  pinMode (dir1, OUTPUT);
  pinMode (dir2 , OUTPUT);
  servo.attach(6);
}

void loop() {
  // put your main code here, to run repeatedly:
  ps2x.read_gamepad (false,vibrate); // Con este comando habilitamos la comunicacion de la lectura de datos que va a mandar el joystick //

lx=ps2x.Analog(PSS_LX),DEC; // Esta funcion nos va a permitr leer el analogico y leer en que posicion se encuentra el analogico //
// y esa lectura se guarda en lx //

lx=lx-127; // esto es para acomodar (a lo que nosotros queremos) la posicion del analogico, en este caso el punto medio era 127 //
// pero ahora tendra valor 0 //

  if (lx==128){ // se hace este if ya que al moverlo a full derecha se marca 128 ( ya que empieza de 127 ) entonces ahora queda //
  // 127 y -127 a ambos extremos, para evitar confunciones en el arduino //
    lx=127;
  }

int grados=map(lx, -127, 127, 0, 180); // aca marcamos los valores minimo y maximo, y lo que hace esta funcion es transformar //
// los valores ingresados siendo -127=0 grados, 0=90 grados y 127=180 grados //
// esta funcion va a poseer los grados // 

 servo.write(grados);

Serial.println(lx);


    if (ps2x.Button(PSB_BLUE)){  // Esta funcion dentro del if nos permite leer los botones y dentro del parentesis hacemos referencia //
    // al boton azul del control, por ende, con ese color de boton especificos haremos lo definido dentro del if, en este caso //
    // al apretar el boton azul se encendera el led amarillo //
        digitalWrite (leda, HIGH);
    }
    else if (ps2x.Button(PSB_PAD_DOWN)){ // Y aca en vez de botones de colores hacemos referencias a las flechas del lado izq del mando //
    // en este caso apagaremos el led amarillo con la flecha abajo del joystick //
      digitalWrite(leda, LOW);
    }
    else if (ps2x.Button(PSB_RED)){
      digitalWrite(ledr, HIGH);
    }
    else if (ps2x.Button(PSB_PAD_RIGHT)){
      digitalWrite(ledr, LOW);
    }
    else if (ps2x.Button(PSB_PINK)){
      digitalWrite(ledv, HIGH);
    }
    else if (ps2x.Button(PSB_PAD_LEFT)){
      digitalWrite(ledv, LOW);
    }
    else if (ps2x.Button(PSB_R3)){
      digitalWrite(buzzer, HIGH);
    }
    else if (ps2x.Button(PSB_L3)){
      digitalWrite(buzzer, LOW);
    }
    else if (ps2x.Button(PSB_R1)){ // Para arrancar los motores tienen que estar sincronizadas las direcciones sino cortocircuito //
      digitalWrite(dir2, LOW);
      digitalWrite(dir1, HIGH);
    }
    else if (ps2x.Button(PSB_R2)){
      digitalWrite(dir1, LOW);
      digitalWrite(dir2, HIGH);
    }
    else if (ps2x.Button(PSB_PAD_UP)){
      digitalWrite(dir1, LOW);
      digitalWrite(dir2, LOW);
    }

    delay (50); // Le damos tiempo descanso al arduino //
}
