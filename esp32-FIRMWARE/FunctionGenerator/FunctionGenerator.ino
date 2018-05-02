#define Num_Samples  112
#define MaxWaveTypes 4

#define FW_VERSAO  1.0
#define HW_MODELO "ESP32 MiniKit"

#define VDD_VALUE 3.3

#define F_GEN_PIN 25


int i = 0;

static byte WaveFormTable[MaxWaveTypes][Num_Samples] = {
   // Sin wave
   { 
    0x80, 0x83, 0x87, 0x8A, 0x8E, 0x91, 0x95, 0x98, 0x9B, 0x9E, 0xA2, 0xA5, 0xA7, 0xAA, 0xAD, 0xAF,
    0xB2, 0xB4, 0xB6, 0xB8, 0xB9, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0xBF, 0xBF, 0xC0, 0xBF, 0xBF, 0xBF,
    0xBE, 0xBD, 0xBC, 0xBB, 0xB9, 0xB8, 0xB6, 0xB4, 0xB2, 0xAF, 0xAD, 0xAA, 0xA7, 0xA5, 0xA2, 0x9E,
    0x9B, 0x98, 0x95, 0x91, 0x8E, 0x8A, 0x87, 0x83, 0x80, 0x7C, 0x78, 0x75, 0x71, 0x6E, 0x6A, 0x67,
    0x64, 0x61, 0x5D, 0x5A, 0x58, 0x55, 0x52, 0x50, 0x4D, 0x4B, 0x49, 0x47, 0x46, 0x44, 0x43, 0x42,
    0x41, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x41, 0x42, 0x43, 0x44, 0x46, 0x47, 0x49, 0x4B,
    0x4D, 0x50, 0x52, 0x55, 0x58, 0x5A, 0x5D, 0x61, 0x64, 0x67, 0x6A, 0x6E, 0x71, 0x75, 0x78, 0x7C
   },
   // Triangular wave
   {
     0x80, 0x84, 0x89, 0x8D, 0x92, 0x96, 0x9B, 0x9F, 0xA4, 0xA8, 0xAD, 0xB2, 0xB6, 0xBB, 0xBF, 0xC4,
     0xC8, 0xCD, 0xD1, 0xD6, 0xDB, 0xDF, 0xE4, 0xE8, 0xED, 0xF1, 0xF6, 0xFA, 0xFF, 0xFA, 0xF6, 0xF1,
     0xED, 0xE8, 0xE4, 0xDF, 0xDB, 0xD6, 0xD1, 0xCD, 0xC8, 0xC4, 0xBF, 0xBB, 0xB6, 0xB2, 0xAD, 0xA8,
     0xA4, 0x9F, 0x9B, 0x96, 0x92, 0x8D, 0x89, 0x84, 0x7F, 0x7B, 0x76, 0x72, 0x6D, 0x69, 0x64, 0x60,
     0x5B, 0x57, 0x52, 0x4D, 0x49, 0x44, 0x40, 0x3B, 0x37, 0x32, 0x2E, 0x29, 0x24, 0x20, 0x1B, 0x17,
     0x12, 0x0E, 0x09, 0x05, 0x00, 0x05, 0x09, 0x0E, 0x12, 0x17, 0x1B, 0x20, 0x24, 0x29, 0x2E, 0x32,
     0x37, 0x3B, 0x40, 0x44, 0x49, 0x4D, 0x52, 0x57, 0x5B, 0x60, 0x64, 0x69, 0x6D, 0x72, 0x76, 0x7B
  },

   // Sawtooth wave
   {
     0x00, 0x02, 0x04, 0x06, 0x09, 0x0B, 0x0D, 0x10, 0x12, 0x14, 0x16, 0x19, 0x1B, 0x1D, 0x20, 0x22,
     0x24, 0x27, 0x29, 0x2B, 0x2D, 0x30, 0x32, 0x34, 0x37, 0x39, 0x3B, 0x3E, 0x40, 0x42, 0x44, 0x47,
     0x49, 0x4B, 0x4E, 0x50, 0x52, 0x54, 0x57, 0x59, 0x5B, 0x5E, 0x60, 0x62, 0x65, 0x67, 0x69, 0x6B, 
     0x6E, 0x70, 0x72, 0x75, 0x77, 0x79, 0x7C, 0x7E, 0x80, 0x82, 0x85, 0x87, 0x89, 0x8C, 0x8E, 0x90,
     0x93, 0x95, 0x97, 0x99, 0x9C, 0x9E, 0xA0, 0xA3, 0xA5, 0xA7, 0xA9, 0xAC, 0xAE, 0xB0, 0xB3, 0xB5,
     0xB7, 0xBA, 0xBC, 0xBE, 0xC0, 0xC3, 0xC5, 0xC7, 0xCA, 0xCC, 0xCE, 0xD1, 0xD3, 0xD5, 0xD7, 0xDA,
     0xDC, 0xDE, 0xE1, 0xE3, 0xE5, 0xE8, 0xEA, 0xEC, 0xEE, 0xF1, 0xF3, 0xF5, 0xF8, 0xFA, 0xFC, 0xFE
   },
   // Square wave
   {
     0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
     0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
     0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
     0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
   }
};

