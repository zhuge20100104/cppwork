%% 二维平面绘图
%% 绘制三角函数
%%
x = 0:0.01:2*pi
y = sin(x)
%建立一个画布，可以省略不写
figure
plot(x, y)
title('y=sin(x)')
xlabel('x')
ylabel('sin(x)')
% x的值限制在0->2*pi范围之内绘图
xlim([0 2*pi])


%% 另一个关于线型的例子
%%
x = 0:0.01:20;
y1 = 200*exp(-0.05*x).*sin(x);
y2 = 0.8*exp(-0.5*x).*sin(10*x);
figure
[AX, H1,H2] = plotyy(x, y1, x, y2, 'plot');
set(get(AX(1), 'Ylabel'), 'String', 'Slow Decay')
set(get(AX(2), 'Ylabel'), 'String', 'Fast Decay')
xlabel('Time (\musec)')
title('Multiple Decay Rates')
% 设置线型， 虚线， 冒号线
set(H1, 'LineStyle', '--')
set(H2, 'LineStyle', ':')

