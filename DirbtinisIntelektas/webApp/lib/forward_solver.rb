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
		#scan each rule requirement and check if it is in facts
		use = true
		missingFacts = Array.new
		rule.req.each do |req|
			if not(facts.include? req)
				use = false
				missingFacts << req
			end
		end

		#take care of printing messages on invalid rule
		if not(use)
			@resultText[-1] << 'Not using rule ' + rule.to_s +
					' because of missing fact(s) '
			missingFacts.each do |misFact|
				@resultText[-1][-1] += misFact + ' '
			end
			return false
		
		end

		#take care of printing messages on valid rule
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
			@resultText[-1] << 'Goal ' + goal + ' Reached. Terminating.'
			return true
		end

		#iterate through rules
		rules.each_with_index do |rule, i|
			#check if rule is used
			if(rule.used)
				@resultText[-1] << 'Not using rule ' + rule.to_s +
							' because already used. FLAG1.'
				next
			end

			#check if we have result in our facts
			if(facts.include? rule.result)
				@resultText[-1] << 'Not using rule ' + rule.to_s +
						' because its result ' + rule.result +
						' is already in facts. FLAG2.'
				next
			end

			#see if we can apply the rule
			if(rule_can_apply(rule, facts))
				facts.append(rule.result)
				rule.used = true
				@path << i
				#go recursively to next iteration
				return recursive_solver(rules, facts, goal)
				break
			end
		end

		#If we are here - it means, that we have not applied any rule
		@resultText[-1] << 'All rules applied, goal not reached. Terminating.'
		return false
	end

	def solve(rules, facts, goal)
		#initialize
		@resultText.clear
		@path.clear
		@tmpFacts.clear

		#solve recursively
		return recursive_solver(rules, facts, goal)

	end
end
