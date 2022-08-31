%% 图形窗口的分割
%%
% 0--> 2*pi 取60个点
x = linspace(0, 2*pi, 60)
subplot(2, 2, 1)
plot(x, sin(x)-1);
title('sin(x)-1');axis([0, 2*pi, -2, 0])

% 2行，1列，第二个区域
subplot(2, 1, 2)
plot(x, cos(x)+1);
title('cos(x)+1'); axis([0, 2*pi, 0, 2])

subplot(4, 4, 3)
plot(x, tan(x))
title('tan(x)'); axis([0, 2*pi, -40, 40])

subplot(4, 4, 8)
plot(x, cot(x))
title('cot(x)'); axis([0, 2*pi, -35, 35])
