

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
     Serial1.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  Serial1.println("xdata=42011234567890ABCDEF1234567890ABCDEF1234567890ABCDEF1234567890ABCDEF1234567890ABCDEF1234567890ABCDEF");
  delay(1000);               // wait for a second
}
