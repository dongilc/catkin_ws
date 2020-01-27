/*
	Copyright 2016 Benjamin Vedder	benjamin@vedder.se

	This file is part of the VESC firmware.

	The VESC firmware is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The VESC firmware is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DATATYPES_H_
#define DATATYPES_H_

#include <stdint.h>
#include <stdbool.h>
//#include "ch.h"
typedef uint32_t systime_t; // defined in ch.h

//#define FW_2_18		// datatype fw version, cdi
//#define FW_3_38		// datatype fw version, cdi
#define FW_3_40			// datatype fw version, cdi

#ifdef FW_3_40
// Data types
typedef enum {
   MC_STATE_OFF = 0,
   MC_STATE_DETECTING,
   MC_STATE_RUNNING,
   MC_STATE_FULL_BRAKE,
} mc_state;

typedef enum {
	PWM_MODE_NONSYNCHRONOUS_HISW = 0, // This mode is not recommended
	PWM_MODE_SYNCHRONOUS, // The recommended and most tested mode
	PWM_MODE_BIPOLAR // Some glitches occasionally, can kill MOSFETs
} mc_pwm_mode;

typedef enum {
	COMM_MODE_INTEGRATE = 0,
	COMM_MODE_DELAY
} mc_comm_mode;

typedef enum {
	SENSOR_MODE_SENSORLESS = 0,
	SENSOR_MODE_SENSORED,
	SENSOR_MODE_HYBRID
} mc_sensor_mode;

typedef enum {
	FOC_SENSOR_MODE_SENSORLESS = 0,
	FOC_SENSOR_MODE_ENCODER,
	FOC_SENSOR_MODE_HALL
} mc_foc_sensor_mode;

// Auxiliary output mode
typedef enum {
	OUT_AUX_MODE_OFF = 0,
	OUT_AUX_MODE_ON_AFTER_2S,
	OUT_AUX_MODE_ON_AFTER_5S,
	OUT_AUX_MODE_ON_AFTER_10S
} out_aux_mode;

typedef enum {
	MOTOR_TYPE_BLDC = 0,
	MOTOR_TYPE_DC,
	MOTOR_TYPE_FOC
} mc_motor_type;

typedef enum {
	FAULT_CODE_NONE = 0,
	FAULT_CODE_OVER_VOLTAGE,
	FAULT_CODE_UNDER_VOLTAGE,
	FAULT_CODE_DRV,
	FAULT_CODE_ABS_OVER_CURRENT,
	FAULT_CODE_OVER_TEMP_FET,
	FAULT_CODE_OVER_TEMP_MOTOR
} mc_fault_code;

typedef enum {
	CONTROL_MODE_DUTY = 0,
	CONTROL_MODE_SPEED,
	CONTROL_MODE_CURRENT,
	CONTROL_MODE_CURRENT_BRAKE,
	CONTROL_MODE_POS,
	CONTROL_MODE_HANDBRAKE,
	CONTROL_MODE_OPENLOOP,
	CONTROL_MODE_NONE
} mc_control_mode;

typedef enum {
	DISP_POS_MODE_NONE = 0,
	DISP_POS_MODE_INDUCTANCE,
	DISP_POS_MODE_OBSERVER,
	DISP_POS_MODE_ENCODER,
	DISP_POS_MODE_PID_POS,
	DISP_POS_MODE_PID_POS_ERROR,
	DISP_POS_MODE_ENCODER_OBSERVER_ERROR
} disp_pos_mode;

typedef enum {
	SENSOR_PORT_MODE_HALL = 0,
	SENSOR_PORT_MODE_ABI,
	SENSOR_PORT_MODE_AS5047_SPI
} sensor_port_mode;

typedef struct {
	float cycle_int_limit;
	float cycle_int_limit_running;
	float cycle_int_limit_max;
	float comm_time_sum;
	float comm_time_sum_min_rpm;
	int32_t comms;
	uint32_t time_at_comm;
} mc_rpm_dep_struct;

typedef enum {
	DRV8301_OC_LIMIT = 0,
	DRV8301_OC_LATCH_SHUTDOWN,
	DRV8301_OC_REPORT_ONLY,
	DRV8301_OC_DISABLED
} drv8301_oc_mode;

typedef enum {
	DEBUG_SAMPLING_OFF = 0,
	DEBUG_SAMPLING_NOW,
	DEBUG_SAMPLING_START,
	DEBUG_SAMPLING_TRIGGER_START,
	DEBUG_SAMPLING_TRIGGER_FAULT,
	DEBUG_SAMPLING_TRIGGER_START_NOSEND,
	DEBUG_SAMPLING_TRIGGER_FAULT_NOSEND,
	DEBUG_SAMPLING_SEND_LAST_SAMPLES
} debug_sampling_mode;

typedef enum {
	CAN_BAUD_125K = 0,
	CAN_BAUD_250K,
	CAN_BAUD_500K,
	CAN_BAUD_1M,
	CAN_BAUD_3M
} CAN_BAUD;

typedef struct {
	// Switching and drive
	mc_pwm_mode pwm_mode;
	mc_comm_mode comm_mode;
	mc_motor_type motor_type;
	mc_sensor_mode sensor_mode;
	// Limits
	float l_current_max;
	float l_current_min;
	float l_in_current_max;
	float l_in_current_min;
	float l_abs_current_max;
	float l_min_erpm;
	float l_max_erpm;
	float l_erpm_start;
	float l_max_erpm_fbrake;
	float l_max_erpm_fbrake_cc;
	float l_min_vin;
	float l_max_vin;
	float l_battery_cut_start;
	float l_battery_cut_end;
	bool l_slow_abs_current;
	float l_temp_fet_start;
	float l_temp_fet_end;
	float l_temp_motor_start;
	float l_temp_motor_end;
	float l_temp_accel_dec;
	float l_min_duty;
	float l_max_duty;
	float l_watt_max;
	float l_watt_min;
	// Overridden limits (Computed during runtime)
	float lo_current_max;
	float lo_current_min;
	float lo_in_current_max;
	float lo_in_current_min;
	float lo_current_motor_max_now;
	float lo_current_motor_min_now;
	// Sensorless (bldc)
	float sl_min_erpm;
	float sl_min_erpm_cycle_int_limit;
	float sl_max_fullbreak_current_dir_change;
	float sl_cycle_int_limit;
	float sl_phase_advance_at_br;
	float sl_cycle_int_rpm_br;
	float sl_bemf_coupling_k;
	// Hall sensor
	int8_t hall_table[8];
	float hall_sl_erpm;
	// FOC
	float foc_current_kp;
	float foc_current_ki;
	float foc_f_sw;
	float foc_dt_us;
	float foc_encoder_offset;
	bool foc_encoder_inverted;
	float foc_encoder_ratio;
	float foc_motor_l;
	float foc_motor_r;
	float foc_motor_flux_linkage;
	float foc_observer_gain;
	float foc_observer_gain_slow;
	float foc_pll_kp;
	float foc_pll_ki;
	float foc_duty_dowmramp_kp;
	float foc_duty_dowmramp_ki;
	float foc_openloop_rpm;
	float foc_sl_openloop_hyst;
	float foc_sl_openloop_time;
	float foc_sl_d_current_duty;
	float foc_sl_d_current_factor;
	mc_foc_sensor_mode foc_sensor_mode;
	uint8_t foc_hall_table[8];
	float foc_sl_erpm;
	bool foc_sample_v0_v7;
	bool foc_sample_high_current;
	float foc_sat_comp;
	bool foc_temp_comp;
	float foc_temp_comp_base_temp;
	float foc_current_filter_const;
	// Speed PID
	float s_pid_kp;
	float s_pid_ki;
	float s_pid_kd;
	float s_pid_kd_filter;
	float s_pid_min_erpm;
	bool s_pid_allow_braking;
	// Pos PID
	float p_pid_kp;
	float p_pid_ki;
	float p_pid_kd;
	float p_pid_kd_filter;
	float p_pid_ang_div;
	// Current controller
	float cc_startup_boost_duty;
	float cc_min_current;
	float cc_gain;
	float cc_ramp_step_max;
	// Misc
	int32_t m_fault_stop_time_ms;
	float m_duty_ramp_step;
	float m_current_backoff_gain;
	uint32_t m_encoder_counts;
	sensor_port_mode m_sensor_port_mode;
	bool m_invert_direction;
	drv8301_oc_mode m_drv8301_oc_mode;
	int m_drv8301_oc_adj;
	float m_bldc_f_sw_min;
	float m_bldc_f_sw_max;
	float m_dc_f_sw;
	float m_ntc_motor_beta;
	out_aux_mode m_out_aux_mode;
} mc_configuration;

// Applications to use
typedef enum {
	APP_NONE = 0,
	APP_PPM,
	APP_ADC,
	APP_UART,
	APP_PPM_UART,
	APP_ADC_UART,
	APP_NUNCHUK,
	APP_NRF,
	APP_CUSTOM
} app_use;

// Throttle curve mode
typedef enum {
	THR_EXP_EXPO = 0,
	THR_EXP_NATURAL,
	THR_EXP_POLY
} thr_exp_mode;

// PPM control types
typedef enum {
	PPM_CTRL_TYPE_NONE = 0,
	PPM_CTRL_TYPE_CURRENT,
	PPM_CTRL_TYPE_CURRENT_NOREV,
	PPM_CTRL_TYPE_CURRENT_NOREV_BRAKE,
	PPM_CTRL_TYPE_DUTY,
	PPM_CTRL_TYPE_DUTY_NOREV,
	PPM_CTRL_TYPE_PID,
	PPM_CTRL_TYPE_PID_NOREV
} ppm_control_type;

typedef struct {
	ppm_control_type ctrl_type;
	float pid_max_erpm;
	float hyst;
	float pulse_start;
	float pulse_end;
	float pulse_center;
	bool median_filter;
	bool safe_start;
	float throttle_exp;
	float throttle_exp_brake;
	thr_exp_mode throttle_exp_mode;
	float ramp_time_pos;
	float ramp_time_neg;
	bool multi_esc;
	bool tc;
	float tc_max_diff;
} ppm_config;

// ADC control types
typedef enum {
	ADC_CTRL_TYPE_NONE = 0,
	ADC_CTRL_TYPE_CURRENT,
	ADC_CTRL_TYPE_CURRENT_REV_CENTER,
	ADC_CTRL_TYPE_CURRENT_REV_BUTTON,
	ADC_CTRL_TYPE_CURRENT_REV_BUTTON_BRAKE_ADC,
	ADC_CTRL_TYPE_CURRENT_NOREV_BRAKE_CENTER,
	ADC_CTRL_TYPE_CURRENT_NOREV_BRAKE_BUTTON,
	ADC_CTRL_TYPE_CURRENT_NOREV_BRAKE_ADC,
	ADC_CTRL_TYPE_DUTY,
	ADC_CTRL_TYPE_DUTY_REV_CENTER,
	ADC_CTRL_TYPE_DUTY_REV_BUTTON,
	ADC_CTRL_TYPE_PID,
	ADC_CTRL_TYPE_PID_REV_CENTER,
	ADC_CTRL_TYPE_PID_REV_BUTTON
} adc_control_type;

typedef struct {
	adc_control_type ctrl_type;
	float hyst;
	float voltage_start;
	float voltage_end;
	float voltage_center;
	float voltage2_start;
	float voltage2_end;
	bool use_filter;
	bool safe_start;
	bool cc_button_inverted;
	bool rev_button_inverted;
	bool voltage_inverted;
	bool voltage2_inverted;
	float throttle_exp;
	float throttle_exp_brake;
	thr_exp_mode throttle_exp_mode;
	float ramp_time_pos;
	float ramp_time_neg;
	bool multi_esc;
	bool tc;
	float tc_max_diff;
	uint32_t update_rate_hz;
} adc_config;

// Nunchuk control types
typedef enum {
	CHUK_CTRL_TYPE_NONE = 0,
	CHUK_CTRL_TYPE_CURRENT,
	CHUK_CTRL_TYPE_CURRENT_NOREV
} chuk_control_type;

typedef struct {
	chuk_control_type ctrl_type;
	float hyst;
	float ramp_time_pos;
	float ramp_time_neg;
	float stick_erpm_per_s_in_cc;
	float throttle_exp;
	float throttle_exp_brake;
	thr_exp_mode throttle_exp_mode;
	bool multi_esc;
	bool tc;
	float tc_max_diff;
} chuk_config;

// NRF Datatypes
typedef enum {
	NRF_SPEED_250K = 0,
	NRF_SPEED_1M,
	NRF_SPEED_2M
} NRF_SPEED;

typedef enum {
	NRF_POWER_M18DBM = 0,
	NRF_POWER_M12DBM,
	NRF_POWER_M6DBM,
	NRF_POWER_0DBM,
  NRF_POWER_OFF
} NRF_POWER;

typedef enum {
	NRF_AW_3 = 0,
	NRF_AW_4,
	NRF_AW_5
} NRF_AW;

typedef enum {
	NRF_CRC_DISABLED = 0,
	NRF_CRC_1B,
	NRF_CRC_2B
} NRF_CRC;

typedef enum {
	NRF_RETR_DELAY_250US = 0,
	NRF_RETR_DELAY_500US,
	NRF_RETR_DELAY_750US,
	NRF_RETR_DELAY_1000US,
	NRF_RETR_DELAY_1250US,
	NRF_RETR_DELAY_1500US,
	NRF_RETR_DELAY_1750US,
	NRF_RETR_DELAY_2000US,
	NRF_RETR_DELAY_2250US,
	NRF_RETR_DELAY_2500US,
	NRF_RETR_DELAY_2750US,
	NRF_RETR_DELAY_3000US,
	NRF_RETR_DELAY_3250US,
	NRF_RETR_DELAY_3500US,
	NRF_RETR_DELAY_3750US,
	NRF_RETR_DELAY_4000US
} NRF_RETR_DELAY;

typedef struct {
	NRF_SPEED speed;
	NRF_POWER power;
	NRF_CRC crc_type;
	NRF_RETR_DELAY retry_delay;
	unsigned char retries;
	unsigned char channel;
	unsigned char address[3];
	bool send_crc_ack;
} nrf_config;

//cdi
typedef enum {
	CUSTOM_APP_VESCuino = 0,
	CUSTOM_APP_SMG_FULL_METAL,
	CUSTOM_APP_DIFF_ROBOT
} CUSTOM_APPs;

typedef struct {
	// Custom App
	uint8_t custom_app_mode;

	// IMU
	uint8_t custom_imu_use_mode;
	uint8_t custom_imu_comm_mode[2];
	uint8_t custom_imu_setup_mode[2];
	uint8_t custom_imu_dof[2];
	uint8_t custom_imu_quaternion_filter_mode;
	uint8_t custom_imu_ascale;
	uint8_t custom_imu_gscale;
	uint8_t custom_imu_mscale;
	uint8_t custom_imu_m_mode;
	int custom_imu_rate_freq;

	uint8_t custom_imu_use_acc_bias_user[2];
	float custom_imu_gyro_bias[2][3];
	float custom_imu_accel_bias[2][3];
	float custom_imu_accel_bias_user[2][3];
//	float custom_imu_mag_bias[2][3];
//	float custom_imu_mag_scale[2][3];
//	float custom_imu_magCalibration[2][3];

	// CTM
//	uint32_t custom_ctm_freq;
//	float custom_ctm_spillover_filter_freq;
//	float custom_ctm_Kp;
//	float custom_ctm_Kd;
//	bool custom_ctm_current_limit_flag;
//	float custom_ctm_current_limit;

	// MG PARAM
	uint8_t smg_control_mode;
	uint32_t smg_control_freq;
	bool spillover_filter_flag;
	float spillover_filter_hz;
	bool current_limit_flag;
	float current_limit;
	float deadzone_current;

	float LQR_X[4];
//	float LQR_Y[4];
//	float LQR_Z[4];

} custom_config;

//cdi
typedef struct {
	float js_x;
	float js_y;
	float acc_x;
	float acc_y;
	float acc_z;
	bool bt_c;
	bool bt_z;
} nunchuk_data_norm;

typedef struct {
	// Settings
	uint8_t controller_id;
	uint32_t timeout_msec;
	float timeout_brake_current;
	bool send_can_status;
	uint32_t send_can_status_rate_hz;
	CAN_BAUD can_baud_rate;

	// Application to use
	app_use app_to_use;

	// PPM application settings
	ppm_config app_ppm_conf;

	// ADC application settings
	adc_config app_adc_conf;

	// UART application settings
	uint32_t app_uart_baudrate;

	// Nunchuk application settings
	chuk_config app_chuk_conf;

	// NRF application settings
	nrf_config app_nrf_conf;

	// Custom application setting
	custom_config app_custom;
} app_configuration;

// Communication commands
typedef enum {
	COMM_FW_VERSION = 0,
	COMM_JUMP_TO_BOOTLOADER,
	COMM_ERASE_NEW_APP,
	COMM_WRITE_NEW_APP_DATA,
	COMM_GET_VALUES,
	COMM_SET_DUTY,
	COMM_SET_CURRENT,
	COMM_SET_CURRENT_BRAKE,
	COMM_SET_RPM,
	COMM_SET_POS,
	COMM_SET_HANDBRAKE,
	COMM_SET_DETECT,
	COMM_SET_SERVO_POS,
	COMM_SET_MCCONF,
	COMM_GET_MCCONF,
	COMM_GET_MCCONF_DEFAULT,
	COMM_SET_APPCONF,
	COMM_GET_APPCONF,
	COMM_GET_APPCONF_DEFAULT,
	COMM_SAMPLE_PRINT,
	COMM_TERMINAL_CMD,
	COMM_PRINT,
	COMM_ROTOR_POSITION,
	COMM_EXPERIMENT_SAMPLE,
	COMM_DETECT_MOTOR_PARAM,
	COMM_DETECT_MOTOR_R_L,
	COMM_DETECT_MOTOR_FLUX_LINKAGE,
	COMM_DETECT_ENCODER,
	COMM_DETECT_HALL_FOC,
	COMM_REBOOT,
	COMM_ALIVE,
	COMM_GET_DECODED_PPM,
	COMM_GET_DECODED_ADC,
	COMM_GET_DECODED_CHUK,
	COMM_FORWARD_CAN,
	COMM_SET_CHUCK_DATA,
	COMM_CUSTOM_APP_DATA,
	COMM_NRF_START_PAIRING,
	COMM_SET_DPS,	//cdi
	COMM_SET_GOTO,	//cdi
	COMM_SET_FINDHOME,	//cdi
	COMM_SET_DUTY_PAIR	//cdi
} COMM_PACKET_ID;

// CAN commands
typedef enum {
	CAN_PACKET_SET_DUTY = 0,
	CAN_PACKET_SET_CURRENT,
	CAN_PACKET_SET_CURRENT_BRAKE,
	CAN_PACKET_SET_RPM,
	CAN_PACKET_SET_POS,
	CAN_PACKET_FILL_RX_BUFFER,
	CAN_PACKET_FILL_RX_BUFFER_LONG,
	CAN_PACKET_PROCESS_RX_BUFFER,
	CAN_PACKET_PROCESS_SHORT_BUFFER,
	CAN_PACKET_STATUS,
	CAN_PACKET_SET_CURRENT_REL,
	CAN_PACKET_SET_CURRENT_BRAKE_REL,
	CAN_PACKET_SET_CURRENT_HANDBRAKE,
	CAN_PACKET_SET_CURRENT_HANDBRAKE_REL,
	CAN_PACKET_SET_ENCODER_RESET,	//cdi
	CAN_PACKET_SET_DPS,			//cdi
	CAN_PACKET_SET_GOTO,		//cdi
	CAN_PACKET_SET_FINDHOME,	//cdi
	CAN_PACKET_SET_DUTY_PAIR,	//cdi
	CAN_PACKET_SET_REBOOT,		//cdi
	CAN_PACKET_SET_ALIVE,		//cdi
	CAN_PACKET_SET_CUSTOM_STATUS	//cdi
} CAN_PACKET_ID;

// Logged fault data
typedef struct {
	mc_fault_code fault;
	float current;
	float current_filtered;
	float voltage;
	float duty;
	float rpm;
	int tacho;
	int cycles_running;
	int tim_val_samp;
	int tim_current_samp;
	int tim_top;
	int comm_step;
	float temperature;
	int drv8301_faults;
} fault_data;

// External LED state
typedef enum {
	LED_EXT_OFF = 0,
	LED_EXT_NORMAL,
	LED_EXT_BRAKE,
	LED_EXT_TURN_LEFT,
	LED_EXT_TURN_RIGHT,
	LED_EXT_BRAKE_TURN_LEFT,
	LED_EXT_BRAKE_TURN_RIGHT,
	LED_EXT_BATT
} LED_EXT_STATE;

typedef struct {
	int js_x;
	int js_y;
	int acc_x;
	int acc_y;
	int acc_z;
	bool bt_c;
	bool bt_z;
} chuck_data;

typedef struct {
	int id;
	systime_t rx_time;
	float rpm;
	float current;
	float duty;
	float rps;	//cdi
	float rad;	//cdi
} can_status_msg;

typedef struct {
	uint8_t js_x;
	uint8_t js_y;
	bool bt_c;
	bool bt_z;
	bool bt_push;
	float vbat;
} mote_state;

typedef enum {
	MOTE_PACKET_BATT_LEVEL = 0,
	MOTE_PACKET_BUTTONS,
	MOTE_PACKET_ALIVE,
	MOTE_PACKET_FILL_RX_BUFFER,
	MOTE_PACKET_FILL_RX_BUFFER_LONG,
	MOTE_PACKET_PROCESS_RX_BUFFER,
	MOTE_PACKET_PROCESS_SHORT_BUFFER,
	MOTE_PACKET_PAIRING_INFO
} MOTE_PACKET;

typedef struct {
	float v_in;
	float temp_mos1;
	float temp_mos2;
	float temp_mos3;
	float temp_mos4;
    float temp_mos5;
    float temp_mos6;
    float temp_pcb;
    float current_motor;
    float current_in;
    float rpm;
    float duty_now;
    float amp_hours;
    float amp_hours_charged;
    float watt_hours;
    float watt_hours_charged;
    int tachometer;
    int tachometer_abs;
    mc_fault_code fault_code;
} mc_values;

typedef enum {
	NRF_PAIR_STARTED = 0,
	NRF_PAIR_OK,
	NRF_PAIR_FAIL
} NRF_PAIR_RES;
#endif
// end of FW_3_40

#ifdef FW_3_38
// Data types
typedef enum {
   MC_STATE_OFF = 0,
   MC_STATE_DETECTING,
   MC_STATE_RUNNING,
   MC_STATE_FULL_BRAKE,
} mc_state;

typedef enum {
	PWM_MODE_NONSYNCHRONOUS_HISW = 0, // This mode is not recommended
	PWM_MODE_SYNCHRONOUS, // The recommended and most tested mode
	PWM_MODE_BIPOLAR // Some glitches occasionally, can kill MOSFETs
} mc_pwm_mode;

typedef enum {
	COMM_MODE_INTEGRATE = 0,
	COMM_MODE_DELAY
} mc_comm_mode;

typedef enum {
	SENSOR_MODE_SENSORLESS = 0,
	SENSOR_MODE_SENSORED,
	SENSOR_MODE_HYBRID
} mc_sensor_mode;

typedef enum {
	FOC_SENSOR_MODE_SENSORLESS = 0,
	FOC_SENSOR_MODE_ENCODER,
	FOC_SENSOR_MODE_HALL
} mc_foc_sensor_mode;

typedef enum {
	MOTOR_TYPE_BLDC = 0,
	MOTOR_TYPE_DC,
	MOTOR_TYPE_FOC
} mc_motor_type;

typedef enum {
	FAULT_CODE_NONE = 0,
	FAULT_CODE_OVER_VOLTAGE,
	FAULT_CODE_UNDER_VOLTAGE,
	FAULT_CODE_DRV,
	FAULT_CODE_ABS_OVER_CURRENT,
	FAULT_CODE_OVER_TEMP_FET,
	FAULT_CODE_OVER_TEMP_MOTOR
} mc_fault_code;

typedef enum {
	CONTROL_MODE_DUTY = 0,
	CONTROL_MODE_SPEED,
	CONTROL_MODE_CURRENT,
	CONTROL_MODE_CURRENT_BRAKE,
	CONTROL_MODE_POS,
	CONTROL_MODE_HANDBRAKE,
	CONTROL_MODE_OPENLOOP,
	CONTROL_MODE_NONE
} mc_control_mode;

typedef enum {
	DISP_POS_MODE_NONE = 0,
	DISP_POS_MODE_INDUCTANCE,
	DISP_POS_MODE_OBSERVER,
	DISP_POS_MODE_ENCODER,
	DISP_POS_MODE_PID_POS,
	DISP_POS_MODE_PID_POS_ERROR,
	DISP_POS_MODE_ENCODER_OBSERVER_ERROR
} disp_pos_mode;

typedef enum {
	SENSOR_PORT_MODE_HALL = 0,
	SENSOR_PORT_MODE_ABI,
	SENSOR_PORT_MODE_AS5047_SPI
} sensor_port_mode;

typedef struct {
	float cycle_int_limit;
	float cycle_int_limit_running;
	float cycle_int_limit_max;
	float comm_time_sum;
	float comm_time_sum_min_rpm;
	int32_t comms;
	uint32_t time_at_comm;
} mc_rpm_dep_struct;

typedef enum {
	DRV8301_OC_LIMIT = 0,
	DRV8301_OC_LATCH_SHUTDOWN,
	DRV8301_OC_REPORT_ONLY,
	DRV8301_OC_DISABLED
} drv8301_oc_mode;

typedef enum {
	DEBUG_SAMPLING_OFF = 0,
	DEBUG_SAMPLING_NOW,
	DEBUG_SAMPLING_START,
	DEBUG_SAMPLING_TRIGGER_START,
	DEBUG_SAMPLING_TRIGGER_FAULT,
	DEBUG_SAMPLING_TRIGGER_START_NOSEND,
	DEBUG_SAMPLING_TRIGGER_FAULT_NOSEND,
	DEBUG_SAMPLING_SEND_LAST_SAMPLES
} debug_sampling_mode;

typedef enum {
	CAN_BAUD_125K = 0,
	CAN_BAUD_250K,
	CAN_BAUD_500K,
	CAN_BAUD_1M,
	CAN_BAUD_3M
} CAN_BAUD;

typedef struct {
	// Switching and drive
	mc_pwm_mode pwm_mode;
	mc_comm_mode comm_mode;
	mc_motor_type motor_type;
	mc_sensor_mode sensor_mode;
	// Limits
	float l_current_max;
	float l_current_min;
	float l_in_current_max;
	float l_in_current_min;
	float l_abs_current_max;
	float l_min_erpm;
	float l_max_erpm;
	float l_erpm_start;
	float l_max_erpm_fbrake;
	float l_max_erpm_fbrake_cc;
	float l_min_vin;
	float l_max_vin;
	float l_battery_cut_start;
	float l_battery_cut_end;
	bool l_slow_abs_current;
	float l_temp_fet_start;
	float l_temp_fet_end;
	float l_temp_motor_start;
	float l_temp_motor_end;
	float l_temp_accel_dec;
	float l_min_duty;
	float l_max_duty;
	float l_watt_max;
	float l_watt_min;
	// Overridden limits (Computed during runtime)
	float lo_current_max;
	float lo_current_min;
	float lo_in_current_max;
	float lo_in_current_min;
	float lo_current_motor_max_now;
	float lo_current_motor_min_now;
	// Sensorless (bldc)
	float sl_min_erpm;
	float sl_min_erpm_cycle_int_limit;
	float sl_max_fullbreak_current_dir_change;
	float sl_cycle_int_limit;
	float sl_phase_advance_at_br;
	float sl_cycle_int_rpm_br;
	float sl_bemf_coupling_k;
	// Hall sensor
	int8_t hall_table[8];
	float hall_sl_erpm;
	// FOC
	float foc_current_kp;
	float foc_current_ki;
	float foc_f_sw;
	float foc_dt_us;
	float foc_encoder_offset;
	bool foc_encoder_inverted;
	float foc_encoder_ratio;
	float foc_motor_l;
	float foc_motor_r;
	float foc_motor_flux_linkage;
	float foc_observer_gain;
	float foc_observer_gain_slow;
	float foc_pll_kp;
	float foc_pll_ki;
	float foc_duty_dowmramp_kp;
	float foc_duty_dowmramp_ki;
	float foc_openloop_rpm;
	float foc_sl_openloop_hyst;
	float foc_sl_openloop_time;
	float foc_sl_d_current_duty;
	float foc_sl_d_current_factor;
	mc_foc_sensor_mode foc_sensor_mode;
	uint8_t foc_hall_table[8];
	float foc_sl_erpm;
	bool foc_sample_v0_v7;
	bool foc_sample_high_current;
	float foc_sat_comp;
	bool foc_temp_comp;
	float foc_temp_comp_base_temp;
	float foc_current_filter_const;
	// Speed PID
	float s_pid_kp;
	float s_pid_ki;
	float s_pid_kd;
	float s_pid_kd_filter;
	float s_pid_min_erpm;
	bool s_pid_allow_braking;
	// Pos PID
	float p_pid_kp;
	float p_pid_ki;
	float p_pid_kd;
	float p_pid_kd_filter;
	float p_pid_ang_div;
	// Current controller
	float cc_startup_boost_duty;
	float cc_min_current;
	float cc_gain;
	float cc_ramp_step_max;
	// Misc
	int32_t m_fault_stop_time_ms;
	float m_duty_ramp_step;
	float m_current_backoff_gain;
	uint32_t m_encoder_counts;
	sensor_port_mode m_sensor_port_mode;
	bool m_invert_direction;
	drv8301_oc_mode m_drv8301_oc_mode;
	int m_drv8301_oc_adj;
	float m_bldc_f_sw_min;
	float m_bldc_f_sw_max;
	float m_dc_f_sw;
	float m_ntc_motor_beta;
} mc_configuration;

// Applications to use
typedef enum {
	APP_NONE = 0,
	APP_PPM,
	APP_ADC,
	APP_UART,
	APP_PPM_UART,
	APP_ADC_UART,
	APP_NUNCHUK,
	APP_NRF,
	APP_CUSTOM
} app_use;

// Throttle curve mode
typedef enum {
	THR_EXP_EXPO = 0,
	THR_EXP_NATURAL,
	THR_EXP_POLY
} thr_exp_mode;

// PPM control types
typedef enum {
	PPM_CTRL_TYPE_NONE = 0,
	PPM_CTRL_TYPE_CURRENT,
	PPM_CTRL_TYPE_CURRENT_NOREV,
	PPM_CTRL_TYPE_CURRENT_NOREV_BRAKE,
	PPM_CTRL_TYPE_DUTY,
	PPM_CTRL_TYPE_DUTY_NOREV,
	PPM_CTRL_TYPE_PID,
	PPM_CTRL_TYPE_PID_NOREV
} ppm_control_type;

typedef struct {
	ppm_control_type ctrl_type;
	float pid_max_erpm;
	float hyst;
	float pulse_start;
	float pulse_end;
	float pulse_center;
	bool median_filter;
	bool safe_start;
	float throttle_exp;
	float throttle_exp_brake;
	thr_exp_mode throttle_exp_mode;
	float ramp_time_pos;
	float ramp_time_neg;
	bool multi_esc;
	bool tc;
	float tc_max_diff;
} ppm_config;

// ADC control types
typedef enum {
	ADC_CTRL_TYPE_NONE = 0,
	ADC_CTRL_TYPE_CURRENT,
	ADC_CTRL_TYPE_CURRENT_REV_CENTER,
	ADC_CTRL_TYPE_CURRENT_REV_BUTTON,
	ADC_CTRL_TYPE_CURRENT_REV_BUTTON_BRAKE_ADC,
	ADC_CTRL_TYPE_CURRENT_NOREV_BRAKE_CENTER,
	ADC_CTRL_TYPE_CURRENT_NOREV_BRAKE_BUTTON,
	ADC_CTRL_TYPE_CURRENT_NOREV_BRAKE_ADC,
	ADC_CTRL_TYPE_DUTY,
	ADC_CTRL_TYPE_DUTY_REV_CENTER,
	ADC_CTRL_TYPE_DUTY_REV_BUTTON,
	ADC_CTRL_TYPE_PID,
	ADC_CTRL_TYPE_PID_REV_CENTER,
	ADC_CTRL_TYPE_PID_REV_BUTTON
} adc_control_type;

typedef struct {
	adc_control_type ctrl_type;
	float hyst;
	float voltage_start;
	float voltage_end;
	float voltage_center;
	float voltage2_start;
	float voltage2_end;
	bool use_filter;
	bool safe_start;
	bool cc_button_inverted;
	bool rev_button_inverted;
	bool voltage_inverted;
	bool voltage2_inverted;
	float throttle_exp;
	float throttle_exp_brake;
	thr_exp_mode throttle_exp_mode;
	float ramp_time_pos;
	float ramp_time_neg;
	bool multi_esc;
	bool tc;
	float tc_max_diff;
	uint32_t update_rate_hz;
} adc_config;

// Nunchuk control types
typedef enum {
	CHUK_CTRL_TYPE_NONE = 0,
	CHUK_CTRL_TYPE_CURRENT,
	CHUK_CTRL_TYPE_CURRENT_NOREV
} chuk_control_type;

typedef struct {
	chuk_control_type ctrl_type;
	float hyst;
	float ramp_time_pos;
	float ramp_time_neg;
	float stick_erpm_per_s_in_cc;
	float throttle_exp;
	float throttle_exp_brake;
	thr_exp_mode throttle_exp_mode;
	bool multi_esc;
	bool tc;
	float tc_max_diff;
} chuk_config;

// NRF Datatypes
typedef enum {
	NRF_SPEED_250K = 0,
	NRF_SPEED_1M,
	NRF_SPEED_2M
} NRF_SPEED;

typedef enum {
	NRF_POWER_M18DBM = 0,
	NRF_POWER_M12DBM,
	NRF_POWER_M6DBM,
	NRF_POWER_0DBM,
  NRF_POWER_OFF
} NRF_POWER;

typedef enum {
	NRF_AW_3 = 0,
	NRF_AW_4,
	NRF_AW_5
} NRF_AW;

typedef enum {
	NRF_CRC_DISABLED = 0,
	NRF_CRC_1B,
	NRF_CRC_2B
} NRF_CRC;

typedef enum {
	NRF_RETR_DELAY_250US = 0,
	NRF_RETR_DELAY_500US,
	NRF_RETR_DELAY_750US,
	NRF_RETR_DELAY_1000US,
	NRF_RETR_DELAY_1250US,
	NRF_RETR_DELAY_1500US,
	NRF_RETR_DELAY_1750US,
	NRF_RETR_DELAY_2000US,
	NRF_RETR_DELAY_2250US,
	NRF_RETR_DELAY_2500US,
	NRF_RETR_DELAY_2750US,
	NRF_RETR_DELAY_3000US,
	NRF_RETR_DELAY_3250US,
	NRF_RETR_DELAY_3500US,
	NRF_RETR_DELAY_3750US,
	NRF_RETR_DELAY_4000US
} NRF_RETR_DELAY;

typedef struct {
	NRF_SPEED speed;
	NRF_POWER power;
	NRF_CRC crc_type;
	NRF_RETR_DELAY retry_delay;
	unsigned char retries;
	unsigned char channel;
	unsigned char address[3];
	bool send_crc_ack;
} nrf_config;

//cdi
typedef struct {
	// IMU
	uint8_t custom_imu_use_mode;
	uint8_t custom_imu_comm_mode;
	uint8_t custom_imu_setup_mode;
	uint8_t custom_imu_dof;
	uint8_t custom_imu_quaternion_filter_mode;
	uint8_t custom_imu_ascale;
	uint8_t custom_imu_gscale;
	uint8_t custom_imu_mscale;
	uint8_t custom_imu_m_mode;
	uint8_t custom_imu_use_acc_bias_user;
	int custom_imu_rate_freq;

	float custom_imu_accel_bias_user[3];
	float custom_imu_mag_bias[3];
	float custom_imu_mag_scale[3];

	// CTM
	uint32_t custom_ctm_freq;
	float custom_ctm_spillover_filter_freq;
	float custom_ctm_Kp;
	float custom_ctm_Kd;
	bool custom_ctm_current_limit_flag;
	float custom_ctm_current_limit;
} custom_config;

typedef struct {
	// Settings
	uint8_t controller_id;
	uint32_t timeout_msec;
	float timeout_brake_current;
	bool send_can_status;
	uint32_t send_can_status_rate_hz;
	CAN_BAUD can_baud_rate;

	// Application to use
	app_use app_to_use;

	// PPM application settings
	ppm_config app_ppm_conf;

	// ADC application settings
	adc_config app_adc_conf;

	// UART application settings
	uint32_t app_uart_baudrate;

	// Nunchuk application settings
	chuk_config app_chuk_conf;

	// NRF application settings
	nrf_config app_nrf_conf;

	// Custom application setting
	custom_config app_custom;
} app_configuration;

// Communication commands
typedef enum {
	COMM_FW_VERSION = 0,
	COMM_JUMP_TO_BOOTLOADER,
	COMM_ERASE_NEW_APP,
	COMM_WRITE_NEW_APP_DATA,
	COMM_GET_VALUES,
	COMM_SET_DUTY,
	COMM_SET_CURRENT,
	COMM_SET_CURRENT_BRAKE,
	COMM_SET_RPM,
	COMM_SET_POS,
	COMM_SET_HANDBRAKE,
	COMM_SET_DETECT,
	COMM_SET_SERVO_POS,
	COMM_SET_MCCONF,
	COMM_GET_MCCONF,
	COMM_GET_MCCONF_DEFAULT,
	COMM_SET_APPCONF,
	COMM_GET_APPCONF,
	COMM_GET_APPCONF_DEFAULT,
	COMM_SAMPLE_PRINT,
	COMM_TERMINAL_CMD,
	COMM_PRINT,
	COMM_ROTOR_POSITION,
	COMM_EXPERIMENT_SAMPLE,
	COMM_DETECT_MOTOR_PARAM,
	COMM_DETECT_MOTOR_R_L,
	COMM_DETECT_MOTOR_FLUX_LINKAGE,
	COMM_DETECT_ENCODER,
	COMM_DETECT_HALL_FOC,
	COMM_REBOOT,
	COMM_ALIVE,
	COMM_GET_DECODED_PPM,
	COMM_GET_DECODED_ADC,
	COMM_GET_DECODED_CHUK,
	COMM_FORWARD_CAN,
	COMM_SET_CHUCK_DATA,
	COMM_CUSTOM_APP_DATA,
	COMM_NRF_START_PAIRING
} COMM_PACKET_ID;

// CAN commands
typedef enum {
	CAN_PACKET_SET_DUTY = 0,
	CAN_PACKET_SET_CURRENT,
	CAN_PACKET_SET_CURRENT_BRAKE,
	CAN_PACKET_SET_RPM,
	CAN_PACKET_SET_POS,
	CAN_PACKET_FILL_RX_BUFFER,
	CAN_PACKET_FILL_RX_BUFFER_LONG,
	CAN_PACKET_PROCESS_RX_BUFFER,
	CAN_PACKET_PROCESS_SHORT_BUFFER,
	CAN_PACKET_STATUS,
	CAN_PACKET_SET_CURRENT_REL,
	CAN_PACKET_SET_CURRENT_BRAKE_REL,
	CAN_PACKET_SET_CURRENT_HANDBRAKE,
	CAN_PACKET_SET_CURRENT_HANDBRAKE_REL,
	CAN_PACKET_SET_ENCODER_RESET	//cdi
} CAN_PACKET_ID;

// Logged fault data
typedef struct {
	mc_fault_code fault;
	float current;
	float current_filtered;
	float voltage;
	float duty;
	float rpm;
	int tacho;
	int cycles_running;
	int tim_val_samp;
	int tim_current_samp;
	int tim_top;
	int comm_step;
	float temperature;
	int drv8301_faults;
} fault_data;

// External LED state
typedef enum {
	LED_EXT_OFF = 0,
	LED_EXT_NORMAL,
	LED_EXT_BRAKE,
	LED_EXT_TURN_LEFT,
	LED_EXT_TURN_RIGHT,
	LED_EXT_BRAKE_TURN_LEFT,
	LED_EXT_BRAKE_TURN_RIGHT,
	LED_EXT_BATT
} LED_EXT_STATE;

typedef struct {
	int js_x;
	int js_y;
	int acc_x;
	int acc_y;
	int acc_z;
	bool bt_c;
	bool bt_z;
} chuck_data;

typedef struct {
	int id;
	systime_t rx_time;
	float rpm;
	float current;
	float duty;
	float rps;	//cdi
	float rad;	//cdi
} can_status_msg;

typedef struct {
	uint8_t js_x;
	uint8_t js_y;
	bool bt_c;
	bool bt_z;
	bool bt_push;
	float vbat;
} mote_state;

typedef enum {
	MOTE_PACKET_BATT_LEVEL = 0,
	MOTE_PACKET_BUTTONS,
	MOTE_PACKET_ALIVE,
	MOTE_PACKET_FILL_RX_BUFFER,
	MOTE_PACKET_FILL_RX_BUFFER_LONG,
	MOTE_PACKET_PROCESS_RX_BUFFER,
	MOTE_PACKET_PROCESS_SHORT_BUFFER,
	MOTE_PACKET_PAIRING_INFO
} MOTE_PACKET;

typedef struct {
	float v_in;
	float temp_mos1;
	float temp_mos2;
	float temp_mos3;
	float temp_mos4;
    float temp_mos5;
    float temp_mos6;
    float temp_pcb;
    float current_motor;
    float current_in;
    float rpm;
    float duty_now;
    float amp_hours;
    float amp_hours_charged;
    float watt_hours;
    float watt_hours_charged;
    int tachometer;
    int tachometer_abs;
    mc_fault_code fault_code;
} mc_values;

typedef enum {
	NRF_PAIR_STARTED = 0,
	NRF_PAIR_OK,
	NRF_PAIR_FAIL
} NRF_PAIR_RES;
#endif
// end of FW_3_38

#ifdef FW_2_18
/*
 * datatypes.h
 *
 *  Created on: 14 sep 2014
 *      Author: benjamin, CDI 2.18 Edition
*/

