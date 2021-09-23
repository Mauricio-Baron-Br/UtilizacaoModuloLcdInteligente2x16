/****************************************************************/
#include<16f877.h>
#use delay(clock=4000000)
#use fast_io(B)
#use fast_io(C)
#fuses NOWDT, XT, PUT, NOPROTECT, NOBROWNOUT, NOLVP, NOCPD, NOWRT
#define E PIN_C3 //define para o compilador que e
#define RS PIN_C1 //define para o compilador que e
/********************************************************/
//definicao de alguns comandos para o display
#define LimpaEMandaCursorInicio 0x01
#define MandaCursorParaSegundaLinha 0xc0
//protopipos de funcao
void Envia_ins(char ins);
void Envia_char(int caracter);
void LCD_Init(void);
//mensagens utilizadas no display maximo 16 letras
const char Mensagem1[16] = "Escreve Linha 1";
const char Mensagem2[16] = "Escreve Linha 2";
void main()
{
  int cont = 0;//usada no envio de mensagem
  set_tris_b(0);//portb configurada como saida
  set_tris_c(0);//portc configurada como saida
  output_b(0);//zera portb
  output_c(0);//zera portc
  LCD_init();//chama a inicializacao do lcd
  
  Envia_ins(LimpaEMandaCursorInicio);//limpa a tela de lcd
  
  cont = 0; //zera cont para iniciar o envio da mensagem
   while(Mensagem1[cont]!=0x00)//enquanto nao for o finalizador
   {
      Envia_char(Mensagem1[cont]);//envia a letra atual
      cont++;
   }
   
   Envia_ins(MandaCursorParaSegundaLinha);//manda o cursor para segunda linha
   cont = 0; //zera cont para iniciar o envio da mensagem
   while(Mensagem2[cont]!=0x00)//enquanto nao for o finalizador
   {
      Envia_char(Mensagem2[cont]);//envia a letra atual
      cont++;
   }
}
//**********************************************************************
//rotina utilizada para o lcd
void Envia_ins(char ins)//funcao para enviar um comando para lcd
{
   output_low(RS);
   output_b(ins); //coloca a instrucao no portb
   output_high(E);
   output_low(E);
   delay_ms(5);
}
void Envia_char(int caracter)//funcao para escrever um caracter no lcd
{
   output_high(RS);
   output_b(caracter); //coloca o caracter no portb
   output_high(E);
   output_low(E);
   delay_ms(1);
   output_low(RS);
}
void LCD_Init(void)//funcao inicializacao do lcd
{
   delay_ms(10); //tempo de startup LCD
   Envia_ins(0x38);
   Envia_ins(0x38);
   Envia_ins(0x0c);
   Envia_ins(0x01);
   delay_ms(1);
}


