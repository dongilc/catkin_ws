# VESCuino CDI CUSTOM_APP RX Messages

Header  header

# FW Version Data
int32 send_mode_index1
int32 fw_ver_major
int32 fw_ver_minor

# Original Get Value Data
#float64 voltage_input        # input voltage (volt)
#float64 temperature_pcb      # temperature of printed circuit board (degrees Celsius)
#float64 current_motor        # motor current (ampere)
#float64 current_input        # input current (ampere)
#float64 speed                # motor electrical speed (revolutions per minute) 
#float64 duty_cycle           # duty cycle (0 to 1)
#float64 charge_drawn         # electric charge drawn from input (ampere-hour)
#float64 charge_regen         # electric charge regenerated to input (ampere-hour)
#float64 energy_drawn         # energy drawn from input (watt-hour)
#float64 energy_regen         # energy regenerated to input (watt-hour)
#float64 displacement         # net tachometer (counts)
#float64 distance_traveled    # total tachnometer (counts)
int32   fault_code
#float64 pid_pos_now    		 # pid position now (deg) 0~360

int32 app_status_code        # application status code

# CAN Status Data 
int32 send_mode_index2
int32 can_devs_num
int32[] can_id
int32[] custom_status

# Raw Encoder Data
float64[] enc_rps		     # Encoder Read Raw Data (No Delay, rad/sec) 
float64[] enc_rad			 # Encoder Read Raw Data (No Delay, rad)
float64[] current			 # can status - current
float64[] duty			     # can status - duty
