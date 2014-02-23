load 'chaining_rule.rb'

class ChainingRules
	@rules
	@errorLine
	@errorString
	attr_accessor :rules, :errorLine, :errorString

	def initialize()
		@rules = []
		@errorLine = 0
		@errorString = ""
	end

	def parse_line(line, index)
		r = ChainingRule.new

		words = line.split
		if(words.size == 0)
			return :ok
		end

		first_word = true
		acceptable = false
		words.each do |word|
			if(word.start_with?("//"))
				break
			end
			if(word.length > 1)
				@errorLine = index
				@errorString = "Rule argument larger than 1 symbol"
				return :parseError
			end

			if(first_word)
				r.result = word
				first_word = false
			else
				r.req << word
				acceptable = true
			end
		end

		if(!acceptable && first_word == false)
			@errorLine = index
			@errorString = "Not enough data to form a rule"
			return :parseError
		end

		@rules << r
		return :ok
	end

	def parse(text)
		text.lines[1..-1].each_with_index do |line, index|
			res = parse_line(line, index + 2)
			if(res != :ok)
				return res
			end
		end
		return :ok
	end

	def to_s()
		str = ""
		rules.each do |rule|
			str += rule.to_s() + "\n"
		end
		return str
	end
end
