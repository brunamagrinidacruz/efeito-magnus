
## Para executar o código
```
gcc chute.c -o chute -lm
./chute
```
## Usar alguma das entradas:
Velocidade: 36.1m/s Theta: 45º Phi: 30º 

## Em seguida, acessar o gnuplot
```
gnuplot
```
## Executar no gnuplot
```
reset
set xrange[-300:10]
set xlabel 'x'
set yrange[-200:200]
set ylabel 'y'
set zrange[0:50]
set zlabel 'z'
set ticslevel 0
set mxtics 20           
set mytics 20           
set ticscale 1.0, 0.01  
set grid x y mx my lt 1 lc "#77dd77" lw 2
splot 'chute.dat' using 1:2:3 with lines lc "red", 'baliza1.dat' with lines lc "black", 'baliza2.dat' with lines lc "black", 'baliza3.dat' with lines lc "black"
```

Explicação: 
`reset`: Limpa as configurações atuais

`set <EIXO>range[<INFERIOR>:<SUPERIOR>]`: Coloca um limite em <EIXO> de <INFERIOR> até <SUPERIOR>

`set <EIXO>label '<TEXTO>'`: Coloca um label com o texto <TEXTO> no <EIXO> para descrever o eixo

...

`lc <COR>`: Atribui <COR> (nome da cor, hexadecimal ou rgb)