// Data types
typedef enum {
   MC_STATE_OFF = 0,
   MC_STATE_DETECTING,
   MC_STATE_RUNNING,
   MC_STATE_FULL_BRAKE
} mc_state;

typedef enum {
	PWM_MODE_NONSYNCHRONOUS_HISW = 0, // This mode is not recommended
	PWM_MODE_SYNCHRONOUS, // The recommended and most tested mode
	PWM_MODE_BIPOLAR // Some glitches occasionally, can kill MOSFETs
} mc_pwm_mode;

typedef enum {
	COMM_MODE_INTEGRATE = 0,
	COMM_MODE_DELAY
} mc_comm_mode;

typedef enum {
	SENSOR_MODE_SENSORLESS = 0,
	SENSOR_MODE_SENSORED,
	SENSOR_MODE_HYBRID
} mc_sensor_mode;

typedef enum {
	FOC_SENSOR_MODE_SENSORLESS = 0,
	FOC_SENSOR_MODE_ENCODER,
	FOC_SENSOR_MODE_HALL
} mc_foc_sensor_mode;

typedef enum {
	MOTOR_TYPE_BLDC = 0,
	MOTOR_TYPE_DC,
	MOTOR_TYPE_FOC
} mc_motor_type;

typedef enum {
	FAULT_CODE_NONE = 0,
	FAULT_CODE_OVER_VOLTAGE,
	FAULT_CODE_UNDER_VOLTAGE,
	FAULT_CODE_DRV8302,
	FAULT_CODE_ABS_OVER_CURRENT,
	FAULT_CODE_OVER_TEMP_FET,
	FAULT_CODE_OVER_TEMP_MOTOR
} mc_fault_code;

