//motor derecho
int velocidadA= 10; // EnA
int mda= 11;
int mdb= 12;

// motor izquierdo
int velocidadB= 9; // EnB
int mia= 13;
int mib= 8;

//sensores de linea
int ir1; 
int ir2;

//Sensor ultrasonico izquierdo
int trigiz= 6;
int echoiz= 7;
long distanciaiz;

//Sensor ultrasonico central
int trigcen= 3;
int echocen= 2;
long distanciacen;

//Sensor ultrasonico derecho
int trigde= 5;
int echode= 4;
long distanciade;

void setup() 
{
  // Motor derecho
  pinMode(mda, OUTPUT);
  pinMode(mdb, OUTPUT);
  pinMode(velocidadA, OUTPUT);

  // Motor izquierdo
  pinMode(mia, OUTPUT);
  pinMode(mib, OUTPUT);
  pinMode(velocidadB, OUTPUT);

  //Ultrasonico izquierdo
  pinMode(trigiz, OUTPUT);
  pinMode(echoiz, INPUT);
  Serial.begin(9600);
  //Ultrasonico central

  pinMode(trigcen, OUTPUT);
  pinMode(echocen, INPUT);
  Serial.begin(9600);

  //Ultrasonico derecho
  pinMode(trigde, OUTPUT);
  pinMode(echode, INPUT);
  Serial.begin(9600);

  // Sensor de linea
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
}

void adelante()
{
  // Motor derecho
  digitalWrite(mda, HIGH);
  digitalWrite(mdb, LOW);

  // Motor izquierdo
  digitalWrite(mia, LOW);
  digitalWrite(mib, HIGH);
}

void atras()
{
  // Motor derecho
  digitalWrite(mda, LOW);
  digitalWrite(mdb, HIGH);

  // Motor izquierdo
  digitalWrite(mia, HIGH);
  digitalWrite(mib, LOW);
}

void derecha()
{
  // Motor derecho
  digitalWrite(mda, LOW);
  digitalWrite(mdb, HIGH);
  // Motor izquierdo
  digitalWrite(mia, LOW);
  digitalWrite(mib, HIGH);  
}

void izquierda()
{
  // Motor derecho
  digitalWrite(mda, HIGH);
  digitalWrite(mdb, LOW);
  // Motor izquierdo
  digitalWrite(mia, HIGH);
  digitalWrite(mib, LOW);  
}

void detener()
{
  // Motor derecho
  digitalWrite(mda, LOW);
  digitalWrite(mdb, LOW);
  // Motor izquierdo
  digitalWrite(mia, LOW);
  digitalWrite(mib, LOW);  
}

void linea()
{
  ir1=digitalRead(A0);
  ir2=digitalRead(A1);
}

void ultraiz()
{
  long duracion;
  digitalWrite(trigiz, LOW);
  delayMicroseconds(4);
  digitalWrite(trigiz, HIGH);
  delayMicroseconds(19);
  digitalWrite(trigiz, LOW);
  duracion=pulseIn(echoiz, HIGH);
  duracion=duracion/2;
  distanciaiz=duracion/29;
}

void ultracen()
{
  long duracion;
  digitalWrite(trigcen, LOW);
  delayMicroseconds(4);
  digitalWrite(trigcen, HIGH);
  delayMicroseconds(19);
  digitalWrite(trigcen, LOW);
  duracion=pulseIn(echocen, HIGH);
  duracion=duracion/2;
  distanciacen=duracion/29;
}

void ultrade()
{
  long duracion;
  digitalWrite(trigde, LOW);
  delayMicroseconds(4);
  digitalWrite(trigde, HIGH);
  delayMicroseconds(19);
  digitalWrite(trigde, LOW);
  duracion=pulseIn(echode, HIGH);
  duracion=duracion/2;
  distanciade=duracion/29;
}

void loop() 
{   
    while(true)
    {
      linea();
      Serial.print(ir1);
      Serial.print(ir2);
      Serial.println("  ");

      if (ir1==1)
      {
        analogWrite(velocidadA, 255);
        analogWrite(velocidadB, 255);
        adelante();
        delay(1000);
      }
      else if(ir2==1)
      {
        analogWrite(velocidadA, 255);
        analogWrite(velocidadB, 255);
        atras();
        delay(1000);
      }
      else if(ir1 && ir2 ==0)
      {
        break;
      }

        ultracen();
        ultraiz();
        ultrade();
        Serial.println("iz   cen      de");
        Serial.print(distanciaiz);
        Serial.print("  ");
        Serial.print(distanciacen);
        Serial.print("  ");
        Serial.print(distanciade);
        Serial.println("  ");

        if (distanciacen<=20)
        {
          analogWrite(velocidadA, 255);
          analogWrite(velocidadB, 255);
          adelante();
        }
        else if (distanciaiz<=20)
        {
          analogWrite(velocidadA, 255);
          analogWrite(velocidadB, 255);
          izquierda();
        }
        else if (distanciade<=20)
        {
          analogWrite(velocidadA, 255);
          analogWrite(velocidadB, 255);
          derecha();
        }
    }
}
