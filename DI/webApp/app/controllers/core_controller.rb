load 'chaining_rules.rb'

class CoreController < ActionController::Base

	def index
	end

	def checkArgs
		if(!params['rules'])
			flash.now[:error] = "Please enter the rules"
			return false
		end
		if(params['rules'].length == 0)
			flash.now[:error] = "Please enter the rules"
			return false
		end

		if(!params['facts'])
			flash.now[:error] = "Please enter the facts"
			return false
		end
		if(params['facts'].length == 0)
			flash.now[:error] = "please enter the facts"
			return false
		end

		if(!params['goal'])
			flash.now[:error] = "Please enter your goal"
			return false
		end
		if(params['goal'].length == 0)
			flash.now[:error] = "Please enter your goal"
			return false
		end
		return true
	end


	def chaining
		if !request.post?
			return
		end

		@ruletext = params['rules']
		@facttext = params['facts']
		@goaltext = params['goal']

		if !checkArgs
			return
		end

		r = ChainingRules.new
		res = r.parse(@ruletext)
		if(res == :parseError)
			flash.now[:error] = "Parse error at line "+ 
						r.errorLine.to_s + ": " +
						r.errorString
			return
		end

		@facts = @facttext.split
		@facts.each do |fact|
			if(fact.length != 1)
				flash.now[:error] = "All facts should be " +
							"space seperated and " +
							"1 charachter in length"
				return
			end
		end

		@goal = @goaltext
		if(@goal.length != 1)
			flash.now[:error] = "goal should be 1 charachter in length"
			return
		end

		@data_exists = true
		@rules_cnt = r.rules.size
		@rules = r.rules
	end
end