typedef enum {
	CONTROL_MODE_DUTY = 0,
	CONTROL_MODE_SPEED,
	CONTROL_MODE_CURRENT,
	CONTROL_MODE_CURRENT_BRAKE,
	CONTROL_MODE_POS,
	CONTROL_MODE_NONE
} mc_control_mode;

typedef enum {
	DISP_POS_MODE_NONE = 0,
	DISP_POS_MODE_INDUCTANCE,
	DISP_POS_MODE_OBSERVER,
	DISP_POS_MODE_ENCODER,
	DISP_POS_MODE_PID_POS,
	DISP_POS_MODE_PID_POS_ERROR,
	DISP_POS_MODE_ENCODER_OBSERVER_ERROR
} disp_pos_mode;

typedef enum {
	SENSOR_PORT_MODE_HALL = 0,
	SENSOR_PORT_MODE_ABI,
	SENSOR_PORT_MODE_AS5047_SPI
} sensor_port_mode;

typedef struct {
	float cycle_int_limit;
	float cycle_int_limit_running;
	float cycle_int_limit_max;
	float comm_time_sum;
	float comm_time_sum_min_rpm;
	int32_t comms;
	uint32_t time_at_comm;
} mc_rpm_dep_struct;

// CDI EEPROM CUSTOM PARAMETER
#define CDI_EEP_UINT8_NUM   30
#define CDI_EEP_INT32_NUM   10
#define CDI_EEP_FLOAT_NUM   30

