load 'chaining_rules.rb'

class Forward_solver
	@resultText
	@path
	attr_accessor :resultText
	attr_accessor :path

	def initialize()
		@resultText = Array.new
		@path = Array.new
	end

	def rule_can_apply(rule, facts)
		if(rule.used)
			@resultText[-1] << 'Not using rule ' + rule.to_s +
							' because already used'
			return false
		end

		rule.req.each do |req|
			exists = facts.include? req
			if not(facts.include? req)
				@resultText[-1] << 'Not using rule ' + rule.to_s +
						' because of missing fact ' + req
				return false
			end
		end

		@resultText[-1] << 'Rule ' + rule.to_s + ' applied'
		return true
	end

	def recursive_solver(rules, facts, goal)
		@resultText << Array.new

		#check for goal
		if(facts.include? goal)
			@resultText[-1] << 'Goal ' + goal + ' Reached'
			return true
		end

		#iterate through rules
		rulesApplied = false
		rules.each_with_index do |rule, i|
			if(rule_can_apply(rule, facts))
				facts.append(rule.result)
				rule.used = true
				rulesApplied = true
				@path << i
				break
			end
		end

		if not(rulesApplied)
			@resultText[-1] << 'All rules applied, goal not reached. Terminating'
			return false
		end

		recursive_solver(rules, facts, goal)
	end

	def solve(rules, facts, goal)
		@resultText.clear
		@path.clear
		return recursive_solver(rules, facts, goal)

	end
end
