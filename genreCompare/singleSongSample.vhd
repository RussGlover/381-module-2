library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
library std;
use std.textio.all;

library work;


entity euclidean_single is
	port(	
		sampleBin0, 
		sampleBin1,
		sampleBin2,
		sampleBin3,
		sampleBin4,
		sampleBin5,
		sampleBin6,
		sampleBin7,
		testBin0, 
		testBin1,
		testBin2,
		testBin3,
		testBin4,
		testBin5,
		testBin6,
		testBin7
		: in std_logic_vector(15 downto 0);
		start: in std_logic;
		done: out std_logic;
		distance : out std_logic_vector(31 downto 0)
	);
end euclidean_single;


architecture behavioural of euclidean_single is	

begin
	process	
	begin
	wait until start = '1';		
		--distance0 := to_unsigned((to_integer(signed(sampleBin0) - signed(testBin0))**2, 32));
		--distance1 := to_unsigned((to_integer(signed(sampleBin1) - signed(testBin1))**2, 32));
		--distance2 := to_unsigned((to_integer(signed(sampleBin2) - signed(testBin2))**2, 32));
		--distance3 := to_unsigned((to_integer(signed(sampleBin3) - signed(testBin3))**2, 32));
		--distance4 := to_unsigned((to_integer(signed(sampleBin4) - signed(testBin4))**2, 32));
		--distance5 := to_unsigned((to_integer(signed(sampleBin5) - signed(testBin5))**2, 32));
		--distance6 := to_unsigned((to_integer(signed(sampleBin6) - signed(testBin6))**2, 32));
		--distance7 := to_unsigned((to_integer(signed(sampleBin7) - signed(testBin7))**2, 32));	
		
		distance <= std_logic_vector(
										to_unsigned((to_integer(signed(sampleBin0) - signed(testBin0))**2), 32) + 
										to_unsigned((to_integer(signed(sampleBin1) - signed(testBin1))**2), 32) +
										to_unsigned((to_integer(signed(sampleBin2) - signed(testBin2))**2), 32) +
										to_unsigned((to_integer(signed(sampleBin3) - signed(testBin3))**2), 32) +
										to_unsigned((to_integer(signed(sampleBin4) - signed(testBin4))**2), 32) +
										to_unsigned((to_integer(signed(sampleBin5) - signed(testBin5))**2), 32) +
										to_unsigned((to_integer(signed(sampleBin6) - signed(testBin6))**2), 32) +
										to_unsigned((to_integer(signed(sampleBin7) - signed(testBin7))**2), 32) );
										
		done <= '1';
	end process;

end behavioural;