//cdi
typedef struct {
	uint8_t	 value_uint8[CDI_EEP_UINT8_NUM];
    int32_t  value_int32[CDI_EEP_INT32_NUM];
	float 	 value_float[CDI_EEP_FLOAT_NUM];
} cdi_eep_struct;

//
typedef enum {
	//
    MG_SPILLOVER_FILTER_FLAG = 0,
	MG_CURRENT_LIMIT_FLAG,
    MG_MOTOR_CONTROL_MODE,
    RS485_ONOFF,
    RS485_AUTO_MANUAL,
    RT_LEGEND_SET,
    IMU_MODE,
    IMU_SETUP_MODE,
    IMU_M_MODE,
    IMU_DOF,
    IMU_QUATERNION_FILTER_SELECT,
    IMU_ASCALE,
    IMU_GSCALE,
    IMU_MSCALE,
	IMU_RATE_INDEX,
	IMU_GROUND_ANGLE_LPF_FLAG,
	IMU_ACC_BIAS_USER_DEFINED_SELECT,
	IMU_ACC_BIAS_USER_DEFINED_SELECT2,
	IMU_MPU_CH_SELECT,
	UINT8_T_20,
	UINT8_T_21,
	UINT8_T_22,
	UINT8_T_23,
	UINT8_T_24,
	UINT8_T_25,
	UINT8_T_26,
	UINT8_T_27,
	UINT8_T_28,
	UINT8_T_29
} cdi_eep_uint8_conf;

