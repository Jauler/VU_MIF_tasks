load 'chaining_rules.rb'

class Backward_solver
	@resultText
	@path
	@tmpFacts
	attr_accessor :resultText
	attr_accessor :path
	attr_accessor :tmpFacts

	def initialize()
		@resultText = Array.new
		@path = Array.new
		@tmpFacts = Array.new
	end

	def recursive_solver(rules, facts, goal, path, usablePath, level)
		@resultText << Array.new
		@tmpFacts << Array.new

		currUsablePath = usablePath.dup

		@resultText[-1] << level
		@resultText[-1] << 'Goal ' + goal

		if(facts.include? goal)
			@resultText[-1] << "Goal is between facts"
			return true
		end

		if(path.include? goal)
			@resultText[-1] << "Loop detected"
			return false
		end

		#search for rule with goal
		rules.each_with_index do |rule, i|
			if(rule.result != goal)
				next
			end

			@resultText[-1] << ' Using rule ' + rule.to_s
			@resultText[-1] << ' New goals ' + rule.reqs_to_s

			#check for every requirement
			allReqsFullfiled = true
			rule.req.each do |req|
				path << goal
				result = recursive_solver(rules, facts, req, path, currUsablePath, level + 1)
				if(result == false)
					@resultText << Array.new
					@resultText[-1] << level
					@resultText[-1] << 'Goal ' + goal
					allReqsFullfiled = false
					path.delete(path.length - 1)
					@path.clear
					break
				end
			end

			#check if we reached goal
			if(allReqsFullfiled)
				@path << i;
				return true
			end
		end

		@resultText[-1] << ' No suitable rule found for current goal'
		return false
	end

	def solve(rules, facts, goal)
		#initialize
		@resultText.clear
		@tmpFacts.clear
		@path.clear

		path = Array.new
		usablePath = Array.new

		#solve recursively
		result = recursive_solver(rules, facts, goal, path, usablePath, 1)

		return result

	end
end
