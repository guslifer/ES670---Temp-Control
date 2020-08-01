%%Encontra a tangente da resposta do sistema ao degrau

t = temp_out.time;
y = temp_out.data;
%derivada num�rica do vetor de pontos e ponto de inflex�o
yp = gradient(y,t); 

[m, p] = max(yp);
%equa��o da linha tangente ao ponto de inflex�o 

tang = yp(p)*(t-t(p))+y(p);
plot(t,y)
hold on
plot(t, tang)
plot(t(p),y(p),'ro')
hold on
%determina��o dos parametros de ZN
L_pos = knnsearch(tang, 0);
L = t(L_pos);
K = max(y);
T_pos = knnsearch(tang, K);
T = t(T_pos) - t(L_pos);

plot(t(T_pos),tang(T_pos),'ro')

%Precisamos verificar se a t�cnica se aplica 

f_incontrol = L/T;

%Ganhos do controlador PID

Kp = 1.2*(T/(K*L)); 
Ki = Kp*1/(2*L); 
Kd = Kp*0.5*L;