typedef enum {
	MG_CONTROL_FREQ = 0,
	MG_K_CT_DUTY_MODE,
	MG_K_CT_CURRENT_MODE,
	MG_SPILLOVER_FILTER_HZ,
	MG_VELOCITY_LOWPASS_FILTER_HZ,
	MG_CURRENT_LIMIT,
	USART3_BAUD_RATE,
	INT32_7,
	INT32_8,
	INT32_9
//	INT32_10,
//	INT32_11,
//	INT32_12,
//	INT32_13,
//	INT32_14,
//	INT32_15,
//	INT32_16,
//	INT32_17,
//	INT32_18,
//	INT32_19,
//	INT32_20
} cdi_eep_int32_conf;

typedef enum {
    MG_LQR_X_0 = 0,
    MG_LQR_X_1,
    MG_LQR_X_2,
	MG_LQR_X_3,
    MG_LQR_Y_0,
    MG_LQR_Y_1,
    MG_LQR_Y_2,
	MG_LQR_Y_3,
	MG_LQR_Z_0,
	MG_LQR_Z_1,
	MG_LQR_Z_2,
	MG_LQR_Z_3,
	MG_DEADZONE_CURRENT,
	MPU9250_MAG_BIAS_X,
	MPU9250_MAG_BIAS_Y,
	MPU9250_MAG_BIAS_Z,
	MPU9250_MAG_SCALE_X,
	MPU9250_MAG_SCALE_Y,
	MPU9250_MAG_SCALE_Z,
	IMU_COMPLIMENTARY_FILTER_CUTOFF_HZ,
	IMU_GYRO_LOWPASS_FILTER_HZ,
	IMU_ACCEL_BIAS_USER_X,
	IMU_ACCEL_BIAS_USER_Y,
	IMU_ACCEL_BIAS_USER_Z,
	IMU_ACCEL_BIAS_USER_X2,
	IMU_ACCEL_BIAS_USER_Y2,
	IMU_ACCEL_BIAS_USER_Z2,
	IMU_GROUND_LPF_CUTOFF_FREQ,
	MG_PITCH_INTEGRAL_CUTOFF_FREQ,
	FLOAT_30
} cdi_eep_float_conf;
// END OF CDI EEPROM CUSTOM PARAMETER

