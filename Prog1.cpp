//Variáveis da senha binária
//Digitos da senha binária
#define Digito1 6
#define Digito2 7
#define Digito3 8
#define Digito4 9
//4 Digitos da senha de ligar
int senhaLigar1 = 0;
int senhaLigar2 = 0;
int senhaLigar3 = 0;
int senhaLigar4 = 0;
//4 Digitos da senha de desligar
int senhaDesligar1 = 1;
int senhaDesligar2 = 1;
int senhaDesligar3 = 1;
int senhaDesligar4 = 1;
//Botão redefinir senha
#define botaoReset 0
//Chave seletora para definir senha
#define InterruptorSenha 12
//Botão de ação para a senha
#define BotaoSenha 2
//Funções para declarar senha
void senha(int dig1, int dig2, int dig3, int dig4);
void definirSenha(int d1, int d2, int d3, int d4);

//Variaveis do Alarme
//Alarme Sonoro, simulado pelo piezo
#define AlarmeSonoro 13
//Variáveis para o LED RGB
const byte G = 3;
const byte B = 4;
const byte R = 5;
//Váriaveis para controle
int ligaAlarme = 0;
#define alarmeLigado 1

//Variáveis da função piscaLed
int passadoMillis;
bool x = 0;
void piscaLed(char cor, int pisca);

//Variáveis do Sensor
float cm,duracao;
int movimento = 1;
//Pinos do Sensor
byte trig=11;
byte echo=10;

void setup()
{
  //PinMode do Alarme
  //Led RGB
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  //Alarme Sonoro
  pinMode(AlarmeSonoro,OUTPUT); 
  //Led falando se o alarme está armado
  pinMode(alarmeLigado,OUTPUT);
  //pinMode dos pinos do Sensor
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  //PinMode dos pinos para a senha
  pinMode(Digito1, INPUT);
  pinMode(Digito2, INPUT);
  pinMode(Digito3, INPUT);
  pinMode(Digito4, INPUT);
  //PinMode para o interruptor
  pinMode(InterruptorSenha, INPUT);
  //PinMode para o botao
  pinMode(BotaoSenha,INPUT);
  pinMode(botaoReset,INPUT);
}

void loop()
{
  //Se o botão para resetar a senha estiver pressionado
  //A função redefinir senha entrará em prática
  if (digitalRead(botaoReset) == 0){
  	definirSenha(digitalRead(Digito1),digitalRead(Digito2),digitalRead(Digito3),digitalRead(Digito4)); 
  }
  //Se o botão para acionar a senha estiver pressionado
  //A função senha entrará em prática
  if(digitalRead(BotaoSenha) == 1){
  	senha(digitalRead(Digito1),digitalRead(Digito2),digitalRead(Digito3),digitalRead(Digito4));
  }
  
  //colocar a distância em uma variável
  cm =  distancia();
  
  //Se o alarme estiver acionado
  if(ligaAlarme == 1){
  //Liga o LED que representa o funcionamento do sistema
  digitalWrite(alarmeLigado,HIGH);
  //Acende o LED de acordo com a distância do objeto
  //Se estiver muito perto, acende o vermelho
  if(cm > 0 && cm <= 100){ 
	piscaLed(R);
    digitalWrite(AlarmeSonoro,HIGH);
  }
  //Se estiver no meio, acende o verde
  else if (cm > 100 && cm <= 200){
	piscaLed(G);
    digitalWrite(AlarmeSonoro,HIGH);
  }
  //Se estiver longe, acende o azul
  else if (cm > 200){
	piscaLed(B);
    digitalWrite(AlarmeSonoro,HIGH);
  }
  //Se não detectar movimento, não ascende
  //Mas se tiver, so desliga o som por senha
  delay(500);
  }
  //Se o alarme estiver desligado, desliga o sistema
  else if (ligaAlarme == 0){
    //Diz que o alarme está desarmado
    digitalWrite(alarmeLigado,LOW);
    //Desliga o alarme
    apaga();
  }
}

