:DECLARACOES
INTEIRO:numero1;
INTEIRO:numero2;
INTEIRO:numero3;
INTEIRO:aux;
INTEIRO:numero4, numero5, numero6;
REAL:numero7,numero8,_numero9;

:ALGORITMO
# Coloca 3 números em ordem crescente
INPUT numero1;
INPUT numero2;
INPUT numero3;
IF numero1 > numero2 THEN
    ASSIGN 2+3-4+5-6*5-1 TO aux;
    ASSIGN numero1 TO numero2;
    ASSIGN aux TO numero1;
IF numero1 > numero3 AND numero2 <= numero4 AND numero1 > 3 OR numero2 != numero4 THEN
    ASSIGN (numero3) TO aux;
    ASSIGN numero1 TO numero3;
    ASSIGN aux TO numero1;
IF numero2 > numero3 THEN
    ASSIGN numero3 TO aux;
    ASSIGN numero2 TO numero3;
    ASSIGN aux TO numero2;
PRINT(numero1);
PRINT(numero2);
PRINT(numero3);

# Exemplo de loop
ASSIGN 0 TO aux;
WHILE aux<3
    IF aux == 1 THEN
        PRINT("UM");
	ELSE 
	    IF aux == 2 THEN
	        PRINT("DOIS");
	ASSIGN aux+1 TO aux;
		