typedef struct {
	// Switching and drive
	mc_pwm_mode pwm_mode;
	mc_comm_mode comm_mode;
	mc_motor_type motor_type;
	mc_sensor_mode sensor_mode;
	// Limits
	float l_current_max;
	float l_current_min;
	float l_in_current_max;
	float l_in_current_min;
	float l_abs_current_max;
	float l_min_erpm;
	float l_max_erpm;
	float l_max_erpm_fbrake;
	float l_max_erpm_fbrake_cc;
	float l_min_vin;
	float l_max_vin;
	float l_battery_cut_start;
	float l_battery_cut_end;
	bool l_slow_abs_current;
	bool l_rpm_lim_neg_torque;
	float l_temp_fet_start;
	float l_temp_fet_end;
	float l_temp_motor_start;
	float l_temp_motor_end;
	float l_min_duty;
	float l_max_duty;
	// Overridden limits (Computed during runtime)
	float lo_current_max;
	float lo_current_min;
	float lo_in_current_max;
	float lo_in_current_min;
	// Sensorless
	float sl_min_erpm;
	float sl_min_erpm_cycle_int_limit;
	float sl_max_fullbreak_current_dir_change;
	float sl_cycle_int_limit;
	float sl_phase_advance_at_br;
	float sl_cycle_int_rpm_br;
	float sl_bemf_coupling_k;
	// Hall sensor
	int8_t hall_table[8];
	float hall_sl_erpm;
	// FOC
	float foc_current_kp;
	float foc_current_ki;
	float foc_f_sw;
	float foc_dt_us;
	float foc_encoder_offset;
	bool foc_encoder_inverted;
	float foc_encoder_ratio;
	float foc_motor_l;
	float foc_motor_r;
	float foc_motor_flux_linkage;
	float foc_observer_gain;
	float foc_pll_kp;
	float foc_pll_ki;
	float foc_duty_dowmramp_kp;
	float foc_duty_dowmramp_ki;
	float foc_openloop_rpm;
	float foc_sl_openloop_hyst;
	float foc_sl_openloop_time;
	float foc_sl_d_current_duty;
	float foc_sl_d_current_factor;
	mc_foc_sensor_mode foc_sensor_mode;
	uint8_t foc_hall_table[8];
	float foc_sl_erpm;
	// Speed PID
	float s_pid_kp;
	float s_pid_ki;
	float s_pid_kd;
	float s_pid_min_erpm;
	// Pos PID
	float p_pid_kp;
	float p_pid_ki;
	float p_pid_kd;
	float p_pid_ang_div;
	// Current controller
	float cc_startup_boost_duty;
	float cc_min_current;
	float cc_gain;
	float cc_ramp_step_max;
	// Misc
	int32_t m_fault_stop_time_ms;
	float m_duty_ramp_step;
	float m_duty_ramp_step_rpm_lim;
	float m_current_backoff_gain;
	uint32_t m_encoder_counts;
	sensor_port_mode m_sensor_port_mode;
} mc_configuration;

// Applications to use
typedef enum {
	APP_NONE = 0,
	APP_PPM,
	APP_ADC,
	APP_UART,
	APP_PPM_UART,
	APP_ADC_UART,
	APP_NUNCHUK,
	APP_NRF,
	APP_CUSTOM,
	APP_OMNI_ROBOT,		//cdi
	APP_BAL_TESTBOT,	//cdi
	APP_M1_CTM,			//cdi
	APP_DYNAMIXEL,		//cdi
	APP_SMG_OMNI,		//cdi
	APP_SMG_DIFF_PROTO1,	//cdi
	APP_SMG_DIFF_PROTO2,	//cdi
	APP_SMG_PROTO3,	//cdi
	APP_AMG_DIFF_PROTO1		//cdi
} app_use;

// PPM control types
typedef enum {
	PPM_CTRL_TYPE_NONE = 0,
	PPM_CTRL_TYPE_CURRENT,
	PPM_CTRL_TYPE_CURRENT_NOREV,
	PPM_CTRL_TYPE_CURRENT_NOREV_BRAKE,
	PPM_CTRL_TYPE_DUTY,
	PPM_CTRL_TYPE_DUTY_NOREV,
	PPM_CTRL_TYPE_PID,
	PPM_CTRL_TYPE_PID_NOREV
} ppm_control_type;

typedef struct {
	ppm_control_type ctrl_type;
	float pid_max_erpm;
	float hyst;
	float pulse_start;
	float pulse_end;
	bool median_filter;
	bool safe_start;
	float rpm_lim_start;
	float rpm_lim_end;
	bool multi_esc;
	bool tc;
	float tc_max_diff;
} ppm_config;

// ADC control types
typedef enum {
	ADC_CTRL_TYPE_NONE = 0,
	ADC_CTRL_TYPE_CURRENT,
	ADC_CTRL_TYPE_CURRENT_REV_CENTER,
	ADC_CTRL_TYPE_CURRENT_REV_BUTTON,
	ADC_CTRL_TYPE_CURRENT_NOREV_BRAKE_CENTER,
	ADC_CTRL_TYPE_CURRENT_NOREV_BRAKE_BUTTON,
	ADC_CTRL_TYPE_CURRENT_NOREV_BRAKE_ADC,
	ADC_CTRL_TYPE_DUTY,
	ADC_CTRL_TYPE_DUTY_REV_CENTER,
	ADC_CTRL_TYPE_DUTY_REV_BUTTON
} adc_control_type;

typedef struct {
	adc_control_type ctrl_type;
	float hyst;
	float voltage_start;
	float voltage_end;
	bool use_filter;
	bool safe_start;
	bool cc_button_inverted;
	bool rev_button_inverted;
	bool voltage_inverted;
	float rpm_lim_start;
	float rpm_lim_end;
	bool multi_esc;
	bool tc;
	float tc_max_diff;
	uint32_t update_rate_hz;
} adc_config;

// Nunchuk control types
typedef enum {
	CHUK_CTRL_TYPE_NONE = 0,
	CHUK_CTRL_TYPE_CURRENT,
	CHUK_CTRL_TYPE_CURRENT_NOREV,
	CHUK_CTRL_TYPE_SEND_OVER_CAN	//cdi
} chuk_control_type;

typedef struct {
	chuk_control_type ctrl_type;
	float hyst;
	float rpm_lim_start;
	float rpm_lim_end;
	float ramp_time_pos;
	float ramp_time_neg;
	float stick_erpm_per_s_in_cc;
	bool multi_esc;
	bool tc;
	float tc_max_diff;
} chuk_config;

// NRF Datatypes
typedef enum {
	NRF_SPEED_250K = 0,
	NRF_SPEED_1M,
	NRF_SPEED_2M
} NRF_SPEED;

typedef enum {
	NRF_POWER_M18DBM = 0,
	NRF_POWER_M12DBM,
	NRF_POWER_M6DBM,
	NRF_POWER_0DBM
} NRF_POWER;

typedef enum {
	NRF_AW_3 = 0,
	NRF_AW_4,
	NRF_AW_5
} NRF_AW;

typedef enum {
	NRF_CRC_DISABLED = 0,
	NRF_CRC_1B,
	NRF_CRC_2B
} NRF_CRC;

typedef enum {
	NRF_RETR_DELAY_250US = 0,
	NRF_RETR_DELAY_500US,
	NRF_RETR_DELAY_750US,
	NRF_RETR_DELAY_1000US,
	NRF_RETR_DELAY_1250US,
	NRF_RETR_DELAY_1500US,
	NRF_RETR_DELAY_1750US,
	NRF_RETR_DELAY_2000US,
	NRF_RETR_DELAY_2250US,
	NRF_RETR_DELAY_2500US,
	NRF_RETR_DELAY_2750US,
	NRF_RETR_DELAY_3000US,
	NRF_RETR_DELAY_3250US,
	NRF_RETR_DELAY_3500US,
	NRF_RETR_DELAY_3750US,
	NRF_RETR_DELAY_4000US
} NRF_RETR_DELAY;

