%% 求a，b两个数组的和
%%
a = [1 2 3]
b = [4 5 6]
c = a + b

%% 求1-5 的平方和
%%

sum = 0 
for i=1:5
    sum = sum + i ^ 2
end

sum 

%% 求1-5的阶乘的和
sum = 0
for i=1:5
    jiecheng = 1
    for j=1:i
        jiecheng = jiecheng .* j
    end
    sum = sum + jiecheng
end

sum


%% 设计一个 9 * 9 乘法表
%%
a = zeros(9, 9)
for i=1:9
    for j=1:9
        a(i,j) = i .* j
    end
end
a


%% while循环求1-10的和
%% 
sum = 0
i = 1
while i<=10
    sum = sum + i
    i = i + 1
end
sum 


%% while循环求1-100的奇数和
%%
i = 1
sum = 0
while i<=100
    sum = sum + i
    i = i + 2
end
sum 


%% 单个if语句
%%
a = 100
b = 20
if a > b
    '成立'
end


%% if ... else ... 语句
%%
a = 100 
b = 20
if a > b
    '成立'
else
    '不成立'
end

%% if elseif elseif else end
%%
a = 3
if a > 10 && a < 100
    '10 < a < 100'
elseif a > 5 && a < 10
    '5 < a < 10'
elseif a > 0 && a < 5
    '0 < a < 5'
else  
    '100 < a'
end

%% switch ... case ... end语句
a = 'x'
switch a 
    case 'x'
        'x'
    case 'y'
        'y'
    otherwise 
        'others'
end

