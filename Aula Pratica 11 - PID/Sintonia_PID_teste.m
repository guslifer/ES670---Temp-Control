%%Encontra a tangente da resposta do sistema ao degrau

t = temp_out.time;
y = temp_out.data;

yp = gradient(y,t) 

[m, p] = max(yp)

tang = yp(p)*(t-t(p))+y(p)
plot(t,y)
hold on
plot(tm, tang)
plot(t(p),y(p),'ro')


L_pos = knnsearch(tang, 0)
L = y(L_pos)
K = max(y)
T_pos = knnsearch(tang, K)
T = t(T_pos) - t(L_pos)

plot(t(T_pos),tang(T_pos),'ro')