typedef struct {
	NRF_SPEED speed;
	NRF_POWER power;
	NRF_CRC crc_type;
	NRF_RETR_DELAY retry_delay;
	unsigned char retries;
	unsigned char channel;
	unsigned char address[3];
	bool send_crc_ack;
} nrf_config;

typedef struct {
	// Settings
	uint8_t controller_id;
	uint32_t timeout_msec;
	float timeout_brake_current;
	bool send_can_status;
	uint32_t send_can_status_rate_hz;

	// Application to use
	app_use app_to_use;

	// PPM application settings
	ppm_config app_ppm_conf;

	// ADC application settings
	adc_config app_adc_conf;

	// UART application settings
	uint32_t app_uart_baudrate;

	// Nunchuk application settings
	chuk_config app_chuk_conf;

	// NRF application settings
	nrf_config app_nrf_conf;
} app_configuration;

// Communication commands
typedef enum {
	COMM_FW_VERSION = 0,
	COMM_JUMP_TO_BOOTLOADER,
	COMM_ERASE_NEW_APP,
	COMM_WRITE_NEW_APP_DATA,
	COMM_GET_VALUES,
	COMM_SET_DUTY,
	COMM_SET_CURRENT,
	COMM_SET_CURRENT_BRAKE,
	COMM_SET_RPM,
	COMM_SET_POS,
	COMM_SET_DETECT,
	COMM_SET_SERVO_POS,
	COMM_SET_MCCONF,
	COMM_GET_MCCONF,
	COMM_GET_MCCONF_DEFAULT,
	COMM_SET_APPCONF,
	COMM_GET_APPCONF,
	COMM_GET_APPCONF_DEFAULT,
	COMM_SAMPLE_PRINT,
	COMM_TERMINAL_CMD,
	COMM_PRINT,
	COMM_ROTOR_POSITION,
	COMM_EXPERIMENT_SAMPLE,
	COMM_DETECT_MOTOR_PARAM,
	COMM_DETECT_MOTOR_R_L,
	COMM_DETECT_MOTOR_FLUX_LINKAGE,
	COMM_DETECT_ENCODER,
	COMM_DETECT_HALL_FOC,
	COMM_REBOOT,
	COMM_ALIVE,
	COMM_GET_DECODED_PPM,
	COMM_GET_DECODED_ADC,
	COMM_GET_DECODED_CHUK,
	COMM_FORWARD_CAN,
	COMM_SET_CHUCK_DATA,
	COMM_CUSTOM_APP_DATA,
	COMM_IK_TEST1,	//ik
	COMM_IK_SET_VR,	//ik
	COMM_IK_SET_DPS,	//ik
	COMM_IK_REQ_ENC,	//ik
	COMM_IK_SET_4W_DPS,	//ik
	COMM_IK_CAN_PACKET_ENC,	//ik
	COMM_IK_RELEASE_MOTOR_ALL,	//ik
	COMM_IK_SET_CURRENT_BRAKE_ALL,	//ik
	COMM_IK_REQ_CURRENT_ALL,	//ik
	COMM_IK_REQ_INDEX_FOUND,	//ik
	COMM_GET_2SPEEDS,	//cdi
	COMM_GET_IMU_DATA,	//cdi
    COMM_GET_IMU_MESSAGE,	//cdi
	COMM_SET_EBIMU_PARAM,	//cdi
	COMM_SET_XBOX360_DATA,	//cdi
    COMM_FORWARD_XBOX360_DATA,	//cdi
	COMM_SET_PID_PARAM,	//cdi
	COMM_SET_PID_STATUS,//cdi
	COMM_SET_CUSTOM_EEPROM_CONF,  //cdi
	COMM_GET_CUSTOM_EEPROM_CONF,  //cdi
	COMM_GET_CUSTOM_EEPROM_CONF_DEFAULT,	//cdi
    COMM_CDI_REQ_WHEEL_SPEED,   //cdi
    COMM_CDI_REQ_ROBOT_SPEED,    //cdi
	COMM_CDI_REQ_ROBOT_POSITION,	//cdi
    COMM_CDI_RT_DATA_SAMPLE,    //cdi
    COMM_QT_SET_DYNAMIXEL_LED, //cdi
    COMM_QT_SET_DYNAMIXEL_TORQUE_STATE, //cdi
    COMM_QT_GET_DYNAMIXEL_CURRENT_POSITION,	//cdi
	COMM_SET_DYNAMIXEL_CURRENT_POSITION,	//cdi
    COMM_QT_SET_DYNAMIXEL_GOAL_POSITION,	//cdi
    COMM_QT_SET_DYNAMIXEL_3AXIS_TORQUE_STATE,   //cdi
    COMM_QT_SET_DYNAMIXEL_3AXIS_GOAL_POSITION,  //cdi
    COMM_MG_STATUS_PRINT,
	COMM_PRINT_IMU_STATUS,
	COMM_UART6_PRINT,
    COMM_ESP8266_AT_COMMAND,
	COMM_SMG_SET_GAIN_TEMP
} COMM_PACKET_ID;

// CAN commands
typedef enum {
	CAN_PACKET_SET_DUTY = 0,
	CAN_PACKET_SET_CURRENT,
	CAN_PACKET_SET_CURRENT_BRAKE,
	CAN_PACKET_SET_RPM,
	CAN_PACKET_SET_POS,
	CAN_PACKET_FILL_RX_BUFFER,
	CAN_PACKET_FILL_RX_BUFFER_LONG,
	CAN_PACKET_PROCESS_RX_BUFFER,
	CAN_PACKET_PROCESS_SHORT_BUFFER,
	CAN_PACKET_STATUS,
	CAN_PACKET_NUNCHUCK_DATA,	//cdi
	CAN_PACKET_IMU_DATA		//cdi
} CAN_PACKET_ID;

// Logged fault data
typedef struct {
	mc_fault_code fault;
	float current;
	float current_filtered;
	float voltage;
	float duty;
	float rpm;
	int tacho;
	int cycles_running;
	int tim_val_samp;
	int tim_current_samp;
	int tim_top;
	int comm_step;
	float temperature;
} fault_data;

// External LED state
typedef enum {
	LED_EXT_OFF = 0,
	LED_EXT_NORMAL,
	LED_EXT_BRAKE,
	LED_EXT_TURN_LEFT,
	LED_EXT_TURN_RIGHT,
	LED_EXT_BRAKE_TURN_LEFT,
	LED_EXT_BRAKE_TURN_RIGHT,
	LED_EXT_BATT
} LED_EXT_STATE;

typedef struct {
	int js_x;
	int js_y;
	int acc_x;
	int acc_y;
	int acc_z;
	bool bt_c;
	bool bt_z;
} nunchuk_data;

typedef struct {
	float js_x;
	float js_y;
	float acc_x;
	float acc_y;
	float acc_z;
	bool bt_c;
	bool bt_z;
} nunchuk_data_norm;

//cdi
typedef struct {
    int jr_x;
    int jr_y;
    int jl_x;
    int jl_y;
    int RT;
    int LT;
    bool RB;
    bool LB;
    bool bt_back;
    bool bt_start;
    bool bt_u;
    bool bt_d;
    bool bt_l;
    bool bt_r;
    bool bt_x;
    bool bt_y;
    bool bt_a;
    bool bt_b;

    bool is_sampling;
    int bt_data;
} xbox360_data;

//cdi
typedef struct {
    float jr_x;
    float jr_y;
    float jl_x;
    float jl_y;
    float RT;
    float LT;
    bool RB;
	bool LB;
	bool bt_back;
	bool bt_start;
	bool bt_u;
	bool bt_d;
	bool bt_l;
	bool bt_r;
	bool bt_x;
	bool bt_y;
	bool bt_a;
	bool bt_b;

    bool is_sampling;
	int bt_data;
} xbox360_norm;

typedef struct {
	int id;
	systime_t rx_time;
	float rpm;
	float current;
	float duty;
	float encoder;
} can_status_msg;

typedef struct {
	uint8_t js_x;
	uint8_t js_y;
	bool bt_c;
	bool bt_z;
	bool bt_push;
	float vbat;
} mote_state;

typedef enum {
	MOTE_PACKET_BATT_LEVEL = 0,
	MOTE_PACKET_BUTTONS,
	MOTE_PACKET_ALIVE,
	MOTE_PACKET_FILL_RX_BUFFER,
	MOTE_PACKET_FILL_RX_BUFFER_LONG,
	MOTE_PACKET_PROCESS_RX_BUFFER,
	MOTE_PACKET_PROCESS_SHORT_BUFFER,
} MOTE_PACKET;

typedef struct {
	float v_in;
	float temp_mos1;
	float temp_mos2;
	float temp_mos3;
	float temp_mos4;
    float temp_mos5;
    float temp_mos6;
    float temp_pcb;
    float current_motor;
    float current_in;
    float rpm;
    float duty_now;
    float amp_hours;
    float amp_hours_charged;
    float watt_hours;
    float watt_hours_charged;
    int tachometer;
    int tachometer_abs;
    mc_fault_code fault_code;
} mc_values;

//cdi, khk
typedef enum {
  EULER_X = 0,
  EULER_Y,
  EULER_Z,
  E_GYRO_X,
  E_GYRO_Y,
  E_GYRO_Z,
  NO_EBIMU_DATA_TYPE
} ebimu_data_type;

