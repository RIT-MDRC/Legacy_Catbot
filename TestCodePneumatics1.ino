//System Constants for Sensor Calculation
const int V_SENSOR = 5;
const int P_MAX = 145; //psi
const int P_MIN = 0;

const int SYSTEM_PRESSURE = 60;


//Arduino Uno Pins
const int COMPRESSOR = 3;
const int VALVE_1 = 2;
const int SENSOR = A0;  //Analog
const int COMP_SWITCH = 5;
const int VALVE1_SWITCH = 4;



void setup() {
  Serial.begin(9600);

  //Setup pins
  pinMode(COMPRESSOR, OUTPUT);
  pinMode(VALVE_1, OUTPUT);
  pinMode(SENSOR, INPUT);
  pinMode(COMP_SWITCH, INPUT);
  pinMode(VALVE1_SWITCH, INPUT);

  //Set relay pins to high (relay is ACTIVE LOW)
  digitalWrite(COMPRESSOR, HIGH);
  digitalWrite(VALVE_1, HIGH);

}

void loop() {
  //Read in and calculate the pressure from the analog pressure sensor (psi)
  double sensorRead = (analogRead(SENSOR) * 0.0049); //Volts
  double pressure = (((sensorRead - 0.1*V_SENSOR)*(P_MAX - P_MIN))/(0.8*V_SENSOR)) + P_MIN + 0.72; //PSI

  //Print out readings
  Serial.print("Pressure: ");
  Serial.print(sensorRead);
  Serial.print("  ...  ");
  Serial.print(pressure);
  Serial.print(", CSwitch: "); 
  Serial.print(digitalRead(COMP_SWITCH)); 
  Serial.print(", VSwitch: "); 
  Serial.println(digitalRead(VALVE1_SWITCH));

  
/*
  if(pressure > SYSTEM_PRESSURE){   //First check if system pressure is too high, turn off compressor
    digitalWrite(COMPRESSOR, HIGH);
  }
*/
pressure = SYSTEM_PRESSURE + 1;
  
  if((pressure < SYSTEM_PRESSURE) || (digitalRead(COMP_SWITCH) == HIGH)){   //If pressure is too low, or overriden by manual switch, turn on compressor
    digitalWrite(COMPRESSOR, LOW);
  }
  else{
     digitalWrite(COMPRESSOR, HIGH);
  }

  if(digitalRead(VALVE1_SWITCH) == HIGH){   //If valve switch is flipped open valve
    digitalWrite(VALVE_1, LOW);
  }
  else{
    digitalWrite(VALVE_1, HIGH);
  }


  delay(100);
}
