load 'chaining_rules.rb'

class Forward_solver
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

	def rule_can_apply(rule, facts)
		if(rule.used)
			@resultText[-1] << 'Not using rule ' + rule.to_s +
							' because already used'
			return false
		end

		use = true
		missingFacts = Array.new
		rule.req.each do |req|
			if not(facts.include? req)
				use = false
				missingFacts << req
			end
		end

		if not(use)
			@resultText[-1] << 'Not using rule ' + rule.to_s +
					' because of missing fact(s) '
			missingFacts.each do |misFact|
				@resultText[-1][-1] += misFact + ' '
			end
			return false
		
		end

		@resultText[-1] << 'Rule ' + rule.to_s + ' applied'
		return true
	end

	def recursive_solver(rules, facts, goal)
		@resultText << Array.new
		@tmpFacts << Array.new

		#put initial iteration facts
		facts.each do |fact|
			@tmpFacts[-1] << fact
		end

		#check for goal
		if(facts.include? goal)
			@resultText[-1] << 'Goal ' + goal + ' Reached'
			return true
		end

		#iterate through rules
		rulesApplied = false
		rules.each_with_index do |rule, i|
			if(facts.include? rule.result)
				@resultText[-1] << 'Not using rule ' + rule.to_s +
						' because its result ' + rule.result +
						' is already in facts'
				next
			end

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
		@tmpFacts.clear
		return recursive_solver(rules, facts, goal)

	end
end
