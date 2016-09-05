function plotData(X, y)
%PLOTDATA Plots the data points X and y into a new figure 
%   PLOTDATA(x,y) plots the data points with + for the positive examples
%   and o for the negative examples. X is assumed to be a Mx2 matrix.

% Create New Figure
figure; hold on;

% ====================== YOUR CODE HERE ======================
% Instructions: Plot the positive and negative examples on a
%               2D plot, using the option 'k+' for the positive
%               examples and 'ko' for the negative examples.
%
	zero_idx = find(y == 0);
	zero_X = [0: 1: length(zero_idx) - 1];
	one_idx = find(y == 1);
	one_X = [0: 1: length(one_idx) - 1];

	plot(X(zero_idx, 1), X(zero_idx, 2), "o", X(one_idx, 1), X(one_idx, 2), "+");

% =========================================================================



hold off;

end
