%% 1. Matlab 数据类型
%% 
% 数字
2 + 4
10 -7 
3 * 5
8 / 2

%% 2. 字符与字符串
%% 
s = 'a'
% abs - Get ascci of current char
abs(s)
% char - Convert ascci to a char 
char(65)
% 数字转字符串 The result is '65'
num2str(65)
% Define a string in matlab should use single quota
str = 'I love Matlab & Machine Learning'
length(str)


%% 3. Matrix
%%
% Create a matrix
A = [1 2 3; 4 5 2; 3 2 7; 4 6 8]
% Matrix transpose
B = A'
% Convert to 1 dimension matrix over vertical direction
C = A(:)

A_ = [1 2 3; 4 5 2; 3 2 7]
% inv:Get the inverse matrix of A_
D = inv(A_)
% A_ * A_.inverse = I
A_ * D

% Generate matrix of zeros
E = zeros(10, 5 ,3)
E(:, :, 1) = rand(10, 5)
% randi - uniform distributed fake random integers
% Return a 10 * 5 matrix between [1, 5]
E(:, :, 2) = randi(5, 10, 5)
E(:, :, 3) = randn(10, 5)
