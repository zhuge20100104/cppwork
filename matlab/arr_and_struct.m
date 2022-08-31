%% 元包数组
%%
% An array with 1 row and 6 cols
A = cell(1, 6)


A{2} = eye(3)
A{5} = magic(5)
B = A{5}

%% 结构体
%%
books = struct('name', {{'Machine Learning' 'Data Mining'}}, 'price', [30  40])
books.name
books.name(1)
books.name{1}

books.price(1)
books.price(2)