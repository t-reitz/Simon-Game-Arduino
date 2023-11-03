int numeroAleatorioAtual = 0;
int sequenciaAleatoria[20];
int numeroEscolhidoAtual = 0;
int sequenciaEscolhida[20];
int nivelAtual = 0;
int verificacaoAtual = 0;
bool deveSortear = true;

// Função para reiniciar o jogo - redefinindo todas as variáveis e aplicando efeitos nos LEDs
void reiniciarJogo()
{
  digitalWrite(PINO_LED_VERDE, HIGH);
  digitalWrite(PINO_LED_VERMELHO, HIGH);
  digitalWrite(PINO_LED_AMARELO, HIGH);
  digitalWrite(PINO_LED_AZUL, HIGH);
  delay(1000);
  digitalWrite(PINO_LED_VERDE, LOW);
  digitalWrite(PINO_LED_VERMELHO, LOW);
  digitalWrite(PINO_LED_AMARELO, LOW);
  digitalWrite(PINO_LED_AZUL, LOW);
  delay(1000);
  nivelAtual = 0;
  deveSortear = true;
  verificacaoAtual = 0;
}

// Função para lidar com a escolha incorreta - acionando efeitos nos LEDs e sons
void escolhaIncorreta()
{
  for (int i = 0; i <= 3; i++)
  {
    noTone(PINO_BUZZER);
    digitalWrite(PINO_LED_VERDE, HIGH);
    digitalWrite(PINO_LED_AMARELO, HIGH);
    tone(PINO_BUZZER, 100);
    delay(100);
    noTone(PINO_BUZZER);
    tone(PINO_BUZZER, 200);
    digitalWrite(PINO_LED_VERDE, LOW);
    digitalWrite(PINO_LED_AMARELO, LOW);
    delay(100);
    noTone(PINO_BUZZER);
    tone(PINO_BUZZER, 300);
    digitalWrite(PINO_LED_VERMELHO, HIGH);
    digitalWrite(PINO_LED_AZUL, HIGH);
    delay(100);
    noTone(PINO_BUZZER);
    tone(PINO_BUZZER, 400);
    digitalWrite(PINO_LED_VERMELHO, LOW);
    digitalWrite(PINO_LED_AZUL, LOW);
    delay(100);
  }
  noTone(PINO_BUZZER);
  for (int i = 0; i <= 10; i++)
  {
    sequenciaAleatoria[i] = 0;
  }
  reiniciarJogo();
}

// Função para mostrar a sequência atual com pausas e efeitos sonoros
void mostrarSequenciaAtual()
{
  for (int i = 0; i <= nivelAtual; i++)
  {
    switch (sequenciaAleatoria[i])
    {
      case 1:
        digitalWrite(PINO_LED_VERDE, HIGH);
        tone(PINO_BUZZER, 100);
        delay(500);
        digitalWrite(PINO_LED_VERDE, LOW);
        noTone(PINO_BUZZER);
        delay(500);
        break;
      case 2:
        digitalWrite(PINO_LED_VERMELHO, HIGH);
        tone(PINO_BUZZER, 200);
        delay(500);
        digitalWrite(PINO_LED_VERMELHO, LOW);
        noTone(PINO_BUZZER);
        delay(500);
        break;
      case 3:
        digitalWrite(PINO_LED_AMARELO, HIGH);
        tone(PINO_BUZZER, 300);
        delay(500);
        digitalWrite(PINO_LED_AMARELO, LOW);
        noTone(PINO_BUZZER);
        delay(500);
        break;
      case 4:
        digitalWrite(PINO_LED_AZUL, HIGH);
        tone(PINO_BUZZER, 400);
        delay(500);
        digitalWrite(PINO_LED_AZUL, LOW);
        noTone(PINO_BUZZER);
        delay(500);
    }
  }
}

// Função para verificar a escolha do jogador e compará-la com a sequência sorteada
void verificarEscolha(int pinoSaida, int som)
{
  if (numeroEscolhidoAtual == sequenciaAleatoria[verificacaoAtual])
  {
    digitalWrite(pinoSaida, HIGH);
    tone(PINO_BUZZER, som);
    delay(500);
    digitalWrite(pinoSaida, LOW);
    noTone(PINO_BUZZER);
    delay(500);
    if (verificacaoAtual == nivelAtual)
    {
      nivelAtual++;
      verificacaoAtual = 0;
      deveSortear = true;
    }
    else
    {
      verificacaoAtual++;
    }
  }
  else
    escolhaIncorreta();
}

void setup()
{
  Serial.begin(9600);
  pinMode(BOTAO_VERDE, INPUT_PULLUP); // Botão LED VERDE
  pinMode(BOTAO_VERMELHO, INPUT_PULLUP); // Botão LED VERMELHO
  pinMode(BOTAO_AMARELO, INPUT_PULLUP); // Botão LED AMARELO
  pinMode(BOTAO_AZUL, INPUT_PULLUP); // Botão LED AZUL
  pinMode(BOTAO_RESET, INPUT_PULLUP); // Botão RESET
  pinMode(PINO_LED_VERDE, OUTPUT);  // LED VERDE
  pinMode(PINO_LED_VERMELHO, OUTPUT);  // LED VERMELHO
  pinMode(PINO_LED_AMARELO, OUTPUT); // LED AMARELO
  pinMode(PINO_LED_AZUL, OUTPUT); // LED AZUL
  pinMode(PINO_BUZZER, OUTPUT); // Buzzer
  randomSeed(analogRead(0));
  delay(3000);
}

void loop()
{
  if (nivelAtual != 21)
  {
    if (deveSortear)
    {
      numeroAleatorioAtual = random(1, 5);
      sequenciaAleatoria[nivelAtual] = numeroAleatorioAtual;
      mostrarSequenciaAtual();
    }
    deveSortear = false;
    if (digitalRead(BOTAO_VERDE) == 0)
    {
      numeroEscolhidoAtual = 1;
      verificarEscolha(PINO_LED_VERDE, 100);
    }
    else if (digitalRead(BOTAO_VERMELHO) == 0)
    {
      numeroEscolhidoAtual = 2;
      verificarEscolha(PINO_LED_VERMELHO, 200);
    }
    else if (digitalRead(BOTAO_AMARELO) == 0)
    {
      numeroEscolhidoAtual = 3;
      verificarEscolha(PINO_LED_AMARELO, 300);
    }
    else if (digitalRead(BOTAO_AZUL) == 0)
    {
      numeroEscolhidoAtual = 4;
      verificarEscolha(PINO_LED_AZUL, 400);
    }
    else if (digitalRead(BOTAO_RESET) == 0)
    {
      reiniciarJogo();
    }
  }
  else
  {
    reiniciarJogo();
  }
}
