// insira as informaçoes enviadas pelo app Blynk
#define BLYNK_TEMPLATE_ID           "TMPL2Qhvrl3VG"
#define BLYNK_TEMPLATE_NAME         "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "DytKbtMilsfueBUg0BLqi19awjV_R0vE"

// selecione o modem:
#define TINY_GSM_MODEM_SIM7000

//incluir bibilhotecas nescesarias
#include <TinyGsmClient.h>
#include <BlynkSimpleTinyGSM.h>

//configuração de rede, deve mudar de acordo com a operadora
char auth[] = BLYNK_AUTH_TOKEN; //este não muda
char apn[]  = "zap.vivo.com.br";
char user[] = "vivo";
char pass[] = "vivo";

//configurando modem interno
#define SerialAT Serial1
#define UART_BAUD   115200
#define PIN_DTR     25
#define PIN_TX      27
#define PIN_RX      26
#define PWR_PIN     4

//definindo pinos de saida 'LEDs'
int LEDpin1 = 32;
int LEDpin2 = 33;
int LEDpin3 = 2;
int LEDpin4 = 15;

/*
 * @brief Controla LEDs e envia sinais virtuais via Blynk de acordo com tempos predefinidos.
 *
 * ALERTA OS TEMPOS TEM QUE SER PASADOS EM ORDEM CRESCENTE!!!!!!!!!! temp1<temp2<temp3<temp4
 *
 * A função acende todos os LEDs (LED1, LED2, LED3 e LED4) e envia o valor 1 para os pinos virtuais V1, V2, V3 e V4 no Blynk. 
 * Após um tempo especificado pelo parâmetro temp1, apaga o LED1 e envia o valor 0 para o pino virtual V1 no Blynk.
 * Esse comportamento se repete para os demais LEDs (LED2, LED3 e LED4) com base nos tempos fornecidos pelos parâmetros 
 * temp2, temp3 e temp4, respectivamente. */
void responderComando(int LED1,int LED2,int LED3,int LED4, int temp1, int temp2, int temp3, int temp4){
  digitalWrite(LED1, HIGH);//ativando as saidas
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  Blynk.virtualWrite(V1, 1);//ativando a visualização no Blynk
  Blynk.virtualWrite(V2, 1);
  Blynk.virtualWrite(V3, 1);
  Blynk.virtualWrite(V4, 1);

  delay(temp1);//desativando a saida
  digitalWrite(LED1, LOW);
  Blynk.virtualWrite(V1, 0);

  delay(temp2 - temp1);
  digitalWrite(LED2, LOW);
  Blynk.virtualWrite(V2, 0);

  delay(temp3 - temp2);
  digitalWrite(LED3, LOW);
  Blynk.virtualWrite(V3, 0);

  delay(temp4 - temp3);
  digitalWrite(LED4, LOW);
  Blynk.virtualWrite(V4, 0);
}

TinyGsm modem(SerialAT);

void setup(){
  pinMode(LEDpin1, OUTPUT);//definindo modos dos pinos de saida
  pinMode(LEDpin2, OUTPUT);
  pinMode(LEDpin3, OUTPUT);
  pinMode(LEDpin4, OUTPUT);

  digitalWrite(LEDpin1, LOW);//desativando saidas
  digitalWrite(LEDpin1, LOW);
  digitalWrite(LEDpin1, LOW);
  digitalWrite(LEDpin1, LOW);

  pinMode(PWR_PIN, OUTPUT); //reset modem
  digitalWrite(PWR_PIN, HIGH);
  // Starting the machine requires at least 1 second of low level, and with a level conversion, the levels are opposite
  delay(1000);
  digitalWrite(PWR_PIN, LOW);
  delay(1000);

  SerialAT.begin(UART_BAUD, SERIAL_8N1, PIN_RX, PIN_TX);//ativação modem

  Blynk.begin(auth, modem, apn, user, pass);//ativação blynk
}

// escuta o botão no app Blynk e ativa a função
BLYNK_WRITE(0) {
    if (param.asInt()) {
        responderComando(LEDpin1,LEDpin2,LEDpin3,LEDpin4, 2000,4000,6000,6000);
    } 
}

//inicia o sistema
void loop(){
    Blynk.run();
}