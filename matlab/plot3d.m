%% 三维立体绘图
%%
t = 0:pi/50:10*pi
plot3(sin(t), cos(t), t)
xlabel('sin(t)')
ylabel('cos(t)')
zlabel('t')
% 保存上面的图，接着画
hold on 
% 不要上面的图了，接着画
% hold off 
% 在图形后端加上网格线
grid on 
% 把整个图形的长宽高拉到相等，成正方形
axis square

%% 绘制双峰函数
%%
[x, y, z] = peaks(30)
mesh(x, y, z)
grid