// Definições dos pinos
const int LED_PINS[4] = {2, 3, 4, 5};  // LEDs
const int BUTTON_PINS[4] = {8, 9, 10, 11};  // Botões
const int BUZZER_PIN = 12;
const int RESET_BUTTON_PIN = 6;

int numSorteados[20];  // Array para armazenar a sequência de números sorteados
int nivel = 0;  // Nível atual do jogo
int indiceAtual = 0;  // Índice atual na sequência que o jogador está tentando replicar
bool sortear = true;  // Flag para controlar o sorteio de novos números

// Função para reiniciar o jogo
void reiniciar() {
  // Todos os LEDs piscam três vezes
  for(int j = 0; j < 3; j++) {
    for(int i = 0; i < 4; i++) {
      digitalWrite(LED_PINS[i], HIGH);
    }
    tone(BUZZER_PIN, 1000);
    delay(250);
    for(int i = 0; i < 4; i++) {
      digitalWrite(LED_PINS[i], LOW);
    }
    noTone(BUZZER_PIN);
    delay(250);
  }
  nivel = 0;
  sortear = true;
}

// Função para indicar escolha errada
void escolhaErrada() {
  for(int i = 0; i < 4; i++) {
    digitalWrite(LED_PINS[i], HIGH);
    tone(BUZZER_PIN, 300);
    delay(250);
    digitalWrite(LED_PINS[i], LOW);
    noTone(BUZZER_PIN);
    delay(250);

    // Verifica se o botão de reset foi pressionado durante a sequência de erro
    if(digitalRead(RESET_BUTTON_PIN) == LOW) {
      reiniciar();
      return;
    }
  }
  // Limpa o array numSorteados e reseta o índiceAtual
  for(int i = 0; i <= 20; i++) {
    numSorteados[i] = 0;
  }
  indiceAtual = 0;  // Reseta o índiceAtual
  reiniciar();
}


// Função para mostrar a sequência
void mostrarSequencia() {
  for(int i = 0; i <= nivel; i++) {
    int ledIndex = numSorteados[i] - 1;
    digitalWrite(LED_PINS[ledIndex], HIGH);
    tone(BUZZER_PIN, 100 * (ledIndex + 1));
    delay(500);
    digitalWrite(LED_PINS[ledIndex], LOW);
    noTone(BUZZER_PIN);
    delay(500);
  }
}


// Função para verificar a escolha do jogador
void verificarEscolha(int botaoPressionado) {
  if(botaoPressionado == numSorteados[indiceAtual]) {
    indiceAtual++;
    if(indiceAtual > nivel) {
      nivel++;
      indiceAtual = 0;
      sortear = true;
    }
  } else {
    escolhaErrada();
  }
}


void setup() {
  // Inicializa os pinos dos LEDs e botões
  for(int i = 0; i < 4; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  }
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RESET_BUTTON_PIN, INPUT_PULLUP);

  randomSeed(analogRead(0));
  reiniciar();
}

void loop() {
  if(nivel != 21) {
    if(sortear) {
      numSorteados[nivel] = random(1, 5);  // Sorteia um número entre 1 e 4
      mostrarSequencia();
      sortear = false;
    }

    for(int i = 0; i < 4; i++) {
      if(digitalRead(BUTTON_PINS[i]) == LOW) {
        verificarEscolha(i + 1);
        delay(300);  // Debouncing simples
      }
    }

    // Verifica se o botão de reset foi pressionado
    if(digitalRead(RESET_BUTTON_PIN) == LOW) {
      reiniciar();
      delay(300);  // Debouncing simples
    }
  } else {
    reiniciar();
  }
}
