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
	address : IN STD_LOGIC_VECTOR(3 DOWNTO 0)	
	);
end genre_classifier_avalon_interface;
 
-------------------------------------------------------------------------------
 
architecture interface of genre_classifier_avalon_interface is

  constant SAMPLES : integer := 7;
  type binData is array(0 to 7 ) of std_logic_vector(15 downto 0);
  type sampleBinDatas is array( 0 to SAMPLES )of binData;
  type doneSignals is array(0 to SAMPLES) of std_logic;
  type distances is array(0 to SAMPLES) of std_logic_vector(31 downto 0);
  signal testData : binData;
  signal sampleBinData: sampleBinDatas;
  signal doneArray : doneSignals;
  signal distanceArray : distances;
  signal start : std_logic := '0';
  
  component euclidean_single
    port (
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
		distance : out std_logic_vector(31 downto 0));
  end component;
  
	
  

  
  begin
  
  GEN_EUCLID: for I in 0 to SAMPLES generate
  UX : euclidean_single port map (
		sampleBin0 =>  sampleBinData(0+I)(0),
		sampleBin1 =>  sampleBinData(0+I)(1),
		sampleBin2 =>  sampleBinData(0+I)(2),
		sampleBin3 =>  sampleBinData(0+I)(3),
		sampleBin4 =>  sampleBinData(0+I)(4),
		sampleBin5 =>  sampleBinData(0+I)(5),
		sampleBin6 =>  sampleBinData(0+I)(6),
		sampleBin7 =>  sampleBinData(0+I)(7),
		testBin0 => testData(0), 
		testBin1 => testData(1),
		testBin2 => testData(2),
		testBin3 => testData(3),
		testBin4 => testData(4),
		testBin5 => testData(5),
		testBin6 => testData(6),
		testBin7 => testData(7),
		start => start,
		done => doneArray(I),
		distance => distanceArray(I) );
	end generate GEN_EUCLID;
	
	-- purpose: synchronization of reset
	process (clk, rst_n)
		variable count: integer := 0;
	begin  -- process
	
    if rst_n = '0' then                 -- asynchronous reset (active low)
        start <= '0';
		readdata <= (others => '0');
		testData <= (others => (others => '0'));
		sampleBinData <= (others => (others =>(others => '0')));
		--doneArray <= (others => '0');
		--distanceArray <= (others => (others => '0'));  
    elsif clk'event and clk = '1' then  -- rising clock edge   
		readdata <= (others => '-');	
		
		if( write_en = '1' ) then
			case address is
				--writing in a new value			
				when "0000" =>					
					testData(0) <= writedata(31 downto 16);
					testData(1) <= writedata(15 downto 0);
				when "0001" =>					
					testData(2) <= writedata(31 downto 16);
					testData(3) <= writedata(15 downto 0);
				when "0010" =>					
					testData(4) <= writedata(31 downto 16);
					testData(5) <= writedata(15 downto 0);	
				when "0011" =>					
					testData(6) <= writedata(31 downto 16);
					testData(7) <= writedata(15 downto 0);
				when "0100" =>					
					sampleBinData(to_integer(signed(writedata(31 downto 16))))(0) <= writedata(15 downto 0);
				when "0101" =>					
					sampleBinData(to_integer(signed(writedata(31 downto 16))))(1) <= writedata(15 downto 0);
				when "0110" =>					
					sampleBinData(to_integer(signed(writedata(31 downto 16))))(2) <= writedata(15 downto 0);
				when "0111" =>						
					sampleBinData(to_integer(signed(writedata(31 downto 16))))(3) <= writedata(15 downto 0);
				when "1000" =>	
					sampleBinData(to_integer(signed(writedata(31 downto 16))))(4) <= writedata(15 downto 0);
				when "1001" =>					
					sampleBinData(to_integer(signed(writedata(31 downto 16))))(5) <= writedata(15 downto 0);
				when "1010" =>					
					sampleBinData(to_integer(signed(writedata(31 downto 16))))(6) <= writedata(15 downto 0);
				when "1011" =>					
					sampleBinData(to_integer(signed(writedata(31 downto 16))))(7) <= writedata(15 downto 0);			
				when "1100" => 
					start <= '1';				
				when "1111" =>
					start <= '0';
					readdata <= (others => '0');
					testData <= (others => (others => '0'));
					sampleBinData <= (others => (others =>(others => '0')));
					--doneArray <= (others => '0');
					--distanceArray <= (others => (others => '0'));  		
				when others => null;
			end case;
					
		elsif( read_en = '1') then
			readdata <= (others => '-');			
				--Report ready status
			case address is
				when "0000" =>				
					readdata <= (0 => doneArray(0) , others => '0');
				when "0001" =>
				
					for J in 0 to SAMPLES loop	
						count := count + to_integer(unsigned(distanceArray(J)));
					end loop;
					
					readdata <= std_LOGIC_VECTOR(to_unsigned(count, 32));
				
				when 	others => null;
			end case;
		end if;
	 end if;
	 
	
	end process;
		
end interface;								
					
					
					
				
					
		
	 
	