#include "main.h"

/*
变量初始化
*/

int16_t ch0=1024;
int16_t ch1=1024;
int16_t ch2=1024;
int16_t ch3=1024;
int16_t s1=0;
int16_t s2=0;
int16_t remote_forward_back_ref=0;
int16_t remote_left_right_ref=0;
int16_t remote_rotate_ref=0;
int16_t left_right_ref=0;
int16_t forward_back_ref=0;
int16_t rotate_ref=0;
float up_down_ref=0;
int16_t Gyro[3];
uint32_t shuzu_cout=0;
double speed_level=1;
uint16_t CM8_9position_high=0 ;
uint16_t CM10_11position_high=0;
uint32_t delay_count=0;
uint32_t climb_step_count=1;
uint32_t down_step_count=1;

int16_t mouse_left_right_slide=0;
int16_t mouse_up_down_slide=0;
uint32_t can_count=0;
int32_t INIT_count=0;
uint32_t can_count_1_4=0;
uint32_t paw_count=0;
uint32_t paw_control_count=0;
uint32_t paw_init_count=0;
double CM5_SPEED_VALUE=0;
double CM6_SPEED_VALUE=0;
double CM7_SPEED_VALUE=0;
double CM8_SPEED_VALUE=0;
double CM9_SPEED_VALUE=0;
double CM10_SPEED_VALUE=0;
double CM11_SPEED_VALUE=0;
double CM12_SPEED_VALUE=0;
double r_f_dif=0;

int8_t press_l=0;
int8_t press_r=0;
int32_t key=0;
int32_t turnaround=1;
int32_t back_car_turnaround=1;

uint16_t PAW_CHANGE_HANDLE=no;
uint16_t PAW_CHANGE_HANDLE2=no;
uint16_t paw_second_changable=yes;

double CM5PositionPID_ref=0;
double CM6PositionPID_ref=0;
double CM7PositionPID_ref=0;
double CM8PositionPID_ref=0;
double CM9PositionPID_ref=0;
double CM10PositionPID_ref=0;
double CM11PositionPID_ref=0;
double CM12PositionPID_ref=0;
double CM13PositionPID_ref=0;
double CM14PositionPID_ref=0;

double debug1=0;
double debug2=0;
double debug3=0;
double debug4=0;
uint16_t debug5=0;
uint16_t debug6=0;
uint16_t debug7=0;
uint16_t debug8=0;
uint16_t debug10=0;

float P_value=0;
float user_float1=0; 
float user_float2=0; 
float user_float3=0; 

double paw_ref=0;
double paw_up_x=1;
double paw_down_x=1;
double paw_init_x=1;

uint8_t computer_tx_buf[COMPUTER_FRAME_BUFLEN]={0};
uint8_t user_data[13]={0};

ringBuffer_t buffer;
uint16_t Tail_Over_Zero_Value =0;   //尾指针通过零点
uint16_t Head_Over_Zero_Value =0;   //头指针通过零点
uint8_t Save_Element_Array[30];
uint8_t CRC8_Ref_Value;
uint8_t CRC8_Solve_Value;
uint16_t CRC16_Ref_Value;    //收到的CRC16校验值
uint16_t CRC16_Solve_Value;  //计算得到的CRC16校验值
uint16_t data_Length;

RampGen_t GMPitchRamp  = RAMP_GEN_DAFAULT;
RampGen_t GMYawRamp =    RAMP_GEN_DAFAULT;
RampGen_t frictionRamp = RAMP_GEN_DAFAULT;   //摩擦轮斜坡
RampGen_t FBSpeedRamp  = RAMP_GEN_DAFAULT;
RampGen_t LOCA_SpeedRamp =RAMP_GEN_DAFAULT;
RampGen_t LRSpeedRamp  = RAMP_GEN_DAFAULT;
RampGen_t RoSpeedRamp  = RAMP_GEN_DAFAULT;
RampGen_t CM8_9ramp    = RAMP_GEN_DAFAULT;
RampGen_t CM10_11ramp  = RAMP_GEN_DAFAULT;
RampGen_t CM12_13ramp  = RAMP_GEN_DAFAULT;
RampGen_t CM14ramp     = RAMP_GEN_DAFAULT;
RampGen_t paw_up_ramp  = RAMP_GEN_DAFAULT;
RampGen_t paw_down_ramp = RAMP_GEN_DAFAULT;
RampGen_t paw_init_ramp = RAMP_GEN_DAFAULT;

