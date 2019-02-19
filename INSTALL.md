# Instalação

Sendo necessário o uso de sistemas Linux ou análogo, para compilar o prorama basta executar o seguinte comando, via terminal:

	$ gcc main.c -o bin

onde ```main.c``` é o arquivo de código fonte contido neste projeto e bin o nome de saída para o executável.

---

### Execução e Uso

O programa deve ser executado com um dentre dois parâmetros aceitos, que definem o modo de execução do software:

	$ ./bin ucp  # Uso intenso somente da UCP

ou

	$ ./bin ucp-mem  # Uso intenso de UCP e Memória

Para qualquer outra forma de uso, o programa gerará uma mensagem de erro e sairá sem efetuar procedimento algum.
