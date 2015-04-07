LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.NUMERIC_STD.ALL;

library work;
--use work.sqrt_package.all;

entity euclidean_single is
	port(	
		input1bin, input2bin : in std_logic_vector(15 downto 0);
		ready: out std_logic;
		distance : out std_logic_vector(31 downto 0)
	);
end euclidean_single;

architecture behavioural of euclidean_single is

--signal operand : unsigned(31 downto 0);

--signal inputbinA, inputbinB : signed(15 downto 0);
signal inputbinA, inputbinB : signed(15 downto 0);

begin
	process(input1bin, input2bin)
	begin
		inputbinA <= signed(input1bin);
		inputbinB <= signed(input2bin);
		--ready <= '0';
		--inputbinA <= input1bin;
		--inputbinB <= input2bin;
	end process;

	process(inputbinA, inputbinB)
	begin
		distance <= std_logic_vector(to_unsigned((to_integer(inputbinA - inputbinB)**2), 32));
		--distance <= inputbinA & inputbinB;
		ready <= '1';
	end process;

end behavioural;