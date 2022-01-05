#Projeto Alarme

Esse Projeto tem como finalidade a criação de um alarme no site tinkercad.

Ele tem duas versões, a 1.0 que utiiza uma chave digital e a 2.0 que utiliza um controle remoto para a manipulação do mesmo.

Em ambas versões a intenção é a mesma, possui um sensor de distância que localiza se tem movimento e quão distante o alvo está.
A partir dessas informações o Arduino liga um buzzer (se tiver movimento) e controla a cor de um led dependendo da distância do alvo
(vermelho, muito perto; verde, médio; azul, longe).
Esse sensor é ativado e desativado por duas senha preestabelecidas que pode ser mudadas, na versão 1.0 a mesma é manipulada através de um
painel com 5 chaves e dois botões. 4 das 5 chaves representam um código binário que será usado como senha, Um dos botões é o de ação que
confirma a senha digitada e o outro em conjunto da 5° chave configura a senha. Essa configuração de senha se da de uma maneira que se a
chave estiver com valor 0, ao pressionar o botão de senha o código binario escrito é a nova senha de desativar o alarme e com valor 1, o
novo código e ativar o alarme. Com as senhas configuradas, ao digitar o código de ativação e pressionar o botão ação, o sistema é ligado
e possui as caracteristicas descritas acima, somente será desativado ao digitar a senha correta de desativação e pressionar o botão de ação.
Agora, na versão 2.0, essa manipulação da senha é dada por um controle ifravermelho, ele possui um botão de ação igual o outro (botão Power),
que deve ser utilizado antes de digitar senha de 4 números. Para mudar a senha utiliza-se os botoes VOL+ e FUNC/STOP, para mudar a senha
de destivar e ativar, respectivamente.

OBS: As senhas se iniciam por padrão como 0000 -> Ativar e 1111 -> Desativar.

Links Tinkercad: 1.0 : https://www.tinkercad.com/things/j55ya7mvowF
2.0: https://www.tinkercad.com/things/j55ya7mvowF