WorkState Engineer_workstate=CONTROL_STATE;
WorkState LAST_workstate=CONTROL_STATE;
SPEED_STATE speed_state=NORMAL_STATE;
climbstate CLIMBSTATE=STEP1;
climbstate LAST_CLIMBSTATE=STEP1;
downstate DOWNSTATE=STEP6;
downstate LAST_DOWNSTATE=STEP6;
CHASIS_STATE chasis_state=FOWARD_STATE;
CHASIS_STATE last_chasis_state=FOWARD_STATE;
AUX_CHASIS_STATE aux_chasis_state=AUX_STATIC_STATE;
PAW_HORI_STATE  paw_hori_state=THIRD_STATE;
PAW_VERTI_STATE paw_verti_state=PAW_INIT_STATE;
PAW_VERTI_STATE last_paw_verti_state=PAW_INIT_STATE;
PAW_CYLINDER_STATE paw_cylinder_state=OPEN_STATE;
TRAILER_STATE trailer_state=TRAILER_UP_STATE;
LEG_STATE  leg_state=LOW_STATE;
SPEED_STEP speed_step=FAST_STEP;
AIM_LOCATION aim_location={0,0,0};

PID_Regulator CM1SpeedPID = CHASSIS_MOTOR_SPEED_PID_DEFAULT;
PID_Regulator CM2SpeedPID = CHASSIS_MOTOR_SPEED_PID_DEFAULT;
PID_Regulator CM3SpeedPID = CHASSIS_MOTOR_SPEED_PID_DEFAULT;
PID_Regulator CM4SpeedPID = CHASSIS_MOTOR_SPEED_PID_DEFAULT;
PID_Regulator CM5SpeedPID = CHASSIS_MOTOR_SPEED_PID_DEFAULT;
PID_Regulator CM6SpeedPID = CHASSIS_MOTOR_SPEED_PID_DEFAULT;
PID_Regulator CM7SpeedPID = CHASSIS_MOTOR_SPEED_PID_DEFAULT;
PID_Regulator CM8SpeedPID = CHASSIS_MOTOR_SPEED_PID_DEFAULT;
PID_Regulator CM9SpeedPID = CHASSIS_MOTOR_SPEED_PID_DEFAULT;
PID_Regulator CM10SpeedPID = CHASSIS_MOTOR_SPEED_PID_DEFAULT;
PID_Regulator CM11SpeedPID = CHASSIS_MOTOR_SPEED_PID_DEFAULT;
PID_Regulator CM12SpeedPID = CHASSIS_MOTOR_SPEED_PID_DEFAULT;
PID_Regulator CM13SpeedPID = CHASSIS_MOTOR_SPEED_PID_DEFAULT;
PID_Regulator CM14SpeedPID = PAW_MOTOR_SPEED_PID_DEFAULT;


PID_Regulator CM1PositionPID= CM_POSITION_PID_DEFAULT;
PID_Regulator CM2PositionPID= CM_POSITION_PID_DEFAULT;
PID_Regulator CM3PositionPID= CM_POSITION_PID_DEFAULT;
PID_Regulator CM4PositionPID= CM_POSITION_PID_DEFAULT;
PID_Regulator CM5PositionPID= CM_POSITION_PID_DEFAULT;
PID_Regulator CM6PositionPID= CM_POSITION_PID_DEFAULT;
PID_Regulator CM7PositionPID= CM_POSITION_PID_DEFAULT;
PID_Regulator CM8PositionPID= CM_POSITION_PID_DEFAULT;
PID_Regulator CM9PositionPID= CM_POSITION_PID_DEFAULT;
PID_Regulator CM10PositionPID= CM_POSITION_PID_DEFAULT;
PID_Regulator CM11PositionPID= CM_POSITION_PID_DEFAULT;
PID_Regulator CM12PositionPID= CM_POSITION_PID_DEFAULT;
PID_Regulator CM13PositionPID= CM_POSITION_PID_DEFAULT;
PID_Regulator CM14PositionPID = BOLUN_POSITION_PID_DEFAULT;

