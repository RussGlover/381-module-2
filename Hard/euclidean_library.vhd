LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.NUMERIC_STD.ALL;

entity euclidean_single_interface is
	port(
		clock, reset : in std_logic;
		writedata : in std_logic_vector(31 downto 0);
		readdata : out std_logic_vector(31 downto 0);
		address : IN STD_LOGIC_VECTOR(2 DOWNTO 0);	
		write_n : in std_logic
	);
end euclidean_single_interface;

architecture behavioural of euclidean_single_interface is
	component euclidean_single
	port (
		input1bin, input2bin : in std_logic_vector(15 downto 0);
		ready : out std_logic;
		distance : out std_logic_vector(31 downto 0)
	);
	end component;

	signal operand1, operand2 : std_logic_vector(15 downto 0) := (others => '0');
	signal result : std_logic_vector(31 downto 0) := (others => '0');
	--signal zeroes : std_logic_vector(191 downto 0) := (others => '0');
	signal isReady: std_logic; 
	signal library_index : std_logic_vector (2 downto 0) := (others => '0');
	signal bin_index : std_logic_vector(1 downt 0) := (others => '0');
	signal lib1, lib2, lib3, lib4, lib5, lib6, lib7 : std_logic_vector (255 downto 0);
	
	
	
	begin
		
		euclidean_distance : euclidean_single port map(
			input1bin => operand1,
			input2bin => operand2,
			ready => isReady,
			distance => result
		);

		process(clock, reset)
			begin
				if (reset = '1') then
					operand1 <= (others => '0');
					operand2 <= (others => '0');
				elsif (rising_edge(clock)) then
				
					if (write_n = '1' && library_index = '000') then
						if (bin_index = '00') then
							lib1 (31 downto 0) <= writedata (31 downto 0);
							bin_index <= '01' 
							--operand1 <= writedata(15 downto 0);
							--operand2 <= writedata(31 downto 16);
						--readdata <= result;
					elsif (isReady = '1') then
						readdata <= result;
					else
						null;
					end if;
				end if;
		end process;

end behavioural;


