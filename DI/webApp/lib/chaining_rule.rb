class ChainingRule
	@req
	@result
	@used
	attr_accessor :req
	attr_accessor :result
	attr_accessor :used

	def initialize()
		@req = Array.new
		@result = ""
		@used = false
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

	def reqs_to_s()
		str = ""
		@req.each do |req|
			str += req + " "
		end

		return str
	end
end
