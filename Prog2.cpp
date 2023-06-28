//Incluir a bibilioteca do controle remoto <IRremote.h>
#include <IRremote.h>

//Variáveis para a utilização do controle 
#define pinoIR 6
IRrecv receptor(pinoIR);//receptor para descodificar o sinal do sensor IR
decode_results resultados;//variavel para armazenar os dados
unsigned long int controle = 0; //Digito clicado no controle

//Variáveis da senha binária
//Digitos da senha binária
unsigned long int Digito[4];
int lerBotao = 0;
int d = 0;
int e = 0;
int erro = 0;
//4 Digitos da senha de ligar o sistema
int senhaLigar1 = 16593103;
int senhaLigar2 = 16593103;
int senhaLigar3 = 16593103;
int senhaLigar4 = 16593103;
//4 Digitos da senha de desligar o sistema
int senhaDesligar1 = 16582903;
int senhaDesligar2 = 16582903;
int senhaDesligar3 = 16582903;
int senhaDesligar4 = 16582903;
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
#define alarmeLigado 2

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
  //Função para habilitar o receptor do controle
  receptor.enableIRIn();
  //Ligar o Monitor serial
  Serial.begin(9600);
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
  // Configura pino de Trigger como saída e inicializa com nível baixo
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT); // configura pino ECHO como entrada
}

void loop()
{
  //O if serve para ler o botão pressionado no controle
  //e armazena-lo na variavel controle
  if(receptor.decode(&resultados)) {        
    receptor.resume();                      
    controle = resultados.value;
    //Esse print serve para mostrar o botão que foi pressionado
    //Como o tinkercad trava muito, é interessante testar o projeto
    //acompanhando o botao pressionado no monitor
    Serial.println(controle);
  }
  //Caso o botão power (16580863) for pressionado
  //será ativado o lerBotao = 1
  //Que faz com que leia uma senha de 4 digitos
  if(controle == 16580863 && lerBotao == 0){
  	lerBotao = 1;
  }
  //Caso o botão VOL+ (16613503) for pressionado
  //será ativado o lerBotao = 2
  //Que faz com que os próximos 4 digitos sejam a nova senha de desativar o alarme
  if(controle == 16613503 && lerBotao == 0){
  	lerBotao = 2;
  }
  //Caso o botão func/stop (16597183) for pressionado
  //será ativado o lerBotao = 3
  //Que faz com que os próximos 4 digitos sejam a nova senha de ativar o alarme
  if(controle == 16597183 && lerBotao == 0){
  	lerBotao = 3;
  }
  //A função if de mudar a senha após 4 digitos serem presionados no controle
  if (lerBotao > 1 && controle != 16580863 && controle != 16613503 && controle != 16597183){
    //Conforme o modo do lerBotão, uma das duas senhas será mudada
    if(lerBotao == 2 || lerBotao == 3){
    //Armazena um digito por vez no vetor digito
    Digito[e] = controle;
    controle = 16613503;
    e++;
    //Quando chega ao ultimo dígito, reseta e, e ativa a função de definir a senha
    if(e == 4){
     e = 0;
     definirSenha(Digito[0],Digito[1],Digito[2],Digito[3]);
     //Com o termino da digitação dos 4 digitos, voltamos os mesmos ao estado inicial
     Digito[0] = 0;
     Digito[1] = 0;
     Digito[2] = 0;
     Digito[3] = 0; 
    }
    }     
  }
  //A função if de ativar a senha após 4 digitos serem presionados no controle
  if(lerBotao == 1 && controle != 16580863 && controle != 16613503 && controle != 16597183){
  	//Após a digitação dos 4 digitos a função irá desativar ou ativar o alarme
    //Armazena um digito por vez no vetor digito
    Digito[d] = controle;
    controle = 16580863;
    d++;
    //Quando chega ao ultimo dígito, reseta d, e ativa a função de acionar a senha
    if(d == 4){
     d = 0;
     senha(Digito[0],Digito[1],Digito[2],Digito[3]);
     erro++;
      //Caso a pessoa erre a senha 3 vezes, o alarme é ligado
      if(erro >= 3){
      erro = -1;
      ligaAlarme = 1;
      digitalWrite(AlarmeSonoro, HIGH);
      }
     //Com o termino da digitação dos 4 digitos, voltamos os mesmos ao estado inicial
     Digito[0] = 0;
     Digito[1] = 0;
     Digito[2] = 0;
     Digito[3] = 0; 
    }
  }
  
  //Se o alarme estiver acionado
  if(ligaAlarme == 1){
  //Verifica se há movimento no sensor, e se tiver, a distância do mesmo 
  cm = distancia();
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
  else if (cm > 200 && cm < 331){
	piscaLed(B);
    digitalWrite(AlarmeSonoro,HIGH);
  }
    
  //Delay para ajudar o tinkercad a não travar  
  delay(100);
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
  float calcDistancia= (duracao) * 0.0343;
  //Se estiver fora da distância do sensor, ele volta 331
  if (calcDistancia>=331){
      calcDistancia=0;
  }
  //Caso a distância estiver dentro dos padrões, movimento é igual a 1
  else{
  	movimento = 1;
  }
  return (calcDistancia); 
  //Delay para ajudar o tinkercad a não travar  
  delay(300);
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
  if(atualMillis - passadoMillis > 100) {
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
  if(atualMillis - passadoMillis > 250) {
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
  if(atualMillis - passadoMillis > 500) {
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

//Funciona para escolher a senha nova
void definirSenha(int d1, int d2, int d3, int d4){
  //de acordo com o lerBotao muda a senha de ativar ou desativar
  if(lerBotao == 2){
  	senhaDesligar1 = d1;
    senhaDesligar2 = d2;
    senhaDesligar3 = d3;
    senhaDesligar4 = d4;
  }else if(lerBotao == 3){
  	senhaLigar1 = d1;
    senhaLigar2 = d2;
    senhaLigar3 = d3;
    senhaLigar4 = d4;
  }
  //Retorna as variaveis ao estado inicial
  controle = 0;
  lerBotao = 0;
}

//Funciona para ver se a senha digitada está certa
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
          	erro = -1;
      	} 
    }
  //Retorna as variaveis ao estado inicial
  controle = 0;
  lerBotao = 0;
}
