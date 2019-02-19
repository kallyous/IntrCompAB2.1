# Identificação

* Página do repositório do trabalho: [link GitHub](https://github.com/kallyous/IntrCompAB2.1)

* Discente 1
	* Nome: Lucas Carvalho
	* Matrícula: 18211784
	* Distribuição da nota (%): 33.33
* Discente 2
	* Nome: Vitor Magno
	* Matrícula: 18211825
	* Distribuição da nota (%): 33.33
* Discente 3
	* Nome: Suleimane Baldé
	* Matrícula: 18210020
	* Distribuição da nota (%): 33.33
	
# Resultados

## Teste Exclusivo do Uso de UCP

Uso da UCP  
![Uso Exclusivo de UCP](https://i.imgur.com/OYpf0FI.png)
  
## Teste Conjunto do Uso de UCP e Memória

Uso de UCP e Memória  
![Uso de UCP no teste com UCP e Memória](https://i.imgur.com/MngPAJm.png)
  
Uso da Memória  
![Uso de Memória em kilobytes](https://i.imgur.com/bYJiDl7.png)

# Discussão

## Considerações Iniciais

Testes iniciais durante o desenvolvimento do projeto foram realizados em diversas máquinas do IC-UFAL (Instituto de Computação - Universidade Federal de Alagoas), com alguns efeitos interessantes à discussão.

Testes em diversas máquinas demonstraram (para os testes conjuntos de UCP e Memória) que processadores mais potentes resultavam em mais rápido enchimento da memória.  
Isso causou o interessante fenômeno em que máquinas mais potentes travaram ou ficaram irresponsivas alocando a mesma quantidade de memória por ciclo que máquinas menos potentes que conseguiam concluir os testes sem travar e mais responsivas.  
Contudo, somente os dados a respeito dos testes finais feitos com uma máquina escolhida foram utilizadas para esquadrinhar os gráficos deste documento.

Para esquadrinhar os gráficos dos testes finais, somente o software do projeto foi executado no computador, sem outros programas ou processos além dos natios do sistema operacional.  
Para os diversos outros testes feitos, a fim de discussão, o navegador web Firefox foi utilizado em conjunto com os testes para avaliar o comportamento do computador.

Os testes finais foram realizados num notebook da marca Positivo, com UCP de 1.5 GHz (dois núcleos) e 4GB de memória principal, sistema operacional [Lubuntu 18.04 LTS](https://lubuntu.me) rodando nativo (sem máquina virtual).

## Utilização Intensa da UCP

Durante os testes da UCP, em todas as máquinas testadas, não foram notados travamentos ou comportamento irresponsivo por parte das máquinas quando rodando apenas o software de teste (além dos processos do próprio sistema operacional).

Porém, ao se utilizar o navegador Firefox simultaneamente, duas coisas foram notadas: o uso da UCP registrado pelo processo pai caiu, e o Firefox ficou um pouco irresponsivo.

Esperávamos que o navegador ficasse extremamente irresponsivo, já que durante os testes com apenas o software deste projeto, ele consumiu quase todo o tempo da UCP, mas isso não aconteceu.  
Ao contrário do que pensávamos, simplesmente o sistema operacional deu menos tempo de UCP para o software de testes, mantendo o Firefox rodando com quase nenhum impacto ao seu funcionamento normal.

Durante este teste, como pode ser observado no gráfico, há dois momentos em que o processo filho parece usar mais de 100% da UCP, nos segundos 1 (105%) e 2 (106%). Esse comportamento foi apresentado algumas vezes na maioria dos testes e em todas as máquinas que testamos, não somente na máquina dos testes finais.  
Embora não tenhamos chegado a uma conclusão - muito menos unanimidade - sobre a causa do fenômeno, acreditamos ser um erro interno de cálculo do próprio sistema ou algum outro fenômeno relacionado a hyper-threading, multi-threading ou mesmo alguma optimização que economize ou ganhe tempo em processos recorrentes e repetitivos, causando variação superior a 100%. (pode ser uma optimização tanto de hardware, no processador, ou mesmo algum algoritmo do sistema operacional).

Em suma, durante o teste de utilização intensa da UCP, o computador não travou nem ficou irresponsivo de forma notável, e atribuímos este comportamento ao balanceamento e distribuição do tempo de UCP dos processos, feito pelo sistema operacional.

Nota: Se houvesse mais tempo para a realização do projeto, seria muito interessante rodar o mesmo software com dois ou três filhos, para observar a distribuição do tempo de processamento feito pelo sistema operacional entre os filhos e esquadrinhar seus respectivos gráficos.  
Para isso, também seria conveniente usar um método de geração automatizada de gráficos.

## Utilização Intensa da UCP e da Memória

A característica mais marcante desta versão dos testes foi a necessidade de ajustar os valores de memória alocada por ciclo para cada máquina diferente testada. E ainda assim houve variações nos resultados, para uma mesma máquina executando o software de testes diversas vezes.

Mesmo em máquinas com a mesma quantidade de memória e alocando o mesmo valor por ciclo do processo filho, em algumas a memória consumida era pouca, abaixo de 10% da memória total, enquanto outras a memória superava 60% e a máquina travava - as vezes indefinidamente, necessitando-se reiniciar o computador.

Outras máquinas travaram com menos de 40% da memória tendo sido alocada, enquanto a máquina final de testes, rodando os testes logo após ter sido inicializada, atingiu quase 80% de sua memória, com um breve momento de irresponsividade após 8 segundos de execução.

Ao discutirmos o assunto entre os integrantes da equipe, decidimos atribuir esses fenômenos principalmente às seguintes causas:

**1. Uso de memória pelo próprio sistema operacional e sua interface gráfica**

A maioria das máquinas testadas possuem 4GB de memória.  
A máquina que conseguiu alocar maior quantidade de sua memória foi a máquina final de testes, **a única a não utilizar** o sistema operacional Ubuntu 18.04 LTS, mas sim sua variante de interface gráfica mais leve, o Lubuntu.  
Como elementos gráficos ocupam memória em grande quantidade (note como as placas gráficas de maior desempenho sempre possuem muita memória embutida e dedicada somente ao processamento gráfico), a máquina com o sistema operacional de interface gráfica mais leve tinha mais memória disponível para alocar.

**2. Fragmentação da memória**

Uma memória fragmentada acaba por ter partes disponíveis de sua memória que não podem ser alocadas por não estarem contínuas, e quanto maior o tempo de execução do sistema operacional e outros processos, maior a chance de haver secções da memória fragmentadas.  
Testamos o software em vários computadores do IC-UFAL e máquinas praticamente idênticas tiveram resultados diferentes no limite de alocação de memória, bem como as mesmas máquinas mostravam-se capazes de alocar diferentes quantidades de memória (antes de travarem ou tornarem-se irresponsivas) ao executar o mesmo teste várias vezes - e com os mesmos valores de alocação.  
Mesmo para o computador dos testes finais, só foram obtidos valores persistentes quando o software de testes foi rodado pouco após a inicialização do sistema, sem dar muito tempo para a memória ser fragmentada por outros processos.

## Conclusão

Para travar um computador, ocupe a memória, não a UCP.

Ainda assim, muitas vezes o sistema consegue funcionar com sua memória cheia, mesmo que irresponsivo.
