#!/usr/bin/octave

input = 1616300
input_binary = dec2bin(input)(end - 15 : end)

input_layout = [0, 3; 1, 3; 2, 3; 3, 3; 0, 2; 1, 2; 2, 2; 3, 2; 0, 1; 1, 1; 2, 1; 3, 1; 0, 0; 1, 0; 2, 0; 3, 0]'

num_0 = sum(input_binary(:) == '0')
num_1 = sum(input_binary(:) == '1')

P_1 = num_0 / length(input_binary)
P_2 = num_1 / length(input_binary)

m_1 = [0; 0];
m_2 = [0; 0];
for i=1:1:16
	pos = input_layout(:, i);
	if input_binary(i) == '1'
		m_1 = m_1 .+ pos;
	else
		m_2 = m_2 .+ pos;
	endif
endfor

m_1 = (m_1 / num_0)
m_2 = (m_2 / num_1)

E = (m_1 - m_2)
Off = -0.5 * (m_1 - m_2)' * (m_1 + m_2) + log(P_1)/log(P_2)

err = 0;
for i=1:1:16
	pos = input_layout(:, i);
	real_class = input_binary(i);
	est_class = (m_1 - m_2)' * pos - 0.5 * (m_1 - m_2)' * (m_1 + m_2) + log(P_1)/log(P_2);

	if real_class == '1' && est_class < 0
		err = err + 1;
	elseif real_class == '0' && est_class >= 0
		err = err + 1;
	endif
endfor

err = err / 16