String serialCmd = "";
bool flagControlRxSerial = false;
uint8_t ModSet = 1;
static byte wave_type = 0; // Sine
//byte wave_type = 1; // Triangle
//byte wave_type = 2; // Sawtooth
//byte wave_type = 3; // Square

void setup() {
  Serial.begin(115200);

  /* 10 caracteres para  comandos */
    serialCmd.reserve(10);
}
 
void loop() {
  static int timeDelay = 1;

  dacWrite(F_GEN_PIN, WaveFormTable[wave_type][i]); 
  i++;
  if (i >= Num_Samples) i = 0; 

  /* Estarou sempre verificando se acabou a recepcao da serial,
     esta variavel flagControlRxSerial se tornara true para isso.
  */
    if (flagControlRxSerial) {
        switch(ModSet)
        {
          case 1:
            serialHandleMenu();
            break;
          case 2:
            serialHandleAmpli();
            break;
        }
      
        
        /* Resetando valores para nova recepcao */
        serialCmd = "";
        flagControlRxSerial = false;
  }
  serialEvent();
  delayMicroseconds(timeDelay);
  
}


void serialEvent() {
    /* Loop verificando se algum byte esta disponivel na serial */
    while (Serial.available()) {
      /* O que chegar pela serial  feito um typecast de char para a variavel caractere */
        char caractere = (char)Serial.read();
        /* Nossa variavel caractere eh concatenada a nossa variavel serialCmd que eh uma String */
        serialCmd += caractere;
        /* Se chegar um CR, nova linha, nossa flag de controle (flagsControlRxSerial) passa para true
           e no loop principal ja podera ser utilizada
        */
        if (caractere == '\n') {
            flagControlRxSerial = true;
        }
    }
}

void SetSquareAmpli(float value)
{
  int8_t i_DAC;
  
  value = (value*0xFF)/VDD_VALUE;

  i_DAC = int8_t(value);
  for(int i =0; i<56 ; i++)
  {
    WaveFormTable[3][i] = i_DAC;
  }
}

void serialHandleMenu()
{
  if( serialCmd == "versao\n" ) {
      Serial.print("\tFirmware: ");
      Serial.print(FW_VERSAO);
  }
  else if ( serialCmd == "hardware\n") {
      Serial.print("\tPlaca : ");
      Serial.print(HW_MODELO);
  }
  else if ( serialCmd == "help\n" || serialCmd == "?\n") {
      Serial.println("\tComandos:");
      Serial.println("\thardware - Retorna o modelo do hardware");
      Serial.println("\tversao - Retorna a versao atual do firmware");
      Serial.println("\tSaída analógica no pino: 25");
      Serial.println("\tPara mudar a forma de onde, digite:");
      Serial.println("\tSeno - Triangulo - Quadrada - Serra");
      Serial.println("\tPara Alterar a Amplitude, digite Amplitude");
  }
  else if (serialCmd == "Seno\n") {
      wave_type = 0;
      Serial.print("\tSeno\n");
  }
  else if (serialCmd == "Triangulo\n") {
      wave_type = 1;
      Serial.print("\tTriangulo\n");
  }
  else if (serialCmd == "Quadrada\n") {
      wave_type = 3;
      Serial.print("\tQuadrada\n");
  }
  else if (serialCmd == "Serra\n") {
      wave_type = 2;
      Serial.print("\tSerra\n");
  }
  
  else if (serialCmd == "Amplitude\n") {
      ModSet = 2;
      Serial.print("\tDigite o Valor de Aplitude separado por ponto\n");
  }
  else if (serialCmd == "\n") {
      Serial.print("\n");
  }
  else {
      Serial.print("\t* Comando invalido *");
  }
}

void serialHandleAmpli()
{
  float value;
  value = serialCmd.toFloat();
  if( (value > 0) && (value <= VDD_VALUE) ) 
  {
    Serial.println(value);
    SetSquareAmpli(value);
  }
  else {
      Serial.print("\t* Comando invalido *");
  }
  ModSet = 1;
  Serial.println("\tMain Menu");
  
}

