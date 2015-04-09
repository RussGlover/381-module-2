library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use ieee.math_complex.all;
library std;
use std.textio.all;
 

-------------------------------------------------------------------------------
 
entity genre_classifier_avalon_interface is
 PORT ( clk, rst_n : IN STD_LOGIC;
	read_en, write_en : IN STD_LOGIC;
	writedata : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
	readdata : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
	address : IN STD_LOGIC_VECTOR(7 DOWNTO 0)	
	);
end genre_classifier_avalon_interface;
 
-------------------------------------------------------------------------------
 
architecture interface of genre_classifier_avalon_interface is

  constant SAMPLES : integer := 63;
  type distances is array(0 to SAMPLES) of std_logic_vector(31 downto 0);
  type sampleBinData is array(0 to SAMPLES ) of std_logic_vector(15 downto 0);
  
  component euclidean_single
    port (
        input1bin, input2bin : in std_logic_vector(15 downto 0);
		  distance : out std_logic_vector(31 downto 0)
		);
  end component;
  
  signal distanceArray: distances := (others =>(others => '0'));
  signal sampleBinDataArray: sampleBinData := (others =>(others => '0'));
  signal testData : std_LOGIC_VECTOR(15 downto 0) := (others => '0');
 
  
  
  begin
  
  GEN_EUCLID: for I in 0 to SAMPLES generate
  UX : euclidean_single port map (
		input1bin => testData,
		input2bin => sampleBinDataArray(I),
		distance => distanceArray(I) 
		);
	end generate GEN_EUCLID;
	
	-- purpose: synchronization of reset
	process (clk, rst_n)
	variable address_int : integer := 0;
	begin  -- process
	 
    if rst_n = '0' then                 -- asynchronous reset (active low)
		readdata <= (others => '0');
		testData <= (others => '0');
		sampleBinDataArray <= (others =>(others => '0'));
    elsif clk'event and clk = '1' then  -- rising clock edge   
		readdata <= (others => '-');	
		if( write_en = '1' ) then
			case address is
				--Reset			
				when "00000000" =>					
					readdata <= (others => '0');
					testData <= (others => '0');
					sampleBinDataArray <= (others =>(others => '0'));
				--Writing in sample
				when "00000001" =>					
					sampleBinDataArray(to_integer(signed(writedata(31 downto 16)))) <= writedata(15 downto 0);
				--Write in test Data	
				when "00000010" =>					
					testData <= writedata(15 downto 0);		
				when others => null;
			end case;
					
		elsif( read_en = '1') then
			address_int := to_integer(unsigned(address));
			case address_int is						
				when 0 =>					
					readdata <= distanceArray(0);
				when 1 =>					
					readdata <= distanceArray(1);
				when 2 =>					
					readdata <= distanceArray(2);	
				when 3 =>					
					readdata <= distanceArray(3);
				when 4 =>					
					readdata <= distanceArray(4);
				when 5 =>					
					readdata <= distanceArray(5);	
				when 6 =>					
					readdata <= distanceArray(6);
				when 7 =>					
					readdata <= distanceArray(7);
				when 8 =>					
					readdata <= distanceArray(8);	
				when 9 =>					
					readdata <= distanceArray(9);
				when 10 =>					
					readdata <= distanceArray(10);
				when 11 =>					
					readdata <= distanceArray(11);	
				when 12 =>					
					readdata <= distanceArray(12);
				when 13 =>					
					readdata <= distanceArray(13);
				when 14 =>					
					readdata <= distanceArray(14);	
				when 15 =>					
					readdata <= distanceArray(15);
				when 16 =>					
					readdata <= distanceArray(16);					
				when others => null;
			end case;
			
		
		end if;
	 end if;
	 
	
	end process;
		
end interface;								
					
					
					
				
					
		
	 
	