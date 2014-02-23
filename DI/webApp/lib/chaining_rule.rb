class ChainingRule
	@req
	@result
	attr_accessor :req
	attr_accessor :result

	def initialize()
		@req = Array.new
		@result = ""
	end

	def to_s()
		str = ""
		@req.each_with_index do |req, index|
			str += req
			if(index < @req.size - 1)
				str += ", "
			end
		end

		str += " -> " + @result
		return str
	end
end