//Função que calcula distância
float distancia()
{  
  //Limpar o pino transmissor, cortar o sinal e aguardar 5us segundos  
  //Recomendado para melhor funcionamento 
  digitalWrite(trig, LOW);
  delayMicroseconds(5); 
  //Envio do pulso de ultrassom 
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10);
  //Desliga o pino que envia, habiliando o pino que recebe
  digitalWrite(trig, LOW);
  //Calcula a duração do pulso para ir e voltar 
  duracao = pulseIn(echo, HIGH);
  //Calcula a distância
  float calcDistancia= (duracao/2) * 0.0343;
  //Se estiver fora da distância do sensor, ele volta 331
  if (calcDistancia>=331){
      calcDistancia=0;
  }
  //Caso a distância estiver dentro dos padrões, movimento é igual a 1
  else{
  	movimento = 1;
  }
  return calcDistancia;  
}

//Funções de cores do led
//Ligar vermelho
void red(){
    analogWrite(R, 255);
    analogWrite(G, 0);
    analogWrite(B, 0);
}
//Ligar verde
void green(){
    analogWrite(R, 0);
    analogWrite(G, 255);
    analogWrite(B, 0);
  }  
//Ligar azul
void blue(){
    analogWrite(R, 0);
    analogWrite(G, 0);
    analogWrite(B, 255);
  } 
//Apagar o led
void apaga(){
    analogWrite(R, 0);
    analogWrite(G, 0);
    analogWrite(B, 0);
  digitalWrite(AlarmeSonoro,LOW);
  }

//Função pisca led em função da cor e tempo de piscada
void piscaLed(char cor){
  unsigned long atualMillis = millis();
  
  switch(cor){ 
//Codigo para piscar caso a cor for vermelha
case R:
  if(atualMillis - passadoMillis > 200) {
    passadoMillis = atualMillis;
    if (x == 0){
      	red();
      	x = 1;
    }else if (x == 1){
      	apaga();
      	x = 0;
    }
  }

case G:  
//Codigo para piscar caso a cor for verde  
  if(atualMillis - passadoMillis > 500) {
    passadoMillis = atualMillis;
    if (x == 0){
      	green();
      	x = 1;
    }else if (x == 1){
      	apaga();
      	x = 0;
    }
  }

//Codigo para piscar caso a cor for azul  
case B:
  if(atualMillis - passadoMillis > 1000) {
    passadoMillis = atualMillis;
    if (x == 0){
      	blue();
      	x = 1;
    }else if (x == 1){
      	apaga();
      	x = 0;
    }
  }
  }
  }

//essa função só liga com o botão reset
//Funciona para escolher a senha nova, quando o botão for pressionado
void definirSenha(int d1, int d2, int d3, int d4){
  //de acordo com o interruptor muda a senha de ativar ou desativar
  if(digitalRead(InterruptorSenha) == 0){
  	senhaDesligar1 = d1;
    senhaDesligar2 = d2;
    senhaDesligar3 = d3;
    senhaDesligar4 = d4;
  }else if(digitalRead(InterruptorSenha) == 1){
  	senhaLigar1 = d1;
    senhaLigar2 = d2;
    senhaLigar3 = d3;
    senhaLigar4 = d4;
  }
}

//essa função so liga com o botão Senha
//Funciona para ver se a senha digitada está certa quando pressionar o botão
void senha(int dig1, int dig2, int dig3, int dig4){
    //liga ou desliga o alarme, vendo se a senha está certa ou não
  	if(ligaAlarme == 0){
      	if(dig1 == senhaLigar1 && dig2 == senhaLigar2 && dig3 == senhaLigar3 && dig4 == senhaLigar4){
      		//como o alarme estava desligado e a senha correta, liga o alarme	
          ligaAlarme = 1;
      	} 
    }else if (ligaAlarme == 1){
    	if(dig1 == senhaDesligar1 && dig2 == senhaDesligar2 && dig3 == senhaDesligar3 && dig4 == senhaDesligar4){
      	//como o alarme estava ligado e a senha correta, desliga o alarme	
          ligaAlarme = 0;
            apaga();
      	} 
    }
}
