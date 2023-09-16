#ifndef _DECLARACAO_FUNCOES_H
#define _DECLARACAO_FUNCOES_H

// Funcoes para o motor andar
void mot1_anti(int velo); //* Função para o motor da esquerda girar no sentido anti horario com a velocidade variavel
void mot1_hor(int velo);  //* Função para o motor da esquerda girar no sentido horario com a velocidade variavel
void mot1_par();          //* Função para o motor da esquerda ficar parado
void mot2_anti(int velo); //* Função para o motor da direita girar no sentido anti horario com a velocidade variavel
void mot2_hor(int velo);  //* Função para o motor da direita girar no sentido horario com a velocidade variavel
void mot2_par();          //* Função para o motor da direita ficar parado

// Funcoes de encoder
void enc_frente(int velo_esq, int velo_dir, int enc_valor);   //* Funcao para fazer passos para frente
void enc_direita(int velo_esq, int velo_dir, int enc_valor);  //* Funcao para fazer passos para direita
void enc_esquerda(int velo_esq, int velo_dir, int enc_valor); //* Funcao para fazer passos para esquerda
void enc_re(int velo_esq, int velo_dir, int enc_valor);       //* Funcao para fazer passos para atras

// Funcao para pegar valores de sensor de ver cor
void sensi();

// Funcao para desviar de obstaculo; esq = false; dir = true
void desv(int velo_esq, int velo_dir, bool esq_dir);

// Funcao de 90°
void esq_90(); //* virar para esquerda
void dir_90(); //* virar para direita

#endif