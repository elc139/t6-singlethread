## Programação Paralela - T6

### Mandelbrot 
### P
### I

##### Lorenzo Schwertner Kaufmann

#### Código

Não chamei de `fractalpar.cpp`. Desenvolvi por cima do original modificando o estilo da programação para utilizar recursos do C++. O código pode ser encontrado na pasta `mandelbrot_mpi` 

As principais classes/arquivos são:

- MandelbrotGenerator.h: Uma classe que engloba o código original, porém apenas gera o Mandelbrot em um vetor passado ao método principal. O salvamento em imagens fica a cargo do método que chamou tal rotina
- MandelbrotManager.h: Classe que gerencia um grupo MPI requisitando batches de frames e juntando a resposta de volta
- MandelbrotWorker.h: Classe que recebe um batch de trabalho, decodifica as informações e encaminha ao MandelbrotGenerator
- main.cpp: Define se o processo será um manager ou worker

#### Slides

[Mandelbrot.pdf](/Mandelbrot.pdf)

##### Animação personalizada

[Custom.gif](Custom.gif) - Minha animação não sofreu muita personalização, são os parâmetros originais, sem cor, porém ela tem uma história. Em um determinado momento do trabalho, decidi testar a criação de 30000 frames. Não me passou pela cabeça que isso seriam 8GB e demoraria uma eternidade. Deixei o computador processando durante mais de uma hora. Ele conseguiu finalizar com sucesso, mas para minha infeliz surpresa o zoom ocorreu em uma região escura (esqueci que isso poderia acontecer). Então 600 frames foram válidos e os outros 29400 são imagens totalmente pretas. Como o trabalho teve várias complicações também, achei poético deixar essa configuração para representar os problemas enfrentados.



##### Referências

https://www.mpich.org/

https://mpitutorial.com/tutorials/

https://wiki.mpich.org/mpich/index.php/Using_the_Hydra_Process_Manager

Além de umas 200 páginas do Stackoverflow para configurar tudo certinho! (😄).
