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

# estiamte covariance matrix
S_1 = cov(C_1')
S_2 = cov(C_2')
S = (N(1) - 1) / (length(learn_set) - 2) * S_1 + (N(2) - 1) / (length(learn_set) - 2) * S_2

# estimate classifier error
err = 0;
for i=1:1:16
	pos = input_layout(:, i);
	real_class = input_binary(i);
	est_class = (m(:, 1) - m(:, 2))' * inv(S) * pos - 0.5 * (m(:, 1) - m(:, 2))' * inv(S) * (m(:, 1) + m(:, 2)) + log(P(1)/P(2));

	if real_class == '1' && est_class < 0
		err = err + 1;
	elseif real_class == '0' && est_class >= 0
		err = err + 1;
	endif
endfor

err = err / 16;

off =  - 0.5 * (m(:, 1) - m(:, 2))' * inv(S) * (m(:, 1) + m(:, 2)) + log(P(1)/P(2))

syms x1 x2;
expand( (m(:, 1) - m(:, 2))' * inv(S) * [x1; x2] - 0.5 * (m(:, 1) - m(:, 2))' * inv(S) * (m(:, 1) + m(:, 2)) + log(P(1)/P(2)) )
[-7/8, 0, 21/16]
err * 100