//cdi, khk
typedef enum {
  QUAT_X = 0,
  QUAT_Y,
  QUAT_Z,
  QUAT_W,
  Q_GYRO_X,
  Q_GYRO_Y,
  Q_GYRO_Z,
  NO_EBIMU_QUAT_DATA_TYPE
} ebimu_quaternion_data_type;

typedef struct {
    int    	imu_mode;
    uint8_t loop_ms;
    float dt;
    float ax;
    float ay;
    float az;
    float gx;
    float gy;
    float gz;
    float mx;
    float my;
    float mz;
    float euler_x;
    float euler_y;
    float euler_z;
    float quat_x;
    float quat_y;
    float quat_z;
    float quat_w;
    float gyro_x;
    float gyro_y;
    float gyro_z;
    float euler_rate_x;
    float euler_rate_y;
	float euler_rate_z;
	float rate_ms;
	float rate_ms_pp;
	float rate_hz;
	float rate_hz_pp;
	float temperature;

    //
    uint8_t ch_select;
    uint8_t ground_imu_lpf_flag;
    float ground_imu_lpf_cutoff_freq;

    //BNO055
    uint8_t cal_sys;
    uint8_t cal_gyro;
    uint8_t cal_accel;
    uint8_t cal_mag;

    // mpu9250
    uint8_t setup_mode;
    uint8_t dof;
    uint8_t quaternion_filter_mode;
    uint8_t send_over_can;

	// complimentary filter
    float simp_angle_x;
    float simp_angle_y;
    float comp_angle_x_lpf;
    float comp_angle_y_lpf;
    float comp_gyro_x_lpf;
    float comp_gyro_y_lpf;
    float comp_gyro_x_int_hpf;
    float comp_gyro_y_int_hpf;
    float comp_angle_x_mix;
    float comp_angle_x_mix_offset;
    float comp_angle_y_mix;
	float comp_angle_y_mix_offset;
    float comp_cutoff_hz;
    float comp_gyro_lpf_hz;
} IMU_DATA;

typedef enum {
	IMU_NONE = 0,
	IMU_EBIMU_EULER,
	IMU_EBIMU_QUAT,
	IMU_MPU9250_EULER,
	IMU_MPU9250_QUAT,
	IMU_LSM9DS1,
	IMU_BNO055
} IMU_MODE_LIST;

//cdi
typedef enum {
	EBIMU_GET_CONFIG_STATUS = 0,
	EBIMU_FACTORY_RESET,
	EBIMU_VERSION,
	EBIMU_START,
	EBIMU_STOP,
	EBIMU_POWERONSTART,
	EBIMU_GYRO_SENSOR_OUT,
	EBIMU_GYRO_CALIBRATION,
	EBIMU_DATA_SEND_RATE,
	EBIMU_MAGNETO_ONOFF,
	EBIMU_MAGNETO_CALIBRATION,
	EBIMU_MAGNETO_TOLERANCE_SET,
	EBIMU_SEND_MSG_R
} ebimu_param;

//cdi
typedef struct {
    double omega_dot_1;
    double omega_dot_2;
    double omega_dot_3;
    double omega_dot_4;
    double vx;
    double vy;
    double wz;
    double px;
    double py;
    double pwz;
} OMNI_ROBOT_DATA;

typedef struct {
	// rotation velocity of wheel
	float omega_dot;
	float omega_dot_m;
	float omega_m1;
	float omega_dot_m1;
	float omega_dot_m1_des;
	float omega_m2;
	float omega_dot_m2;
	float omega_dot_m2_des;
	float omega_m3;
	float omega_dot_m3;
	float omega_dot_m3_des;
	float omega_m4;
	float omega_dot_m4;
	float omega_dot_m4_des;

	// tilt along x-axis
	float roll;
	float roll_dot;
	float roll_des;
	float roll_dot_des;
	float roll_err;
	float roll_dot_err;
	float roll_dt;

	// tilt along y-axis
	float pitch;
	float pitch_dot;
	float pitch_des;
	float pitch_dot_des;
	float pitch_err;
	float pitch_dot_err;
	float pitch_dt;

	//
	float pitch_int;

	// rotation along z-axis
	float yaw;
	float yaw_dot;
	float yaw_des;
	float yaw_dot_des;
	float yaw_err;
	float yaw_dot_err;
	float yaw_dt;

	// x-axis state
	float x;
	float x_dot;
	float x_dot_lpf;
	float x_des;
	float x_dot_des;
	float x_dot_des_lpf;
	float x_err;
	float x_dot_err;

	// y-axis state
	float y;
	float y_dot;
	float y_dot_lpf;
	float y_des;
	float y_dot_des;
	float y_dot_des_lpf;
	float y_err;
	float y_dot_err;

	// z-axis state
	float z;
	float z_dot;
	float z_dot_lpf;
	float z_des;
	float z_dot_des;
	float z_dot_des_lpf;
	float z_err;
	float z_dot_err;

	float gyro_x;
	float gyro_x_int;
	float gyro_y;
	float gyro_y_int;
	float gyro_z;
	float gyro_z_int;

	float imu_rate_hz;

	uint16_t imu_valid_cnt;

	// control state
	float control_rate_hz;
	float u_x;
	float u_y;
	float u_z;

	// current out
	float current_sensed_1;
	float current_1;
	float current_1_lpf;
	float current_sensed_2;
	float current_2;
	float current_2_lpf;
	float current_sensed_3;
	float current_3;
	float current_3_lpf;
	float current_sensed_4;
	float current_4;
	float current_4_lpf;

	// duty out
	float duty_1;
	float duty_1_lpf;
	float duty_2;
	float duty_2_lpf;
	float duty_3;
	float duty_3_lpf;
	float duty_4;
	float duty_4_lpf;

	//
	float cont_out_forward;
	float cont_out_translation;
	float cont_out_rotation;

	// Force and torque out
	float Fx;
	float Fy;
	float Tz;

	// remote sw
	uint8_t remote_sw[2];
	uint8_t output_to_remote[2];

	// fsr sensor
	int fsr[2];

	//amg
	uint8_t amg_linear_actuator_position_flag;	// 0:unknown, 1:initial, 2:home, 3:end
} CONT_VAR_MG;

typedef struct {
	//
	float dt;
	uint32_t ms;
	uint32_t freq;
	bool en_flag;
	bool init_flag;
	bool bal_control_ready_flag;
	uint8_t bal_control_ready_state;
	bool bal_control_flag;
	bool brake_flag;//
	bool brake_flag_xbox;//
	bool brake_flag_nunchuck;//
	bool brake_flag_rsw;//
	uint8_t error_flag;
	bool spillover_filter_flag;
	bool current_limit_flag;
	uint32_t duration;
	uint8_t control_mode;	// 0:duty mode, 1:current mode
	uint8_t imu_mode;
	uint8_t ground_imu_lpf_flag;

	//gains
	float spillover_filter_hz;
	float velocity_lowpass_filter_hz;
	float Kct_duty_mode;
	float Kct_current_mode;
	float deadzone_current;
	float current_limit;
	float LQR_X[4];
	float LQR_Y[4];
	float LQR_Z[4];
	float pitch_integral_cuttoff_hz;
	char gain_mode;

	//can
	bool status_update_flag;
	char can_status_str[500];
	uint16_t cs_ind;

	//mcconf
	char mcconf_status_str[500];
	uint16_t ms_ind;
} PARAM_MG;

typedef enum {
	//
	RT_DEFAULT = 0,
	RT_MG_PROTO1,
	RT_MG_PROTO3,
	RT_MG_CURRENT,
	RT_MG_DIFF_CONT_VAR,
	RT_MG_DIFF_DUTY_OUT,
	RT_MG_JT,
	RT_IMU_RAW,
	RT_IMU_EULER,
	RT_IMU_QUATERNION,
	RT_IMU_COMPLIMENTARY,
	RT_XBOX_DATA,
	RT_NUNCHUK_DATA
} RT_LEGEND_LOGGING;

typedef enum {
  ESP8266_AT = 0,
  ESP8266_GET_MODE,
  ESP8266_SET_MODE_1,
  ESP8266_SET_MODE_2,
  ESP8266_SET_MODE_3,
  ESP8266_GET_MUX,
  ESP8266_SET_MUX_SINGLE,
  ESP8266_SET_MUX_MULTIPLE,
  ESP8266_GET_WIFI_CONNECTION,
  ESP8266_SET_WIFI_CONNECTION,
  ESP8266_GET_IP_ADDR,
  ESP8266_CREATE_UDP_SERVER,
  ESP8266_SET_TT_MODE_ON,
  ESP8266_SET_TT_MODE_OFF,
  ESP8266_ENTER_SENDING_MODE,
  ESP8266_OUT_TO_AT_MODE,
  ESP8266_UART6_PRINT_ON,
  ESP8266_UART6_PRINT_OFF
} ESP8266_AT_COMMAND;

// Applications to use
typedef enum {
	I2C_SPEED_100KHZ = 0,
	I2C_SPEED_400KHZ
} i2c_speed;

typedef enum {
	ERROR_NONE = 0,
	ERROR_IMU_WHOAMI_FIRST_MCU,
	ERROR_IMU_WHOAMI_SECOND_MCU,
	ERROR_IMU_I2C_RATE,
	ERROR_IMU_POSTPROCESS_RATE,
	ERROR_IMU_VALID_CNT,
	ERROR_TILT_ANGLE_OVER,
	ERROR_TILT_RATE_OVER,
	ERROR_MG_PROTO3_RATE
} error_flags;
#endif

#endif /* DATATYPES_H_ */
