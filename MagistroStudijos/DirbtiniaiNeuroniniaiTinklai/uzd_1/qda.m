#!/usr/bin/octave

pkg load symbolic

input = 1616300
input_binary = dec2bin(input)(end - 15 : end)
input_layout = [0, 3; 1, 3; 2, 3; 3, 3; 0, 2; 1, 2; 2, 2; 3, 2; 0, 1; 1, 1; 2, 1; 3, 1; 0, 0; 1, 0; 2, 0; 3, 0]'
learn_set = input_layout

data = zeros(4, 4);
for i=1:1:16
	pos = input_layout(:, i);
	if input_binary(i) == '0'
		data(pos(1) + 1, pos(2) + 1) = 2;
	elseif input_binary(i) == '1'
		data(pos(1) + 1, pos(2) + 1) = 1;
	endif
endfor
data

# Build up vectors of different classes attributes
C_1 = [];
C_2 = [];
for i=1:1:length(learn_set)
	pos = input_layout(:, i);
	pos = learn_set(:, i);
	if data(pos(1) + 1, pos(2) + 1) == 1
		C_1 = [C_1, pos];
	elseif data(pos(1) + 1, pos(2) + 1) == 2
		C_2 = [C_2, pos];
	endif
endfor
C_1
C_2

# estimate class probability
N = [0; 0];
for i=1:1:length(learn_set)
	pos = learn_set(:, i);
	if data(pos(1) + 1, pos(2) + 1) == 1
		N(1) = N(1) + 1;
	elseif data(pos(1) + 1, pos(2) + 1) == 2
		N(2) = N(2) + 1;
	endif
endfor
P = N / length(learn_set)

# estimate averages for classes
m = [0, 0; 0, 0]';
for i=1:1:length(learn_set)
	pos = learn_set(:, i);
	if data(pos(1) + 1, pos(2) + 1) == 1
		m(:, 1) = m(:, 1) .+ pos;
	elseif data(pos(1) + 1, pos(2) + 1) == 2
		m(:, 2) = m(:, 2) .+ pos;
	endif
endfor
m = [(m(:, 1) / N(1)), (m(:, 2) / N(2))]

# estiamte covariance matrices
S_1 = cov(C_1')
S_2 = cov(C_2')

# estimate classifier error
err = 0;
for i=1:1:16
	pos = input_layout(:, i);
	real_class = input_binary(i);
	est_class = (pos - m(:, 2))' * inv(S_2) * (pos - m(:, 2)) - (pos - m(:, 1))' * inv(S_1) * (pos - m(:, 1)) + log(det(S_2) / det(S_1)) + 2 * log(P(1) / P(2));

	if real_class == '1' && est_class < 0
		err = err + 1;
	elseif real_class == '0' && est_class >= 0
		err = err + 1;
	endif
endfor

err = err / 16;

syms x1 x2;
coefs = expand( ([x1; x2] - m(:, 2))' * inv(S_2) * ([x1; x2] - m(:, 2)) - ([x1; x2] - m(:, 1))' * inv(S_1) * ([x1; x2] - m(:, 1)) + log(det(S_2) / det(S_1)) + 2 * log(P(1) / P(2)) )

[25/48, (19/48) * 2, -(227/96) * 2, (19/48) * 2, 1/48, -(65/96) * 2, -(227/96) * 2, -(65/96) * 2, 245477/42944]
err


