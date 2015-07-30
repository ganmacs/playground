class MyStruct
  def self.new(*names)
    Class.new do |_obj|
      def initialize(*values)
        @__values = values
      end

      names.each_with_index do |method, i|
        class_eval <<-EOS
          def #{method}
             @__values[#{i}]
          end

          def #{method}=(value)
             @__values[#{i}] = value
          end
        EOS
      end
    end
  end
end

Dog = MyStruct.new(:name, :age)
fred = Dog.new('fred', 5)
fred.age = 6
printf "name:%s age:%d\n", fred.name, fred.age
