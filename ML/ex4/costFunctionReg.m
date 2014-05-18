function [J, grad] = costFunctionReg(theta, X, y, lambda)
%COSTFUNCTIONREG Compute cost and gradient for logistic regression with regularization
%   J = COSTFUNCTIONREG(theta, X, y, lambda) computes the cost of using
%   theta as the parameter for regularized logistic regression and the
%   gradient of the cost w.r.t. to the parameters. 

% Initialize some useful values
m = length(y); % number of training examples

% You need to return the following variables correctly 
J = 0;
grad = zeros(size(theta));

% ====================== YOUR CODE HERE ======================
% Instructions: Compute the cost of a particular choice of theta.
%               You should set J to the cost.
%               Compute the partial derivatives and set grad to the partial
%               derivatives of the cost w.r.t. each parameter in theta


	%Calculate cost value
	tmpTheta = theta;
	tmpTheta(1) = 0; %Do not penalize Theta(0)
	tmpTheta = tmpTheta .** 2;

	h = sigmoid(X*theta);
	singleCost = y .* log(h) + (1 .- y) .* log(1 .- h);
	multipleCost = - sum(singleCost) / m;
	multipleCost = multipleCost + (lambda/(2*m)) * sum(tmpTheta);
	J = multipleCost;

	%Calculate gradients
	tmpTheta = theta;
	tmpTheta(1) = 0; % Do not penalize Theta(0)

	h = (sigmoid(X*theta) .- y);
	h = X' * h;
	h = h ./ m;
	h = h .- (lambda/m) .* tmpTheta;
	grad = h;




% =============================================================

end
