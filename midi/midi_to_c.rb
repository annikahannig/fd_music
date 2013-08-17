
require 'rubygems'
require 'midilib'

require 'serialport'

# midi 0 -> C_0 -> 16 HZ
tone_map_hz = [
  16.35, 17.32,  18.35,  19.45,  20.60,  21.83,  23.12,  24.50,
  25.96,  27.50,  29.14,  30.87,  32.70,  34.65,  36.71,  38.89,
  41.20,  43.65,  46.25,  49.00,  51.91,  55.00,  58.27,  61.74, 
  65.41,  69.30,  73.42,  77.78,  82.41,  87.31,  92.50,  98.00, 
 103.83,  110.00,  116.54,  123.47,  130.81,  138.59,  146.83,  155.56,
 164.81,  174.61,  185.00,  196.00,  207.65,  220.00,  233.08,  246.94,
 261.63,  277.18,  293.66,  311.13,  329.63,  349.23,  369.99,  392.00
]


filename = 'imperial_short.mid'
outfile  = 'imperial_short.h'

seq = MIDI::Sequence.new

File.open filename, 'rb' do |file|
  seq.read file 
end


#
# Open serial port
#
# fdrive = SerialPort.new '/dev/ttyUSB0', 9600


tones_seq = []
delay_seq = []

# play 
seq.each do |track|
  track.each do |e|
    if e.is_a? MIDI::NoteOn 
      # sleep e.delta_time / 1000.0
      puts "write 0, #{e.delta_time}"
      puts "NoteOn! #{e.note}"
    
      tones_seq << 0
      delay_seq << e.delta_time

      transposed = e.note - (4*8) - 4
      freq = tone_map_hz[transposed] 
      freq = 420 if freq.nil?

      # fdrive.write "200 #{freq.round}\n"
      puts " -> #{freq.round} Hz"
      
      puts "write #{freq.round}, #{e.off.delta_time}"
      tones_seq << freq.round
      delay_seq << e.off.delta_time

      # sleep (e.off.delta_time / 1000.0)

      puts "NoteOff."
      
     # fdrive.write "200 0\n"
    end
  end
end

tones_seq << 255
delay_seq << 0

puts "Tones: "
puts tones_seq.inspect

puts "Delays: "
puts delay_seq.inspect 


puts "Exporting: "

File.open outfile, 'w+' do |out|
  out.write "uint8_t imperial_tones_seq[] = {\n#{tones_seq.join(',')}\n};"
  out.write "\n";
  out.write "\n";
  out.write "uint16_t imperial_delay_seq[] = {\n#{delay_seq.join(',')}\n};"
  out.write "\n";
end