PID_Regulator GMPPositionPID = GIMBAL_MOTOR_PITCH_POSITION_PID_DEFAULT;     
PID_Regulator GMPSpeedPID 	 = GIMBAL_MOTOR_PITCH_SPEED_PID_DEFAULT;
PID_Regulator GMYPositionPID = GIMBAL_MOTOR_YAW_POSITION_PID_DEFAULT;			
PID_Regulator GMYSpeedPID 	 = GIMBAL_MOTOR_YAW_SPEED_PID_DEFAULT;

volatile Encoder CM1Encoder			= {0,0,0,0,0,0,0,{0,0,0,0,0,0},0,0,0,0};
volatile Encoder CM2Encoder			= {0,0,0,0,0,0,0,{0,0,0,0,0,0},0,0,0,0};
volatile Encoder CM3Encoder			= {0,0,0,0,0,0,0,{0,0,0,0,0,0},0,0,0,0};
volatile Encoder CM4Encoder		 	= {0,0,0,0,0,0,0,{0,0,0,0,0,0},0,0,0,0};
volatile Encoder CM5Encoder		 	= {0,0,0,0,0,0,0,{0,0,0,0,0,0},0,0,0,0};
volatile Encoder CM6Encoder		 	= {0,0,0,0,0,0,0,{0,0,0,0,0,0},0,0,0,0};
volatile Encoder CM7Encoder		 	= {0,0,0,0,0,0,0,{0,0,0,0,0,0},0,0,0,0};
volatile Encoder CM8Encoder		 	= {0,0,0,0,0,0,0,{0,0,0,0,0,0},0,0,0,0};
volatile Encoder CM9Encoder		 	= {0,0,0,0,0,0,0,{0,0,0,0,0,0},0,0,0,0};
volatile Encoder CM10Encoder		 	= {0,0,0,0,0,0,0,{0,0,0,0,0,0},0,0,0,0};
volatile Encoder CM11Encoder		 	= {0,0,0,0,0,0,0,{0,0,0,0,0,0},0,0,0,0};
volatile Encoder CM12Encoder		 	= {0,0,0,0,0,0,0,{0,0,0,0,0,0},0,0,0,0};
volatile Encoder CM13Encoder		 	= {0,0,0,0,0,0,0,{0,0,0,0,0,0},0,0,0,0};
volatile Encoder CM14Encoder		 	= {0,0,0,0,0,0,0,{0,0,0,0,0,0},0,0,0,0};
volatile Encoder GMPitchEncoder		= {0,0,0,0,0,0,0,{0,0,0,0,0,0},0,0,0,0};
volatile Encoder GMYawEncoder		 	= {0,0,0,0,0,0,0,{0,0,0,0,0,0},0,0,0,0};

int32_t Q_PRESS=0;
int32_t E_PRESS=0;
int32_t R_PRESS=0;
int32_t F_PRESS=0;
int32_t G_PRESS=0;
int32_t Z_PRESS=0;
int32_t X_PRESS=0;
int32_t C_PRESS=0;
int32_t V_PRESS=0;
int32_t B_PRESS=0;
int32_t PRESS_MOUSE_R=0;
int32_t PRESS_MOUSE_L=0;
int32_t CS_PRESS=0;

int32_t KEY_Q_count=0;
int32_t KEY_E_count=0;
int32_t KEY_R_count=0;
int32_t KEY_F_count=0;
int32_t KEY_G_count=0;
int32_t KEY_Z_count=0;
int32_t KEY_X_count=0;
int32_t KEY_C_count=0;
int32_t KEY_V_count=0;
int32_t KEY_B_count=0;
int32_t MOUSE_R_count=0;
int32_t MOUSE_L_count=0;
int32_t KEY_CS_count=0;

uint16_t V_STATE_FLAG=0;
uint16_t B_STATE_FLAG=0;
uint16_t C_STATE_FLAG=0;
uint16_t X_STATE_FLAG=0;
uint32_t REMOTE_LOSE_COUT=0;

double OVER_P_SPEED=1;
double speed_buchang=3.0;
uint16_t handle_state=no;
uint16_t handle_state2=no;
uint16_t handle_state3=no;
uint16_t handle_state4=no;